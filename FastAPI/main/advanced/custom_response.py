from fastapi import FastAPI
from fastapi.responses import HTMLResponse, Response, PlainTextResponse, UJSONResponse

app = FastAPI()


@app.get("/read_html_response_items/", response_class=HTMLResponse, tags=["Html Reponse"])
async def read_html_response_items():
    return """
    <html>
        <head>
            <title>Some HTML in here</title>
        </head>
        <body>
            <h1>Look ma! HTML!</h1>
        </body>
    </html>
    """

# HTML Response

@app.get("/return_html_response_items/", response_class=HTMLResponse, tags=["Html Reponse"])
async def return_html_response_items():
    html_content = """
    <html>
        <head>
            <title>Some HTML in here</title>
        </head>
        <body>
            <h1>Look ma! HTML!</h1>
        </body>
    </html>
    """
    return HTMLResponse(content=html_content, status_code=200)

# Document in OpenAPI and override Response

def generate_html_response():
    html_content = """
    <html>
        <head>
            <title>Some HTML in here</title>
        </head>
        <body>
            <h1>Look ma! HTML!</h1>
        </body>
    </html>
    """
    return HTMLResponse(content=html_content, status_code=200)


@app.get("/read_html_generated_response_items/", response_class=HTMLResponse, tags=["OpenApi and override response"])
async def read_generated_html_respose_items():
    return generate_html_response()


# Response
#
# It accepts the following parameters:
# content - A str or bytes.
# status_code - An int HTTP status code.
# headers - A dict of strings.
# media_type - A str giving the media type. E.g. "text/html".

@app.get("/legacy_data_item/", tags=["Xml Response Type"])
def get_legacy_data():
    data = """<?xml version="1.0"?>
    <shampoo>
    <Header>
        Apply shampoo here.
    </Header>
    <Body>
        You'll have to use soap here.
    </Body>
    </shampoo>
    """
    return Response(content=data, media_type="application/xml", status_code=200)


# PlainTextResponse
@app.get("/plaintext_response_type_item", response_class=PlainTextResponse, tags=["Plaintext Response"])
async def main_plaintext_response():
    return "Hello World, Plaintext response from FastApi"

# UJSONResponse
@app.get("/read_ujson_response_items/", response_class=UJSONResponse, tags=["UJson Response"])
async def read_ujson_response_items():
    return [{"item_id": "UJson Response Item"}]
