from typing import Optional

from fastapi import FastAPI
from pydantic import BaseModel


class Item(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None


app = FastAPI()


@app.post("/items/")
async def create_item(item: Item):
    return item

@app.post("/items/")
async def create_item(item: Item):
    item_dict = item.dict()
    if item.tax:
        price_with_tax = item.price + item.tax
        item_dict.update({"price_with_tax": price_with_tax})
    return item_dict

# http://127.0.0.1:8000/request_and_path_parameter/678
# {
#  "item_id": 678,
#  "name": "string",
#  "description": "string",
#  "price": 0,
#  "tax": 0
# }
# http://127.0.0.1:8000/request_and_path_parameter/345
# {
#  "request_and_path_parameter": 345,
#  "name": "string",
#  "description": "string",
#  "price": 0,
#  "tax": 0
# }

@app.put("/request_and_path_parameter/{request_and_path_parameter}")
async def create_request_and_path_parameter_item(request_and_path_parameter: int, item: Item):
    return {"request_and_path_parameter": request_and_path_parameter, **item.dict()}

# Request body + path + query parameters
# http://127.0.0.1:8000/request_and_path_and_query_parameter/123?query=justinTime
# {
#  "request_and_path_and_query_parameter": 123,
#  "name": "string",
#  "description": "string",
#  "price": 0,
#  "tax": 0,
#  "query": "justinTime"
# }

@app.put("/request_and_path_and_query_parameter/{request_and_path_and_query_parameter}")
async def create_request_and_path_and_query_parameter_item(request_and_path_and_query_parameter: int, item: Item, query: Optional[str] = None):
    result = {"request_and_path_and_query_parameter": request_and_path_and_query_parameter, **item.dict()}
    if query:
        result.update({"query": query})
    return result

# Query Parameters
# http://127.0.0.1:8000/items/?query=justinTime
# {"items": [{"item_id": "Foo"},{"item_id": "Bar"}],"query": "justinTime"}
#
# http://127.0.0.1:8000/query_parameter/
# {"query_parameter": [{"item_id": "Foo"},{"item_id": "Bar"}]}
#
# http://127.0.0.1:8000/query_parameter/?query=naija_news
# {"query_parameter": [{"naija_news": "Nairaland.com"},{"naija_entertainment": "Naijaloaded.com"}],"query": "naija_news"}
@app.get("/query_parameter/")
async def read_query_items(query: Optional[str] = None):
    results = {"query_parameter": [{"naija_news": "Nairaland.com"}, {"naija_entertainment": "Naijaloaded.com"}]}
    if query:
        results.update({"query": query})
    return results
