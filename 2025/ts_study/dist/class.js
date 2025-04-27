"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var Animal = /** @class */ (function () {
    function Animal(name) {
        this.name = name;
    }
    Animal.prototype.move = function (dist) {
        if (dist === void 0) { dist = 0; }
        console.log("".concat(this.name, " move ").concat(dist, "."));
    };
    return Animal;
}());
var Snake = /** @class */ (function (_super) {
    __extends(Snake, _super);
    function Snake(name) {
        return _super.call(this, name) || this;
    }
    Snake.prototype.move = function (dist) {
        _super.prototype.move.call(this, dist);
    };
    return Snake;
}(Animal));
var snake = new Snake("snake");
snake.move(5);
// 기본적으로 public
// private, protected도 일반적인 oop랑 똑같이 사용 가능 
// readonly도 다 적용 가능 
var Employee = /** @class */ (function () {
    function Employee() {
    }
    Object.defineProperty(Employee.prototype, "fullname", {
        // getter, setter 지원 
        get: function () {
            return this._fullname;
        },
        set: function (name) {
            this._fullname = name;
        },
        enumerable: false,
        configurable: true
    });
    return Employee;
}());
var emp = new Employee();
emp.fullname = "name!!!!";
console.log(emp.fullname);
