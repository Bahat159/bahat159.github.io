# CORS (Cross-Origin Resource Sharing)
#
# CORS or "Cross-Origin Resource Sharing" refers to 
# the situations when a frontend running in a browser has
# JavaScript code that communicates with a backend, 
# and the backend is in a different "origin" than the frontend.
#
# Origin
#
# An origin is the combination of protocol (http, https), 
# domain (myapp.com, localhost, localhost.tiangolo.com), and port (80, 443, 8080).
#
# So, all these are different origins:
#
# http://localhost
# https://localhost
# http://localhost:8080
#
# Use CORSMiddleware
#
# You can configure it in your FastAPI application using the CORSMiddleware.
#
# Import CORSMiddleware.
# Create a list of allowed origins (as strings).
# Add it as a "middleware" to your FastAPI application.
#
# You can also specify if your backend allows:
#
# Credentials (Authorization headers, Cookies, etc).
# Specific HTTP methods (POST, PUT) or all of them with the wildcard "*".
# Specific HTTP headers or all of them with the wildcard "*".

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

app = FastAPI()

origins = [
    "http://localhost.tiangolo.com",
    "https://localhost.tiangolo.com",
    "http://localhost",
    "http://localhost:8080",
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.get("/")
async def main():
    return {"message": "Hello World from FastApi Cors with same-origin"}
