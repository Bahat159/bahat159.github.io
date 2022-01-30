from pydantic import BaseModel, EmailStr
from fastapi.responses import JSONResponse
from typing import List, Optional, Union, Dict, Set
from fastapi.exceptions import RequestValidationError
from fastapi.responses import PlainTextResponse
from starlette.exceptions import HTTPException as StarletteHTTPException
from fastapi import FastAPI, status, Form, UploadFile, File, HTTPException, Request

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
        return items

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


# Form Data
#
# curl -X 'POST' \
#  'http://127.0.0.1:8000/form_login/' \
#  -H 'accept: application/json' \
#  -H 'Content-Type: application/x-www-form-urlencoded' \
#  -d 'username=bahat&password=passcoder'

@app.post("/form_login/")
async def login_form(username: str = Form(...), password: str = Form(...)):
    return {"username": username, "password": password}


# Request Files

@app.post("/get_files_parameter_size/")
async def create_file(file: bytes = File(...)):
    return {"file_size": len(file)}

# Current issue with FastApi
#
# @app.post("/uploadfile/")
# async def create_upload_file(file: UploadFile):
#    return {"filename": file.filename, "file_content_type": file.content_type}

from fastapi.responses import HTMLResponse

@app.post("/multiple_files_size/")
async def create_multiple_files_size(files: List[bytes] = File(..., description="Multiple files as bytes")):
    return {"file_sizes": [len(file) for file in files]}

@app.get("/main_html_type/")
async def main_html_type():
    content = """
    <body>
        <form action="/files/" enctype="multipart/form-data" method="post">
            <input name="files" type="file" multiple>
            <input type="submit">
        </form>
        <form action="/uploadfiles/" enctype="multipart/form-data" method="post">
            <input name="files" type="file" multiple>
            <input type="submit">
        </form>
    </body>
    """
    return HTMLResponse(content=content)

# Request Forms and Files

@app.post("/recieve_file_with_uploadfile_and_files/")
async def create_recieve_file_with_uploadfile_and_file(file: bytes = File(...), fileb: UploadFile = File(...), token: str = Form(...)):
    return {
        "file_size": len(file),
        "token": token,
        "fileb_content_type": fileb.content_type,
    }

# Handling Error

items = {"foo": "The Foo Wrestlers", "bar":"The Bar Wrestlers"}


@app.get("/use_http_exception_error_handling_items/{exception_id}")
async def read_http_exception_error_handling_item(exception_id: str):
    if exception_id not in items:
        raise HTTPException(status_code=404, detail="Item not found")
    return {"item": items[exception_id]}

# Exception with custom header

@app.get("/assert_items_with_custom_header/{exception_id}")
async def read_item_with_custom_header(exception_id: str):
    if exception_id not in items:
        raise HTTPException(status_code=404,detail="Item not found",headers={"X-Error": "There goes my error"},)
    return {"item": items[exception_id]}


class UnicornException(Exception):
    def __init__(self, name: str):
        self.name = name

@app.exception_handler(UnicornException)
async def unicorn_exception_handler(request: Request, exc: UnicornException):
    return JSONResponse(
        status_code=418,
        content={"message": f"Oops! {exc.name} did something. There goes a rainbow..."},
    )


@app.get("/unicorns_exception_handler/{name}")
async def read_unicorn_exception_handler(name: str):
    if name == "yolo":
        raise UnicornException(name=name)
    return {"unicorn_exception_name": name}

# Override the default exception handlers
#
# Override request validation exceptions
#

@app.exception_handler(StarletteHTTPException)
async def http_starlette_exception_handler(request, exc):
    return PlainTextResponse(str(exc.detail), status_code=exc.status_code)


@app.exception_handler(RequestValidationError)
async def validation_exception_handler(request, exc):
    return PlainTextResponse(str(exc), status_code=400)


@app.get("/excpetion_items/{exception_id}")
async def read_exception_item(exception_id: int):
    if exception_id == 3:
        raise HTTPException(status_code=418, detail="Nope! I don't like 3.")
    return {"exception_id": exception_id}


# Use the RequestValidationError body

@app.exception_handler(RequestValidationError)
async def validation_exception_handler(request: Request, exc: RequestValidationError):
    try:
        from fastapi.encoders import jsonable_encoder
        from fastapi.responses import JSONResponse
        return JSONResponse(
            status_code=status.HTTP_422_UNPROCESSABLE_ENTITY,
            content=jsonable_encoder({"detail": exc.errors(), "body": exc.body}),
        )
    except Exception:
        sys.exit()

class ExcpetItem(BaseModel):
    title: str = "towel"
    size: int ="XL"


