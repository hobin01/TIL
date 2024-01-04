ch13

우수 고객 (구매 3개 이상) 중 가장 큰 금액을 고르는 것은 어떻게?

체이닝(chaining)을 이용

체이닝 : map, filter, reduce 등으로 조건에 맞게 체인처럼 연결

```javascript
function map(array, f) {
    var newArray = [];
    forEach(array, function(element) {
        newArray.push(f(element));
    });
    return newArray;
}

function filter(array, f) {
    var newArray = [];
    forEach(array, function(element) {
        if(f(element)) {
            newArray.push(element);
        }
    });
    return newArray;
}

function reduce(array, init, f) {
    var accum = init;
    forEach(array, function(element) {
        accum = f(accum, element);
    });
    return accum;
}

// 우수 고객 (구매 3개 이상) 중 가장 비싼 금액 고르기 
function biggestPurchaseBestCustomers(customers) {
    // 우수 고개 : filter로 선정
    var bestCustomers = filter(customers, function(customer) {
        return customer.purchases.length >= 3;
    });

    // 우수 고객과 해당 고개의 가장 비싼 구매 금액을 매핑 후 (map)
    // 그 중 가장 비싼 것을 선정 (reduce)
    var biggestPurchases = map(bestCustomers, function(customer) {
        return reduce(customer.purchases, {total : 0}, function(biggestSoFar, purchase) {
            if(biggestSoFar.total > purchase.total)
                return biggestSoFar;
            else 
                return purchase;
        });
    });

    return biggestPurchases;
}
```

하지만 위와 같이 구성 시 콜백이 중첩되서 알아보기 어려움

아래와 같이 각 콜백에 해당하는 기능을 분리하는 것이 더 간결하고 이해하기 쉬움

```javascript
// 위처럼 구성 시 콜백 중첩으로 읽기 어려움
// 배열 중 가장 큰 값 찾는 maxKey() 함수 구성
function maxKey(array, init, f) {
    return reduce(array, init, function(biggestSoFar, element) {
        if(f(biggestSoFar) > f(element))
            return biggestSoFar;
        else 
            return element;
    });
}

function biggestPurchaseBestCustomers(customers) {
    // 우수 고개 : filter로 선정
    var bestCustomers = filter(customers, function(customer) {
        return customer.purchases.length >= 3;
    });

    // 우수 고객과 해당 고개의 가장 비싼 구매 금액을 매핑 후 (map)
    // 그 중 가장 비싼 것을 선정 (reduce)
    var biggestPurchases = map(bestCustomers, function(customer) {
        return maxKey(customer.purchases, {total : 0}, function(purchase) {
            return purchase.total;
        });
    });

    return biggestPurchases;
}
```

더 간결하게 만들기

```javascript
// 위와 같이 별도의 maxKey 함수를 구성하여 간결하게 만드는 것처럼 
// 콜백을 분리시키는 것이 더 간결

function biggestPurchaseBestCustomers(customers) {
    var bestCustomers = filter(customers, isGoodCustomer);
    var biggestPurchases = map(bestCustomers, getBiggestPurchase);
    return biggestPurchases;
}

function isGoodCustomer(customer) {
    return customer.purchases.length >= 3;
}

function getBiggestPurchase(customer) {
    return maxKey(customer.purchases, {total: 0}, getPurchaseTotal);
}

function getPurchaseTotal(purchase) {
    return purchase.total;
}
```

loop를 체이닝으로 변경하기

```javascript
// 반복문을 함수형 도구로 리팩토링
// 1. 코드 이해하고 다시 만들기
// 2. 리팩토링하기

var answer = [];
var window = 5;

for(var i = 0; i < array.length; i++) {
    var sum = 0;
    var count = 0;
    for(var w = 0; w < window; w++) {
        var idx = i + w;
        if(idx < array.length) {
            sum += array[idx];
            count += 1;
        }
    }
    answer.push(sum/count);
}

// 위 코드는 array에서 window 단위로 평균값 구하는 코드
// 이를 리팩토링
 
// 1. 데이터 만들기
// 위에서 idx는 직접적으로 for문과 연관은 없음 
// 하위 배열로 변경

var answer = [];
var window = 5;

for(var i = 0; i < array.length; i++) {
    var sum = 0;
    var count = 0;
    var subarray = array.slice(i, i + window);
    for(var w = 0; w < subarray.length; w++) {
        sum += subarray[w];
        count += 1;
    }
    answer.push(sum/count);
}

// 2. 한 번에 전체 배열 조작
// 위에서 평균 구하는 부분은 별도로 구성 가능

function average(numbers) {
    return reduce(numbers, 0, plus) / numbers.length;
}

function plus(a, b) {
    return a + b;
}

var answer = [];
var window = 5;

for(var i = 0; i < array.length; i++) {
    var subarray = array.slice(i, i + window);
    answer.push(average(subarray));
}

// 3. 작은 단계로 나누기
// 위에서는 for문 돌면서 일일이 window 크기만큼의 배열을 새로 생성
// 인덱스 접근이 불가능할 때는 어떻게?
// 인덱스 접근하는 부분을 별도로 계산

var window = 5;

var indices = range(0, array.length);
var windows = map(indices, function(i) {
    return array.slice(i, i + window);
});
var answer = map(windows, average);

function range(start, end) {
    var ret = [];
    for(var i = start; i < end; i++) {
        ret.push(i);
    }
    return ret;
}
```

체이닝 디버깅을 위한 팁

1. 구체적인 것 유지하기

파이프라인이 많다면 변수가 뭘 의미하는 지 잊기 쉬움

변수명은 의미있게 선정하기

2. 출력하기 

각 체인 단계에 print 찍어서 확인하면서 코드 작성

테스트 완료 후 출력 부분 제거하기

3. 타입 따라가기

체인의 각 단계에서 리턴되는 타입 체크하기 

---

추가적인 함수형 언어 도구

```javascript
// pluck : map으로 콜백을 일일이 짜지 않아도 됨 
// array에서 field에 해당하는 값만 추출
function pluck(array, field) {
    return map(array, function(object) {
        return object[field];
    });
}

// concat : 중첩된 배열을 한 단계의 배열로 만듬
function concat(arrays) {
    var ret = [];
    forEach(arrays, function(array) {
        forEach(array, function(element) {
            ret.push(element);
        });
    });
    return ret;
}

// frequenciesBy : 특정 값 개수 세기
// groupBy : 값 별로 그룹화
function frequenciesBy(array, f) {
    var ret = {};
    forEach(array, function(element) {
        var key = f(element);
        if(ret[key])
            ret[key] += 1;
        else 
            ret[key] = 1;
    });
    return ret;
}

function groupBy(array, f) {
    var ret = {};
    forEach(array, function(element) {
        var key = f(element);
        if(ret[key])
            ret[key].push(element);
        else 
            ret[key] = [element];
    });
    return ret;
}
```

