import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, password_validating

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    data = db.execute("SELECT symbol, shares FROM shares_counter WHERE user_id=?", session['user_id'])
    dataset = list()
    total = 0
    for i in range(0, len(data)):
        temp = dict()
        symbol = data[i]['symbol']
        shares = int(data[i]['shares'])
        results = lookup(symbol)
        name = results['name']
        price = float(results['price'])

        temp['symbol'] = symbol
        temp['shares'] = shares
        temp['name'] = name
        temp['price'] = price
        temp['total'] = shares * price

        dataset.append(temp)
        total = total + temp['total']
    user_cash = round(float((db.execute("SELECT cash FROM users WHERE id=?", session['user_id']))[0]['cash']), 2)
    total = total + user_cash
    total = round(total, 2)
    return render_template("index.html", dataset=dataset, cash=user_cash, total=total)


@app.route("/change-password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "GET":
        return render_template("change-password.html")
    else:
        confirmation_old_password = request.form.get("old-password")
        current_password = (db.execute("SELECT hash FROM users WHERE id=?", session['user_id']))[0]['hash']
        if check_password_hash(current_password, confirmation_old_password):
            new_password = request.form.get("new-password")
            if password_validating(new_password) == 0:
                return apology('Too short password', 400)
            if password_validating(new_password) == 1:
                return apology('Too simple password', 400)
            db.execute("UPDATE users SET hash=? WHERE id=?", generate_password_hash(new_password), session['user_id'])
        else:
            return apology("Wrong old password")
    return redirect("/logout")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        shares = request.form.get("shares")
        if not shares.isnumeric():
            return apology("Expected numeric value", 400)

        shares = int(float(shares))
        if shares < 1:
            return apology("Expected positive number", 400)

        symbol = request.form.get("symbol")
        symbol = symbol.upper()
        results = lookup(symbol)

        if results == None:
            return apology("Invalid symbol")
        else:
            price = float(results['price'])
            total = round(price * shares, 2)
            db_cash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])
            available_cash = db_cash[0]['cash']
            if total > available_cash:
                return apology("You cannot afford those shares", 400)
            else:
                available_cash = available_cash - total
                db.execute("UPDATE users SET cash=? WHERE id=?", available_cash, session['user_id'])
                db.execute("INSERT INTO transactions (user_id, symbol, shares, price, total) VALUES (?,?,?,?,?)",
                           session['user_id'], symbol, shares, price, total)
                user_symbols = db.execute("SELECT symbol FROM shares_counter WHERE user_id = ?", session['user_id'])
                for i in range(0, len(user_symbols)):
                    if symbol == user_symbols[i]['symbol']:
                        symbol_shares = int(
                            (db.execute("SELECT shares FROM shares_counter WHERE user_id=? AND symbol=?", session['user_id'], symbol))[0]['shares'])
                        new_shares = symbol_shares + shares
                        db.execute("UPDATE shares_counter SET shares=? WHERE user_id=? AND symbol=?",
                                   new_shares, session['user_id'], symbol)
                        return redirect("/")
                db.execute("INSERT INTO shares_counter (user_id, symbol, shares) VALUES (?,?,?)",
                           session['user_id'], symbol, shares)
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    data = db.execute("SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id = ?", session['user_id'])
    return render_template("history.html", dataset=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        results = lookup(symbol)
        if results == None:
            return apology("Invalid symbol")
    return render_template("quoted.html", name=results['name'], price=results['price'], symbol=results['symbol'])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    username = request.form['username']
    password = request.form['password']
    confirmation = request.form['confirmation']

    if len(username) == 0:
        return apology("Enter username", 400)

    if len(password) == 0:
        return apology("Enter password", 400)

    if len(confirmation) == 0:
        return apology("Enter confirmation", 400)

    if password_validating(password) == 0:
        return apology("Too short password", 400)

    if password_validating(password) == 1:
        return apology("Too simple password", 400)

    if password != confirmation:
        return apology("Wrong confirmation", 400)

    db_usernames = db.execute("SELECT username FROM users")
    usernames = list()
    for i in range(0, len(db_usernames)):
        usernames.append(db_usernames[i]['username'])

    if username in usernames:
        return apology("These username is occupied, please choose another one", 400)
    db.execute("INSERT INTO users (username, hash) VALUES (?,?)", username, generate_password_hash(password))
    return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_symbols = db.execute("SELECT symbol FROM shares_counter WHERE user_id = ?", session['user_id'])
        symbols = list()
        for i in range(0, len(user_symbols)):
            symbols.append(user_symbols[i]['symbol'])
        return render_template("sell.html", symbols=symbols)
    else:
        shares = int(request.form.get("shares"))
        symbol = (request.form.get("symbol")).upper()

        # Check if the user has the selected shares
        user_symbols = db.execute("SELECT symbol FROM shares_counter WHERE user_id = ?", session['user_id'])
        symbols = list()
        for i in range(0, len(user_symbols)):
            symbols.append(user_symbols[i]['symbol'])
        if symbol not in symbols:
            return apology("You don't have those shares")

        available_shares = int(db.execute("SELECT shares FROM shares_counter WHERE user_id = ? AND symbol=?",
                                          session['user_id'], symbol)[0]['shares'])
        if shares < 1:
            return apology("Wrong value")

        if shares > available_shares:
            return apology("You don't have that number of shares")

        results = lookup(symbol)
        if results == None:
            return apology("Invalid symbol")

        price = float(results['price'])
        total = price * shares

        available_cash = (db.execute("SELECT cash FROM users WHERE id = ?", session['user_id']))[0]['cash']

        available_cash = available_cash + total
        db.execute("UPDATE users SET cash=? WHERE id=?", available_cash, session['user_id'])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, total) VALUES (?,?,?,?,?)",
                   session['user_id'], symbol, -shares, price, total)
        user_symbols = db.execute("SELECT symbol FROM shares_counter WHERE user_id = ?", session['user_id'])
        for i in range(0, len(user_symbols)):
            if symbol == user_symbols[i]['symbol']:
                symbol_shares = int((db.execute("SELECT shares FROM shares_counter WHERE user_id=? AND symbol=?",
                                                session['user_id'], symbol))[0]['shares'])
                new_shares = symbol_shares - shares
                if new_shares == 0:
                    db.execute("DELETE FROM shares_counter WHERE user_id=? AND symbol=?", session['user_id'], symbol)
                else:
                    db.execute("UPDATE shares_counter SET shares=? WHERE user_id=? AND symbol=?",
                               new_shares, session['user_id'], symbol)
                return redirect("/")
        db.execute("INSERT INTO shares_counter (user_id, symbol, shares) VALUES (?,?,?)", session['user_id'], symbol, shares)
    return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


"""
CREATE TABLE transactions
(
timestamp datetime default CURRENT_TIMESTAMP,
user_id int,
symbol varchar(10),
shares int,
price float,
total float,
PRIMARY KEY(timestamp)
);

CREATE TABLE shares_counter
(
user_id int,
symbol varchar(10),
shares int
);

SELECT username FROM
users JOIN purchases ON
users.id = purchases.user_id;

"""
