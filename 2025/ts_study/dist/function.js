"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var output_1 = require("./output");
function get(first, second) {
    return first + " " + second;
}
(0, output_1.default)(get("123", "123"));
function get2(first, second) {
    return first;
}
(0, output_1.default)(get2("123"));
(0, output_1.default)(get2(undefined, "234"));
function get3(first, second) {
    if (first === void 0) { first = "123"; }
    return first + " " + second;
}
(0, output_1.default)(get3("234", "234"));
(0, output_1.default)(get3(undefined, "234"));
function get4(first, second) {
    if (second === void 0) { second = "234"; }
    return first + " " + second;
}
(0, output_1.default)(get4("123"));
(0, output_1.default)(get4("123", "123"));
function get5(first) {
    var second = [];
    for (var _i = 1; _i < arguments.length; _i++) {
        second[_i - 1] = arguments[_i];
    }
    return first + " " + second.join(" ");
}
(0, output_1.default)(get5("123", "123", "234", "345"));
function get6(x) {
    if (typeof x == "number") {
        console.log(x);
    }
    if (typeof x == "string") {
        console.log(x + "!!!");
    }
}
get6(123);
get6("123");
