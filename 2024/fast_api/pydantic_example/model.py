from pydantic import BaseModel, constr

# pydantic의 BaseModel 상속받아 사용
# 기본적으로 타입 체크 기능 제공
class Creature(BaseModel) :
    name: str 
    country: str 
    area: str
    description: str 
    aka: str 

# pydantic으로 값 유효성 검사도 가능 
# conint : gt (초과), lt (미만), ge (이상), le (이하), multiple_of (정수 배수)
# constr : min_length (최소 문자 길이 (바이트 X)), max_length (최대 길이), to_upper (대문자 변환),
# to_lower (소문자 변환), regex (정규표현식 일치)
# tuple, list, set : min_items (최소 원소 개수), max_items (최대 원소 개수)
class Creature2(BaseModel) :
    name: constr(min_length=2)
    country: constr(max_length=2) 
    area: str
    description: str 
    aka: str 

thing = Creature(
    name="yeti",
    country="CN",
    area="Himalaya",
    description="Mystery Himalayan",
    aka="Snowman"
)

thing2 = Creature2(
    name="yeti",
    country="CN",
    area="Himalaya",
    description="Mystery Himalayan",
    aka="Snowman"
)

if __name__ == "__main__" : 
    print(thing)
    print(thing2)