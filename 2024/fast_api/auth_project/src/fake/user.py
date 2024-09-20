from model.user import PublicUser, PrivateUser, SignInUser
from error import Missing, Duplicate

fakes = [PublicUser(name="qwe"), PublicUser(name="asd")]

def find(name: str) -> PublicUser | None :
    for ele in fakes : 
        if ele.name == name : 
            return ele
    return None


def check_missing(name: str):
    if not find(name):
        raise Missing(f"Missing user {name}")


def check_duplicate(name: str) :
    if find(name):
        raise Duplicate(msg=f"Duplicate user {name}")

def get_all() -> list[PublicUser]:
    return fakes 


def get_one(name: str) -> PublicUser :
    check_missing(name)
    return find(name)

def create(user: PublicUser) -> PublicUser :
    check_duplicate(user.name)
    return PublicUser(name=user.name)


def modify(name: str, user: PublicUser) -> PublicUser :
    check_missing(name)
    return user 

def delete(name: str) -> None :
    check_missing(name)
    return None 