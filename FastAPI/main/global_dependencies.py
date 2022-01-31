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


@app.get("/global_dependencies_items/", tags=["Sub-dependencies"])
async def read_global_items():
    return [{"item": "Portal Gun"}, {"item": "Plumbus"}]


@app.get("/global_dependencies_users/", tags=["Sub-dependencies"])
async def read_global_users():
    return [{"username": "Rick"}, {"username": "Morty"}]
