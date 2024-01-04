// 특정 필드가 아닌, 임의의 필드에 대한 값을 수정하는 함수들
// 하지만 실질적인 동작은 +-1 차이일 뿐 의미는 무엇인가를 수정한다는 의미
function increamentField(item, field) {
    var value = item[field];
    var newValue = value + 1;
    var newItem = objectSet(item, field, newValue);
    return newItem;
}

function decreamentField(item, field) {
    var value = item[field];
    var newValue = value - 1;
    var newItem = objectSet(item, field, newValue);
    return newItem;
}

// 따라서 위의 본문 앞뒤를 따로 빼내 리팩토링
function updateField(item, field, modify) {
    var value = item[field];
    var newValue = modify(value);
    var newItem = objectSet(item, field, newValue);
    return newItem;
}

function increamentField(item, field) {
    return updateField(item, field, function(value) {
        return value + 1;
    });
}

function decreamentField(item, field) {
    return updateField(item, field, function(value) {
        return value - 1;
    });
}

// 좀 더 일반화된 update 함수
// 여기서 objectSet : 해시맵 기반으로 동작한다 가정
function update(object, key, modify) {
    var value = object[key]; // 조회
    var newValue = modify(value); // 변경 
    var newObject = objectSet(object, key, newValue); // 설정 (카피 온 라이트)
    return newObject;
}

// 데이터 중첩이 여러 번 있다면?
function increamentSize(item) {
    var options = item.options; // 조회
    var size = options.size; // 조회
    var newSize = size + 1; // 변경
    var newOptions = objectSet(options, 'size', newSize); // 설정
    var newItem = obejctSet(item, 'options', newOptions); // 설정
    return newItem;
}

// 위의 가운데 조회, 변경, 설정을 하나의 변경으로 바꾸기
function increamentSize(item) {
    var options = item.options; // 조회
    var newOptions = update(options, 'size', increament); // 변경
    var newItem = objectSet(item, 'options', newOptions); // 설정
    return newItem;
}

// 같은 논리로 동일하게 변경 가능
function increamentSize(item) {
    return update(item, 'options', function(options) {
        return update(options, 'size', increament);
    });
}

// 하지만 위에서 냄새가 나는 부분은 함수 이름에 암묵적으로 size가 들어가 있음
// 따라서 최종적으로 아래와 같이 수정 가능

// update2 : 데이터 2개 중첩된 것을 의미
function update2(object, key1, key2, modify) {
    return update(object, key1, function(value1) {
        return update(value1, key2, modify);
    });
}

function increamentSize(item) {
    return update2(item, 'options', 'size', function(size) {
        return size + 1;
    });
}

// update3가 필요하다면 update -> update2 순으로 호출하면 됨
// update4 필요하면 update -> update3 순으로 호출
// 하지만 이런 경우 파라미터로 들어오는 키 별로 계속 새로 만들어줘야 함
// 이를 방지하고자 recursive하게 update 함수를 생성
// 단 update0는 modify와 동일하다는 것만 구분
function nestesUpdate(object, keys, modify) {
    if(keys.length === 0)
        return modify(object);
    var key1 = keys[0];
    var restOfKeys = drop_first(keys);
    return update(object, key1, function(value) {
        return nestesUpdate(value, restOfKeys, modify);
    });
}

// 그렇다면 API와 같이 호출해야 할 이름이 너무 긴 경우는 어떻게 관리?
// 너무 깊이 중첩된 데이터의 경우 어떻게 효율적으로?
// 추상화 벽을 이용
