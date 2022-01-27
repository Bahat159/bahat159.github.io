from typing import List, Optional

from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()


class ResponseModelItem(BaseModel):
    name: str = "Response Model"
    description: Optional[str] = "Test application for FastApi Response Model"
    price: float = 2.30
    tax: Optional[float] = 0.0
    tags: List[str] = ["response model"]


@app.post("/create_response_model_item/", response_model=ResponseModelItem)
async def create_response_model_item(item: ResponseModelItem):
    return item
