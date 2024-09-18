간단한 fast api 프로젝트 구조

src : 모든 웹사이트 코드 포함
- web : fast api 웹 계층
- service : 비즈니스 로직 계층 
- data : 저장소와의 인터페이스 계층 
- model : pydantic 모델 정의
- fake : 미리 하드코딩된 스텁 데이터 

각 디렉토리 별 하위 파일
- `__init__.py` : 디렉토리를 패키지로 취급
- `creature.py` : 현재 계층에서 다루는 생명체에 대한 코드
- `explorer.py` : 현재 계층에서 다루는 탐험가에 대한 코드 

test : pytest 이용. web, service, data, model과 같은 레벨의 디렉토리
- unit : 단일 기능 테스트
  - web : 웹 계층 유닛 테스트
  - service : 서비스 계층 유닛 테스트
  - data : 데이터 계층 유닛 테스트
- full : end-to-end test

`pytest.ini` : 프로젝트 최상단에 위치
- ini 내부 설정으로 어떤 path, file을 테스트할 지 명명
- 실행 : 최상단 디렉토리 이동 후, pytest -v 등 넣고 싶은 옵션 넣어서 진행 
  - 자주 사용되는 옵션
    - `-v` : 상세 정보 출력
    - `-q` : 최소한 정보 출력
    - `-s` : 테스트 중 발생되는 stdout, stderr 출력을 콘솔에 바로 출력
    - `-k <표현식>` : args로 입력되는 표현식과 일치하는 테스트 함수만 실행 
    - `-m <마커>` : args로 입력되는 마커만 실행
    - `--lf` : 이전에 실패한 테스트만 실행
    - `--ff` : 이전에 실패한 테스트 우선 실행, 그리고 나머지 테스트 진행
    - `-x` : 첫 번째 실패 시 즉시 중단
    - `--maxfile=<num>` : num만큼 실패 시 중단
    - `--durations=<num>` : 가장 오래 걸린 num개의 테스트 시간 출력
    - `-n <num>` : num개로 테스트 병렬 처리 
    - `--cov=<package/module name>` : 코드 커버리지 측정 (`pytest-cov` 설치 필요, `--cov-report=<type>` 추가 시 커버리시 보고서 형식 지정하여 생성)
