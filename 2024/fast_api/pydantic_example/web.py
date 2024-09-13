from model import Creature
from fastapi import FastAPI
from typing import List
import uvicorn

app = FastAPI()

@app.get("/creature")
def get_all() -> List[Creature]:
    from data import get_creature
    return get_creature()

if __name__ == "__main__" : 
    uvicorn.run("web:app")