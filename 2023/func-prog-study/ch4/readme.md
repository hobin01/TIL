ch4

액션에서 계산 빼내기 (리펙토링)

일반적으로 돌아가게 만 만든 기능들 

```javascript
// megamart.js

// 장바구니 제품, 금액에 대한 전역변수
var shopping_cart = [];
var shopping_cart_total = 0;
// 전역값은 변경될 수 있으므로 액션

// 카트에 아이템 추가 (액션)
function add_item_to_cart(name, price) {
    shopping_cart.push({
        name: name,
        price: price,
    });
    calc_cart_total();
}
// 전역값을 바꾸므로 액션 

// 전체 카트에 담긴 금액 계산 (액션)
function calc_cart_total() {
    shopping_cart_total = 0;
    for(var i = 0; i < shopping_cart.length; i++) {
        var item = shopping_cart[i];
        shopping_cart_total += item.price;
    }
    set_cart_total_dom(); // DOM에 반영
    update_shipping_icons(); // 무료 배송 아이콘 추가 여부 
    update_tax_dom(); // 세금 업데이트 
}
// 전역값 변경 및 DOM 업데이트하므로 액션

// 구매 합 20 달러 이상인 경우, 무료 배송 아이콘 추가 (액션)
function update_shipping_icons() {

    // DOM으로부터 현재 페이지에 있는 모든 아이템 정보 가져와서 20달러 넘는 지 확인
    var buy_buttons = get_buy_buttons_dom();
    for(var i = 0; i < buy_buttons.length; i++) {
        var button = buy_buttons[i];
        var item = button.item;
        if(item.price + shopping_cart_total >= 20)
            button.show_free_shipping_icon();
        else 
            button.hide_free_shipping_icon();
    }
}
// 전역값 읽기 및 DOM 읽기하므로 액션

// 세금 계산 (액션)
function update_tax_dom() {
    set_tax_dom(shopping_cart_total * 0.10);
}
// 전역값 읽기 및 DOM 업데이트하므로 액션 
```

리팩토링 불가능한 케이스
- 전역값이 아닌, DB에서 값을 호출하여 사용하는 경우
- DOM을 사용하지 않는 경우

해당 케이스들은 다수 발생 가능한 경우

---

function에 암묵적 입출력이 있는 경우 : 모두 액션 

명시적 입력 : 파라미터

암묵적 입력 : 파라미터 외 다른 입력 (전역 읽기 등)

명시적 출력 : 리턴값

암묵적 출력 : 리턴값 외 다른 출력 (console.log 등)

위에서 작성한 megamart.js에 대해 암묵적 입출력을 모두 제외시켜서 액션에서 계산을 분리

```javascript
// megamart_refactoring.js

// 장바구니 제품, 금액에 대한 전역변수
// 전역값은 변경될 수 있으므로 항상 액션 (mutable한 경우)
var shopping_cart = [];
var shopping_cart_total = 0;

// 카트에 아이템 추가 (액션)
function add_item_to_cart(name, price) {
    // 전역을 직접 수정하지 않고, add_item의 리턴값으로 수정
    shopping_cart = add_item(shopping_cart, name, price)
    calc_cart_total();
}

// 전체 카트에 담긴 금액 (액션)
function calc_cart_total() {
    // 전역을 직접 수정하지 않고 calc_total의 인자 및 리턴값으로 수정 
    shopping_cart_total = calc_total(shopping_cart);
    set_cart_total_dom(); // DOM에 반영
    update_shipping_icons(); // 무료 배송 아이콘 추가 여부 
    update_tax_dom(); // 세금 업데이트 
}

// 구매 합 20 달러 이상인 경우, 무료 배송 아이콘 추가 (액션)
function update_shipping_icons() {

    // DOM으로부터 현재 페이지에 있는 모든 아이템 정보 가져와서 20달러 넘는 지 확인
    var buy_buttons = get_buy_buttons_dom();
    for(var i = 0; i < buy_buttons.length; i++) {
        var button = buy_buttons[i];
        var item = button.item;
        if(gets_free_shipping(shopping_cart_total, item.price))
            button.show_free_shipping_icon();
        else 
            button.hide_free_shipping_icon();
    }
}

// 세금 계산 : DOM만 업데이트 (액션)
function update_tax_dom() {
    set_tax_dom(calc_tax(shopping_cart_total));
}

// 카트에 아이템 추가 (계산)
function add_item(cart, name, price) {
    var new_cart = cart.slice(); // cart에 대해 복사본 생성
    new_cart.push({
        name: name,
        price: price,
    });
    return new_cart;
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
function gets_free_shipping(total, item_price) {
    return total + item_price >= 20;
}

// 세금 계산 (계산)
function calc_tax(amout) {
    return amout * 0.10;
}
```

암묵적 입출력을 빼내기 = 계산 추출하기 

전역값을 사용하지 않았는지, DOM 등 호출 시점에 따라 달라지는 상황이 없는 지 등

암묵적 입출력을 빼내야 한다. 

즉, 계산을 원하는 부분에서는 암묵적 입출력이 없어야 한다.

### 액션에서 계산 빼내기

1. 계산 코드를 찾아 빼낸다.
2. 새 함수에 암묵적 입출력을 찾는다.
3. 암묵적 입력은 인자로, 암묵적 출력은 리턴값으로 변경한다.

