from sqlalchemy.orm import Session
import models, schemas


# CRUD utils
# CRUD comes from: Create, Read, Update, and Delete.
#
# This example is not secure, the password is not hashed.
# In a real life application you would need to hash the password and never save them in plaintext.
# For more details, go back to the Security section in the tutorial.
# Here we are focusing only on the tools and mechanics of databases.
#
# Create utility functions to:



# Read a single user by ID and by email.
def get_user(db: Session, user_id: int):
    return db.query(models.User).filter(models.User.id == user_id).first()


def get_user_by_email(db: Session, email: str):
    return db.query(models.User).filter(models.User.email == email).first()

# Read multiple users.
def get_users(db: Session, skip: int = 0, limit: int = 100):
    return db.query(models.User).offset(skip).limit(limit).all()

# Create User data
# 
# Create a SQLAlchemy model instance with your data.
# add that instance object to your database session.
# commit the changes to the database (so that they are saved).
# refresh your instance (so that it contains any new data from the database, like the generated ID).

def create_user(db: Session, user: schemas.UserCreate):
    fake_hashed_password = user.password + "notreallyhashed"
    db_user = models.User(email=user.email, hashed_password=fake_hashed_password)
    db.add(db_user)
    db.commit()
    db.refresh(db_user)
    return db_user

# Read multiple items
def get_items(db: Session, skip: int = 0, limit: int = 100):
    return db.query(models.Item).offset(skip).limit(limit).all()

# Create User Item data
def create_user_item(db: Session, item: schemas.ItemCreate, user_id: int):
    db_item = models.Item(**item.dict(), owner_id=user_id)
    db.add(db_item)
    db.commit()
    db.refresh(db_item)
    return db_item
