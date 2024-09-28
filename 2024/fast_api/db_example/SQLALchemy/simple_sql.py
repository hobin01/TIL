def get_one(name: str) :
    qry = "select * from explorer where name=:name"
    params = {"name": name}
    curs.execute(qry, params)
    return row_to_model(curs.fetchone())

# sqlite3로 db 테이블 만들어져 있다 가정
