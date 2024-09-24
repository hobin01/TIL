import os

os.environ["CRYPTID_SQLITE_DB"] = ":memory:"

import pytest 
from model.creature import Creature
from error import Missing, Duplicate
from data import creature as data 

@pytest.fixture
def sample() -> Creature:
    return Creature(
        name="yeti",
        aka="Snowman",
        country="CN",
        area="Himalaya",
        description="Himalayan!!!"
    )


def test_create(sample):
    resp = data.create(sample)
    assert resp == sample


def test_create_duplicate(sample):
    resp = data.create(sample)
    assert resp == sample 
    with pytest.raises(Duplicate):
        resp = data.create(sample)


def test_get_exists(sample):
    resp = data.create(sample)
    assert resp == sample

    resp = data.get_one(sample.name)
    assert resp == sample


def test_get_missing():
    with pytest.raises(Missing):
        _ = data.get_one("boxturtle")


def test_modify(sample):
    sample.country = "KR"
    resp = data.modify(sample.name, sample)
    assert resp == sample


def test_modify_missing():
    alice: Creature = Creature(
        name="alice",
        country="JP",
        area="*",
        aka="???",
        description="girl!!!!"
    )
    with pytest.raises(Missing):
        _ = data.modify(bob.name, bob)