from fastapi import FastAPI
from fastapi.responses import HTMLResponse

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
