from typing import List
from model import Creature

_creatures : List[Creature] = [
    Creature(
        name="yeti",
        country="CN",
        area="Himalaya",
        description="Mystery Himalayan",
        aka="Snowman"
    ),
    Creature(
        name="sasquatch",
        country="US",
        area="*",
        description="Yeti's Cousin",
        aka="Bigfoot"
    ),
]

def get_creature() -> List[Creature]:
    return _creatures

if __name__ == "__main__" : 
    print(get_creature())