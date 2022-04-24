import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session['user_id'])
    quotes = None
    total = 0
    if len(stocks) > 0:
        quotes = []
        for stock in stocks:
            quote = lookup(symbol=stock['symbol'])
            quote['shares'] = stock['shares']
            quote['total'] = (quote['shares'] * quote['price'])
            quote['price'] = usd(quote['price'])
            quotes.append(quote)
        total = 0
        for quote in quotes:
            total += quote['total']
            quote['total'] = usd(quote['total'])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']
    total += cash
    total = usd(total)
    cash = usd(cash)
    return render_template("index.html", quotes=quotes, total = total, cash = cash)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = None
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Please enter postive integers for shares")
        if not symbol:
            return apology("Please enter symbol")
        quote = lookup(symbol)
        if quote is None:
            return apology("Symbol does not exist")
        if shares < 1:
            return apology("Share should be a positive integer")
        price = quote.get("price")
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']
        total_price = price * shares
        if cash < total_price:
            return apology("You don't have enough balance to buy stocks")
        current_cash = cash - total_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, session["user_id"])
        current_date = datetime.now()
        db.execute("INSERT INTO buy(price, user_id, symbol, date, share, category) VALUES(?, ?, ?, ?, ?, 'bought')", price, session['user_id'], symbol, current_date, shares)
        current_shares = db.execute("SELECT shares FROM stocks WHERE user_id = ? AND symbol = ?", session['user_id'], symbol)
        if len(current_shares) == 0:
            db.execute("INSERT INTO stocks(symbol, user_id, shares) VALUES(?, ?, ?)", symbol, session['user_id'], shares)
        else:
            db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?", current_shares + shares, session['user_id'], symbol)
        return redirect('/')

    return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM buy WHERE user_id = ?", session['user_id'])
    for row in rows:
        row['price'] = usd(row['price'])
    return render_template("history.html", rows = rows)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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

    # POST request
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please Enter valid symbol!")
        quote = lookup(symbol)
        if quote is None:
            return apology("Please Enter valid symbol!")
        quote['price'] = usd(quote['price'])
        return render_template("quoted.html", quote=quote)
    # GET request
    return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        userName = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        user = db.execute("SELECT * FROM users WHERE username = ?", userName)
        if userName == "" or len(user) != 0:
            return apology("Username already exists")
        if password == "" or confirmation == "" or password != confirmation:
            return apology("Passwords do not match")

        hashed_password = generate_password_hash(password)
        db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", userName, hashed_password)
        return redirect("/login")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        available_shares = db.execute("SELECT shares FROM stocks WHERE symbol = ? AND user_id = ?", symbol, session['user_id'])
        # print(available_shares)
        if not symbol or len(available_shares) == 0:
            return apology("Please select a valid symbol")
        available_shares = available_shares[0]['shares']
        if shares < 1 or shares > available_shares:
            return apology("You don't have enough shares to sell")
        current_shares = available_shares - shares
        if current_shares == 0:
            db.execute("DELETE FROM stocks WHERE user_id = ? AND symbol = ?", session['user_id'], symbol)
        else:
            db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?", current_shares, session['user_id'], symbol)
        price = lookup(symbol)['price']
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (shares * price) + cash, session['user_id'])
        current_date = datetime.now()
        db.execute("INSERT INTO buy(price, user_id, symbol, date, share, category) VALUES(?, ?, ?, ?, ?, 'sold')", price, session['user_id'], symbol, current_date, shares)
        return redirect("/")

    symbols = db.execute("SELECT symbol FROM stocks WHERE user_id = ?", session['user_id'])
    if len(symbols) == 0:
        return render_template("sell.html", symbols = None)

    return render_template("sell.html", symbols = symbols)
