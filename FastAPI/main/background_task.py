# You can define background tasks to be run after returning a response.
#
#This is useful for operations that need to happen after a request, 
# but that the client doesn't really have to be waiting for the 
# operation to complete before receiving the response.
#
# This includes, for example:
#
# Email notifications sent after performing an action:
# As connecting to an email server and sending an email tends to 
# be "slow" (several seconds), 
# you can return the response right away and send the email notification in the background.
#
# Processing data:
# For example, let's say you receive a file that must go 
# through a slow process, you can return a response of 
# "Accepted" (HTTP 202) and process it in the background.

from fastapi import BackgroundTasks, FastAPI

app = FastAPI()


def write_notification(email: str, message=""):
    with open("background_task_log.txt", mode="w") as email_file:
        content = f"notification for {email}: {message}"
        email_file.write(content)


@app.post("/send-notification/{email}")
async def send_notification(email: str, background_tasks: BackgroundTasks):
    background_tasks.add_task(write_notification, email, message="some notification")
    return {"message": "Notification sent in the background"}
