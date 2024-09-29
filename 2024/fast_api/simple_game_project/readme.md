에러 처리 관련 메모

1. pytest로 테스트 시 조치해볼 사항
- test 하위 디렉토리가 실제 src 내의 모듈과 이름 충돌 발생 가능
  - 이름 겹치는 것들 변경
  - test 디렉토리 자체도 모듈로 변경 (`__init__.py`) 추가
  - pytest.ini 파일 프로젝트 root 디렉토리에 추가 후, test config 설정 


2. 클라이언트에서 post로 request 보냈지만, 실제 서버에서는 options로 인식을 할 때
- `main.py` 에 cors 설정을 추가

