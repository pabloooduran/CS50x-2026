# CS50x-2026

My problem sets for **[CS50x 2026](https://cs50.harvard.edu/x/2026/)**, Harvard University's Introduction to Computer Science, completed between February and March 2026.

The course goes from Scratch to C, then data structures and algorithms, and finally Python, SQL, HTML/CSS/JavaScript and Flask. My final project lives in a separate repository.

## Contents

| Week | Topic | Problems |
|---|---|---|
| [0](week-0) | Scratch | [Scape from the ghost](week-0) — a Scratch game |
| [1](week-1) | C | [hello (world)](week-1/world), [hello (me)](week-1/me), [mario-more](week-1/mario-more), [credit](week-1/credit) |
| [2](week-2) | Arrays | [scrabble](week-2/scrabble), [readability](week-2/readability), [substitution](week-2/substitution) |
| [3](week-3) | Algorithms | [sort](week-3/sort), [plurality](week-3/plurality), [tideman](week-3/tideman) |
| [4](week-4) | Memory | [volume](week-4/volume), [filter-more](week-4/filter-more), [recover](week-4/recover) |
| [5](week-5) | Data structures | [inheritance](week-5/inheritance), [speller](week-5/speller) |
| [6](week-6) | Python | [sentimental-hello](week-6/sentimental-hello), [sentimental-mario-more](week-6/sentimental-mario-more), [sentimental-credit](week-6/sentimental-credit), [sentimental-readability](week-6/sentimental-readability), [dna](week-6/dna) |
| [7](week-7) | SQL | [songs](week-7/songs), [movies](week-7/movies), [fiftyville](week-7/fiftyville) |
| [8](week-8) | HTML, CSS, JavaScript | [trivia](week-8/trivia), [homepage](week-8/homepage) |
| [9](week-9) | Flask | [birthdays](week-9/birthdays), [finance](week-9/finance) |

## Highlights

- **tideman** (C) — ranked-choice election that builds a graph of candidate preferences, sorts pairs by strength of victory and locks them in while avoiding cycles.
- **filter-more** (C) — image filters on 24-bit BMP files: grayscale, horizontal reflection, box blur and Sobel edge detection.
- **recover** (C) — recovers JPEGs from a raw memory-card image by scanning 512-byte blocks for JPEG signatures.
- **speller** (C) — spell checker that loads a dictionary into a hash table and checks texts against it, tuned for speed.
- **dna** (Python) — identifies a person from a DNA sequence by counting the longest runs of short tandem repeats (STRs) and matching them against a CSV database.
- **fiftyville** (SQL) — a mystery solved purely with SQL queries over a town's database; the reasoning is in `log.sql`.
- **finance** (Flask) — web app for "buying" and "selling" stocks with real-time quotes: registration and login with hashed passwords, portfolio, quotes, buy, sell and transaction history, backed by SQLite.

## Running the code

The projects were written in the CS50 codespace, which comes with the `cs50` libraries for C and Python preinstalled. Outside that environment:

- **C:** install the [CS50 Library for C](https://github.com/cs50/libcs50) and compile with `make <name>` or `clang <file>.c -lcs50`.
- **Python:** `pip install cs50`, then `python <file>.py`.
- **Flask apps:** `pip install -r requirements.txt` (finance) or `pip install cs50 flask flask-session`, then `flask run` from the project folder.

`week-9/finance/finance.db` is shipped with the schema only, so you need to register a new user to try the app.
