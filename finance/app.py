import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
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
    user_id=session["user_id"]
    records=db.execute('SELECT SUM(shares) AS shares, symbol FROM buy WHERE user_id = ?  GROUP BY symbol', user_id)
    print(records)

    cash=db.execute("SELECT cash FROM users WHERE id=?",user_id)
    total=0

    #这里需要注意哦，因为我们需要所有share加起来的总和的钱，但是jinja或者html里面不能像python这里+= 不能记数字，所以在python这边做完算数，再传过去
    for record in records:
        currentprice=lookup(record["symbol"])
        total+=currentprice['price'] * record["shares"]


    return render_template("index.html",records=records,total=total,cash=cash[0]['cash'],lookup=lookup)






@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method=="POST":
        symbol=request.form.get("symbol")
        share=request.form.get("share")
        if not symbol:
            return apology("Please enter a symbol name.")
        elif not share:
            return apology("Please enter a share number.")
        elif not lookup(symbol):
            return apology("Not valid symbol.")
        elif int(share)<=0:
            return apology("Enter a positive number.")

        item=lookup(symbol)
        name=item["name"]
        user_id=session["user_id"]
        item_price=item["price"]
        total_price=int(item_price * float(share))

        current=db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        current_money=current[0]['cash']
        if current_money -total_price<0:
            return apology("Not enough money.")


        try:
            db.execute("UPDATE users SET cash= ? WHERE id =?",current_money -total_price, user_id)
            db.execute("INSERT INTO buy(user_id, shares, price, type, symbol) VALUES (?,?,?,?,?)",user_id,share,total_price,"buy",symbol)
        except:
            return apology("Did not insert into database.")

        return redirect("/")


    else:
        return render_template("buy.html")







@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    records=db.execute("SELECT * FROM buy WHERE user_id=?",session["user_id"])

    return render_template("history.html",records=records,lookup=lookup)









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
    if request.method=="POST":
        symbol=request.form.get("symbol")
        if not symbol:
            return apology("Please enter a symbol.")

        sym=lookup(symbol)
        if not sym:
            return apology("Not valid symbol.")

        return render_template("quoted.html",item=sym,usd=usd)


    else:
        return render_template("quote.html")






@app.route("/register",methods=["GET","POST"])
def register():
    if request.method == "POST":

        username=request.form.get("username")
        password=request.form.get("password")
        confirmation=request.form.get("confirmation")

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 403)

        elif request.form.get("password")!=request.form.get("confirmation"):
            return apology("Provide the same password", 403)

        try:
            new_user=db.execute("INSERT INTO users(username, hash) VALUES (?,?)",username,generate_password_hash(password))
        except:
            return apology("Username exists",403)

        session["user_id"]=new_user

        return redirect('/')
    else:
        return render_template("register.html")








@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol=request.form.get("symbol")
        share=request.form.get("share")
        user_id=session["user_id"]

        if not symbol:
            return apology("Please enter a symbol name.")
        elif not share:
            return apology("Please enter a share number.")
        elif not lookup(symbol):
            return apology("Not valid symbol.")
        elif int(share)<=0:
            return apology("Enter a positive number.")

        records=db.execute("SELECT SUM(shares) as shares FROM buy WHERE symbol=? AND user_id=? ",symbol,user_id,)

        if records[0]['shares']-int(share)<0:
            return apology("Not enough share.")

        item=lookup(symbol)
        name=item["name"]
        item_price=item["price"]
        total_price=int(item_price * float(share))

        current=db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        current_money=current[0]['cash']


        try:
            db.execute("UPDATE users SET cash= ? WHERE id =?",current_money +total_price, user_id)
            # 这里需要注意 再卖出股票的时候 存档在buy里面 shares存的是负数表示卖出
            db.execute("INSERT INTO buy(user_id, shares, price, type, symbol) VALUES (?,?,?,?,?)",user_id,0-int(share),total_price,"sell",symbol)
        except:
            return apology("Did not insert into database.")

        return redirect("/")


    else:
        return render_template("sell.html")


