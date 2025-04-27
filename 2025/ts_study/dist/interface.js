"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var output_1 = require("./output");
;
var p = { age: 123, name: "asdasd" };
(0, output_1.default)(p.name);
(0, output_1.default)(p);
function make_person(conf) {
    var p = { age: 0, name: "" };
    if (conf.age) {
        p.age = conf.age;
    }
    if (conf.name) {
        p.name = conf.name;
    }
    return p;
}
var pc = { age: 123 };
var p2 = make_person(pc);
(0, output_1.default)(p2);
;
var r = { x: 123, y: 234, arr: [1, 2, 3] };
(0, output_1.default)(r);
var ext = { name: "123", something: "something" };
console.log(ext);
// 초과 프로퍼티 없어도 됨
var ext2 = { age: 123 };
console.log(ext2);
var search;
search = function (src, sub) {
    var res = src.search(sub);
    return res > -1;
};
console.log(search("123", "23"));
var Clock = /** @class */ (function () {
    function Clock(num) {
        this.cur = new Date();
    }
    Clock.prototype.setTime = function (d) {
        this.cur = d;
    };
    return Clock;
}());
var clock = new Clock(123);
clock.setTime(new Date());
(0, output_1.default)(clock.cur);
var Control = /** @class */ (function () {
    function Control() {
        this.x = 123;
    }
    Control.prototype.printX = function () {
        console.log(this.x);
    };
    return Control;
}());
var SelectControl = /** @class */ (function () {
    function SelectControl() {
        // interface가 class 상속 시, 상위 class의 프로퍼티도 interface에 지정됨
        // 그러므로 해당 interface implements 할려는 class는 제일 상위 class의 프로퍼티도 다 구현해야 함
        // interface implements 한 것이므로 super는 안 됨 
        this.x = 123;
    }
    SelectControl.prototype.select = function () { };
    SelectControl.prototype.printX = function () {
        console.log(this.x + 123);
    };
    return SelectControl;
}());
var sel = new SelectControl();
sel.printX();
