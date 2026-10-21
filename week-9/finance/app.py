import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
@login_required
def index():
    user_id = session["user_id"]

    rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    money = rows[0]["cash"]

    shares = db.execute(
        "SELECT symbol, SUM(shares) AS share_quantity "
        "FROM transactions "
        "WHERE user_id = ? "
        "GROUP BY symbol "
        "HAVING share_quantity > 0",
        user_id
    )

    grand_total = money

    for share in shares:
        quote = lookup(share["symbol"])
        total_price = float(quote["price"]) * float(share["share_quantity"])
        share["price"] = quote["price"]
        share["total_price"] = total_price
        grand_total += total_price

    return render_template(
        "index.html",
        cash=money,
        shares=shares,
        grand_total=grand_total
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    money = rows[0]["cash"]
    if request.method == "POST":
        user_id = session["user_id"]
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must provide a symbol", 403)
        shares_str = request.form.get("shares")
        if not shares_str:
            return apology("must provide shares", 400)
        try:
            shares = int(shares_str)
            if shares < 1:
                return apology("invalid shares", 400)
        except ValueError:
            return apology("invalid shares", 400)
        result = lookup(symbol)
        if result is None:
            return apology("Symbol does not exist", 400)
        if money < shares * result["price"]:
            return apology("Not enough cash", 400)

        db.execute("INSERT INTO transactions (symbol, shares, price, user_id, operation_type) VALUES (?, ?, ?, ?, ?)", result["symbol"], shares, result["price"], user_id, "Purchase")
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", shares * result["price"], session["user_id"])
        return redirect("/")
    else:
        prefilled_symbol = request.args.get("symbol")
        return render_template("buy.html", cash=money, quote=None, prefilled_symbol=prefilled_symbol)


@app.route("/history", methods=["GET"])
@login_required
def history():
    user_id = session["user_id"]
    history = db.execute("SELECT operation_type, symbol, shares, price, transacted FROM transactions WHERE user_id = ? ORDER BY transacted DESC", user_id)
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must provide a symbol", 400)
        result = lookup(symbol)
        if result is None:
            return apology("Symbol does not exist", 400)
        return render_template("quoted.html", result=result)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        try:
            username = request.form.get("username")
            if not request.form.get("username"):
                return apology("must provide username", 400)
            password = request.form.get("password")
            if not request.form.get("password"):
                return apology("must provide password", 400)
            confirmation = request.form.get("confirmation")
            if not request.form.get("confirmation"):
                return apology("must provide password confirmation", 400)
            if password != confirmation:
                return apology("passwords must match", 400)
            else:
                hash = generate_password_hash(password, method='scrypt',salt_length=16)
                db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
                return redirect("/login")
        except ValueError:
            return apology("username repeated. Select another one", 400)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    money = rows[0]["cash"]
    owned_stocks = db.execute("SELECT symbol, SUM(shares) AS share_quantity FROM transactions WHERE user_id = ? GROUP BY symbol HAVING share_quantity > 0", user_id)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        shares_str = request.form.get("shares")
        if not shares_str:
            return apology("must provide shares", 400)
        try:
            shares = int(shares_str)
            if shares < 1:
                return apology("invalid shares", 400)
        except ValueError:
            return apology("invalid shares", 400)
        stock_rows = db.execute(
            "SELECT SUM(shares) AS share_quantity FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)
        if len(stock_rows) != 1 or stock_rows[0]["share_quantity"] <= 0:
            return apology("you do not own this stock", 400)
        owned_shares = stock_rows[0]["share_quantity"]
        if shares > owned_shares:
            return apology("too many shares", 400)
        quote = lookup(symbol)
        if quote is None:
            return apology("invalid symbol", 400)
        db.execute("INSERT INTO transactions (symbol, shares, price, user_id, operation_type) VALUES (?, ?, ?, ?, ?)", quote["symbol"], -shares, quote["price"], user_id, "Sell")
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", shares * quote["price"], user_id)
        return redirect("/")
    else:
        prefilled_symbol = request.args.get("symbol")
        return render_template("sell.html", cash=money, shares=owned_stocks, prefilled_symbol=prefilled_symbol)
