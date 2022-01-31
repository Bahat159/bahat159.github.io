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

# Classes as dependencies

class Cat:
    def __init__(self, name: str):
        self.name = name
    
    def __str__(self):
        return self


fake_items_db = [{"item_name": "Foo"}, {"item_name": "Bar"}, {"item_name": "Baz"}]


class CommonQueryParams:
    def __init__(self, query: Optional[str] = None, skip: int = 0, limit: int = 100):
        self.query = query
        self.skip = skip
        self.limit = limit


@app.get("/common_query_parameters_items/", tags=["Class Common Query Parameters Dependencies"])
async def read_common_query_parameters_items(commons: CommonQueryParams = Depends(CommonQueryParams)):
    response = {}
    if commons.query:
        response.update({"query_string": commons.query})
    items = fake_items_db[commons.skip : commons.skip + commons.limit]
    response.update({"query_items": items})
    return response

@app.get("/common_query_parameters_without_type_annonation_items/", tags=["Class Common Query Parameters Dependencies"])
async def read_common_query_parameters_without_type_annonation_items(commons = Depends(CommonQueryParams)):
    response = {}
    if commons.query:
        response.update({"query_string": commons.query})
    items = fake_items_db[commons.skip : commons.skip + commons.limit]
    response.update({"query_items": items})
    return response

@app.get("/common_query_parameters_with_shortcut_method_items/", tags=["Class Common Query Parameters Dependencies"])
async def read_common_query_parameters_with_shortcut_mothod_items(commons: CommonQueryParams = Depends()):
    response = {}
    if commons.query:
        response.update({"query_string": commons.query})
    items = fake_items_db[commons.skip : commons.skip + commons.limit]
    response.update({"iquery_tems": items})
    return response
