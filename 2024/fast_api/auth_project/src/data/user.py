from model.user import PublicUser, PrivateUser, SignInUser
from .init import (conn, curs, get_db, IntegrityError)
from error import Missing, Duplicate

# user : user table, xuser : deleted user table
curs.execute("create table if not exists user(name text primary key, hash text)")
curs.execute("create table if not exists xuser(name text primary key, hash text)")

def row_to_model(row: tuple, is_public: bool = True) -> PublicUser | PrivateUser :
    name, hash = row 
    if is_public:
        return PublicUser(name=name)
    else :
        return PrivateUser(name=name, hash=hash)


def model_to_dict(user: PrivateUser) -> dict :
    return user.model_dump()


def get_one(name: str, is_public: bool = True) -> PublicUser | PrivateUser :
    query = "select * from user where name=:name"
    params = {"name": name}
    curs.execute(query, params)
    row = curs.fetchone()

    if row:
        return row_to_model(row=row, is_public=is_public)
    else :
        raise Missing(msg=f"User {name} not found")


def get_all() -> list[PublicUser] :
    query = "select * from user"
    curs.execute(query)
    return [row_to_model(row) for row in curs.fetchall()]


# user 생성 시 password 해시값 저장 (갖고 있다고 가정)
# 외부로 노출되도 되는 PublicUser를 리턴 
def create(user: PrivateUser, table: str = "user") -> PublicUser : 
    query = f"insert into {table} (name, hash) values (:name, :hash)"
    params = model_to_dict(user)

    try:
        curs.execute(query, params)
    except IntegrityError:
        raise Duplicate(msg=f"{table} : user {user.name} already exists")

    return PublicUser(name=user.name)


def modify(name: str, user: PublicUser) -> PublicUser :
    query = "update user set name=:name where name=:name0"
    params = {"name": user.name, "name0": name}
    curs.execute(query, params)

    if curs.rowcount == 1:
        return get_one(user.name)
    else :
        raise Missing(msg=f"User {name} not found")
    
# 삭제 시 xuser로 이동
def delete(name: str) -> None :
    user = get_one(name, is_public=False)
    query = "delete from user where name=:name"
    params = {"name": name}
    curs.execute(query, params)

    if curs.rowcount != 1:
        raise Missing(msg=f"User {name} not found")
    create(user, table="xuser")