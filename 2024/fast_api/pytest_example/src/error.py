# 계층 별 error 를 직접적으로 전달하지 않고
# 예외 캐치될 때까지 계층 간 데이터 전송시키기 위한 파일 

class Missing(Exception):
    # db에 없는 데이터 호출 시 발생되는 에러
    def __init__(self, msg: str):
        self.msg = msg

class Duplicate(Exception):
    # db에 이미 존재하는 데이터와 동일한 primary key가 신규 입력으로 주어질 때 발생되는 에러 
    def __init__(self, msg: str):
        self.msg = msg 