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