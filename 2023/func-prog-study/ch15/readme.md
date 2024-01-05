ch15

타임라인 다이어그램으로 코드 관리하기

현재 빠르게 두 번 cart에 item 담기하는 경우, total이 제대로 계산되지 않는 버그 있다고 가정

아래는 버그가 존재하는 코드

```javascript
// cart, total : 전역값
function add_item_to_cart(name, price, quantity) {
    cart = add_item(cart, name, price, quantity);
    calc_cart_total();
}

function calc_cart_total() {
    total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
        shipping_ajax(cart, function(shipping) {
            total += shipping;
            update_total_dom(total);
        });
    });
}
```

타임라인 다이어그램 구분하는 방법

1. 액션 확인
2. 순서대로 실행되는 지, 동시에 실행되는 액션인지 구분
3. 다이어그램 그리기

위 내용에 대해 타임라인 구분하기

1. cart 읽기 (add_item 파라미터) 
2. cart 쓰기 (cart = )
3. total 쓰기 (total = 0)
4. cart 읽기 (cost_ajax 파라미터)
5. cost_ajax() 호출
6. total 읽기 (total += cost)
7. total 쓰기 (total += cost)
8. cart 읽기 (shipping_ajax 파라미터)
9. shipping_ajax() 호출
10. total 읽기 (total += shipping)
11. total 쓰기 (total += shipping)
12. total 읽기 (update_total_dom 파라미터)
13. update_total_dom() 호출

위 케이스에서는 ajax의 비동기 처리로 인해 내부의 total 업데이트가 제대로 이루어지지 않을 수 있음

아래는 ajax 비동기 처리로 인해 에러 발생할 수 있는 간단한 예제

(그리고 js 자체가 기본적으로 비동기 처리)

```javascript
saveUserAjax(user, function() {
    setUserLoadingDOM(false);
});
setUserLoadingDOM(true);

saveDocumentAjax(document, function() {
    setDocLoadingDOM(false);
});
setDocLoadingDOM(true);

// 위 케이스에서는 setUserLoadingDOM(true), setDocLoadingDOM(true) 실행 이후
// false가 실행될 수 있음
```

따라서 각 타임라인에 대해 순서대로 진행이 필요한 경우

타임라인을 합쳐야 함

즉, 액션에 따른 타임라인이 최소화되어야 함

순서대로 진행될 필요가 있는 액션의 경우, 동일 타임라인 내에서 돌아가도록 코드 작성해야 함

---

좋은 타임라인의 원칙

1. 타임라인은 적을수록 이해하기 쉽다.

모든 케이스에서 타임라인을 하나로 처리할 수는 없다. 멀티스레드, 비동기 콜백 등 여러 상황이 존재 가능하지만 최대한 적게 타임라인을 구성하는 것이 좋다. 

가능한 실행 순서 공식

o = (t*a)! / (a!)^t

(t : 타임라인 수, a : 타임라인 당 액션 수)

2. 타임라인은 짧을수록 이해하기 쉽다.

타임라인 당 액션 수를 줄임으로써 실행 가능한 순서의 수를 줄일 수 있다.

3. 공유하는 자원이 적을수록 이해하기 쉽다.

두 액션이 자원을 공유하지 않는다면 실행 순서에 신경 쓸 필요가 없다. 따라서 여러 타임라인에 대해 공유하는 자원이 있는 지 신경써야 한다.

4. 자원을 공유한다면 조율해야 한다.

타임라인은 공유 자원을 안전하게 공유해야 한다. 안전한 자원 공유란, 자원을 쓴 다음 반환해야 함을 의미한다.

5. 시간을 일급으로 다룬다.

타임라인을 다루는 재사용 가능한 객체를 만들면 타이밍 문제를 쉽게 해결할 수 있다.

---

타임라인 올바르게 그리기

```javascript
saveUserAjax(user, function() {
    setUserLoadingDOM(false);
});
setUserLoadingDOM(true);

saveDocumentAjax(document, function() {
    setDocLoadingDOM(false);
});
setDocLoadingDOM(true);
```

