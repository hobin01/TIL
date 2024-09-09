from fastapi import FastAPI, Body, Header, Response

app = FastAPI()

# zsh 이용 시 ? 대신 \? 필요

# localhost:8000/hi/123
@app.get("/hi/{who}")
def greet(who) : 
    return f"Hello! {who}"

# localhost:8000/hello?who=123
@app.get("/hello")
def greet2(who) :
    return f"Hello!!!!! {who}????"

# localhost:8000/hello_post who=123
@app.post("/hello_post")
def greet3(who: str = Body(embed=True)) :
    return f"Hello!!!! {who}!!!!"

# localhost:8000/header who:123
@app.get("/header")
def greet4(who: str = Header()) :
    return f"Hello!! Header!!! {who}"

# localhost:8000/user_agent
@app.get("/user_agent")
def greet5(user_agent: str = Header()) :
    return user_agent

# localhost:8000/header/name/value
@app.get("/header/{name}/{value}")
def greet6(name:str, value:str, response:Response):
    response.headers[name] = value
    return "body!!!"

if __name__ == "__main__":
    import uvicorn
    uvicorn.run("hello:app", reload=True)
