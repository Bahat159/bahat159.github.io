from typing import Optional
from fastapi import FastAPI, Path
from pydantic import BaseModel

app = FastAPI()


class Item(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None

class User(BaseModel):
    username: str
    full_name: Optional[str] = None


# http://127.0.0.1:8000/path_query_and_body_parameter/677?query=JustInTime
# {"item_id": 677,"query": "JustInTime","item": {"name": "string","description": "string","price": 0,"tax": 0}}
#
# http://127.0.0.1:8000/path_query_and_body_parameter/677?query=JustInTime
# {"item_id": 677,"query": "JustInTime","model_body_item": {"name": "string","description": "string","price": 0,"tax": 0}}

@app.put("/path_query_and_body_parameter/{item_id}")
async def update_path_query_and_body_parameter_item(*,item_id: int = Path(..., title="The ID of the item to get", ge=0, le=1000),query: Optional[str] = None,item: Optional[Item] = None,):
    results = {"item_id": item_id}
    if query:
        results.update({"query": query})
    if item:
        results.update({"model_body_item": item})
    return results


def validate_data_type(data, type):
    return isinstance(data, type)

# Multiple body parameters

# http://127.0.0.1:8000/multiple_body_parameter/6767
# [{"user.full_name": "Busari Habibullaah"},{"user.username": "Bahat"},{"item.name": "new_path"},{"item.description":
#  "Another FastApi tutorial"},{"item.price": "$0.77"},{"item.tax": "$0.002"}]

@app.put("/multiple_body_parameter/{item_id}")
async def update_multiple_body_item(item_id: int, item: Item, user: User):
    results = {"item_id": item_id, "item": item,"user": user}
    item_id_check = validate_data_type(item_id, int)
    if item_id_check:
        return [{"user.full_name": "Busari Habibullaah"}, {"user.username": "Bahat"}, {"item.name": "new_path"}, {"item.description":"Another FastApi tutorial"} , {"item.price": "$0.77"}, {"item.tax":"$0.002"}]
    else:
        return ("Data type not of Integer")
    return results


# curl -X 'PUT' \'http://127.0.0.1:8000/multiple_body_parameter/7878' \-H 'accept: application/json' \-H 'Content-Type: application/json' \-d '{"item": {"name": "string","description": "string","price": 0,"tax": 0},"user": {"username": "string","full_name": "string"}}'
# 
# {"item_id": 6557,"item": {"name": "string","description": "string","price": 0,"tax": 0},"user": {"username": "string",  # "full_name": "string"}}

@app.put("/multiple_body_parameter_/{item_id}")
async def update_multiple_body_item_original(item_id: int, item: Item, user: User):
    results = {"item_id": item_id, "item": item,"user": user}
    return results
