ch5

모든 암묵적 입출력을 없애는 것은 실제 설계와 맞지 않음

요구사항을 최대한 충족하면서 최대한 암묵적 입출력을 없애는 것이 중요

또한 각 함수는 하나의 목적을 갖고 동작하도록 계산을 더 작은 계산으로 분리해야 함

예를 들어, 버튼을 클릭해 카트에 아이템을 담고, DOM에 반영하는 함수라는 것은

버튼 클릭 + 카트에 아이템 담기 + DOM 반영 3가지 기능을 가짐

따라서 각 동작을 최대한 분리하도록 구성해야 함

```javascript
// 장바구니 제품, 금액에 대한 전역변수
// 전역값은 변경될 수 있으므로 항상 액션 (mutable한 경우)
var shopping_cart = [];
var shopping_cart_total = 0;

// 카트에 아이템 추가 (액션)
function add_item_to_cart(name, price) {
    var item = make_cart_item(name, price);
    shopping_cart = add_item(shopping_cart, item);
    var total = calc_total(cart);
    set_cart_total_dom(total); // DOM에 반영
    update_shipping_icons(cart); // 무료 배송 아이콘 추가 여부 
    update_tax_dom(total); // 세금 업데이트 
}

// 구매 합 20 달러 이상인 경우, 무료 배송 아이콘 추가 (액션)
// 기존 로직은 여러 역할을 담당 (버튼, DOM 등)
// 이를 분리

// 구매 버튼 관련 동작 
function update_shipping_icons(cart) {
    var buy_buttons = get_buy_buttons_dom();
    for(var i = 0; i < buy_buttons.length; i++) {
        var button = buy_buttons[i];
        var item = button.item;
        var hasFreeShipping = gets_free_shipping_with_item(cart, item);
        set_free_shipping_icon(button, hasFreeShipping);
    }
}

// cart, item 관련 동작
function gets_free_shipping_with_item(cart, item) {
    var new_cart = add_item(cart, item);
    return gets_free_shipping(new_cart);
}

// DOM 관련 동작 
function set_free_shipping_icon(button, isShown) {
    if(isShown)
        button.show_free_shipping_icon();
    else 
        button.hide_free_shipping_icon();
}

// 세금 계산 : DOM만 업데이트 (계산)
function update_tax_dom(total) {
    set_tax_dom(calc_tax(total));
}

// item 객체 생성
// item 계산 역할 담당 
function make_cart_item(name, price) {
    return {
        name: name, 
        price: price,
    };
}

// 배열에 element 추가하는 일반적인 함수
function add_element_last(array, elem) {
    var new_array = array.slice(); // array 카피 후 작업 (copy on write)
    new_array.push(elem);
    return new_array;
}

// 카트에 아이템 추가 (계산)
function add_item(cart, item) {
    return add_element_last(cart, item);
}

// 전체 카트 금액 계산하는 것으로 변경 (계산)
function calc_total(cart) {
    var total = 0;
    for(var i = 0; i < cart.length; i++) {
        var item = cart[i];
        total += item.price;
    }
    return total;
}

// 20달러 넘는 지 계산 (계산)
function gets_free_shipping(cart) {
    return calc_total(cart) >= 20;
}

// 세금 계산 (계산)
function calc_tax(amout) {
    return amout * 0.10;
}
```