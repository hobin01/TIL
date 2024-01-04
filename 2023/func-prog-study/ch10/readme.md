ch 10

일급함수란? 어디에 쓰고 어떻게 만드는가?

코드의 냄새와 중복을 없애 추상화를 잘 할 수 있는 리팩토링 기법 2개

코드의 냄새 : 함수 이름에 있는 암묵적 인자
1. 거의 똑같이 구현된 함수가 있다.
2. 함수 이름이 구현에 있는 다른 부분을 가리킨다.

리팩토링 : 암묵적 인자 드러내기
1. 함수 이름에 있는 암묵적 인자를 확인
2. 명시적인 인자 추가
3. 하뭇 본문에 하드코딩된 값을 인자로 변경 
4. 함수 호출하는 곳 수정

리팩토링 : 함수 본문을 콜백으로 바꾸기
1. 함수 본문의 바꿀 부분의 앞뒤 부분 확인
2. 리팩토링 할 코드를 함수로 빼내기
3. 빼낸 함수의 인자로 넘길 부분을 또 다른 함수로 빼내기 

---

현재 요구받은 요구사항

1. 장바구니 제품 값 설정
2. 장바구니 제품 개수 설정
3. 장바구니 제품 배송 설정
4. 장바구니 제품 세금 설정

```javascript
function setPriceByName(cart, name, price) {
    var item = cart[name];
    var newItem = objectSet(item, 'price', price);
    var newCart = objectSet(cart, name, newItem);

    return newCart;
}

function setQuantityByName(cart, name, quantity) {
    var item = cart[name];
    var newItem = objectSet(item, 'quantity', quantity);
    var newCart = objectSet(cart, name, newItem);

    return newCart;
}

function setShippingByName(cart, name, ship) {
    var item = cart[name];
    var newItem = objectSet(item, 'ship', ship);
    var newCart = objectSet(cart, name, newItem);

    return newCart;
}

function setTaxByName(cart, name, tax) {
    var item = cart[name];
    var newItem = objectSet(item, 'tax', tax);
    var newCart = objectSet(cart, name, newItem);

    return newCart;
}

```

위와 같이 요구사항은 거의 비슷하며, 필드만 다른 경우 : 사실상 동일한 애들 

=> 문제점 : 중복이 너무 많음 

=> 그리고 함수 이름에 인자가 섞여 있어 반드시 해당 필드만 써야 할 거 같음

=> 필드를 일급으로 구성하여 인자로 넘기면 된다!

```javascript
// 위와 같이 중복이 많은 함수를 필드라는 것으로 통일
// 즉, 암묵적 인자를 드러내 명시적 인자 (괄호 안 파라미터) 로 추가
function setFieldByName(cart, name, field, value) {
    var item = cart[name];
    var newItem = objectSet(item, field, value);
    var newCart = objectSet(cart, name, newItem);

    return newCart;
}

// field, value 모두에 쓰일 수 있는 것들 ""로 처리 
cart = setFieldByName(cart, "shoe", 'price', 13);
cart = setFieldByName(cart, "shoe", 'quantity', 3);
cart = setFieldByName(cart, "shoe", 'shipping', 0);
cart = setFieldByName(cart, "shoe", 'tax', 2.34);
```

암묵적 인자 드러내기 : setTaxByName 처럼 함수 이름에 암묵적인 인자를 () 안의 파라미터에 명시적 인자로 추가

일급 (first-class) : 언어에 있는 다른 값처럼 쓸 수 있는 것 (변수, 배열 등에 저장 가능)

일급으로 할 수 있는 것
1. 변수에 할당
2. 함수 인자로 넘기기
3. 함수 리턴값
4. 배열이나 객체에 담기

자바스크립트에서 일급인 것 : 숫자, 문자열, 배열, 객체 등

자바스크립트에서 일급이 아닌 것 : 사칙연산자, if, for 문 등 

```javascript
// 필드에 문자열을 넣을 수 있다면, 문자열 오타 발생 시 버그 발생
// 이러한 것 대처를 위해 올바른 필드인지 검사하는 부분 추가 
var validItemFields = ['price', 'quantity', 'shipping', 'tax'];

function setFieldByName(cart, name, field, value) {
    if(!validItemFields.includes(field)) {
        throw "Not a valid item field: " + "'" + field + "'.";
    }
    
    var item = cart[name];
    var newItem = objectSet(item, field, value);
    var newCart = objectSet(cart, name, newItem);

    return newCart;
}
```

위와 같이 구현하면 필드명이 추상화벽 위로 노출된 것 아닌가?

=> 구현이 외부로 노출된 것은 아니다.

=> 어떤 이유에서 특정 필드가 바뀐 경우는 추상화벽 아래에서 처리 가능

예를 들어 quantity 필드가 number로 변경된 경우 다음과 같이 처리 가능

