import os
from fastapi import APIRouter, HTTPException, Depends
from datetime import timedelta
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from model.user import PrivateUser, PublicUser, SignInUser
from error import Missing, Duplicate

if os.getenv("CRYPTID_UNIT_TEST"):
    from fake import user as service 
else :
    from service import user as service

ACCESS_TOKEN_EXPIRE_MINUTES = 30 

router = APIRouter(prefix="/user")

# oauth2_dep : /user/token 동작하게 함
# username, pass 유무를 담고 있는 form을 읽고 접근 토큰을 반환 
oauth2_dep = OAuth2PasswordBearer(tokenUrl="/user/token")

def unauthed() :
    raise HTTPException(
        status_code=401, 
        detail="Incorrect username or password",
        headers={"WWW-Authenticate": "Bearer"}
    )

@router.post("/token")
async def create_access_token(form_data: OAuth2PasswordRequestForm = Depends()) -> dict : 
    # username, password를 oauth 양식에서 꺼내고 jwt 토큰 반환 
    user = service.auth_user(form_data.username, form_data.password)
    if not user:
        unauthed()
    expires = timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES)
    access_token = service.create_access_token(data={"sub": user.name}, expires=expires)
    return {"access_token":access_token, "token_type":"bearer"}


@router.get("/token")
def get_access_token(token:str = Depends(oauth2_dep)) -> dict:
    # 현재 접속 토큰 반환 
    return {"token": token}


# 이전 CRUD 내용들 
@router.get("/")
def get_all() -> list[PublicUser]:
    return service.get_all()


@router.get("/{name}")
def get_one(name) -> PublicUser:
    try:
        return service.get_one(name)
    except Missing as exc:
        raise HTTPException(status_code=404, detail=exc.msg)


@router.post("/", status_code=201)
def create(user: SignInUser) -> PublicUser:
    try:
        return service.create(user)
    except Duplicate as exc:
        raise HTTPException(status_code=409, detail=exc.msg)


@router.patch("/{name}")
def modify(name: str, user: PublicUser) -> PublicUser:
    try:
        return service.modify(name, user)
    except Missing as exc:
        raise HTTPException(status_code=404, detail=exc.msg)


@router.delete("/{name}")
def delete(name: str) -> None:
    try:
        return service.delete(name)
    except Missing as exc:
        raise HTTPException(status_code=404, detail=exc.msg)
    except Duplicate as exc:
        raise HTTPException(status_code=409, detail=exc.msg)