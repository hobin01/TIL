from datetime import timedelta, datetime
import os 
from jose import jwt 
import bcrypt
from model.user import PublicUser, PrivateUser, SignInUser

if os.getenv("CRYPTID_UNIT_TEST"):
    from fake import user as data 
else :
    from data import user as data 

SECRET_KEY = "secret-key"
HASH_ALG = "HS256"

def verify_password(plain: str, hash: str) -> bool :
    # plain 해시와 db에 저장된 해시 비교 
    password_bytes = plain.encode("utf-8")
    hash_bytes = hash.encode("utf-8")
    is_valid = bcrypt.checkpw(password_bytes, hash_bytes)
    return is_valid


def get_hash(plain: str) -> str:
    # 해시값 생성 
    # bcrypt 구조 : $2b$10$saltHASHEDPASSWORD 
    # version = 2b, hash round = 10, salt = salt, hash value = HASHEDPASSWORD
    password_bytes = plain.encode("utf-8")
    salt = bcrypt.gensalt()
    hashed_password = bcrypt.hashpw(password_bytes, salt)
    return hashed_password.decode("utf-8")


def get_jwt_username(token: str) -> str | None :
    try : 
        payload = jwt.decode(token, SECRET_KEY, [HASH_ALG])
        if not (username := payload.get("sub")) :
            return None 
    except jwt.JWTError : 
        return None 

    return username


def get_current_user(token: str) -> PublicUser | None :
    if not (username := get_jwt_username(token)) :
        return None 
    if (user := lookup_user(username)):
        return user 
    return None 


def lookup_user(username: str, is_public: bool = True) -> PublicUser | PrivateUser | None :
    # db에서 username에 매칭되는 user 반환 
    # is_public True 시 PublicUser 반환 
    if (user := data.get_one(username, is_public=is_public)) :
        return user 
    return None 


def auth_user(name: str, plain: str) -> PublicUser | PrivateUser | None : 
    if not (user := lookup_user(name, is_public=False)):
        return None 
    if not verify_password(plain, user.hash):
        return None 
    return user


def create_access_token(data: dict, expires: timedelta | None = None) :
    # jwt 토큰 만들기 
    src = data.copy()
    now = datetime.utcnow()
    if not expires:
        expires = timedelta(minutes=15)

    src.update({"exp": now + expires})
    encoded_jwt = jwt.encode(src, SECRET_KEY, HASH_ALG)
    return encoded_jwt


# CRUD 통과 코드 
def get_all() -> list[PublicUser] :
    return data.get_all()


def get_one(name: str) -> PublicUser:
    return data.get_one(name)


def create(sign_in_user: SignInUser) -> PublicUser:
    user = PrivateUser(name=sign_in_user.name, hash=get_hash(sign_in_user.password))
    return data.create(user)


def modify(name: str, user: PublicUser) -> PublicUser :
    return data.modify(name, user)


def delete(name: str) -> None :
    return data.delete(name)