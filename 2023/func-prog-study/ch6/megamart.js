// copy-on-write

// 아래 예제에서 shopping_cart가 전역에 선언되어 있다 가정

// splice() 메서드를 사용 시에만 호출하도록
// copy-on-write 로 array에 직접 쓰지 않고 복사 후 쓰고 리턴
function removeItems(array, idx, count) {
    var copy = array.slice();
    copy.splice(idx, count);
    return copy;
}

// name 일치하는 item을 cart에서 제거
function remove_item_by_name(cart, name) {
    var idx = null;
    for(var i = 0; i < cart.length; i++) {
        if(new_cart[i].name === name)
            idx = i;
    }
    if(idx != null)
        return removeItems(cart, idx, 1);
    return cart; // 제거할 대상 없으면 불필요한 복사 할 필요 없음
}

function delete_handler(name) {
    shopping_cart = remove_item_by_name(shopping_cart, name);
    var total = calc_total(shopping_cart);
    set_cart_total_dom(total);
    update_shipping_icons(shopping_cart);
    update_tax_dom(total);
}

// 새로운 메일 추가
// 여기서는 mailing_list가 전역에 있다고 가정
// copy-on-write 적용
function add_contact(mailing_list, email) {
    var list_copy = mailing_list.slice();
    list_copy.push(email);
    return list_copy;
}

function submit_form_handler(event) {
    var form = event.target;
    var email = form.elements["email"].value;
    mailing_list = add_contact(mailing_list, email);
}

// 쓰기, 읽기 동시에 수행하는 함수 분리하기
// 1. 쓰기, 읽기 분리

// 원래 .shift() 메서드는 첫 번째 element 리턴하고, 첫 번째 element 삭제된 배열을 생성
// 읽기, 쓰기로 분리

// 읽기 동작
function first_element(array) {
    return array[0];
}
// 쓰기 동작 (기존 리턴을 무시)
// copy-on-write
function drop_first(array) {
    var array_copy = array.slice();
    array_copy.shift();
    return array_copy;
}

// 2. 읽으면서 쓰도록 리턴값 2개로 분리
function shift(array) {
    var array_copy = array.slice();
    var first = array_copy.shift();
    return {
        first: first,
        array: array_copy,
    };

    // 또는 위에서 작성한 함수 기반으로 아래와 같이 작성해도 무관
    /*
    return {
        first: first_element(array),
        array: drop_first(array),
    }
    */
}

// pop의 경우를 분리
// 읽기, 쓰기 분리 
function last_element(array) {
    return array[array.length - 1];
}
function drop_last(array) {
    var array_copy = array.slice();
    array_copy.pop();
    return array_copy;
}

// 읽기, 쓰기 리턴 값 2개 
function pop(array) {
    var array_copy = array.slice();
    var last = array_copy.pop();
    return {
        last: last,
        array: array_copy,
    };
}

// push의 경우
function push(array, element) {
    var array_copy = array.slice();
    array_copy.push(element);
    return array_copy;
}

// add_contact를 리팩토링
function add_contact(mailing_list, email) {
    return push(mailing_list, email);
}

// 객체에 대한 copy-on-write
// js 기준 : object에 대한 copy : .assign() 메서드 
// 어디서든 쓸 수 있도록 리팩토링
function objectSet(object, key, value) {
    var copy = Object.assign({}, object);
    copy[key] = value;
    return copy;
}

// item의 가격 변경
function setPrice(item, new_price) {
    return objectSet(item, "price", new_price);
}

// item의 수량 변경 
function setQuantity(item, new_quantity) {
    return objectSet(item, "quantity", new_quantity);
}

// 중첩된 데이터 구조에 대해 쓰기를 읽기로 변경
// 기존 코드
// cart라는 값을 직접적으로 변경
// cart라는 배열 아래에는 name, price 키를 갖는 객체 저장
// 중첩된 데이터 구조
// 여기서 직접적으로 값을 바꾸게 되면 cart, 그 아래 데이터를 가리키는 다른 값들도 다 변경됨 
function setPriceByName(cart, name, price) {
    for(var i = 0; i < cart.length; i++) {
        if(cart[i].name === name)
            cart[i].price = price;
    }
}

// copy-on-write 적용
function setPriceByName(cart, name, price) {
    var cartCopy = cart.slice();
    for(var i = 0; i < cartCopy.length; i++) {
        if(cartCopy[i].name === name)
            setPrice(cartCopy[i], price);
    }
    return cartCopy;
}