위 예제에서 타임라인 순서는 다음과 같음

1. saveUserAjax() 호출
   1. ajax 비동기 호출로 setUserLoadingDOM(false) 호출
2. setUserLoadingDOM(true) 호출
3. saveDocumentAjax() 호출
   1. ajax 비동기 호출로 setDocLoadingDOM(false) 호출
4. setDocLoadingDOM(true) 호출

위 예에서 올바르게 동작 원하는 것은 다음과 같음

saveUserAjax -> setUserLoadingDOM(true)
saveDocumentAjax -> setDocLoadingDOM(true)

따라서 타임라인 구성이 다음과 같아야 함

1. saveUserAjax() -> setUserLoadingDOM(true) -> saveDocumentAjax() -> saveDocLoadingDOM(true)

1. setUserLoadingDOM(false)
   
1. setDocLoadingDOM(false)

위 3개가 별도의 타임라인으로 구성되어야 한다.

그리고 setUserLoadingDOM, setDocLoadingDOM은 순서에 상관없으므로, 하나의 타임라인으로 병합하면 된다.

---

이를 원래 예제에 적용

1. cart 읽기 (add_item 파라미터) 
2. cart 쓰기 (cart = )
3. total 쓰기 (total = 0)
4. cart 읽기 (cost_ajax 파라미터)
5. cost_ajax() 호출
6. total 읽기 (total += cost)
7. total 쓰기 (total += cost)
8. cart 읽기 (shipping_ajax 파라미터)
9. shipping_ajax() 호출
10. total 읽기 (total += shipping)
11. total 쓰기 (total += shipping)
12. total 읽기 (update_total_dom 파라미터)
13. update_total_dom() 호출

- 하나의 타임라인에 있는 모든 액션을 하나로 통합

1. cart 읽기 (1) -> cart 쓰기 (2) -> total 쓰기 (3) -> cart 읽기 (4) -> cost_ajax() 호출 (5)
2. total 읽기 (6) -> total 쓰기 (7) -> cart 읽기 (8) -> shipping_ajax() 호출 (9)
3. total 읽기 (10) -> total 쓰기 (11) -> total 읽기 (12) -> update_total_dom() 호출 (13)

- 타임라인이 끝나는 곳에 새로운 타임라인이 생기면 통합
  
위의 1,2,3 순으로 타임라인 구성

따라서 위의 1,2,3 순으로 타임라인이 구성되며, ajax와 같이 비동기처리하는 과정에 따라 빠르게 클릭하면 에러 발생 가능

즉, 빠르게 두 번 클릭했을 때 첫 번째 클릭의 total 읽기가 시작될 지, 두 번째 클릭의 cart 읽기부터 시작할 지 모름

해결 방법 

1. 공유 중인 자원인 전역 변수를 지역 변수로 수정

```javascript
function add_item_to_cart(name, price, quantity) {
    cart = add_item(cart, name, price, quantity);
    calc_cart_total();
}

function calc_cart_total() {
    var total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
        shipping_ajax(cart, function(shipping) {
            total += shipping;
            update_total_dom(total);
        });
    });
}
```

2. 전역 변수를 파라미터로 설정

```javascript
// 2. 전역변수 인자로 변경
function add_item_to_cart(name, price, quantity) {
    cart = add_item(cart, name, price, quantity);
    calc_cart_total(cart);
}

function calc_cart_total(cart) {
    var total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
        shipping_ajax(cart, function(shipping) {
            total += shipping;
            update_total_dom(total);
        });
    });
}
```

3. 공유 자원을 리턴값으로 구성

```javascript
// 3. DOM 업데이트 대신 total을 리턴하도록 구성
function add_item_to_cart(name, price, quantity) {
    cart = add_item(cart, name, price, quantity);
    calc_cart_total(cart, update_total_dom);
}

function calc_cart_total(cart, callback) {
    var total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
        shipping_ajax(cart, function(shipping) {
            total += shipping;
            callback(total);
        });
    });
}
```
