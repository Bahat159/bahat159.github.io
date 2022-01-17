from typing import Optional
from fastapi import FastAPI, Path, Query

app = FastAPI()

# http://127.0.0.1:8000/url_path/5678?path-query=myownserver
# {"url_path": 5678,"query": "myownserver"}
#
# http://127.0.0.1:8000/url_path/54645?path_query=path_query_with_get
# {"url_path": 54645,"url_query": "path_query_with_get"}
#
# http://127.0.0.1:8000/url_path/45645?path_query=get_path_query
# {"url_path_id": 45645,"url_query": "get_path_query"}

@app.get("/url_path/{item_id}")
async def get_url_path(item_id: int = Path(..., title="The ID of the item to get"),query: Optional[str] = Query(None, alias="path_query"),):
    results = {"url_path_id": item_id}
    if query:
        results.update({"url_query": query})
    return results


# http://127.0.0.1:8000/url_path_with_query/7688?query=query_this_path
# {"item_id": 7688,"query": "query_this_path"}

@app.get("/url_path_with_query/{item_id}")
async def get_url_path_with_query(query: str, item_id: int = Path(..., title="The ID of the item to get")):
    results = {"item_id": item_id}
    if query:
        results.update({"url_query": query})
    return results