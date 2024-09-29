from fastapi import APIRouter, HTTPException
from model.creature import Creature
import service.creature as service
from error import Missing, Duplicate

router = APIRouter(prefix="/creature")

@router.get("")
@router.get("/")
def get_all() -> list[Creature]:
    return service.get_all()

@router.get("/{name}")
@router.get("/{name}/")
def get_one(name: str) -> Creature:
    try : 
        return service.get_one(name)
    except Missing as exc :
        raise HTTPException(status_code=404, detail=exec.msg)

@router.post("", status_code=201)
@router.post("/", status_code=201)
def create(creature: Creature) -> Creature:
    try : 
        return service.create(creature)
    except Duplicate as exc :
        raise HTTPException(status_code=404, detail=exc.msg)

@router.patch("/{name}")
@router.patch("/{name}/")
def modify(name: str, creature: Creature) -> Creature:
    try : 
        return service.modify(name, creature)
    except Missing as exc :
        raise HTTPException(status_code=404, detail=exc.msg)

@router.put("/{name}")
@router.put("/{name}/")
def replace(name, creature: Creature) -> Creature:
    try : 
        return service.replace(name, creature)
    except Missing as exc :
        raise HTTPException(status_code=404, detail=exc.msg)

@router.delete("/{name}")
@router.delete("/{name}/")
def delete(name) -> bool:
    try : 
        return service.delete(name)
    except Missing as exc : 
        raise HTTPException(status_code=404, detail=exc.msg)
