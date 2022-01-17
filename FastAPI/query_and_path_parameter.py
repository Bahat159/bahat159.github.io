from enum import Enum
from typing import Optional
from fastapi import FastAPI
from pydantic import BaseModel


app = FastAPI()


class ModelName(str, Enum):
    alexnet = "alexnet"
    resnet = "resnet"
    lenet = "lenet"

class Item(BaseModel):
    name: str
    price: float
    is_offer: Optional[bool] = None


# Path Parameters
# http://127.0.0.1:8000/
# {"message":"Hello FastAPI"}

@app.get("/")
def read_fastAPI_root():
    return {"message": "Hello FastAPI"}

# http://127.0.0.1:8000/users/me
# {"user_id": "The current User"}
# curl -X 'GET' \'http://127.0.0.1:8000/users/me' \-H 'accept: application/json'

@app.get('/users/me')
async def read_user_me():
    return {"user_id": "The current User"}

# http://127.0.0.1:8000/users/159
# {"user_id": "159"}

@app.get("/users/{user_id}")
async def read_user(user_id: str):
    return {"user_id": user_id}

# http://127.0.0.1:8000/items/139
# {"item_name": "string","item_id": 139}
# curl -X 'PUT' \'http://127.0.0.1:8000/items/139' \-H 'accept: application/json' \-H 'Content-Type: application/json' \-d '{"name": "string"  
# "price": 0,"is_offer": true}'

@app.put("/items/{item_id}")
def update_item(item_id: int, item: Item):
    return {"item_name": item.name, "item_id": item_id}

# http://127.0.0.1:8000/items/150?query_type=myown%20query
# {"item_id": 150,"url_query_parameter": "myown query"}

@app.get("/items/{item_id}")
def read_item(item_id: int, query_type: Optional[str] = None):
    return {"item_id": item_id, "url_query_parameter": query_type}

# http://127.0.0.1:8000/myquery/129?query_parameter=post_to_server_from_us
# {"query_id": 129,"query_details": "post_to_server_from_us"}

@app.post("/myquery/{query_id}")
def post_parameter_to_myquery(query_id: int, query_parameter: Optional[str] = None):
    return {"query_id": query_id, "query_details": query_parameter}

# http://127.0.0.1:8000/models/alexnet
# {"model_name": "alexnet","message": "Deep Learning FTW!"}

@app.get("/models/{model_name}")
async def get_model(model_name: ModelName):
    if model_name == ModelName.alexnet:
        return {"model_name": model_name, "message": "Deep Learning FTW!"}
    if model_name.value == "lenet":
        return {"model_name": model_name, "message": "LeCNN all the images"}

    return {"model_name": model_name, "message": "Have some residuals"}


# File path Url parameter
# http://127.0.0.1:8000/files/%2Ffastapi%2Fmain.py
# {"file_path": "/fastapi/main.py"}

@app.get("/files/{file_path:path}")
async def read_file_path(file_path: str):
    return {"file_path": file_path}



# Query Parameters
#
# http://127.0.0.1:8000/query_items/?skip=0&limit=1
# returns [{"item_name":"Foo"}]
#
# http://127.0.0.1:8000/query_items/?skip=0&limit=2
# returns [{"item_name":"Foo"},{"item_name":"Bar"}]
#
# http://127.0.0.1:8000/query_items/?skip=0&limit=3
# returns [{"item_name":"Foo"},{"item_name":"Bar"},{"item_name":"Baz"}]
#
# curl -X 'GET' \'http://127.0.0.1:8000/query_items/?start=0&finish=3' \
# -H 'accept: application/json'
# 
# http://127.0.0.1:8000/query_items/?start=0&finish=3
# [{"item_name": "First Page"},{"item_name": "Second Page"},{"item_name": "Index Page"}]

fake_items_db = [{"item_name": "First Page"}, {"item_name": "Second Page"}, {"item_name": "Index Page"}]

@app.get("/query_items/")
async def read_query_item(start: int = 0, finish: int = 10):
    return fake_items_db[start : start + finish]

@app.get("/query_items/{item_id}")
async def read_optional_query_item(item_id: str, query_id: Optional[str] = None):
    if query_id:
        return {"item_id": item_id, "query_id": query_id}
    return {"item_id": item_id}


# http://127.0.0.1:8000/query_items_with_type_conversion/456?query_id=justimTime&short=true
# {"item_id": "456","query_id": "justimTime"}
#
# http://127.0.0.1:8000/query_items_with_type_conversion/1?query_id=justimTime
# {"item_id": "1","query_id": "justimTime","description": "This is an amazing item that has a long description"}

@app.get("/query_items_with_type_conversion/{item_id}")
async def read_optional_query_item_with_type_conversion(item_id: str, query_id: Optional[str] = None, short: bool = False):
    item = {"item_id": item_id}
    if query_id:
        item.update({"query_id": query_id})
    if not short:
        item.update(
            {"description": "This is an amazing item that has a long description"}
        )
    return item

# Multiple path and query parameters
# http://127.0.0.1:8000/users/178/items/456?query_id=urlshortner
# {"item_id": "456","owner_id": 178,"query_id": "urlshortner","description": "This is an amazing item that has a long description"}
# 
# http://127.0.0.1:8000/users/178/items/456?query_id=urlshortner&short=true
# {"item_id": "456","owner_id": 178,"query_id": "urlshortner"}
#
# http://127.0.0.1:8000/users/178/items/456?query_id=urlshortner&short=false
# {"item_id": "456","owner_id": 178,"query_id": "urlshortner","description": "This is an amazing item that has a long description"}

@app.get("/users/{user_id}/items/{item_id}")
async def read_multiple_path_and_query_parameter(user_id: int, item_id: str, query_id: Optional[str] = None, short: bool = False):
    item = {"item_id": item_id, "owner_id": user_id}
    if query_id:
        item.update({"query_id": query_id})
    if not short:
        item.update(
            {"description": "This is an amazing item that has a long description"}
        )
    return item
