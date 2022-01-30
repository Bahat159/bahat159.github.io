from datetime import datetime
from typing import Optional

from fastapi import FastAPI
from fastapi.encoders import jsonable_encoder
from pydantic import BaseModel


# JSON Compatible Encoder
# There are some cases where you might need to convert 
# a data type (like a Pydantic model) to something compatible 
# with JSON (like a dict, list, etc).
#
# For example, if you need to store it in a database.


fake_db = {}


class JsonEnablerItem(BaseModel):
    title: str
    timestamp: datetime
    description: Optional[str] = None


app = FastAPI()


@app.put("/json_enabler_items/{id}")
def update_with_json_enabler_item(id: str, item: JsonEnablerItem):
    json_compatible_item_data = jsonable_encoder(item)
    fake_db[id] = json_compatible_item_data
    return fake_db[id]
