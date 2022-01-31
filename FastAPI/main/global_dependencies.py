from fastapi import Depends, FastAPI, Header, HTTPException

# Global Dependencies
# For some types of applications you might want to add dependencies to the whole application.
# Similar to the way you can add dependencies to 
# the path operation decorators, you can add them to the FastAPI application.

async def global_verify_token(x_token: str = Header(...)):
    if x_token != "fake-super-secret-token":
        raise HTTPException(status_code=400, detail="X-Token header invalid")


async def global_verify_key(x_key: str = Header(...)):
    if x_key != "fake-super-secret-key":
        raise HTTPException(status_code=400, detail="X-Key header invalid")
    return x_key


app = FastAPI(dependencies=[Depends(global_verify_token), Depends(global_verify_key)])


@app.get("/global_dependencies_items/", tags=["Global dependencies"])
async def read_global_items():
    return [{"item": "Portal Gun"}, {"item": "Plumbus"}]


@app.get("/global_dependencies_users/", tags=["Global dependencies"])
async def read_global_users():
    return [{"username": "Rick"}, {"username": "Morty"}]

# Dependencies with yield
#
# A database dependency with yield
# For example, you could use this to create a database session and close it after finishing.

async def get_db():
    db = DBSession()
    try:
        yield db
    finally:
        db.close()

async def dependency_a():
    dep_a = generate_dep_a()
    try:
        yield dep_a
    finally:
        dep_a.close()


async def dependency_b(dep_a=Depends(dependency_a)):
    dep_b = generate_dep_b()
    try:
        yield dep_b
    finally:
        dep_b.close(dep_a)


async def dependency_c(dep_b=Depends(dependency_b)):
    dep_c = generate_dep_c()
    try:
        yield dep_c
    finally:
        dep_c.close(dep_b)

# Context Managers
# "Context Managers" are any of those Python objects that you can use in a with statement.
file_path = "./somefile.txt"
with open(file_path) as f:
    contents = f.read()
    print(contents)

# Underneath, the open("./somefile.txt") creates an object that is a called a "Context Manager".
#
# Using context managers in dependencies with yield
class MySuperContextManager:
    def __init__(self):
        self.db = DBSession()

    def __enter__(self):
        return self.db

    def __exit__(self, exc_type, exc_value, traceback):
        self.db.close()


async def get_db():
    with MySuperContextManager() as db:
        yield db

