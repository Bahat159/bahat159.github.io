from typing import Optional
from fastapi import Depends, FastAPI

# Dependencies - First Steps
# Dependency Injection
#
# "Dependency Injection" means, in programming, 
# that there is a way for your code (in this case, your path operation functions) 
# to declare things that it requires to work and use: "dependencies".
#
# And then, that system (in this case FastAPI) will 
# take care of doing whatever is needed to provide your code 
# with those needed dependencies ("inject" the dependencies).


app = FastAPI()


async def common_parameters(q: Optional[str] = None, skip: int = 0, limit: int = 100):
    return {"q": q, "skip": skip, "limit": limit}


@app.get("/items/", tags=["Dependecies injection"])
async def read_items(commons: dict = Depends(common_parameters)):
    return commons


@app.get("/users/", tags=["Dependecies injection"])
async def read_users(commons: dict = Depends(common_parameters)):
    return commons
