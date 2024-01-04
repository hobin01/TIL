// 넥타이를 사면 넥타이 클립을 제공하고자 하는 코드
// 계층적 문제 :
// 비즈니스 로직 - 넥타이를 사면 넥타이 클립을 준다.
// 비즈니스 로직 상에서 cart가 배열인지 여부 알 필요 없음
// 해당 함수에서는 "넥타이를 산다 => 넥타이 클립을 준다" 라는 것이 중요
function freeTieClip(cart) {
    var hasTie = false;
    var hasTieClip = false;

    for(var i = 0; i < cart.length; i++) {
        var item = cart[i];
        if(item.name === "tie")
            hasTie = true;
        if(item.name === "tie clip")
            hasTieClip = true;
    }

    if(hasTie && !hasTieClip) {
        var tieClip = make_item("tie clip", 0);
        return add_item(cart, tieClip);
    }
    return cart;
}

// 장바구니에 필요한 동작들

// 제품 추가하기
function add_item(cart, item) {
    return add_element_last(cart, item);
}

// 제춤 삭제하기
function remove_item_by_name(cart, name) {
    var idx = null;
    for(var i = 0; i < cart.length; i++) {
        if(cart[i].name === name)
            idx = i;
    }
    if(idx != null)
        return removeItems(cart, idx, 1);
    return cart; // 제거할 대상 없으면 불필요한 복사 할 필요 없음
}

// 장바구니에 제품 있는 지 확인


// 합계 계산
function calc_total(cart) {
    var total = 0;
    for(var i = 0; i < cart.length; i++) {
        var item = cart[i];
        total += item.price;
    }
    return total;
}

// 장바구니 비우기


// 제품 이름으로 가격 설정
function setPriceByName(cart, name, price) {
    var cartCopy = cart.slice();
    for(var i = 0; i < cartCopy.length; i++) {
        if(cartCopy[i].name === name)
            setPrice(cartCopy[i], price);
    }
    return cartCopy;
}

// 세금 계산
function cartTax(cart) {
    return calc_tax(calc_total(cart));
}

// 무료 배송 여부 
function gets_free_shipping(cart) {
    return calc_total(cart) >= 20;
}

//////////////////////////////////////////////////////////////

// freeTieClip 에서 특정 항목 있는 지 여부 검사하는 부분 추출
function isInCart(cart, name) {
    for(var i = 0; i < cart.length; i++) {
        if(cart[i].name === name)
            return true;
    }
    return false;
}

function freeTieClip(cart) {
    var hasTie = isInCart(cart, "tie");
    var hasTieClip = isInCart(cart, "tie clip");

    if(hasTie && !hasTieClip) {
        var tieClip = make_item("tie clip", 0);
        return add_item(cart, tieClip);
    }
    return cart;
}