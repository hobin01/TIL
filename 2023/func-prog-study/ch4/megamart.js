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