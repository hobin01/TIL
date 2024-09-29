# data 계층에 대한 초기화를 위한 파일
# 환경변수 설정을 이용해 sqlite3에 대한 초기화를 진행함
import os 
from pathlib import Path 
from sqlite3 import connect, Connection, Cursor, IntegrityError

conn: Connection | None = None 
curs: Cursor | None = None 

def get_db(name: str | None = None, reset: bool = False) :
    # sqlite db 파일에 연결 
    global conn, curs 

    if conn :
        if not reset :
            return
        conn = None 

    if not name : 
        name = os.getenv("CRYPTID_SQLITE_DB")
        top_dir = Path(__file__).resolve().parents[1]
        db_dir = top_dir / "db"
        db_dir.mkdir(exist_ok=True)
        db_name = "cryptid.db"
        db_path = str(db_dir / db_name)
        name = os.getenv("CRYPTID_SQLITE_DB", db_path)
    
    conn = connect(name, check_same_thread=False)
    curs = conn.cursor()

get_db()