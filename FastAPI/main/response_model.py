from fastapi import FastAPI, status
from pydantic import BaseModel, EmailStr
from typing import List, Optional, Union, Dict

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

@app.get("/response_model_exclude_item_name/{item_id}/name", response_model=ResponseModelExculdeItem, response_model_include=set({"name", "description"}),)
async def read_response_model_exculde_item_name(item_id: str):
    for x in items:
        return items[x]


@app.get("/response_model_exclude_item_public_data/{item_id}/public", response_model=ResponseModelExculdeItem, response_model_exclude={"tax"})
async def read_response_model_exclude_item_public_data(item_id: str):
    for x in items:
        return items[x]


# Multiple models

class MultipleModelUserIn(BaseModel):
    username: str = "bahat"
    password: str
    email: EmailStr = "busarihabib159@gmail.com"
    full_name: Optional[str] = "Busari Habibullaah"


class MultipleModelUserOut(BaseModel):
    username: str
    email: EmailStr
    full_name: Optional[str] = None


class MultipleModelUserInDB(BaseModel):
    username: str = "bahat"
    hashed_password: str
    email: EmailStr = "busarihabib159@gmail.com"
    full_name: Optional[str] = "Busari Habibullaah"


def multiple_model_fake_password_hasher(raw_password: str):
    return "supersecret" + raw_password


def multiple_model_fake_save_user(user_in: MultipleModelUserIn):
    hashed_password = multiple_model_fake_password_hasher(user_in.password)
    user_in_db = MultipleModelUserInDB(**user_in.dict(), hashed_password=hashed_password)
    print("User saved! ..not really")
    return user_in_db


@app.post("/miltiple_model_user/", response_model= MultipleModelUserOut)
async def create_multiple_model_user(user_in: MultipleModelUserIn):
    user_saved = multiple_model_fake_save_user(user_in)
    return user_saved

def get_most_out_of_model_dict(user_object):
    user_in = user_object(username="john", password="secret", email="john.doe@example.com")
    user_dict = user_in.dict()
    return user_dict

# print(get_most_out_of_model_dict(MultipleModelUserIn))


# Extra Models
# Reduce duplication

class ReduceDuplicateUserBase(BaseModel):
    username: str = "bahat"
    email: EmailStr = "busarihabib159@gmail.com"
    full_name: Optional[str] = "Busari Habibullaah"


class ReduceDuplicateUserIn(ReduceDuplicateUserBase):
    password: str


class ReduceDuplicateUserOut(ReduceDuplicateUserBase):
    pass


class ReduceDuplicateUserInDB(ReduceDuplicateUserBase):
    hashed_password: str


def reduce_duplicate_fake_password_hasher(raw_password: str):
    return "supersecret" + raw_password


def reduce_duplicate_fake_save_user(user_in: ReduceDuplicateUserIn):
    hashed_password = reduce_duplicate_fake_password_hasher(user_in.password)
    user_in_db = ReduceDuplicateUserInDB(**user_in.dict(), hashed_password=hashed_password)
    print("User saved! ..not really")
    return user_in_db


@app.post("/user_to_reduce_duplication/", response_model=ReduceDuplicateUserOut)
async def create_user_to_reduce_duplication(user_in: ReduceDuplicateUserIn):
    user_saved = reduce_duplicate_fake_save_user(user_in)
    return user_saved

# Union or anyOf
# You can declare a response to be the Union of two types, 
# that means, that the response would be any of the two.

class UnionBaseItem(BaseModel):
    description: str 
    type: str


class CarItem(UnionBaseItem):
    type = "car"


class PlaneItem(UnionBaseItem):
    type = "plane"
    size: int


items = {
    "item1": {
        "description": "All my friends drive a low rider", 
        "type": "car"
    },
    "item2": {
        "description": "Music is my aeroplane, it's my aeroplane",
        "type": "plane",
        "size": 5,
    },
}


@app.get("/union_or_anyof_response/{item_id}", response_model=Union[PlaneItem, CarItem])
async def read_response_with_union_item(item_id: str):
    for x in items:
        return items[x]

# List of Model

class ListOfModelItem(BaseModel):
    name: str
    description: str


items = [
    {"name": "Entertainment", "description": "List of entertainment websites in Nigeria"},
    {"name": "Sport betting", "description": "List of sporting bet websites in Nigeria"},
]


@app.get("/list_of_model_items/", response_model=List[ListOfModelItem])
async def read_list_of_model_items():
    return items

# Response with dict

@app.get("/keyword-weights_with_dict/", response_model=Dict[str, float])
async def read_keyword_weights_with_dict():
    return {"foo": 2.3, "bar": 3.4}



# Response Status Code
# The same way you can specify a response model, 
# you can also declare the HTTP status code used for the response with the 
# parameter status_code in any of the path operations:
# @app.get()
# @app.post()
# @app.put()
# @app.delete()

@app.post("/response_status_code_items/", status_code=200)
async def create_response_status_code_item(name: str):
    return {"name": name}


@app.post("/fastapi_status_items/", status_code=status.HTTP_201_CREATED)
async def create_with_fastapi_status_item(name: str):
    return {"name": name}
