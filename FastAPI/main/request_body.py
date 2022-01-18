from pydantic import BaseModel
from typing import List, Optional
from fastapi import FastAPI, Query

class Item(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None


app = FastAPI()


@app.post("/items/")
async def create_item(item: Item):
    return item

@app.post("/create_parameter_with_module/")
async def create_parameter_with_module(item: Item):
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
async def read_query_parameter_items(query: Optional[str] = None):
    results = {"query_parameter": [{"naija_news": "Nairaland.com"}, {"naija_entertainment": "Naijaloaded.com"}]}
    if query:
        results.update({"query": query})
    return results

# Query Parameters with string limit
# http://127.0.0.1:8000/query_parameter_with_limit/?query=parameterwithlimit
# {"query_parameter": [{"naija_news": "Nairaland.com"},{"naija_entertainment": "Naijaloaded.com"}],"query": "parameterwithlimit"}

@app.get("/query_parameter_with_limit/")
async def read_query_parameter_with_limit_items(query: Optional[str] = Query(None, max_length=50)):
    results = {"query_parameter": [{"naija_news": "Nairaland.com"}, {"naija_entertainment": "Naijaloaded.com"}]}
    if query:
        results.update({"query": query})
    return results

# Query Parameters set as optional with string limit
# http://127.0.0.1:8000/query_parameter_as_optional_with_limit/?query=optional_query
# {"query_parameter": [{"naija_news": "Nairaland.com"},{"naija_entertainment": "Naijaloaded.com"}],"query": "optional_query"}
#
# http://127.0.0.1:8000/query_parameter_as_optional_with_limit/?query=indo_query
# {"query_parameter": [{"naija_news": "Nairaland.com"},{"naija_entertainment": "Naijaloaded.com"}],"query": "indo_query"}

@app.get("/query_parameter_as_optional_with_limit/")
async def get_query_parameter_as_optional_with_limit(query: Optional[str] = Query(None, max_length=50)):
    results = {"query_parameter": [{"naija_news": "Nairaland.com"}, {"naija_entertainment": "Naijaloaded.com"}]}
    if query:
        results.update({"query": query})
    return results

# Query Parameters set as optional with string limit and minlength
# http://127.0.0.1:8000/query_parameter_as_optional_with_limit_validation/?query=que
# {"query_parameter": [{"naija_news": "Nairaland.com"},{"naija_entertainment": "Naijaloaded.com"}],"query": "que"}
# 
# http://127.0.0.1:8000/query_parameter_as_optional_with_limit_validation/?query=quertz
# {"query_parameter": [{"naija_news": "Nairaland.com"},{"naija_entertainment": "Naijaloaded.com"}],"query": "quertz"}

@app.get("/query_parameter_as_optional_with_limit_validation/")
async def get_query_parameter_as_optional_with_limit_validation(query: Optional[str] = Query(None, min_length=3, max_length=50)):
    results = {"query_parameter": [{"naija_news": "Nairaland.com"}, {"naija_entertainment": "Naijaloaded.com"}]}
    if query:
        results.update({"query": query})
    return results

# Query Parameters set as optional with string limit and minlength with Regex
# http://127.0.0.1:8000/query_parameter_as_optional_with_limit_validation_with_regex/?query=fixedquery
# {"query_parameter": [{"naija_news": "Nairaland.com"},{"naija_entertainment": "Naijaloaded.com"}],"query": "fixedquery"}

@app.get("/query_parameter_as_optional_with_limit_validation_with_regex/")
async def query_parameter_as_optional_with_regex(query: Optional[str] = Query(None, min_length=3, max_length=50, regex="^fixedquery$")):
    results = {"query_parameter": [{"naija_news": "Nairaland.com"}, {"naija_entertainment": "Naijaloaded.com"}]}
    if query:
        results.update({"query": query})
    return results

# http://127.0.0.1:8000/query_parameter_with_default_value/?query=fixed_query
# {"query_parameter": [{"naija_news": "Nairaland.com"},{"naija_entertainment": "Naijaloaded.com"}],"query": "fixed_query"}
# http://127.0.0.1:8000/query_parameter_with_default_value/?query=fixedme
# {"query_parameter": [{"naija_news": "Nairaland.com"},{"naija_entertainment": "Naijaloaded.com"}],"query": "fixedme"}

@app.get("/query_parameter_with_default_value/")
async def query_parameter_with_default_value(query: str = Query("fixedquery", min_length=3)):
    results = {"query_parameter": [{"naija_news": "Nairaland.com"}, {"naija_entertainment": "Naijaloaded.com"}]}
    if query:
        results.update({"query": query})
    return results

# http://127.0.0.1:8000/query_parameter_with_default/?query=quertyz
# {"query_parameter": [{"naija_news": "Nairaland.com"},{"naija_entertainment": "Naijaloaded.com"}],"query": "quertyz"}

@app.get("/query_parameter_with_default/")
async def query_parameter_with_default(query: str = Query(..., min_length=3)):
    results = {"query_parameter": [{"naija_news": "Nairaland.com"}, {"naija_entertainment": "Naijaloaded.com"}]}
    if query:
        results.update({"query": query})
    return results


# Query parameter list / multiple values
# http://127.0.0.1:8000/query_parameter_with_multiple_value/?query=string0&query=string1&query=string2
# {"query": ["string0","string1","string2"]}

@app.get("/query_parameter_with_multiple_value/")
async def query_parameter_with_multiple_value(query: Optional[List[str]] = Query(None)):
    if query:
        query_items = {"query": query}
    return query_items

# Query parameter list / multiple values with defaults
# http://127.0.0.1:8000/query_parameter_with_multiple_default_value/?query=foo&query=bar&query=geez
# {"query": ["foo","bar","geez"]}
#
# http://127.0.0.1:8000/query_parameter_with_multiple_default_value/?parameter_query=foo&parameter_query=bar&parameter_query=breez
# {"parameter_query": ["foo","bar","breez"]}

@app.get("/query_parameter_with_multiple_default_value/")
async def query_parameter_with_multiple_default_value(parameter_query: List[str] = Query(["foo", "bar"])):
    if parameter_query:
        query_items = {"parameter_query": parameter_query}
    return query_items

# Declare more metadata
# You can add more information about the parameter.
# http://127.0.0.1:8000/query_with_title_parameter/?parameter_query=nice_title_match
# {"query_parameter": [{"naija_news": "Nairaland.com"},{"naija_entertainment": "Naijaloaded.com"}],"parameter_query": "nice_title_match"}

@app.get("/query_with_title_parameter/")
async def get_query_with_title_parameter(parameter_query: Optional[str] = Query(None, title="Query string", min_length=3)):
    results = {"query_parameter": [{"naija_news": "Nairaland.com"}, {"naija_entertainment": "Naijaloaded.com"}]}
    if parameter_query:
        results.update({"parameter_query": parameter_query})
    return results


# http://127.0.0.1:8000/query_parameter_validation/?item-query=fixedquery
# {"items": [{"item_id": "Foo"},{"item_id": "Bar"}],"query_parameter": "fixedquery"}

@app.get("/query_parameter_validation/")
async def get_query_parameter_validation(
    query: Optional[str] = Query(
        None,
        alias="item-query",
        title="Query string",
        description="Query string for the items to search in the database that have a good match",
        min_length=3,
        max_length=50,
        regex="^fixedquery$",
        deprecated=True,
    )
):
    results = {"items": [{"item_id": "Foo"}, {"item_id": "Bar"}]}
    if query:
        results.update({"query_parameter": query})
    return results