@app.post("/validation_exception_handler_items/")
async def create_validation_exception_handler_item(item: ExcpetItem):
    return item

# Re-use FastAPI's exception handlers
# You could also just want to use the exception somehow, 
# but then use the same default exception handlers from FastAPI.

from fastapi.exception_handlers import (http_exception_handler,request_validation_exception_handler,)
@app.exception_handler(StarletteHTTPException)
async def custom_http_exception_handler(request, exc):
    print(f"OMG! An HTTP error!: {repr(exc)}")
    return await http_exception_handler(request, exc)


@app.exception_handler(RequestValidationError)
async def validation_exception_handler(request, exc):
    print(f"OMG! The client sent invalid data!: {exc}")
    return await request_validation_exception_handler(request, exc)


@app.get("/validation_excpetion_handler_items/{excpetion_handler_id}")
async def read_validation_excpetion_handler_item(excpetion_handler_id: int):
    if excpetion_handler_id == 3:
        raise HTTPException(status_code=418, detail="Nope! I don't like 3.")
    return {"excpetion_handler_item_id": excpetion_handler_id}


# Path Operation Configuration
# There are several parameters that you can pass 
# to your path operation decorator to configure it.


class PathOperationConfigurationItem(BaseModel):
    name: str = "Path configuration Item"
    description: Optional[str] = "PathOperationConfigurationItem"
    price: float
    tax: Optional[float] = None
    tags: Set[str] = set({"path","configuration","item"})


@app.post("/path_cofiguration_items/", response_model=PathOperationConfigurationItem, status_code=status.HTTP_201_CREATED)
async def create_item(item: PathOperationConfigurationItem):
    return item

# Tags

class TagsItem(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None
    tags: Set[str] = set()


@app.post("/create_tags_items/", response_model=TagsItem, tags=["items"])
async def create_item(item: TagsItem):
    return item


@app.get("/read_tags_items/", tags=["items"])
async def read_items():
    return [{"name": "Foo", "price": 42}]


@app.get("/read_users_tags/", tags=["users"])
async def read_users():
    return [{"username": "johndoe"}]

# Tags with Enums
# If you have a big application, you might end up accumulating several tags, 
# and you would want to make sure you always use the same tag for related path operations.

from enum import Enum

class TagsWithEnum(Enum):
    items = "items"
    users = "users"


@app.get("/get_enum_items/", tags=[TagsWithEnum.items])
async def get_Enumitems():
    return {"items":"Portal gun", "uses":"Plumbus"}


@app.get("/read_enum_users/", tags=[TagsWithEnum.users])
async def read_Enum_users():
    return {"items":"Rick", "users":"Morty"}


# Summary and description
# You can add a summary and description (metadata)

class SummaryDescriptionItem(BaseModel):
    name: str = "Busari Habibullaah"
    description: Optional[str] = "Summary and description"
    price: float
    tax: Optional[float] = None
    tags: Set[str] = set()


@app.post("/summary_and_description_items/",
    response_model=SummaryDescriptionItem,
    summary="Create summary and description item",
    description="Create an item with all the information, name, description, price, tax and a set of unique tags",
)
async def create_sumary_and_description_item(item: SummaryDescriptionItem):
    return item


# Description from docstring
# As descriptions tend to be long and cover multiple lines, 
# you can declare the path operation description in 
# the function docstring and FastAPI will read it from there.

class DescriptionAndDocStringItem(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None
    tags: Set[str] = set()


@app.post("/description_and_docstring_items/", response_model=DescriptionAndDocStringItem, summary="Create Descrption and Docstring item")
async def create_description_and_docstring_item(item: DescriptionAndDocStringItem):
    """
    Create an item with all the information:

    - **name**: each item must have a name
    - **description**: a long description
    - **price**: required
    - **tax**: if the item doesn't have tax, you can omit this
    - **tags**: a set of unique tag strings for this item
    """
    return item

# Response description
# You can specify the response description 
# with the parameter response_description

class ResponseDescriptionItem(BaseModel):
    name: str = "Response and description"
    description: Optional[str] = "Response and description Item creation"
    price: float
    tax: Optional[float] = None
    tags: Set[str] = set()


@app.post(
    "/response_and_description_items/",
    response_model=ResponseDescriptionItem,
    summary="Create Response and Description item",
    response_description="The created item",
    tags=["Response and Description"],
)
async def create_item(item: ResponseDescriptionItem):
    """
    Create an item with all the information:

    - **name**: each item must have a name
    - **description**: a long description
    - **price**: required
    - **tax**: if the item doesn't have tax, you can omit this
    - **tags**: a set of unique tag strings for this item
    """
    return item
