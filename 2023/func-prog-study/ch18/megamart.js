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

/////////
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