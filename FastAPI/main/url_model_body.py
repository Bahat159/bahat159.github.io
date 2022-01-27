from typing import List, Optional, Set
from fastapi import FastAPI, Path, Body
from pydantic import BaseModel, Field

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


# http://127.0.0.1:8000/update_item_with_body/565
# {"item_id": 565,"item": {"name": "string","description": "string","price": 0,"tax": 0},"user": {"username": "string",#   "full_name": "string"},"importance": 0}

@app.put("/update_item_with_body/{item_id}")
async def update_body_with_item(item_id: int, item: Item, user: User, importance: int = Body(...)):
    results = {"item_id": item_id, "item": item, "user": user, "importance": importance}
    return results


# Body Field

class BodyItemField(BaseModel):
    name: str
    description: Optional[str] = Field(None, title="The description of the item", max_length=300)
    price: float = Field(..., gt=0, description="The price must be greater than zero")
    tax: Optional[float] = None

@app.put("/update_body_field_items/{item_id}")
async def update_body_field_item(item_id: int, item: BodyItemField = Body(..., embed=True)):
    results = {"item_id": item_id, "item": item.name}
    return results

# Body - Nested Models
# List fields

class ListItem(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None
    tags: list = []


@app.put("/update_with_list_item/{item_id}")
async def update_with_list_item(item_id: int, item: ListItem):
    results = {"item_id": item_id, "item_tag": item.tags, "item_name": item.name, "item_tax": item.tax}
    return results

# List fields with type parameter

class ListFiedWithParameterItem(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None
    tags: List[str] = []

@app.put("/update_list_with_parameter_item/{item_id}")
async def update_list_with_parameter_item(item_id: int, item: ListFiedWithParameterItem):
    results = {"item_id": item_id, "item": item}
    return results

class ListWithSetItem(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None
    tags: Set[str] = set()

@app.put("/update_list_with_set_item/{item_id}")
async def update_list_with_set_item(item_id: int, item: ListWithSetItem):
    results = {"item_id": item_id, "item": item}
    return results

# Nested Models

class Image(BaseModel):
    url: str
    name: str


class NestedModelItem(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None
    tags: Set[str] = []
    image: Optional[Image] = None

@app.put("/update_nested_model_item/{item_id}")
async def update_nested_model_item(item_id: int, item: NestedModelItem):
    results = {"item_id": item_id, "item": item}
    return results
