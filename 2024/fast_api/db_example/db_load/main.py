from fastapi import FastAPI
import uvicorn
from web import creature, explorer

app = FastAPI()
app.include_router(explorer.router)
app.include_router(creature.router)

@app.get("/")
def top() : 
    return "hello"

if __name__ == "__main__" :
    uvicorn.run("main:app", reload=True)

