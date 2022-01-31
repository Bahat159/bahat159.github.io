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
#
# Other common terms for this same idea of "dependency injection" are:
# resources
# providers
# services
# injectables
# components

app = FastAPI()


async def common_parameters(query_string: Optional[str] = None, optional_query_parameter_skip: int = 0, optional_query_parameter_limit: int = 100):
    return {"query_string": query_string, "query_parameter_skip": optional_query_parameter_skip, "query_parameter_limit": optional_query_parameter_limit}


@app.get("/dependency_query_items/", tags=["Dependecies injection"])
async def read_items(commons: dict = Depends(common_parameters)):
    return commons


@app.get("/dependency_query_users/", tags=["Dependecies injection"])
async def read_users(commons: dict = Depends(common_parameters)):
    return commons
