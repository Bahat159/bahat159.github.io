import yaml
from typing import Optional, Set, List
from fastapi import FastAPI, status, Request, HTTPException
from pydantic import BaseModel, ValidationError
from fastapi.routing import APIRoute


# Path Operation Advanced Configuration

app = FastAPI()


# OpenAPI operationId
@app.get("/set_operation_id_items/", tags=["OpenApi Path Operation"], operation_id="some_specific_id_you_define")
async def read_operation_ids_items():
    return [{"item_id": "Foo"}]

# Using the path operation function name as the operationId
@app.get("/path_operation_as_operation_id_items/", tags=["OpenApi Path Operation"])
async def read_operation_path_items():
    return [{"item_id": "Foo"}]

# Exclude from OpenAPI
@app.get("/exclude_path_operation_from_openapi_items/", include_in_schema=False) # turn true if you need to view
async def read_exclude_path_operation_items():
    return [{"item_id": "Foo"}]

def use_route_names_as_operation_ids(app: FastAPI) -> None:
    """
    Simplify operation IDs so that generated API clients have simpler function
    names.

    Should be called only after all routes have been added.
    """
    for route in app.routes:
        if isinstance(route, APIRoute):
            route.operation_id = route.name  # in this case, 'read_items'


use_route_names_as_operation_ids(app)

# Advanced description from docstring

class Item(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None
    tags: Set[str] = []


@app.post("/advanced_doc_string_description_items/", response_model=Item, summary="Create an item", tags=["Advanced docstring description"], status_code=200)
async def create_advanced_docstring_description_item(item: Item):
    """
    Create an item with all the information:

    - **name**: each item must have a name
    - **description**: a long description
    - **price**: required
    - **tax**: if the item doesn't have tax, you can omit this
    - **tags**: a set of unique tag strings for this item
    \f
    :param item: User input.
    """
    return item

# OpenAPI Extensions

@app.get("/open_api_extension_items/", openapi_extra={"x-aperture-labs-portal": "blue"}, tags=["OpenApi Extension"])
async def read_with_openapi_extension_items():
    return [{"item_id": "portal-gun"}]


# Custom OpenAPI path operation schema

def magic_data_reader(raw_body: bytes):
    return {
        "size": len(raw_body),
        "content": {
            "name": "Maaaagic",
            "price": 42,
            "description": "Just kiddin', no magic here. ✨",
        },
    }


@app.post(
    "/custom_path_operation_items/",
    openapi_extra={
        "requestBody": {
            "content": {
                "application/json": {
                    "schema": {
                        "required": ["name", "price"],
                        "type": "object",
                        "properties": {
                            "name": {"type": "string"},
                            "price": {"type": "number"},
                            "description": {"type": "string"},
                        },
                    }
                }
            },
            "required": True,
        },
    },
    tags=["Custom Path Operation"]
)
async def create_custom_openapi_path_operation_item(request: Request):
    raw_body = await request.body()
    data = magic_data_reader(raw_body)
    return data

# Custom OpenAPI content type

class CustomAPIItem(BaseModel):
    name: str
    tags: List[str]


@app.post(
    "/custom_operation_content_type_items/",
    openapi_extra={
        "requestBody": {
            "content": {"application/x-yaml": {"schema": CustomAPIItem.schema()}},
            "required": True,
        },
    },
    tags=["Custom Operation Content Type"]
)
async def create_custom_operation_content_type_item(request: Request):
    raw_body = await request.body()
    try:
        data = yaml.safe_load(raw_body)
    except yaml.YAMLError:
        raise HTTPException(status_code=422, detail="Invalid YAML")
    try:
        item = CustomAPIItem.parse_obj(data)
    except ValidationError as e:
        raise HTTPException(status_code=422, detail=e.errors())
    return item
