"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var output_1 = require("./output");
var done = false;
var num = 123;
var str = "123123";
var expr = "hello\nhello\nhello\n".concat(num);
var arr = [1, 2, 3];
var arr2 = arr.slice();
arr2[2] = 4;
var tup;
tup = ["abcd", 1234];
var Color;
(function (Color) {
    Color[Color["Red"] = 0] = "Red";
    Color[Color["Green"] = 1] = "Green";
    Color[Color["Blue"] = 2] = "Blue";
})(Color || (Color = {}));
;
var c = Color.Green;
var c2 = Color[2];
var v = true;
v = 123;
// v.something(); // 컴파일은 통과함 (any 타입은 별도 검사 안 함.) (런타임에서 에러 발생)
var arrV = ["something", 123];
// never : 절대 발생할 수 없는 타입. 발생해서 안 되거나 에러 일으킬 때 사용. any도 never에 할당 불가. 
var nev = function () { throw Error('error!'); };
// <number>와 같이 형변환 가능하지만, jsx 호환성 때문에 as 많이 씀
var a = "123";
var b = a;
(0, output_1.default)(done);
(0, output_1.default)(num);
(0, output_1.default)(str);
(0, output_1.default)(expr);
(0, output_1.default)(arr);
(0, output_1.default)(arr2);
(0, output_1.default)(tup);
(0, output_1.default)(c);
(0, output_1.default)(c2);
(0, output_1.default)(v);
(0, output_1.default)(arrV);
// output(nev());
(0, output_1.default)(b);
