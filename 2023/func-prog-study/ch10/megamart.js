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

// 필드에 문자열을 넣을 수 있다면, 문자열 오타 발생 시 버그 발생
// 이러한 것 대처를 위해 올바른 필드인지 검사하는 부분 추가 
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

// operateOnArray가 사실상 자바스크립트의 foreach와 동일하므로 이로 변경
function forEach(array, f) {
    for(var i = 0; i < array.length; i++) {
        var item = array[i];
        f(item);
    }
}

forEach(foods, cookAndEat);
forEach(dishes, clean);

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
