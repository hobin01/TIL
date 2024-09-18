from fastapi import APIRouter
from model.creature import Creature
import fake.creature as service

router = APIRouter(prefix="/creature")

@router.get("/")
def get_all() -> list[Creature]:
    return service.get_all()

@router.get("/{name}")
def get_one(name) -> Creature | None:
    return service.get_one(name)

# 나머지 엔드포인트 (현재는 아무 기능 없음)
@router.post("/")
def create(creature: Creature) -> Creature:
    return service.create(creature)

@router.patch("/{name}")
def modify(name, creature: Creature) -> Creature:
    return service.modify(name, creature)

@router.put("/{name}")
def replace(name, creature: Creature) -> Creature:
    return service.replace(name, creature)

@router.delete("/{name}")
def delete(name) -> bool:
    return service.delete(name)