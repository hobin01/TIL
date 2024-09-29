from model.explorer import Explorer
from service import explorer as code 

sample = Explorer(
    name="Claude Hande",
    country="FR",
    description="보름달이 뜨면 만나기 힘듦"
)

def test_create() : 
    resp = code.create(sample)
    assert resp == sample 

def test_get_exists() : 
    resp = code.get_one("Claude Hande")
    assert resp == sample 

def test_get_missing() : 
    resp = code.get_one("boxturtle")
    assert resp is None 
