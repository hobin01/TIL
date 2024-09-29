from model.creature import Creature

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
    # 탐험가 목록 반환 
    return _creatures

def get_one(name: str) -> Creature:
    # 탐험가 1명 반환
    for _creature in _creatures:
        if _creature.name == name :
            return _creature
    return None 

# 아직은 실제 동작하지 않는 것들
def create(creature: Creature) -> Creature :
    # 탐험가 추가
    return creature

def modify(name: str, creature: Creature) -> Creature :
    # 탐험가 정보 수정 
    return creature

def replace(name: str, creature: Creature) -> Creature :
    # 탐험가 교체
    return creature

def delete(name: str) -> bool :
    # 탐험가 삭제 
    for _creature in _creatures :
        if _creature.name == name :
            return True 
    return False 

