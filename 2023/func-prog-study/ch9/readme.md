ch9

추상화 벽 (abstraction barrier) : 세부 구현을 감춘 함수로 이루어진 계층

추상화 벽 : 데이터의 구체적인 구조를 몰라도 함수를 사용하는 것을 의미

(일종의 API와 비슷. API 사용 시 API 개발자는 API로 뭘 할려고 하는 지 신경쓰지 않음. 또한 API 갖다 쓰는 사람도 API가 하는 기능만 적절하게 수행되면 그대로 갖다 쓰면 됨.)

```javascript
// 기존 배열로 탐색하는 것은 비효율적 => 해시맵 기반으로 변경
// 함수가 수행하는 기능은 변경하지 않고 효율적으로 함수 내부를 변경
// 그러한 함수들 : 추상화 벽 

function add_item(cart, item) {
    return objectSet(cart, item.name, item);
}

function calc_total(cart) {
    var total = 0;
    var names = Object.keys(cart);
    for(var i = 0; i < names.length; i++) {
        var item = cart[names[i]];
        total += item.price;
    }
    return total;
}

function setPriceByName(cart, name, price) {
    if(isInCart(cart, name)) {
        var item = cart[name];
        var copy = setPrice(item, price);
        return objectSet(cart, name, copy);
    } else {
        var item = make_item(name, price);
        return objectSet(cart, name, item);
    }
}

function remove_item_by_name(cart, name) {
    return objectDelete(cart, name);
}

function isInCart(cart, name) {
    return cart.hasOwnProperty(name);
}
```

추상화 벽 위의 코드는 아래의 코드 상의 데이터 구조에 대해 전혀 신경 쓸 필요가 없다.

하지만 이렇게 구성하려면 설계를 잘 해야 한다.

즉, 어떤 부분을 추상화 벽으로 설정할 것이며, 설계한 부분에서 추상화 벽을 가로지르는 부분이 없는 지 검토해야 한다.

---

작은 인터페이스 (minimal interface) : 인터페이스를 최소화하면 하위 계층에 불필요한 기능이 쓸데없이 커지는 것을 막을 수 있다.

시계 할인 예제

```javascript
// 작은 인터페이스
// 새로운 기능을 추가할 때 추상화 벽에 새로운 기능을 넣는 것이 아닌
// 추상화 벽 위의 계층에 추상화 벽의 기능을 이용해서 새로운 기능을 추가
// 즉, 인터페이스 개수를 최소화

// 시계 할인 예제 
// 100 달러 이상 장바구니에 있고, 시계를 담았을 때 할인을 알려주는 조건문을 만들어주세요.

// 1. 추상화 벽에 만들기
function getsWatchDiscount(cart) {
    var total = 0;
    var names = Object.keys(cart);
    for(var i = 0; i < names.length; i++) {
        var item = cart[names[i]];
        total += item.price;
    }
    return total > 100 && cart.hasOwnProperty("watch");
}

// 2. 추상화 벽 위에 만들기
// 현재 calcTotal, isInCart 가 추상화벽에 존재하는 함수들 
function getsWatchDiscount(cart) {
    var total = calcTotal(cart);
    var hasWatch = isInCart("watch");
    return total > 100 && hasWatch;
}
```

중간에 코드를 삽입하게 된다면 어디서 삽입하는 것이 좋을까

이 때도 마찬가지로 추상화 벽 위에서 삽입하는 것이 좋음

추상화 벽에 삽입 시, 아래 예제와 같이 기존에 계산이었던 부분이 액션으로 변경되고, 

액션이 코드 전체로 퍼질 수 있음.

```javascript
// 액션 기능을 수행하는 코드를 중간에 삽입
// 로그를 남기는 함수 logAddToCart() 를 구현한 상황
// 장바구니에 담긴 아이템에 대한 로그를 남김
// 어디서 해당 함수를 호출?

// 아래와 같이 add_item에서 호출 시, 계산이었던 add_item이 액션으로 변경
// 로그를 남기는 것 자체는 액션이기 때문
// 그렇게 되면 add_item을 호출하는 모든 곳으로 액션이 퍼짐
function add_item(cart, item) {
    logAddToCart(global_user_id, item);
    return objectSet(cart, item.name, item);
}

// 따라서 기존에 액션이었던 함수에서 로그 기록을 호출 
function add_item_to_cart(name, price) {
    var item = make_cart_item(name, price);
    shopping_cart = add_item(shopping_cart, item);
    var total = calc_total(shopping_cart);
    set_cart_total_dom(total); // DOM에 반영
    update_shipping_icons(shopping_cart); // 무료 배송 아이콘 추가 여부 
    update_tax_dom(total); // 세금 업데이트 
    logAddToCart(global_user_id, item); // 로그 기록
}
```

--- 

편리한 계층 (confortable layer) : 언제 패턴을 적용하고 언제 패턴 적용을 멈출 지 실용적인 방법

=> 현재 작업 중인 코드가 편리하다? 설계는 조금 멈춰도 됨 (충분히 설계가 잘 이루어졌기 때문)

=> 현재 작업 중인 코드가 너무 많은 것을 알고 있거나 지저분하다? 다시 앞선 패턴들을 적용

