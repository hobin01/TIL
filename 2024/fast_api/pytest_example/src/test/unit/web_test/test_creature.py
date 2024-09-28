from fastapi import HTTPException
import pytest 
import os 

os.environ["CRYPTID_UNIT_TEST"] = "true"

from web import creature
from model.creature import Creature

@pytest.fixture
def sample() -> Creature:
    return Creature(
        name="dragon",
        description="Fire!!!!",
        country="*",
        area="",
        aka=""
    )


@pytest.fixture
def fakes() -> list[Creature]:
    return creature.get_all()


def assert_duplicate(exc):
    assert exc.value.status_code == 404 
    assert "Duplicate" in exc.value.msg 


def assert_missing(exc):
    assert exc.value.status_code == 404 
    assert "Missing" in exc.value.msg 


def test_create_duplicate(fakes):
    with pytest.raises(HTTPException) as exc:
        _ = creature.create(fakes[0])
        assert_duplicate(exc)


def test_get_one(fakes):
    assert creature.get_one(fakes[0].name) == fakes[0]


def test_get_one_missing():
    with pytest.raises(HTTPException) as exc:
        _ = creature.get_one("bobcat")
        assert_missing(exc)


def test_modify(fakes):
    assert creature.modify(fakes[0].name, fakes[0]) == fakes[0]


def test_modify_missing(sample):
    with pytest.raises(HTTPException) as exc:
        _ = creature.modify(sample.name, sample)
        assert_missing(exc)


def test_delete(fakes):
    assert creature.delete(fakes[0].name) is None 


def test_delete_missing(sample):
    with pytest.raises(HTTPException) as exc:
        _ = creature.delete("emu")
        assert_missing(exc)

# fake에 있는 creature 변하므로 테스트 순서대로 성공 체크 위해 가장 마지막에 create 테스트 
def test_create(sample):
    assert creature.create(sample) == sample