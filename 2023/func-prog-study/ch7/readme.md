ch7

레거시 코드(legacy code) (오래 전에 만들어서 당장 수정 불가능한 코드), 외부 라이브러리 (수정 불가능한 경우)에 대해서는 직접적으로 수정이 불가능하므로 copy-on-write 적용 불가능

=> 방어적 복사(defensive copy)를 적용

안전한 코드 : copy-on-write 규칙에 따라 동작하는 코드

- 방어적 복사 규칙
1. 데이터가 안전한 코드에서 나갈 때 복사 (deep copy)
2. 안전한 코드로 데이터가 들어올 때 복사 (deep copy)

```javascript
shopping_cart = []

function add_item_to_cart(name, price) {
    var item = make_cart_item(name, price);
    shopping_cart = add_item(shopping_cart, item);
    var total = calc_total(shopping_cart);
    set_cart_total_dom(total); // DOM에 반영
    update_shipping_icons(shopping_cart); // 무료 배송 아이콘 추가 여부 
    update_tax_dom(total); // 세금 업데이트 

    // 현재 블랙프라이데이 관련 함수가 레거시 코드라 가정
    // 레거시 코드와 관련된 부분 전후로 방어적 복사 진행 
    shopping_cart = black_friday_promotion_safe(shopping_cart);
}

function black_friday_promotion_safe(cart) {
    var cart_copy = deepCopy(cart);
    black_friday_promotion(cart_copy);
    return deepCopy(cart_copy);
}
```

안전한 코드가 있는 경우, 불필요하게 복사 다시 할 필요는 없음

```javascript
// 아래 예제는 payrollCalc가 함수가 레거시 코드인 경우
/*
function payrollCalc(employees) {
    ...
    return payrollChecks;
}
*/

// 방어적 복사로 변경
function payrollCalcSafe(employees) {
    var copy = deepCopy(employees);
    var payrollChecks = payrollCalc(copy);
    return deepCopy(payrollChecks);
}

// 아래 예제에서 processUser는 안전한 코드라 가정
// 그리고 user 데이터는 모두 메모리 참조로 구성 중
userChanges.subscribe(function(user) {
    var copy = deepCopy(user);
    processUser(copy);
    // processUser가 안전한 코드로 가정했으므로 한 번 더 복사할 필요 없음
});
```

=> 안전한 코드 외의 부분과 데이터 주고 받아야 한다면 방어적 복사를 진행 