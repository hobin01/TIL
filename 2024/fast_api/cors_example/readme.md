CORS (Cross-Origin Resource Sharing)
- 웹 브라우저에서 **다른 도메인의 리소스**에 접근할 수 있도록 허용하는 메커니즘이다.
- 웹 브라우저는 기본적으로 **Same-Origin Policy**를 적용해 다른 도메인으로의 요청을 제한하지만, CORS를 통해 이를 허용할 수 있다.
- CORS는 주로 API 서버에서 설정되며, 응답 헤더를 통해 요청을 허용할 도메인, HTTP 메서드, 헤더 등을 명시한다.
- 주요 설정 항목:
  - `Access-Control-Allow-Origin`: 허용할 도메인
  - `Access-Control-Allow-Methods`: 허용할 HTTP 메서드 (GET, POST 등)
  - `Access-Control-Allow-Headers`: 허용할 요청 헤더 (Content-Type, Authorization 등)
  - `Access-Control-Max-Age`: Preflight 요청 캐시 시간
- Preflight 요청: 비표준 헤더나 메서드 사용 시 서버가 CORS 요청을 허용하는지 미리 확인하는 과정 (OPTIONS 메서드 사용)
