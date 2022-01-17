from typing import Optional
from fastapi import FastAPI, Path, Query

app = FastAPI()

# http://127.0.0.1:8000/url_path/5678?path-query=myownserver
# {"url_path": 5678,"query": "myownserver"}

@app.get("/url_path/{item_id}")
async def get_url_path(
    item_id: int = Path(..., title="The ID of the item to get"),
    query: Optional[str] = Query(None, alias="path-query"),
):
    results = {"url_path": item_id}
    if query:
        results.update({"query": query})
    return results
