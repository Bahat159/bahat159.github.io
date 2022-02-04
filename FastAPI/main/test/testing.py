# Using TestClient
#
# Import TestClient.
#
# Create a TestClient passing to it your FastAPI application.
# Create functions with a name that starts with test_ (this is standard pytest conventions).
# Use the TestClient object the same way as you do with requests.
# Write simple assert statements with the standard Python 
# expressions that you need to check (again, standard pytest).

from fastapi import FastAPI
from fastapi.testclient import TestClient

app = FastAPI()


@app.get("/")
async def read_main():
    return {"msg": "Hello World"}


client = TestClient(app)


def test_read_main():
    response = client.get("/")
    assert response.status_code == 200
    assert response.json() == {"msg": "Hello World"}
