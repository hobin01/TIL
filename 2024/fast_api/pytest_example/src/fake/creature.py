from model.creature import Creature
from error import Duplicate, Missing

# fake data 
_creatures = [
    Creature(
        name="Yeti",
        country="CN",
        area="Himalayas",
        description="전설의 히말라야 괴물",
        aka="Abominable Snowman"
    ),
    Creature(
        name="Bigfoot",
        country="US",
        area="*",
        description="예티의 친척! 전설의 큰 발!",
        aka="Sasquatch"
    ),
]

def get_all() -> list[Creature]:
    # creature 목록 반환 
    return _creatures

def get_one(name: str) -> Creature:
    # creature 1명 반환
    for _creature in _creatures:
        if _creature.name == name :
            return _creature
    return Missing(msg=f"Creature {name} not found") 

def create(creature: Creature) -> Creature :
    # creature 추가
    if next((x for x in _creatures if x.name == creature.name), None):
        raise Duplicate(msg=f"Creature {creature.name} already exists")
    _creatures.append(creature)
    return creature

def modify(name: str, creature: Creature) -> Creature :
    # creature 정보 수정 
    _creature = next((x for x in _creatures if x.name == creature.name), None)
    if _creature is not None :
        _creature = creature
        return _creature
    else :
        raise Missing(msg=f"Creature {name} not found")

def replace(name: str, creature: Creature) -> Creature :
    # creature 교체
    _creature = next((x for x in _creatures if x.name == creature.name), None)
    if _creature is None :
        raise Missing(msg=f"Creature {name} not found")
    
    _creature = creature
    return _creature

def delete(name: str) -> bool :
    # creature 삭제
    if not name:
        return False 
    
    _creature = next((x for x in _creatures if x.name == name), None)
    if _creature is None :
        raise Missing(msg=f"Creature {name} not found")

    _creatures.remove(_creature)
    return True

