ch 11

고차 함수를 만드는 법

1. 함수 이름에 있는 암묵적 인자 드러내기

2. 함수 본문을 콜백으로 바꾸기 

이전 copy-on-write 예제에서 인자를 복사하고, 로직 수행 후, 결과 리턴하는 과정 중, 복사와 리턴은 공통 사항

따라서 본문인 로직 수행 부분을 따로 빼내 콜백으로 바꾸면 고차 함수로 수정 가능

```javascript
// copy-on-write : 본문을 콜백으로 바꾸기로 리팩토링 하기
// copy-on-write 과정 : 
// 1. 복사본 만들기
// 2. 복사본 변경
// 3. 복사본 리턴
// 
// 함수 본문을 콜백으로 바꾸기
// 1. 본문 앞 뒤 확인
// 2. 함수 본문 빼내기 
// 3. 콜백으로 빼내기 

function arraySet(array, idx, value) {
    var copy = array.slice();
    copy[idx] = value;
    return copy;
}

function push(array, elem) {
    var copy = array.slice();
    copy.push(elem);
    return copy;
}

// 위 copy-on-write 부분에서 2번째 줄 외에는 공통 사항
// 따라서 아래와 같이 콜백으로 구성
function arraySet(array, idx, value) {
    return withArrayCopy(array, function(copy) {
        copy[idx] = value;
    });
}

function withArrayCopy(array, modify) {
    var copy = array.slice();
    modify(copy);
    return copy;
}
```

위 예제에서 withArrayCopy에 콜백으로 동작하는 function(copy) 부분이 arraySet 함수 실행 시 리턴을 위해 호출됨

즉, modify = function(copy) {copy[idx] = value;};

이를 이용하여 push도 동일한 구조로 변경 가능

```javascript
function push(array, elem) {
    return withArrayCopy(array, function(copy) {
        copy.push(elem);
    });
}
```

배열 이외에 객체에 적용한 유사한 리팩토링 예제

```javascript
// 배열 이외의 객체에 적용한 유사한 리팩토링 예제
function objectSet(object, key, value) {
    var copy = Object.assign({}, object);
    copy[key] = value;
    return copy;
}

function objectDelete(object, key) {
    var copy = Object.assign({}, object);
    delete copy[key];
    return copy;
}

// 위 예제도 마찬가지로 본문 (copy[key] = value, delete copy[key]) 이외의 부분 동일
// 따라서 아래와 같이 리팩토링 가능
function withObjectCopy(object, modify) {
    var copy = Object.assign({}, object);
    modify(copy);
    return copy;
}

function objectSet(object, key, value) {
    return withObjectCopy(object, function(copy){
        copy[key] = value;
    });
}

function objectDelete(object, key) {
    return withObjectCopy(object, function(copy) {
        delete copy[key];
    });
}
```

꼭 어떤 컴포넌트가 아닌, try, catch, if 등 구문에 대해서도 동작 가능

아래는 try, catch에 해당 리팩토링 적용 예제

```javascript
// try, catch 구문 예제
try{
    sendEmail();
} catch(error) {
    logToSnapErrors(error);
}

try{
    getPrice();
} catch(error) {
    logToErrors(error);
}

// 위와 같이 try 내의 본문, catch 내의 본문 외에는 동일한 구조가 있는 경우
function tryCatch(f, errorHandler) {
    try {
        return f();
    } catch(error) {
        return errorHandler(error);
    }
}

tryCatch(sendEmail, logToSnapErrors);
tryCatch(getPrice, logToErrors);

// 사실 위 tryCatch 예제에서는 return f(); 외에 그냥 f(); 로 
// 구성해도 동작은 동일하게 함 (현재 별다른 리턴이 없으므로)
// 하지만 일반적으로 리턴값이 존재할 수 있으므로 return으로 표현한 듯
```

위와 같이 단순 함수 실행의 경우, 간단히 리팩토링이 가능

하지만 try, catch 내부에서 실행할 부분에 arg가 필요하고, 

arg를 필요로 하는 게 아주 많은 다양한 함수가 있다면?

함수 자체를 function으로 감싸서 리턴을 시키면 됨

```javascript
// 함수를 리턴으로 하도록 리팩토링
// try, catch 구문이 반복되고 arg도 있는 경우에는?

try {
    saveUserData(user);
} catch(error) {
    logToSnapErrors(error);
}

try {
    fetchProduct(productId);
} catch(error) {
    logToSnapErrors(error);
}

// 위의 경우, try 본문 외에는 모든 것이 동일 
// 그리고 단순 f(); 가 아닌, arg도 필요
// 아래와 같이 함수 자체를 리턴시키도록 리팩토링
function wrapLogging(f) {
    return function(arg) {
        try {
            f(arg);
        } catch(error) {
            logToSnapErrors(error);
        }
    };
}

// 아래와 같이 선언 시, wrapLogging 인자로 받는 함수 이름은 
// function에 의해 감싸져 있으므로
// var로 선언한 함수가 arg 주면서 실행할 때까지 호출되지 않음
var saveUserDataWithLogging = wrapLogging(saveUserData);
var fetchProductWithLogging = wrapLogging(fetchProduct);

// 이제 saveUserData, fetchProduct 함수 실행됨
saveUserDataWithLogging(user);
fetchProductWithLogging(productId);
```

위 예제에서 wrapLogging 함수 리턴인 function에 try, catch 시

리턴 필요하다면 return 키워드 추가하면 됨

어짜피 function 으로 감싸져 있으므로, var 과 같이 할당된 변수로 arg 입력하여 

호출하기 전까지는 해당 함수 실행되지 않음

