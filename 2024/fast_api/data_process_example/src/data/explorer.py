from .init import conn, curs, IntegrityError
from model.explorer import Explorer
from error import Missing, Duplicate


curs.execute("""create table if not exists 
            explorer(
                name text primary key, 
                description text, 
                country text)""")


def row_to_model(row: tuple) -> Explorer:
    name, description, country = row 

    return Explorer(
        name=name,
        description=description,
        country=country
    )


def model_to_dict(explorer: Explorer) -> dict : 
    return explorer.model_dump()


def get_one(name: str) -> Explorer:
    query = "select * from explorer where name=:name"
    params = {"name": name}
    curs.execute(query, params)
    row = curs.fetchone()

    if row:
        return row_to_model(row)
    else :
        raise Missing(msg=f"Explorer {name} not found")


def get_all(name: str) -> list[Explorer] :
    query = "select * from explorer"
    curs.execute(query)
    rows = list(curs.fetchall())

    return [row_to_model(row) for row in rows]


def create(explorer: Explorer) -> Explorer :
    if not explorer:
        return None

    query = "insert into explorer values (:name, :description, :country)"
    params = model_to_dict(explorer)

    try : 
        _ = curs.execute(query, params)
    except IntegrityError :
        raise Duplicate(msg=f"Explorer {explorer.name} already exists")

    return get_one(explorer.name)


def modify(name: str, explorer: Explorer) -> Explorer :
    if not (name and explorer):
        return None 
    query = """update explorer 
            set country=:country,
            name=:name,
            description=:description
            where name=:name_orig"""
    params = model_to_dict(explorer)
    params["name_orig"] = explorer.name 
    _ = curs.execute(query, params)

    if curs.rowcount == 1:
        return get_one(explorer.name)
    else :
        raise Missing(msg=f"Explorer {name} not found")


def replace(name: str, explorer: Explorer) -> Explorer:
    if not (name and explorer):
        return None
    qry = """update explorer
             set country=:country,
             name=:name,
             description=:description
             where name=:name_orig"""
    params = model_to_dict(explorer)
    params["name_orig"] = explorer.name
    curs.execute(qry, params)

    if curs.rowcount == 1:
        return get_one(explorer.name)
    else:
        raise Missing(msg=f"Explorer {name} not found")


def delete(name: str) -> bool :
    if not name:
        return False
    query = "delete from explorer where name=:name"
    params = {"name": name}
    res = curs.execute(query, params)
    
    if curs.rowcount != 1:
        raise Missing(msg=f"Explorer {name} not found")

    return True