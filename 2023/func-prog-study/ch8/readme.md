ch8

계층형 설계 (stratified design) : 설계 시 계층에 따라 구현

=> 구현, 테스트, 유지보수에 용이

계층 구성 (꼭 답이 있는 것은 아님. 설계자가 중요하다고 판단되는 것에 따라 계층을 구성)

1. 비즈니스 규칙
2. 규칙을 위한 동작
3. copy-on-write
4. language에서 지원하는 기능 

계층형 설계 패턴에서 중요한 패턴 4가지

1. 직접 구현 : 계층 별로 직접 구현. 함수 시그니처가 나타내고 있는 문제를 함수 본문에서 적절한 수준에서 해결해야 함. (너무 구체적이면 냄새나는 코드)
2. 추상화 벽 : 특정 계층에 대해 중요 세부 구현은 감추고 인터페이스를 제공. 
3. 작은 인터페이스 : 비즈니스 개념을 나타내는 중요 인터페이스는 작고 강력한 동작으로 구성. 다른 동작도 최소한의 인터페이스를 유지하면서 정의하는 것이 좋음.
4. 편리한 계층 : 개발자의 요구를 만족시키면서, 비즈니스 문제를 잘 풀 수 있도록 계층을 구성. 코드와 코드가 속한 추상화 계층은 작업할 때 편리해야 함.

```javascript
// 넥타이를 사면 넥타이 클립을 제공하고자 하는 코드
// 계층적 문제 :
// 비즈니스 로직 - 넥타이를 사면 넥타이 클립을 준다.
// 비즈니스 로직 상에서 cart가 배열인지 여부 알 필요 없음
// 해당 함수에서는 "넥타이를 산다 => 넥타이 클립을 준다" 라는 것이 중요
function freeTieClip(cart) {
    var hasTie = false;
    var hasTieClip = false;

    for(var i = 0; i < cart.length; i++) {
        var item = cart[i];
        if(item.name === "tie")
            hasTie = true;
        if(item.name === "tie clip")
            hasTieClip = true;
    }

    if(hasTie && !hasTieClip) {
        var tieClip = make_item("tie clip", 0);
        return add_item(cart, tieClip);
    }
    return cart;
}
```

위 코드에서 for loop 는 언어에서 제공하는 기능

make_item, add_item 함수는 직접 구현한 함수

언어에서 제공하는 기능은 직접적으로 건들지 못하므로 계층 구조 상 더 아래에 존재

따라서 이러한 부분을 최소화해야 함

또한 비슷한 동작을 하는 부분을 공통 부분으로 분리하는 것이 좋음

```javascript
// freeTieClip 에서 특정 항목 있는 지 여부 검사하는 부분 추출
function isInCart(cart, name) {
    for(var i = 0; i < cart.length; i++) {
        if(cart[i].name === name)
            return true;
    }
    return false;
}

function freeTieClip(cart) {
    var hasTie = isInCart(cart, "tie");
    var hasTieClip = isInCart(cart, "tie clip");

    if(hasTie && !hasTieClip) {
        var tieClip = make_item("tie clip", 0);
        return add_item(cart, tieClip);
    }
    return cart;
}
```

위와 같이 개선 시, freeTieClip 함수에 대해서는 cart가 배열인지 여부랑 상관 없이 동작하게 됨

isInCart가 cart에 name 항목이 있는 지 여부를 올바르게 확인한다면,

freeTieClip 함수에서는 비즈니스 로직에 맞게 cart에 tie가 있고, tie clip이 없다

그러면 cart에 tie clip을 추가한다. 라는 것만 확인하면 됨.

이처럼 계층적 구조로 비즈니스 로직, 동작, 언어 기능 등에 따라서 계층 그래프를 구성하여 각 계층에 적합하도록 구현하여야 함.

---

직접 구현 시, 계층 그래프가 가리키는 함수, 동작들은 모두 같은 레벨에 존재해야 함

그렇지 않으면 그래프 자체가 복잡해져버림

예를 들어 remove_item_by_name() 함수가 다음과 같음

```javascript
function remove_item_by_name(cart, name) {
    var idx = null;
    for(var i = 0; i < cart.length; i++) {
        if(cart[i].name === name)
            idx = i;
    }
    if(idx != null)
        return removeItems(cart, idx, 1);
    return cart; // 제거할 대상 없으면 불필요한 복사 할 필요 없음
}

function removeItems(array, idx, count) {
    var copy = array.slice();
    copy.splice(idx, count);
    return copy;
}
```

위 함수 내부에 존재하는 것에는 다음과 같음

1. for loop
2. index : cart[i]
3. removeItems() function

for loop 와 index 는 언어에서 제공하는 기능이며, removeItems 는 직접 생성한 함수

따라서 removeItems 가 더 높은 계층에 위치

이를 방지하기 위해서 for loop, indexing 과 remove_item_by_name 사이에 적절한 다른 함수가 필요 (모든 계층이 같은 레벨에 있어야 함!)

위 내용을 다음과 같이 구성 가능

```javascript
function remove_item_by_name(cart, name) {
    var idx = indexOfItem(cart, name);

    if(idx != null)
        return removeItems(cart, idx, 1);
    return cart; // 제거할 대상 없으면 불필요한 복사 할 필요 없음
}

function indexOfItem(cart, name) {
    for(var i = 0; i < cart.length; i++) {
        if(cart[i].name === name)
            return i;
    }
    return null;
}

function removeItems(array, idx, count) {
    var copy = array.slice();
    copy.splice(idx, count);
    return copy;
}
```

엄밀히 따지면 indexOfItem이 removeItems 보다 더 높은 계층에 위치

왜냐하면 removeItems에서는 name이라는 속성이 있는 지 여부는 몰라도 되기 때문

하지만 러프하게 봤을 때 아까보다 개선됨.

이러한 사고를 계속적으로 진행하여 모든 계층을 동등하게 구성하는 것이 목표