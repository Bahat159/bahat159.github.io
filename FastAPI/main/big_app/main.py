from internal import admin
from routers import items, users
from fastapi import Depends, FastAPI
from dependencies import get_query_token, get_token_header


app = FastAPI(dependencies=[Depends(get_query_token)])


app.include_router(users.router)
app.include_router(items.router)
app.include_router(
    admin.router,
    prefix="/admin/v1",
    tags=["admin/v1"],
    dependencies=[Depends(get_token_header)],
    responses={418: {"description": "I'm a teapot"}},
)


@app.get("/")
async def root():
    return {"message": "Hello Bigger Applications!"}
