// 타임라인 다이어그램으로 버그 찾기

// 현재 클릭 빠르게 진행 시 add_cart 결과가 올바르지 않게 되는 버그 있다고 가정
// 아래는 버그가 있는 부분

// cart, total : 전역값
function add_item_to_cart(name, price, quantity) {
    cart = add_item(cart, name, price, quantity);
    calc_cart_total();
}

function calc_cart_total() {
    total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
        shipping_ajax(cart, function(shipping) {
            total += shipping;
            update_total_dom(total);
        });
    });
}

// 타임라인 다이어그램 구분하기 
// 1. 액션 확인
// 2. 순서대로 실행되는 지, 동시에 실행되는 액션인지 구분
// 3. 다이어그램 그리기

// 위 부분의 액션 다이어그램
// 1. cart 읽기 (add_item 파라미터) 
// 2. cart 쓰기 (cart = )
// 3. total 쓰기 (total = 0)
// 4. cart 읽기 (cost_ajax 파라미터)
// 5. cost_ajax() 호출
// 6. total 읽기 (total += cost)
// 7. total 쓰기 (total += cost)
// 8. cart 읽기 (shipping_ajax 파라미터)
// 9. shipping_ajax() 호출
// 10. total 읽기 (total += shipping)
// 11. total 쓰기 (total += shipping)
// 12. total 읽기 (update_total_dom 파라미터)
// 13. update_total_dom() 호출

// ajax는 기본적으로 비동기로 처리
// 그리고 콜백 또한 이전 호출 끝난 이후 아무 때나 실행됨
// 아래는 실행이 꼬일 수 있는 케이스
saveUserAjax(user, function() {
    setUserLoadingDOM(false);
});
setUserLoadingDOM(true);

saveDocumentAjax(document, function() {
    setDocLoadingDOM(false);
});
setDocLoadingDOM(true);

// 위 케이스에서는 setUserLoadingDOM(true), setDocLoadingDOM(true) 실행 이후
// false가 실행될 수 있음

// 현재 에러가 발생하는 이유
// 1. 전역변수를 공유 중
// 이를 위해 지역 변수로 바꿀 수 있는 것들 바꾸기
function add_item_to_cart(name, price, quantity) {
    cart = add_item(cart, name, price, quantity);
    calc_cart_total();
}

function calc_cart_total() {
    var total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
        shipping_ajax(cart, function(shipping) {
            total += shipping;
            update_total_dom(total);
        });
    });
}

// 2. 전역변수 인자로 변경
function add_item_to_cart(name, price, quantity) {
    cart = add_item(cart, name, price, quantity);
    calc_cart_total(cart);
}

function calc_cart_total(cart) {
    var total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
        shipping_ajax(cart, function(shipping) {
            total += shipping;
            update_total_dom(total);
        });
    });
}

// 하지만 위와 같이 진행하여도 아직 DOM을 공유하게 됨

// 3. DOM 업데이트 대신 total을 리턴하도록 구성
function add_item_to_cart(name, price, quantity) {
    cart = add_item(cart, name, price, quantity);
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