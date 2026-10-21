# CS50x 2026 — Problem Sets

My solutions to the problem sets of **[CS50x 2026](https://cs50.harvard.edu/x/2026/)**, Harvard University's Introduction to Computer Science.

**Final project:** [EmotionScope](https://github.com/pabloooduran/CS50x-2026-Final-Project), a Flask web app that detects faces in an image and classifies their facial expressions with a custom-trained model.

> All code in this repository was written by me, following [CS50's academic honesty policy](https://cs50.harvard.edu/x/2026/honesty/).

## Live demos

The web projects can be tried directly in the browser, with nothing to install:

| Project | Stack | Demo |
|---|---|---|
| [finance](#finance) | Flask · SQLite · Jinja | [pabloooduran-cs50-finance.onrender.com](https://pabloooduran-cs50-finance.onrender.com) |
| [birthdays](#birthdays) | Flask · SQLite | [pabloooduran-cs50-birthdays.onrender.com](https://pabloooduran-cs50-birthdays.onrender.com) |
| [homepage](#homepage) | HTML · CSS · Bootstrap · JavaScript | [pabloooduran.github.io/CS50x-2026/week-8/homepage](https://pabloooduran.github.io/CS50x-2026/week-8/homepage/) |
| [trivia](#trivia) | HTML · CSS · JavaScript | [pabloooduran.github.io/CS50x-2026/week-8/trivia](https://pabloooduran.github.io/CS50x-2026/week-8/trivia/) |

The Flask apps run on a free plan and go to sleep when nobody uses them, so the first load can take up to a minute.

## What's covered

| | |
|---|---|
| **Languages** | C, Python, SQL (SQLite), HTML, CSS, JavaScript, Scratch |
| **Frameworks & tools** | Flask, Jinja, Bootstrap, Make, Git |
| **Concepts** | Pointers and manual memory management · file I/O on binary formats (WAV, BMP, JPEG) · hash tables, linked lists and trees · recursion · sorting algorithms and their complexity · graph cycle detection · relational databases and nested queries · DOM events · server-side web apps with sessions and authentication |

## Contents

| Week | Topic | Projects |
|---|---|---|
| [0](#week-0--scratch) | Scratch | Scape from the ghost |
| [1](#week-1--c) | C | hello, mario-more, credit |
| [2](#week-2--arrays-and-strings) | Arrays and strings | scrabble, readability, substitution |
| [3](#week-3--algorithms) | Algorithms | sort, plurality, tideman |
| [4](#week-4--memory) | Memory | volume, filter-more, recover |
| [5](#week-5--data-structures) | Data structures | inheritance, speller |
| [6](#week-6--python) | Python | sentimental-\*, dna |
| [7](#week-7--sql) | SQL | songs, movies, fiftyville |
| [8](#week-8--html-css-and-javascript) | HTML, CSS, JavaScript | trivia, homepage |
| [9](#week-9--flask) | Flask | birthdays, finance |

---

## Week 0 — Scratch

### [Scape from the ghost](week-0)
A maze-style game with an introduction screen, three levels, a victory screen and a game-over screen. The player moves with the arrow keys, has to pick up a key to unlock each level's exit and avoid two patrolling ghosts. Touching a ghost costs a life and sends the player back to the start, and some holes teleport the player across the map. The logic is split into custom blocks (player movement, enemy movement, respawn) and coordinated through shared variables such as `Lives` and `PlayerHasKey`.

## Week 1 — C

### [hello](week-1/me)
Asks for the user's name and greets them. Includes the classic [hello, world](week-1/world).

### [mario-more](week-1/mario-more)
Prints two side-by-side pyramids of `#` with a gap in the middle, like the ones in Super Mario Bros. It keeps asking until the height is between 1 and 8, and builds each row with nested loops.

### [credit](week-1/credit)
Checks whether a credit card number is valid using **Luhn's algorithm** and identifies the issuer (AMEX, MASTERCARD or VISA) from the number's length and leading digits. Everything is done with integer arithmetic and digit manipulation.

## Week 2 — Arrays and strings

### [scrabble](week-2/scrabble)
Two players enter a word and the program decides who wins based on Scrabble letter values. It maps each letter to its score through an array indexed by the letter's ASCII value.

### [readability](week-2/readability)
Estimates the US school grade needed to understand a text using the **Coleman-Liau index**. It counts letters, words and sentences, then outputs from "Before Grade 1" to "Grade 16+".

### [substitution](week-2/substitution)
Encrypts text with a **substitution cipher** given a 26-letter key passed as a command-line argument. The key is validated (length, only letters, no repeats) and the original upper/lowercase is preserved.

## Week 3 — Algorithms

### [sort](week-3/sort)
Identifies which sorting algorithm (bubble, selection or merge sort) each of three compiled programs uses. This is done by timing them on sorted, reversed and random inputs of 5,000 to 50,000 numbers and comparing the results with each algorithm's best- and worst-case behaviour. The reasoning is in [`answers.txt`](week-3/sort/answers.txt).

### [plurality](week-3/plurality)
Runs a simple first-past-the-post election: it collects votes, counts them per candidate and prints the winner, or every tied winner.

### [tideman](week-3/tideman)
Implements the **Tideman (ranked pairs)** voting method:
1. Builds a preference matrix from every voter's ranking.
2. Creates the pairs of candidates where one beats the other.
3. Sorts the pairs by strength of victory.
4. Locks them into a directed graph, skipping any pair that would create a cycle (detected with a recursive search).

The winner is the source of the graph, the candidate with no edges pointing at them.

## Week 4 — Memory

### [volume](week-4/volume)
Changes the volume of a WAV file by a given factor. It copies the 44-byte header unchanged and then scales each 16-bit audio sample.

### [filter-more](week-4/filter-more)
Applies image filters to 24-bit BMP files, working directly on the 2D array of RGB pixels:
- **Grayscale:** averages each pixel's channels.
- **Reflect:** mirrors the image horizontally.
- **Blur:** 3×3 box blur that handles edges and corners.
- **Edges:** **Sobel operator** with Gx/Gy kernels, combined as √(Gx² + Gy²).

### [recover](week-4/recover)
Recovers deleted JPEG photos from a raw memory-card image. It reads the card in 512-byte blocks, detects the JPEG signature at the start of each image and writes every photo to its own file (`000.jpg`, `001.jpg`, …).

## Week 5 — Data structures

### [inheritance](week-5/inheritance)
Simulates how blood type is inherited across generations. It builds a family **tree of dynamically allocated structs** in which each child receives one random allele from each parent, prints the tree and frees all the memory recursively.

### [speller](week-5/speller)
A spell checker that loads a dictionary of over 140,000 words into a **hash table** (5,000 buckets, polynomial hash, collisions handled with linked lists) and reports every misspelled word in a text. Lookups are case-insensitive, and all memory is released at the end. The program reports the time spent loading, checking and unloading, so the hash function can be tuned for speed.

## Week 6 — Python

### [sentimental-\*](week-6)
Python rewrites of earlier C problems ([hello](week-6/sentimental-hello), [mario-more](week-6/sentimental-mario-more), [credit](week-6/sentimental-credit), [readability](week-6/sentimental-readability)). They show how much shorter the same logic becomes in a higher-level language.

### [dna](week-6/dna)
Identifies who a DNA sample belongs to. For each **short tandem repeat (STR)** in a CSV database, it finds the longest run of consecutive repeats in the sequence and looks for the person whose STR counts match exactly.

## Week 7 — SQL

### [songs](week-7/songs)
Queries over a database of the top 100 Spotify songs of 2018: filtering, ordering, averages and subqueries that link songs to their artists. [`answers.txt`](week-7/songs/answers.txt) describes the listener's "audio aura" and discusses the limits of that analysis.

### [movies](week-7/movies)
Thirteen queries over an IMDb database of movies, people, stars, directors and ratings. They go from simple filters to nested subqueries, for example finding every movie two given actors starred in together, or everyone who has appeared in a film with Kevin Bacon.

### [fiftyville](week-7/fiftyville)
A mystery solved only with SQL. Starting from a crime-scene report, I cross-referenced interviews, security logs, ATM transactions, phone calls and flight records to identify the thief, the city they escaped to and their accomplice. Every query and the reasoning behind it is in [`log.sql`](week-7/fiftyville/log.sql).

## Week 8 — HTML, CSS and JavaScript

### [trivia](week-8/trivia)
A two-question trivia page: a multiple-choice question and a free-response one. Answers are checked in JavaScript: the chosen answer turns green or red and a feedback message appears.

**▶ [Live demo](https://pabloooduran.github.io/CS50x-2026/week-8/trivia/)**

### [homepage](week-8/homepage)
A four-page personal website (Home, About, Sports, Contact) built with HTML, custom CSS and **Bootstrap**. JavaScript adds interactivity: a welcome button, random facts, a mood selector, sport cards and client-side validation of the contact form.

**▶ [Live demo](https://pabloooduran.github.io/CS50x-2026/week-8/homepage/)**

## Week 9 — Flask

### [birthdays](week-9/birthdays)
A small Flask app backed by SQLite for keeping track of friends' birthdays. You can add new entries through a form and delete existing ones.

**▶ [Live demo](https://pabloooduran-cs50-birthdays.onrender.com)**

### [finance](week-9/finance)
A full-stack web app for "trading" stocks with virtual money, built with **Flask, Jinja and SQLite**, using real-time quotes from an external API.
- **Accounts:** register and log in with session-based authentication and passwords hashed with scrypt. Each new user starts with $10,000.
- **Quote:** look up the current price of any stock symbol.
- **Buy / Sell:** server-side validation of symbols, share amounts, available cash and owned shares.
- **Portfolio:** current holdings, their live value, cash balance and grand total.
- **History:** a log of every purchase and sale.

All database queries are parameterised to prevent SQL injection.

**▶ [Live demo](https://pabloooduran-cs50-finance.onrender.com)** — register any username to try it.

> The Flask demos are hosted on Render's free plan. They go to sleep after 15 minutes without visits, so the first load can take up to a minute. The databases also reset periodically.

---

## Running the code

The projects were written in the CS50 codespace, which comes with CS50's libraries preinstalled. To run them elsewhere:

- **C:** install the [CS50 Library for C](https://github.com/cs50/libcs50), then compile with `make <name>` (or `make` inside `filter-more` and `speller`).
- **Python:** `pip install cs50`, then `python <file>.py`.
- **Flask:** inside `week-9/finance` or `week-9/birthdays`, run `pip install -r requirements.txt`, then `flask run`.

Some large or binary files that CS50 provides with each problem aren't included here: the speller dictionaries, the DNA databases, `movies.db`, the precompiled `sort` programs and the sample images and audio. They come with each problem's distribution code on the [CS50x website](https://cs50.harvard.edu/x/2026/). `week-9/finance/finance.db` contains the schema only, so register a new user to try the app.
