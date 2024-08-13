react 공부용 레포

ref 
- https://ko.react.dev/learn
- https://wikidocs.net/book/10082

시작
- npx create-react-app \<app name\>

기본 구조
- node_modules/ : 라이브러리, 모듈 저장소, npm install 로 설치한 거 저장
- public/ : 정적 파일 저장되는 폴더. html, image, icon 등. index.html이 기본 템플릿으로 사용
- src/ : 애플리케이션 소스 코드 저장되는 폴더. 컴포넌트, 스타일, 이미지 파일 등
  - index.js : 리액트 진입점. ReactDom.render() 이용해서 App 컴포넌트를 index.html에 렌더링
  - App.js : 애플리케이션 메인인 App 컴포넌트. 다른 컴포넌트 불러와서 렌더링.
  - App.css : App 컴포넌트 스타일 지정하는 css 파일
  - App.test.js : App 컴포넌트에 대한 테스트 코드 지정
  - reportWebVitals.js : 애플리케이션 성능 측정을 제공