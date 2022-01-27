from typing import List, Optional

from fastapi import FastAPI
from pydantic import BaseModel,EmailStr

app = FastAPI()


class ResponseModelItem(BaseModel):
    name: str = "Response Model"
    description: Optional[str] = "Test application for FastApi Response Model"
    price: float = 2.30
    tax: Optional[float] = 0.0
    tags: List[str] = ["response model"]


@app.post("/create_response_model_item/", response_model=ResponseModelItem)
async def create_response_model_item(item: ResponseModelItem):
    return item

# Return the same input data

class UserIn(BaseModel):
    username: str = "Bahat"
    password: str = "Ju99sterpo00se%\intT0oF5astA0pi" # we could be sending our user's passwords to every client.
    email: EmailStr = "busarihabib159@gmail.com"
    full_name: Optional[str] = "Busari Habibullaah"

# Don't do this in production!
@app.post("/user_input_model/", response_model=UserIn)
async def create_user_input_model(user: UserIn):
    return user

class UserOut(BaseModel):
    username: str
    email: EmailStr
    full_name: Optional[str] = None

@app.post("/user_output_model/", response_model=UserOut)
async def create_user_output_model(user: UserIn):
    return user


# Response Model encoding parameters

class ResponseModelEncodingParameterItem(BaseModel):
    name: str = "Busari Habibullaah"
    description: Optional[str] = "The complete code"
    price: float
    tax: float = 10.5
    tags: List[str] = []
    
items = {
    "foo": {"name": "Foo", "price": 50.2},
    "bar": {"name": "Bar", "description": "The bartenders", "price": 62, "tax": 20.2},
    "baz": {"name": "Baz", "description": None, "price": 50.2, "tax": 10.5, "tags": []},
}


@app.get("/response_model_encoding_parameter_items/{item_id}", response_model=ResponseModelEncodingParameterItem, response_model_exclude_unset=True)
async def read_response_model_encoding_parameter_item(item_id: str):
    for x in items:
        return items[x]


class ResponseModelExculdeItem(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: float = 10.5


items = {
    "foo": {"name": "Foo", "price": 50.2},
    "bar": {"name": "Bar", "description": "The Bar fighters", "price": 62, "tax": 20.2},
    "baz": {
        "name": "Baz",
        "description": "There goes my baz",
        "price": 50.2,
        "tax": 10.5,
    },
}

@app.get("/response_model_exclude_item_name/{item_id}/name", response_model=ResponseModelExculdeItem, response_model_include={"name", "description"},)
async def read_response_model_exculde_item_name(item_id: str):
    for x in items:
        return items[x]


@app.get("/response_model_exclude_item_public_data/{item_id}/public", response_model=ResponseModelExculdeItem, response_model_exclude={"tax"})
async def read_response_model_exclude_item_public_data(item_id: str):
    for x in items:
        return items[x]
