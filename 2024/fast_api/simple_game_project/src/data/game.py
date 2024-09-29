from .init import curs 

def get_word() -> str:
    query = "select name from creature order by random() limit 1"
    curs.execute(query)
    row = curs.fetchone()

    if row:
        name = row[0]
    else:
        name = "bigfoot"
        
    return name 