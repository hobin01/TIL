간단한 fast api 프로젝트 구조

src : 모든 웹사이트 코드 포함
- web : fast api 웹 계층
- service : 비즈니스 로직 계층 
- data : 저장소와의 인터페이스 계층 
- model : pydantic 모델 정의
- fake : 미리 하드코딩된 스텁 데이터 

각 디렉토리 별 하위 파일
- __init__.py : 디렉토리를 패키지로 취급
- creature.py : 현재 계층에서 다루는 생명체에 대한 코드
- explorer.py : 현재 계층에서 다루는 탐험가에 대한 코드 

