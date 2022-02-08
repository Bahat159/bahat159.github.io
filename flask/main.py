from flask import Flask
from flask import url_for
from markupsafe import escape

app = Flask(__name__)


# Routing

@app.route('/')
def index():
    return 'Index Page'

@app.route('/login')
def login():
    return 'login'

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

def url_binding():
    with app.test_request_context():
        print(url_for('index'))
        print(url_for('login'))
        print(url_for('login', next='/'))
        print(url_for('profile', username='John Doe'))


# HTTP Methods
#
# Web applications use different HTTP methods when accessing URLs. 
# You should familiarize yourself with the HTTP methods as 
# you work with Flask. By default, a route only answers to GET requests. 
# You can use the methods argument of the route() decorator to handle different HTTP methods.

from flask import request

@app.route('/login_http_request', methods=['GET', 'POST'])
def login_http_request():
    if request.method == 'POST':
        return do_the_login()
    else:
        return show_the_login_form()

# Static Files
#
# Dynamic web applications also need static files. 
# That’s usually where the CSS and JavaScript files are coming from. 
# Ideally your web server is configured to serve them for you, but during development 
# Flask can do that as well. Just create a folder called static in your package or next 
# to your module and it will be available at /static on the application.
#
# To generate URLs for static files, use the special 'static' endpoint name:

# url_for('static', filename='style.css')


# Rendering Templates
# 
# Generating HTML from within Python is not fun, and 
# actually pretty cumbersome because you have to do the HTML 
# escaping on your own to keep the application secure. 
# Because of that Flask configures the Jinja2 template engine for you automatically.
#
# To render a template you can use the render_template() method. 
# All you have to do is provide the name of the template and the 
# variables you want to pass to the template engine as keyword arguments. 
# Here’s a simple example of how to render a template:

from flask import render_template

@app.route('/hello/')
@app.route('/hello/<name>')
def hello_template(name=None):
    return render_template('hello.html', name=name)
