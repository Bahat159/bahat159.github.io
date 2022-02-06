from typing import Optional
from datetime import datetime
from pydantic import BaseModel
from fastapi import Body, FastAPI, status, Response
from fastapi.responses import JSONResponse
from fastapi.encoders import jsonable_encoder

app = FastAPI()


# Additional Status Codes

items = {"foo": {"name": "Fighters", "size": 6}, "bar": {"name": "Tenders", "size": 3}}


@app.put("/upsert_items/{item_id}", tags=["Additional Status code"])
async def upsert_item(
    item_id: str, name: Optional[str] = Body(None), size: Optional[int] = Body(None)
):
    if item_id in items:
        item = items[item_id]
        item["name"] = name
        item["size"] = size
        return item
    else:
        item = {"name": name, "size": size}
        items[item_id] = item
        return JSONResponse(status_code=status.HTTP_201_CREATED, content=item)


# Return a Response Directly
#
# When you create a FastAPI path operation you can normally 
# return any data from it: a dict, a list, a Pydantic model, a database model, etc.
#
# By default, FastAPI would automatically convert that return value 
# to JSON using the jsonable_encoder explained in JSON Compatible Encoder.

class Item(BaseModel):
    title: str
    timestamp: datetime
    description: Optional[str] = None



@app.put("/return_response_directly_items/{id}", tags=["Return Response directly"])
def update_return_response_directly_item(id: str, item: Item):
    json_compatible_item_data = jsonable_encoder(item)
    return JSONResponse(content=json_compatible_item_data)


# Returning a custom Response

@app.get("/legacy/", tags=["Return Custom Response"])
def get_legacy_data():
    data = """<?xml version="1.0"?>
    <shampoo>
    <Header>
        Apply shampoo here.
    </Header>
    <Body>
        You'll have to use soap here.
    </Body>
    </shampoo>
    """
    return Response(content=data, media_type="application/xml")
