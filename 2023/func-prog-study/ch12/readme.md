ch 12

함수형 프로그래밍에서 반복문 대신 map(), filter(), reduce() 적용하기

우선 앞선 것들 복습

```javascript
function emailsForCustomers(customers, goods, bests) {
    var emails = [];
    for(var i = 0; i < customers.length; i++) {
        var customer = customers[i];
        var email = emailForCustomer(customer, goods, bests);
        emails.push(email);
    }
    return emails;
}

// 위 내용에서 반복문을 forEach로 변경 
function forEach(array, f) {
    for(var i = 0; i < array.length; i++) {
        var item = array[i];
        f(item);
    }
}

function emailsForCustomers(customers, goods, bests) {
    var emails = [];
    forEach(customers, function(customer) {
        var email = emailForCustomer(customer, goods, bests);
        emails.push(email);
    });
    return emails;
}
```

위 내용에서 forEach 구문은 실제로 map()과 동일한 역할

```javascript
// 위 내용과 동일한 map() 구성
function map(array, f) {
    var newArray = [];
    forEach(array, function(element) {
        newArray.push(f(element));
    });
    return newArray;
}

function emailsForCustomers(customers, goods, bests) {
    return map(customers, function(customer) {
        return emailForCustomer(custoer, goods, bests);
    });
}
```

하지만 map에 특정 조건을 만족하는 element만 적용하고 싶다면 null 이 들어갈 수 있음 

이러한 문제 해결 위한 것이 filter

```javascript
// map은 기존 입력 배열과 동일한 길이의 배열을 리턴
// 특정 조건에 맞는 것만 추출할 때 불가능
// 이를 가능하게 하기 위해 filter 구성
// 위 내용과 동일한 filter() 구성
function filter(array, f) {
    var newArray = [];
    forEach(array, function(element) {
        if(f(element)) {
            newArray.push(element);
        }
    });
    return newArray;
}

function selectBestCustomers(customers) {
    return filter(custoers, function(customer){
        return customer.purchases.length >= 3;
    });
}
```

입력과 같은 형 이외에 다른 형을 리턴하는 등의 작업을 하고 싶다면?
reduce 이용하면 됨

```javascript
// map, filter 모두 입력과 동일한 형을 리턴
// 다른 형을 반환하려면? reduce 로 해당 동작을 제어하면 됨
function reduce(array, init, f) {
    var accum = init;
    forEach(array, function(element) {
        accum = f(accum, element);
    });
    return accum;
}

function countAllPurchases(customers) {
    return reduce(customers, 0, function(total, customer) {
        return total + customer.purchase.length;
    });
}
```

map() : 어떤 배열의 모든 항목에 함수를 적용해 새로운 배열 생성

filter() : 어떤 배열의 하위 집합을 선택해 새로운 배열 생성

reduce() : 초기값을 이용해 어떤 배열의 항목을 조합하여 새로운 값을 생성 