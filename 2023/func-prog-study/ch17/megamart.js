// 현재 ajax 호출 최적화를 위해 아래와 같이 구성 중
// shipping_ajax 가 먼저 끝나버리게 되면 total에 shipping만 더해지고
// done으로 끝남

function add_item_to_cart(item) {
    cart = add_item(cart, item);
    update_total_queue(cart);
}

function calc_cart_total(cart, callback) {
    var total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
    });

    shipping_ajax(cart, function(shipping) {
        total += shipping;
        callback(total);
    });
}

function calc_cart_worker(cart, done) {
    calc_cart_total(cart, function(total) {
        update_total_dom(total);
        done(total);
    });
}

var update_total_queue = DroppingQueue(1, calc_cart_worker);

// Cut : 타임라인 수 카운트하면서 다 끝나면 callback 실행함
function Cut(num, callback) {
    var num_finished = 0;
    return function() {
        num_finished += 1;
        if(num_finished === num)
            callback();
    };
}

function calc_cart_total(cart, callback) {
    var total = 0;
    var done = Cut(2, function() {
        callback(total);
    });

    cost_ajax(cart, function(cost) {
        total += cost;
        done();
    });

    shipping_ajax(cart, function(shipping) {
        total += shipping;
        done();
    });
}