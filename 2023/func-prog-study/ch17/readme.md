ch 17

좋은 타임라인 원칙

1. 타임라인은 적을수록 이해하기 쉽다
2. 타임라인은 짧을수록 이해하기 쉽다
3. 공유하는 자원이 적을수록 이해하기 쉽다
4. 자원을 공유한다면 서로 조율해야 한다
5. 시간을 일급으로 다룬다

아래는 현재 ajax 호출 최적화를 위해 수정한 코드

ajax 호출 시점에 따라 total 에 shipping만 기록되고 total 계산이 끝나게 됨

```javascript
// 현재 ajax 호출 최적화를 위해 아래와 같이 구성 중
// shipping_ajax 가 먼저 끝나버리게 되면 total에 shipping만 더해지고
// done으로 끝남

function add_item_to_cart(item) {
    cart = add_item(cart, item);
    update_total_queue(cart);
}

function calc_cart_total(cart, callback) {
    var total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
    });

    shipping_ajax(cart, function(shipping) {
        total += shipping;
        callback(total);
    });
}

function calc_cart_worker(cart, done) {
    calc_cart_total(cart, function(total) {
        update_total_dom(total);
        done(total);
    });
}

var update_total_queue = DroppingQueue(1, calc_cart_worker);
```

원래 total은 전역이었지만 지역변수로 바꿔 계산으로 처리하려 함

하지만 여러 타임라인에서 공유 중

---

자바스크립트 스레드 모델에서 타임라인 단순화하기

1. 하나의 타임라인에 있는 모든 액션을 하나로 통합
2. 타임라인이 끝나는 곳에서 새로운 타임라인이 하나만 생기면 통합

현재 문제점 : ajax가 병렬적으로 처리되기 때문에 shipping_ajax가 끝남과 동시에 dom 업데이트 가능

해결 방안 : ajax 응답이 모두 끝난 다음 dom 업데이트 시키도록 변경

=> 기존 정상 코드는 ajax 응답 자체를 순차적으로 처리
=> 응답 전체 시간이 오래 걸리는 문제점
=> 최적화를 위해서 ajax 따로 처리
=> DOM 업데이트 문제
=> DOM 업데이트만 ajax 모두 끝난 다음 처리하면 ajax 별도 처리에 따른 최적화 효과도 얻을 수 있음

일반적인 멀티스레드 지원 언어는 스레드가 변경 가능한 상태를 공유하기 위해 atomic 업데이트 기능 사용해야 함

하지만 자바스크립트는 단일 스레드 모델이기 때문에 이러한 기능 굳이 사용하지 않아도 됨

Cut : 타임라인 수 카운트하면서 다 끝나면 callback 실행함

문제가 되는 부분인 ajax 타임라인 끝나는 부분에 Cut 함수 실행시키면 됨

```javascript
// Cut : 타임라인 수 카운트하면서 다 끝나면 callback 실행함
function Cut(num, callback) {
    var num_finished = 0;
    return function() {
        num_finished += 1;
        if(num_finished === num)
            callback();
    };
}

function calc_cart_total(cart, callback) {
    var total = 0;
    var done = Cut(2, function() {
        callback(total);
    });

    cost_ajax(cart, function(cost) {
        total += cost;
        done();
    });

    shipping_ajax(cart, function(shipping) {
        total += shipping;
        done();
    });
}
```

