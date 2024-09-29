from fastapi import APIRouter, HTTPException
from model.creature import Creature
import service.creature as service
from error import Missing, Duplicate

router = APIRouter(prefix="/creature")

@router.get("")
@router.get("/")
def get_all() -> list[Creature]:
    return service.get_all()

@router.get("/{name}")
@router.get("/{name}/")
def get_one(name: str) -> Creature:
    try : 
        return service.get_one(name)
    except Missing as exc :
        raise HTTPException(status_code=404, detail=exec.msg)

@router.post("", status_code=201)
@router.post("/", status_code=201)
def create(creature: Creature) -> Creature:
    try : 
        return service.create(creature)
    except Duplicate as exc :
        raise HTTPException(status_code=404, detail=exc.msg)

@router.patch("/{name}")
@router.patch("/{name}/")
def modify(name: str, creature: Creature) -> Creature:
    try : 
        return service.modify(name, creature)
    except Missing as exc :
        raise HTTPException(status_code=404, detail=exc.msg)

@router.put("/{name}")
@router.put("/{name}/")
def replace(name, creature: Creature) -> Creature:
    try : 
        return service.replace(name, creature)
    except Missing as exc :
        raise HTTPException(status_code=404, detail=exc.msg)

@router.delete("/{name}")
@router.delete("/{name}/")
def delete(name) -> bool:
    try : 
        return service.delete(name)
    except Missing as exc : 
        raise HTTPException(status_code=404, detail=exc.msg)

#############################

from fastapi import Response
import plotly.express as px


@router.get("/test")
def test():
    df = px.data.iris()
    fig = px.scatter(df, x="sepal_width", y="sepal_length", color="species")
    fig_bytes = fig.to_image(format="png")
    return Response(content=fig_bytes, media_type="image/png")


from collections import Counter


@router.get("/plot/")
def plot():
    creatures = service.get_all()
    letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    counts = Counter(creature.name[0] for creature in creatures)
    y = {letter: counts.get(letter, 0) for letter in letters}
    fig = px.histogram(
        x=list(letters), y=y, title="Creature Names", labels={"x": "Initial", "y": "Initial"}
    )
    fig_bytes = fig.to_image(format="png")
    return Response(content=fig_bytes, media_type="image/png")


import country_converter as coco


@router.get("/map/")
def map():
    creatures = service.get_all()
    iso2_codes = set(creature.country for creature in creatures)
    iso3_codes = coco.convert(names=iso2_codes, to="ISO3")
    fig = px.choropleth(locationmode="ISO-3", locations=iso3_codes)
    fig_bytes = fig.to_image(format="png")
    return Response(content=fig_bytes, media_type="image/png")


@router.get("/map2/")
def map():
    creatures = service.get_all()
    areas = [creature.area for creature in creatures]
    fig = px.choropleth(locationmode="USA-states", locations=areas)
    fig_bytes = fig.to_image(format="png")
    return Response(content=fig_bytes, media_type="image/png")