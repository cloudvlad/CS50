import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form['name']
        month = request.form['month']
        day = request.form['day']

        # TODO: Add the user's entry into the database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?,?,?)", name, month, day)
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT id, name, month, day FROM birthdays")
        jsonify(birthdays)
        return render_template("index.html", birthdays=birthdays)



@app.route("/delete", methods=["GET", "POST"])
def delete():
    if request.method == "POST":
        db_ids = db.execute("SELECT id FROM birthdays")
        s_id = request.form['id'] #selected id

        for db_id in db_ids:
            if int(s_id) == int(db_id["id"]):
                db.execute("DELETE FROM birthdays WHERE id = ?", s_id)

    return redirect("/")



@app.route("/update", methods=["GET", "POST"])
def update():
    if request.method == "POST":
        db_ids = db.execute("SELECT id FROM birthdays")

        s_id = request.form['id'] #selected id
        u_name = request.form['name']
        u_month = request.form['month']
        u_day = request.form['day']

        print(s_id)
        for db_id in db_ids:
            if int(s_id) == int(db_id["id"]):
                db.execute("UPDATE birthdays SET name=?, month=?, day=? WHERE id = ?", u_name, u_month, u_day, s_id)

    return redirect("/")