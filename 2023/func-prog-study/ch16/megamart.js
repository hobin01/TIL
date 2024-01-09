// 동시성 기본형 만들기

// 원래 코드

function add_item_to_cart(item) {
    cart = add_item(cart, item);
    calc_cart_total(cart, update_total_dom);
}

function calc_cart_total(cart, callback) {
    var total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
        shipping_ajax(cart, function(shipping) {
            total += shipping;
            callback(total);
        });
    });
}

// 동시성 기본형 코드

function add_item_to_cart(item) {
    cart = add_item(cart, item);
    calc_cart_total(cart, update_total_dom);
}

function calc_cart_total(cart, callback) {
    var total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
        shipping_ajax(cart, function(shipping) {
            total += shipping;
            callback(total);
        });
    });
}

function Queue() {
    var queue_items = [];
    var working = false;

    function runNext() {
        if(working)
            return;
        if(queue_items.length === 0)
            return;
        working = true;
        var cart = queue_items.shift();
        calc_cart_total(cart, function(total) {
            update_total_dom(total);
            working = false;
            runNext();
        });
    }

    return function(cart) {
        queue_items.push(cart);
        setTimeout(runNext, 0);
    }
}

var update_total_queue = Queue();

// 큐를 일반적인 형태로 변경

function add_item_to_cart(item) {
    cart = add_item(cart, item);
    calc_cart_total(cart, update_total_dom);
}

function calc_cart_total(cart, callback) {
    var total = 0;
    cost_ajax(cart, function(cost) {
        total += cost;
        shipping_ajax(cart, function(shipping) {
            total += shipping;
            callback(total);
        });
    });
}

function Queue(worker) {
    var queue_items = [];
    var working = false;

    function runNext() {
        if(working)
            return;
        if(queue_items.length === 0)
            return;
        working = true;
        var item = queue_items.shift();
        worker(item.data, function(val) {
            working = false;
            setTimeout(item.callback, 0, val);
            runNext();
        });
    }

    return function(data, callback) {
        queue_items.push({
            data: data,
            callback: callback || function() {}
        });

        setTimeout(runNext, 0);
    }
}

function calc_cart_worker(cart, done) {
    calc_cart_total(cart, function(total) {
        update_total_dom(total);
        done(total);
    });
}

var update_total_queue = Queue(calc_cart_worker);