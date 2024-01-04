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