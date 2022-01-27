from typing import List, Optional, Set
from fastapi import FastAPI, Path, Body
from pydantic import BaseModel, Field, HttpUrl

app = FastAPI()


class Item(BaseModel):
    name: str = "Base model"
    description: Optional[str] = "Described by Busari Habibullaah"
    price: float
    tax: Optional[float] = None

class User(BaseModel):
    username: str = "First Base Model Username"
    full_name: Optional[str] = "FastApi user model class"



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
    name: str = "Nigeria bet application company"
    description: Optional[str] = "Nigerian bet application platform website list"
    price: float
    tax: Optional[float] = None
    tags: List[str] = ["sportybet.com", "nairabet.com", "betnaija.com"]

@app.put("/update_list_with_parameter_item/{item_id}")
async def update_list_with_parameter_item(item_id: int, item: ListFiedWithParameterItem):
    results = {"item_id": item_id, "item": item}
    return results

class ListWithSetItem(BaseModel):
    name: str = "Nigerian Entertainment List"
    description: Optional[str] = "Nigerian Entertainment List of website"
    price: float = 2.4
    tax: Optional[float] = None
    tags: Set[str] = set({"Nairaland.com", "naijaloaded.com", "Tooexclusive.com"})

@app.put("/update_list_with_set_item/{item_id}")
async def update_list_with_set_item(item_id: int, item: ListWithSetItem):
    results = {"item_id": item_id, "item": item}
    return results

# Nested Models

class Image(BaseModel):
    url: str = "https://bahat159.github.io"
    name: str = "Busari Habibullaah"


class NestedModelItem(BaseModel):
    name: str = "Busari Habibullaah"
    description: Optional[str] = "First ever understanding of model body item"
    price: float = 90.00
    tax: Optional[float] =  2.40
    tags: Set[str] = ["tag array", "second_tag_array"]
    image: Optional[Image] = None

@app.put("/update_nested_model_item/{item_id}")
async def update_nested_model_item(item_id: int, item: NestedModelItem):
    results = {"item_id": item_id, "item_model_name": item.name, "item_description": item.description, "item_price":item.price, "item_price": item.price, "item_tax": item.tax, "item_tags": item.tags, "item_image_url":item.image}
    return results

# Use the submodel as a type
#
# And then we can use it as the type of an attribute:

class Submodel_Image(BaseModel):
    url: str = "http://example.com/baz.jpg"
    name: str = "The Foo live"


class SubModel_as_type_Item(BaseModel):
    name: str = "Foo"
    description: Optional[str] = "The pretender"
    price: float = 42.0
    tax: Optional[float] = 3.2
    tags: Set[str] = ["rock", "metal", "bar"]
    image: Optional[Submodel_Image] = None


@app.put("/update_submodel_as_type_item/{item_id}")
async def update_submodel_as_type_item(item_id: int, item: SubModel_as_type_Item):
    results = {"item_id": item_id, "item": item}
    return results

# Special types and validation
#
# Apart from normal singular types like str, int, float, etc. 
# You can use more complex singular types that inherit from str.
# To see all the options you have, checkout the docs for Pydantic's exotic types
# https://pydantic-docs.helpmanual.io/usage/types/

class UrlImage(BaseModel):
    url: HttpUrl
    name: str 


class SpecialValidationItem(BaseModel):
    name: str = "Special types and validation"
    description: Optional[str] = "Apart from normal singular types like str, int, float, etc.You can use more complex singular types that inherit from str."
    price: float
    tax: Optional[float] = None
    tags: Set[str] = set({"rock","metal","bar"})
    images: Optional[List[UrlImage]] = UrlImage

@app.put("/update_special_types_and_validation_item/{item_id}")
async def update_special_types_and_validation_item(item_id: int, item: SpecialValidationItem):
    results = {"item_id": item_id, "item": item}
    return results

# Declare Request Example Data
#
# You can declare examples of the data your app can receive.
# Here are several ways to do it.

class SchemaItem(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None

class Config:
    schema_extra = {
        "example": {
            "name": "Foo",
            "description": "A very nice Item",
            "price": 35.4,
            "tax": 3.2,
            }
        }

@app.put("/update_schema_extra_item/{item_id}")
async def update_schema_extra_item(item_id: int, item: SchemaItem):
    results = {"item_id": item_id, "item": item}
    return results

# Field additional arguments
#
# When using Field() with Pydantic models, 
# you can also declare extra info (metadata) for the JSON Schema 
# by passing any other arbitrary arguments to the function.

class Schema_with_additional_field_Item(BaseModel):
    name: str = Field(..., example="Busari Habibullaah")
    description: Optional[str] = Field(None, example="Working with FastAPIs")
    price: float = Field(..., example=35.4)
    tax: Optional[float] = Field(None, example=3.2)

@app.put("/update_schema_with_additional_field_item/{item_id}")
async def update_schema_with_additional_field_item(item_id: int, item: Schema_with_additional_field_Item):
    results = {"item_id": item_id, "item": item}
    return results


class BodyWithExampleItem(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None


@app.put("/update_body_with_example_item/{item_id}")
async def update_body_with_example_item(item_id: int, item: BodyWithExampleItem = Body(...,
example={
    "name": "Foo",
    "description": "A very nice Item",
    "price": 35.4,
    "tax": 3.2,},),):
    results = {"item_id": item_id, "item": item}
    return results

# Body with multiple examples

class BodyWithMultipleItem(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None


@app.put("/update_body_with_multiple_item/{item_id}")
async def update_body_with_multiple_item(
    *,
    item_id: int,
    item: BodyWithMultipleItem = Body(
        ...,
        examples={
            "normal": {
                "summary": "A normal example",
                "description": "A **normal** item works correctly.",
                "value": {
                    "name": "Foo",
                    "description": "A very nice Item",
                    "price": 35.4,
                    "tax": 3.2,
                },
            },
            "converted": {
                "summary": "An example with converted data",
                "description": "FastAPI can convert price `strings` to actual `numbers` automatically",
                "value": {
                    "name": "Bar",
                    "price": "35.4",
                },
            },
            "invalid": {
                "summary": "Invalid data is rejected with an error",
                "value": {
                    "name": "Baz",
                    "price": "thirty five point four",
                },
            },
        },
    ),
):
    results = {"item_id": item_id, "item": item}
    return results
