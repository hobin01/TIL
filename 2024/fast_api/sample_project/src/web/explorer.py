from fastapi import APIRouter, HTTPException
from model.explorer import Explorer
import service.explorer as service
from error import Missing, Duplicate

router = APIRouter(prefix="/explorer")

@router.get("")
@router.get("/")
def get_all() -> list[Explorer]:
    return service.get_all()

@router.get("/{name}")
@router.get("/{name}/")
def get_one(name: str) -> Explorer:
    try : 
        return service.get_one(name)
    except Missing as exc :
        raise HTTPException(status_code=404, detail=exec.msg)

@router.post("", status_code=201)
@router.post("/", status_code=201)
def create(explorer: Explorer) -> Explorer:
    try : 
        return service.create(explorer)
    except Duplicate as exc :
        raise HTTPException(status_code=404, detail=exc.msg)

@router.patch("/{name}")
@router.patch("/{name}/")
def modify(name: str, explorer: Explorer) -> Explorer:
    try : 
        return service.modify(name, explorer)
    except Missing as exc :
        raise HTTPException(status_code=404, detail=exc.msg)

@router.put("/{name}")
@router.put("/{name}/")
def replace(name, explorer: Explorer) -> Explorer:
    try : 
        return service.replace(name, explorer)
    except Missing as exc :
        raise HTTPException(status_code=404, detail=exc.msg)

@router.delete("/{name}")
@router.delete("/{name}/")
def delete(name) -> bool:
    try : 
        return service.delete(name)
    except Missing as exc : 
        raise HTTPException(status_code=404, detail=exc.msg)