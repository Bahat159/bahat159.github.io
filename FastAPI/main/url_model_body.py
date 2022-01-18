from typing import Optional
from fastapi import FastAPI, Path
from pydantic import BaseModel

app = FastAPI()


class Item(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None


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
