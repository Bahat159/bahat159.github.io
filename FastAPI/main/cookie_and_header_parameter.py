from typing import Optional
from typing import List, Optional
from fastapi import Cookie, FastAPI, Header

app = FastAPI()


@app.get("/read_cookie_items/")
async def read_cookie_items(ads_id: Optional[str] = Cookie(None)):
    return {"ads_id": ads_id}


# Header Parameters
# You can define Header parameters the same way you define Query, Path and Cookie parameters.

@app.get("/read_header_items/")
async def read_header_items(user_agent: Optional[str] = Header(None)):
    return {"User-Agent": user_agent}

# Declare Header parameters

@app.get("/read_header_as_optional_parameter_items/")
async def read_header_as_optional_parameter_items(user_agent: Optional[str] = Header(None)):
    return {"User-Agent": user_agent}


# Automatic conversion
# If for some reason you need to disable automatic 
# conversion of underscores to hyphens, set the parameter convert_underscores of Header to False:

@app.get("/read_automatic_header_conversion_items/")
async def read_automatic_header_conversion_items(
    strange_header: Optional[str] = Header(None, convert_underscores=False)
):
    return {"strange_header": strange_header}

# Duplicate headers
# It is possible to receive duplicate headers. That means, the same header with multiple values.
# You will receive all the values from the duplicate header as a Python list.

@app.get("/read_duplicate_header_items/")
async def read_duplicate_header_items(x_token: Optional[List[str]] = Header(None)):
    return {"X-Token values": x_token}
