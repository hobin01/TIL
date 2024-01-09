ch 16

안전하게 자원을 공유할 수 있는 동시성 기본형 (concurrency primitive)

좋은 타임라인 원칙

1. 타임라인은 적을수록 이해하기 쉽다.
- 타임라인 수를 줄이면 시스템을 이해하기 더 쉽다.

2. 타임라인은 짧을수록 이해하기 쉽다.
- 타임라인 단계를 줄이면 실행 가능한 순서를 많이 줄일 수 있다.

3. 공유하는 자원이 적을수록 이해하기 쉽다.
- 자원을 공유하는 단계만 조심하면 된다. 
- 자원을 공유하는 단계를 줄이면 가능한 순서를 줄일 수 있다.

4. 자원을 공유한다면 서로 조율해야 한다.
- 여전히 없앨 수 있는 공유 자원은 남게 된다.
- 타임라인은 공유 자원을 안전하게 공유할 수 있어야 한다.
- 안전하게 공유하는 것은 올바른 순서대로 자원을 쓰고 돌려준다는 의미이다.
- 타임라인을 조율하는 것은 실행 가능한 순서를 줄인다는 것을 의미한다.

5. 시간을 일급으로 다룬다.
- 액션의 순서와 타이밍을 맞추기는 어렵다.
- 타임라인을 관리하는 재사용 가능한 객체를 만들면 타이밍 문제를 해결할 수 있다.

현재 구성된 타임라인

첫 번째 클릭 : cart 읽기 > cart 쓰기 > cart 읽기 > cost_ajax() 호출 >> shipping_ajax() 호출 >> DOM 업데이트

두 번째 클릭 : cart 읽기 > cart 쓰기 > cart 읽기 > cost_ajax() 호출 >> shipping_ajax() 호출 >> DOM 업데이트

```javascript
// 원래 코드

function add_item_to_cart(item) {
    cart = add_item(cart, item);
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

두 번째 클릭 이벤트는 첫 번쨰 클릭의 shipping_ajax() 와 같이 실행됨

하지만 이러한 경우에도 DOM 업데이트 순서에 차이 발생 가능

즉, 두 번째 클릭에 의한 DOM 업데이트가 먼저 발생하면 이전 DOM으로 덮어써지게 됨

따라서 DOM 업데이트를 큐에 넣음으로써 실행 결과를 보존하도록 한다.

---

동시성 기본형 : 자원을 안전하게 공유할 수 있는 재사용 가능한 코드

큐를 타임라인 조율에 사용한다면 동시성 기본형으로 사용 가능

기존 타임라인 : cart 읽기 > cart 쓰기 > cart 읽기 > cost_ajax() 호출 >> shipping_ajax() 호출 >> DOM 업데이트

cost_ajax() 가 비동기 호출이기 때문에 cost_ajax() 호출 전 핸들러를 끝내고 큐에 추가

원하는 다이어그램

첫 번째 클릭 : cart 읽기 > cart 쓰기 > cart 읽기 > 큐에 추가

두 번째 클릭 : (첫 번째 클릭 이벤트 완료 후) cart 읽기 > cart 쓰기 > cart 읽기 > 큐에 추가

첫 번째 클릭 DOM : (첫 번쨰 클릭 이벤트 완료 후) 큐에서 꺼내기 > cost_ajax() 호출 > shipping_ajax() 호출 > DOM 업데이트

두 번째 클릭 DOM : (두 번째 클릭 이벤트 완료 후) 큐에서 꺼내기 > cost_ajax() 호출 > shipping_ajax() 호출 > DOM 업데이트

위와 같이 DOM 순서가 꼬이지 않는 것이 목표

```javascript
// 동시성 기본형 코드

function add_item_to_cart(item) {
    cart = add_item(cart, item);
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

function Queue() {
    var queue_items = [];
    var working = false;

    function runNext() {
        if(working)
            return;
        if(queue_items.length === 0)
            return;
        working = true;
        var cart = queue_items.shift();
        calc_cart_total(cart, function(total) {
            update_total_dom(total);
            working = false;
            runNext();
        });
    }

    return function(cart) {
        queue_items.push(cart);
        setTimeout(runNext, 0);
    }
}

var update_total_queue = Queue();
```

큐를 좀 더 일반적인 형태로 변경하기

```javascript
// 큐를 일반적인 형태로 변경

function add_item_to_cart(item) {
    cart = add_item(cart, item);
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

function Queue(worker) {
    var queue_items = [];
    var working = false;

    function runNext() {
        if(working)
            return;
        if(queue_items.length === 0)
            return;
        working = true;
        var item = queue_items.shift();
        worker(item.data, function(val) {
            working = false;
            setTimeout(item.callback, 0, val);
            runNext();
        });
    }

    return function(data, callback) {
        queue_items.push({
            data: data,
            callback: callback || function() {}
        });

        setTimeout(runNext, 0);
    }
}

function calc_cart_worker(cart, done) {
    calc_cart_total(cart, function(total) {
        update_total_dom(total);
        done(total);
    });
}

var update_total_queue = Queue(calc_cart_worker);
```
