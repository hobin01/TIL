ch 18

반응형 아키텍처 : 코드에 나타난 순차적 액션의 순서를 뒤집는다.

효과와 효과에 대한 원인을 분리하여 복잡하게 꼬인 부분을 해결한다.

어니언 아키텍처 : 웹 서비스, 온도 조절 장치 등 현실 세계와 상호작용하기 위한 서비스 구조를 만든다.

---

이벤트 핸들러 예제

- 웹 서비스

(웹 요청) : GET /cart/cost

(요청 핸들러)

1. DB에서 가격 읽기
2. 장바구니에 가격 변경 
3. DB에서 할인 정보 읽기
4. 할인 적용
5. 합계 합산
6. 웹 응답 전송

- 사용자 인터페이스

(UI 이벤트) : 제춤 추가 버튼 클릭

(이벤트 핸들러)

1. 전역 장바구니에 제품 추가
2. 합계 계산
3. 합계 DOM 업데이트
4. 배송 아이콘 업데이트
5. 세금 DOM 업데이트 

- 반응형 아키텍처

웹 서비스 : 순차적으로 처리

사용자 인터페이스 : 배송 아이콘 업데이트, DOM 업데이트는 순서가 중요하지 않음

반응형 아키텍처 : X 를 하고 Y 를 하는 대신, X 를 하고 난 뒤 언제나 Y 를 하도록 구성 

---

전역과 같이 변경 가능한 값을 제어하는 경우 일급 함수로 처리하여 항상 업데이트되는 값을 다른 곳에서도 갱신시키도록 함

예제

```javascript
// 변경 가능한 값(ex. 전역 변수)을 일급 함수로 만드는 과정

function ValueCell(initialValue) {
    var currentValue = initialValue;
    var watchers = []; // 감시자 목록
    return {
        val : function() {
            return currentValue;
        },
        update : function(f) {
            var oldValue = currentValue;
            var newValue = f(oldValue);

            if(oldValue !== newValue) {
                currentValue = newValue;
                forEach(watchers, function(watcher) {
                    watcher(newValue);
                });
            }
        },
        addWatcher : function(f) {
            watchers.push(f);
        }
    };
}

// 장바구니라는 전역 값에 대해 ValueCell 함수 적용

// 기존 코드 
var shopping_cart = {};

function add_item_to_cart(name, price) {
    var item = make_cart_item(name, price);
    shopping_cart = add_item(shopping_cart, item);

    var total = calc_total(shopping_cart);
    set_cart_total_dom(total);
    update_shipping_icons(shopping_cart);
    update_tax_dom(total);
}

// ValueCell 적용 코드 
var shopping_cart = ValueCell({});

function add_item_to_cart(name, price) {
    var item = make_cart_item(name, price);
    shopping_cart.update(function(cart) {
        return add_item(cart, item);
    })

    var total = calc_total(shopping_cart);
    set_cart_total_dom(total);

    update_tax_dom(total);
}

// 배송 아이콘 업데이트는 굳이 순차적으로 일어나지 않아도 됨
shopping_cart.addWatcher(update_shipping_icons);
```

FormulaCell : 파생된 값을 계산

이미 있는 셀에서 파생한 셀을 만드는 데 사용

다른 셀의 변화가 감지되면 값을 다시 계산

```javascript
// FormulaCell : 파생된 값을 계산
// 이미 있는 셀에서 파생된 셀을 만드는 역할
// 다른 셀의 변화가 있으면 값을 다시 계산시킴

function FormulaCell(upstreamCell, f) {
    var myCell = ValueCell(f(upstreamCell.val()));
    upstreamCell.addWatcher(function(newUpstreamValue) {
        myCell.update(function(currentValue) {
            return f(newUpstreamValue);
        });
    });

    return {
        val : myCell.val,
        addWatcher : myCell.addWatcher
    };
}

var shopping_cart = ValueCell({});
var cart_total = FormulaCell(shopping_cart, calc_total);

function add_item_to_cart(name, price) {
    var item = make_cart_item(name, price);
    shopping_cart.update(function(cart) {
        return add_item(cart, item);
    });
}

shopping_cart.addWatcher(update_shipping_icons);
cart_total.addWatcher(set_cart_total_dom);
cart_total.addWatcher(update_tax_dom);
```

DOM 업데이트까지 별도로 계산 가능

- ValueCell 과 유사한 기능
- 클로저 : Atom, 엘릭서 : Agent, 리액트 : Redux Store, 하스켈 : TVar

반응형 아키텍처로 변경 후 효과 : 직접적인 액션과 하위 액션을 분리

- 원인과 효과가 결합된 것을 분리
- 여러 단계를 파이프라인으로 처리
- 타임라인이 유연해짐

---

어니언 아키텍처 : 반응형 아키텍처보다 더 넓은 범위에 사용, 현실 세계와 상호작용하기 위한 서비스 구조를 만듬

언어 in 도메인 in 인터렉션 구조

인터렉션 : 바깥 세상에 영향을 주고 받는 액션

도메인 : 비즈니스 규칙을 정의하는 계산

언어 : 언어 유틸리티와 라이브러리

도메인 규칙은 도메인 용어를 사용한다.

예를 들어, db, new, old 등은 도메인 용어가 아닌 인터렉션

도메인 규칙 ex : product, image, price, discount ... 직접적으로 비즈니스 규칙에 적용되는 것들

도메인 계층을 계산으로 만들어 인터렉션 계층과 분리하는 것이 중요


