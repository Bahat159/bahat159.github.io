from flask import Flask
from flask import url_for
from markupsafe import escape

app = Flask(__name__)


# Routing

@app.route('/')
def index():
    return 'Index Page'

@app.route("/hello_world")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route('/binlex_flask')
def binlex_flask():
    return 'Welcome to Flask API creation, Busari Habibullaah. Courtsey of BinLex!!!'


# Variable Rules

@app.route('/user/<username>')
def show_user_profile(username):
    # show the user profile for that user
    return f'User {escape(username)}'

@app.route('/post/<int:post_id>')
def show_post(post_id):
    # show the post with the given id, the id is an integer
    return f'Post {post_id}'

@app.route('/path/<path:subpath>')
def show_subpath(subpath):
    # show the subpath after /path/
    return f'Subpath {escape(subpath)}'

# Unique URLs / Redirection Behavior

@app.route('/projects/')
def unique_url_projects():
    return 'The project page'

@app.route('/about')
def unique_url_about():
    return 'The about page'

# URL Building
#
# To build a URL to a specific function, use the url_for() function. 
# It accepts the name of the function as its first argument 
# and any number of keyword arguments, each corresponding 
# to a variable part of the URL rule. Unknown variable 
# parts are appended to the URL as query parameters.

