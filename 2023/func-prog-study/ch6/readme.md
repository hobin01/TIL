ch 6

함수형 프로그래밍에서 쓰기 동작은 불변성 원칙에 따라 구현

불변성 원칙 : copy-on-wirte : 복사하고 쓰기

- copy-on-write
1. 복사본 만들기 (copy)
2. 복사본 변경하기 (write)
3. 복사본 리턴하기 (명시적 출력)

```javascript
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
```

쓰기와 읽기를 동시에 하는 메서드의 경우는 2가지 방법으로 분리 가능

1. 쓰기, 읽기를 분리
2. 리턴값을 쓰기, 읽기에 해당하는 것 2가지로 분리

ex) .shift() 메서드 : 리턴은 배열의 첫 번째 element, 그리고 메서드 동작 후 첫 번째 element 삭제된 배열 생성 

```javascript
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
```

copy-on-write 시, 복사 후 쓰기를 진행

하지만 복사에 대한 cost가 생각보다 크지 않음

왜냐면 불변형 데이터 구조를 가질 경우, shallow copy 이용하면 최상위 데이터 외에는 메모리 참조를 공유하게 됨 

shallow copy 시, 공유하는 메모리가 가리키는 값이 변경되면 문제가 되지만, 불변형 데이터를 사용하게 되면 데이터가 변경될 일 없으므로 정상 동작함 

따라서 copy-on-write에 대해 복사에 대한 cost가 크지 않음 

단, 불변형 데이터 타입으로 구성해야 함 

```javascript
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
```

계산 : 변경 가능한 데이터에 쓰기를 할 수 없다.

=> 계산을 위해서는 불변형 데이터를 이용해 copy-on-write를 해야 한다.

=> 함수형 프로그래밍에서는 최대한 계산을 지향한다.

=> 함수형 프로그래밍을 하기 위해서는 불변형 데이터를 이용해 copy-on-write로 구성해야 한다.

클로저, 하스켈 등 함수형 프로그래밍 언어는 기본적으로 copy-on-write를 제공

즉, 기본적으로 쓰기를 동작시킬 때 copy-on-write로 동작함

그렇지 않은 경우는 불변형 데이터를 이용해 copy-on-write를 구현해주어야 함

하지만, 중요한 것은 불변형 데이터로 제어해야 한다는 것

=> 즉, 함수형 프로그래밍 언어가 아닌 언어로 함수형 프로그래밍을 할 시, 
중간에 실수로 데이터 값 변형이 발생되지 않게 주의해야 한다. 

(ex. 인자 값 copy 안 하고 직접적으로 수정, 메모리 참조하는 기본 메서드 그대로 사용 등)

따라서 이러한 경우를 대비와 리팩토링, 보일러 플레이트 코드 (비슷한 동작 반복) 최소화를 위해서 필요한 기본 메서드를 모두 copy-on-write로 변경 후 함수형 프로그래밍을 진행해야 한다.

