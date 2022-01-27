from typing import List, Optional

from fastapi import FastAPI
from pydantic import BaseModel,EmailStr

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

# Return the same input data

class UserIn(BaseModel):
    username: str = "Bahat"
    password: str = "Ju99sterpo00se%\intT0oF5astA0pi" # we could be sending our user's passwords to every client.
    email: EmailStr = "busarihabib159@gmail.com"
    full_name: Optional[str] = "Busari Habibullaah"

# Don't do this in production!
@app.post("/user_input_model/", response_model=UserIn)
async def create_user_input_model(user: UserIn):
    return user

class UserOut(BaseModel):
    username: str
    email: EmailStr
    full_name: Optional[str] = None

@app.post("/user_output_model/", response_model=UserOut)
async def create_user_output_model(user: UserIn):
    return user