```javascript
var validItemFields = ['price', 'quantity', 'shipping', 'tax'];
var translations = {'quantity' : 'number'};

function setFieldByName(cart, name, field, value) {
    if(!validItemFields.includes(field)) {
        throw "Not a valid item field: " + "'" + field + "'.";
    }

    if(translations.hasOwnProperty(field)) {
        field = translations[field];
    }

    var item = cart[name];
    var newItem = objectSet(item, field, value);
    var newCart = objectSet(cart, name, newItem);

    return newCart;
}
```

---

일급 필드 사용 시 코드에 객체를 너무 많이 사용되게 됨

하지만 일반적으로 많이 사용되는 entity는 재사용을 할 수 있어야 하므로 일반적인 형식을 지향해야 함 : 데이터 지향 (이벤트와 엔티티에 대한 사실을 표현하기 위해 일반 데이터 구조를 사용하는 프로그래밍 형식)

---

일급 (first-class) : 인자로 전달 가능한 것

일급 함수 : 인자로 전달 가능한 함수

고차 함수(higher-order function) : 인자로 함수를 받거나 리턴값으로 함수를 리턴할 수 있는 함수

=> 반복문 같은 것을 고차 함수를 이용해 표현이 가능할 것인가?

=> 콜백으로 바꾸기 를 통해 가능 

```javascript
// 반복문을 고차 함수로 변경 예제

// 준비하고 먹기 
function cookAndEatFoods() {
    for(var i = 0; i < foods.length; i++) {
        var food = foods[i];
        cook(food);
        eat(food);
    }
}

function cleanDishes() {
    for(var i = 0; i < dishes.length; i++) {
        var dish = dishes[i];
        wash(dish);
        dry(dish);
        putAway(dish);
    }
}
```

위 예에서 현재 공통인 부분 : 배열에서 값 불러오기 

```javascript
// 현재 공통으로 있는 배열에서 불러오는 부분을 일반화
function cookAndEatFoods(array) {
    for(var i = 0; i < array.length; i++) {
        var item = array[i];
        cook(item);
        eat(item);
    }
}

function cleanDishes(array) {
    for(var i = 0; i < array.length; i++) {
        var item = array[i];
        wash(item);
        dry(item);
        putAway(item);
    }
}
```

반복문 내의 함수를 밖으로 빼기

```javascript
// 반복문 안의 본문 분리
function cookAndEatFoods(array) {
    for(var i = 0; i < array.length; i++) {
        var item = array[i];
        cookAndEat(item);
    }
}

function cookAndEat(food) {
    cook(food);
    eat(food);
}

function cleanDishes(array) {
    for(var i = 0; i < array.length; i++) {
        var item = array[i];
        clean(item);
    }
}

function clean(dish) {
    wash(dish);
    dry(dish);
    putAway(dish);
}
```

유사한 반복문 구문 일반화

```javascript

// 유사한 반복문 구문 일반화
function operateOnArray(array, f) {
    // f : 인자로 들어오는 함수명 
    for(var i = 0; i < array.length; i++) {
        var item = array[i];
        f(item);
    }
}

operateOnArray(foods, cookAndEat);
operateOnArray(dishes, clean);
```

위의 operateOnArray가 사실상 자바스크립트의 foreach와 동일

```javascript
// operateOnArray가 사실상 자바스크립트의 foreach와 동일하므로 이로 변경
function forEach(array, f) {
    for(var i = 0; i < array.length; i++) {
        var item = array[i];
        f(item);
    }
}

forEach(foods, cookAndEat);
forEach(dishes, clean);
```

위의 forEach는 함수를 인자로 받으므로 고차함수 

고차함수를 만드는 법

1. 코드를 함수로 감싸기
2. 일반적인 이름으로 변경
3. 암묵적 인자 드러내기
4. 함수 추출
5. 암묵적 인자 드러내기 

--- 

콜백으로 고차함수 만들기

```javascript
// 콜백으로 고차함수 만들기
try {
    saveUserData(user);
} catch {
    logToSnapErrors(error);
}

try {
    fetchProduct(productId);
} catch {
    logToSnapErrors(error);
}

// 위 try catch 구문에서 실제 에러 발생 시 동작하는 것은 동일
// 본문은 try 내부 구문
// 따라서 본문을 따로 빼내 함수로 변환 후, 인자로 넘기기 

function withLogging(f) {
    try {
        f();
    } catch(error) {
        logToSnapErrors(error);
    }
}

withLogging(function() {
    saveUserData(user);
});

withLogging(function() {
    fetchProduct(productId);
});
```

꼭 인라인으로 익명 함수로 함수를 인자를 넘기지 않아도 됨

var f = function() {...} 으로 저장해도 되고, 위처럼 직접 넣어도 됨

중요한 것은 함수를 인자로 넘기므로, 함수 호출 이전에 함수 내부 내용이 실행되면 안 된다는 것

즉, withLogging 함수 인자로 saveUserData 함수를 직접 인자로 넣으면 인자로 넘김과 동시에 해당 함수가 실행되므로 try catch 구문 동작 전, 먼저 해당 함수 실행됨. 따라서 이러한 경우, 에러 발생 시, catch 부분이 동작되지 않고 다른 에러 처리가 발생 가능함.