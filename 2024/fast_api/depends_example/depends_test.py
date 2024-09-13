from fastapi import FastAPI, Depends, Query
import uvicorn

app = FastAPI()

def user_dep(name: str = Query(...), gender: str = Query(...)):
    return {"name": name, "valid": True}

# user_dep이 의존성 함수
# 즉, user_dep이 먼저 실행이 되어야 get_user가 실행됨
# 따라서 localhost:8000/user?name=123123&gender=male
# 과 같이 query 내용 필수로 넣어줘야 get_user가 동작함 
@app.get("/user")
def get_user(user:dict = Depends(user_dep)) -> dict:
    return user

# 데코레이터에서 직접 의존성 검사
# 포맷 : @app.method(url, dependencies=[Depends(dep_func)])
def check_dep(name: str = Query(...), gender: str = Query(...)):
    if not name :
        raise Exception("there is no name")

@app.get("/check_user", dependencies=[Depends(check_dep)])
def check_user() -> bool :
    return True

"""
# 애플리케이션 레벨 의존성 정의 예시 
def dep_func1() : 
    pass 

def dep_func2() : 
    pass 

app = FastAPI(dependencies=[Depends(dep_func1), Depends(dep_func2)])
"""

if __name__ == "__main__" : 
    uvicorn.run("depends_test:app")