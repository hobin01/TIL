from model.explorer import Explorer

# fake data 
_explorers = [
    Explorer(
        name="Claude Hande",
        country="FR",
        description="보름달이 뜨면 만나기 힘듦"
    ),
    Explorer(
        name="Noah Weiser",
        country="DE",
        description="눈이 나쁘고 벌목도를 가지고 다님"
    ),
]

def get_all() -> list[Explorer]:
    # 탐험가 목록 반환 
    return _explorers

def get_one(name: str) -> Explorer:
    # 탐험가 1명 반환
    for _explorer in _explorers:
        if _explorer.name == name :
            return _explorer
    return None 

# 아직은 실제 동작하지 않는 것들
def create(explorer: Explorer) -> Explorer :
    # 탐험가 추가
    return explorer

def modify(name: str, explorer: Explorer) -> Explorer :
    # 탐험가 정보 수정 
    return explorer

def replace(name: str, explorer: Explorer) -> Explorer :
    # 탐험가 교체
    return explorer

def delete(name: str) -> bool :
    # 탐험가 삭제 
    for _explorer in _explorers :
        if _explorer.name == name :
            return True 
    return False 