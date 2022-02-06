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

# RedirectResponse
@app.get("/typer", tags=["RedirectResponse"])
async def redirect_typer():
    return RedirectResponse("https://typer.tiangolo.com")


@app.get("/fastapi", response_class=RedirectResponse, tags=["RedirectResponse"])
async def redirect_fastapi():
    return "https://fastapi.tiangolo.com"


@app.get("/pydantic", response_class=RedirectResponse, status_code=302, tags=["RedirectResponse"])
async def redirect_pydantic():
    return "https://pydantic-docs.helpmanual.io/"

# StreamingResponse
# Takes an async generator or a normal generator/iterator and streams the response body.

async def fake_video_streamer():
    for i in range(10):
        yield b"some fake video bytes"


@app.get("/fake_video_streaming_response", tags=["Streaming Response"])
async def fake_video_streaming_response():
    return StreamingResponse(fake_video_streamer())


# Using StreamingResponse with file-like objects


some_file_path = "large-video-file.mp4"



@app.get("/streaming_response_with_file_like_object", tags=["Streaming Response"])
def main():
    def iterfile():  # This is the generator function. It's a "generator function" 
                    # because it contains yield    statements inside.
        with open(some_file_path, mode="rb") as file_like:  # 
            yield from file_like  # By using a with block, we make sure that the file-like object 
                                    # is closed after the generator function is done.
                                    #  So, after it finishes sending the response.

    return StreamingResponse(iterfile(), media_type="video/mp4")


# FileResponse

some_file_path = "large-video-file.mp4"

@app.get("/file_response", tags=["File Response"])
async def get_file_response_main():
    return FileResponse(some_file_path)

@app.get("/file_response_main_response_class", response_class=FileResponse, tags=["File Response"])
async def get_file_response_main_response_class():
    return some_file_path
