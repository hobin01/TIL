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