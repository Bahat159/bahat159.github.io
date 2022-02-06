# Path Operation Advanced Configuration

from fastapi import FastAPI
from fastapi.routing import APIRoute

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
