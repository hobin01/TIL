ch3

액션 : 실행 시점과 횟수에 의존
- 부수효과(side effect), 부수효과가 있는 함수, 순수하지 않음 함수

계산 : 입력으로 출력을 계산
- 순수함수, 수학함수 

데이터 : 이벤트에 대한 사실

### 항상 고민해야 할 사항
- 무엇이 액션, 계산, 데이터인지
- 액션에서 최대한 계산을 빼내기
- 액션을 더 작은 액션으로 분리할 수 없는 지
- 계산을 더 작은 계산으로 분리할 수 없는 지

### 장보기 예제

기본적인 장보기 과정
1. 냉장고 확인하기 (액션)
   - 냉장고 확인 시점에 따라 냉장고 안에 뭐가 있는 지 달라짐
2. 운전해서 상점으로 가기 (액션)
   - 운전하는 과정, 시간에 따라 연료, 시간 소비 등이 달라짐
3. 필요한 것 구입 (액션)
   - 필요한 물품이 시간에 따라 상점에서 다 떨어져 있을 수도, 존재할 수도 있음
4. 집으로 오기 (액션)
   - 이미 집에 있었다면 집으로 오는 것이 불가능 

### 세분화하기
1. 냉장고 확인하기
   - 냉장고에 있는 현재 물품 : 데이터 

2. 운전해서 상점으로 가기 
   - 상점 위치, 경로 : 데이터 

3. 필요한 것 구입하기 
   - 다음과 같이 세분화 가능
     - 현재 재고 (데이터)
     - 필요한 재고 (데이터)
     - 재고 빼기 (필요한 재고 - 현재 재고) (계산)
     - 장보기 목록 (데이터)
     - 목록에 있는 것 구입하기 (액션)

4. 집으로 오기 
   - not our scope...
   - 장보는 것이 목적 

-------------

### 쿠폰 이메일 발송 예제 

- 추천 수가 10명 이상인 사용자(구독자)는 더 좋은 쿠폰을 제공받음

- 쿠폰에는 best, good, bad 등급이 존재 

- 쿠폰은 사용자에게 이메일로 전송

필요한 사항 (액션 : A, 계산 : C, 데이터 : D)
- 이메일 보내기 (A)
- 데이터베이스에서 구독자 가져오기 (A)
- 쿠폰에 등급 매기기 (D)
- 데이터베이스에서 쿠폰 읽기 (A)
- 이메일 제목 (D)
- 이메일 주소 (D)
- 추천 수 (D)
- 어떤 이메일이 쿠폰을 받을 지 결정 (C)
- 구독자 DB 레코드 (D)
- 쿠폰 DB 레코드 (D)
- 쿠폰 목록 DB 레코드 (D)
- 구독자 목록 DB 레코드 (D)
- 이메일 본문 (D)

```javascript
// coupon.js

// 구독자 데이터 예시 (데이터)
var subscriber = {
    email: "sample@mail.com", 
    rec_count : 16,
};

// 쿠폰 등급 예시 (데이터)
var rank1 = "best";
var rank2 = "good";
var rank3 = "bad";

// 구독자 쿠폰 등급 계산 예시 (계산)
function subCouponRank(subscriber) {
    if(subscriber.rec_count >= 10)
        return "best";
    else 
        return "good";
}

// 쿠폰 데이터 예시 (데이터)
var coupon = {
    code: "10PERCENT",
    rank: "bad",
};

// 특정 등급의 쿠폰 목록을 선택 예시 (계산)
function selectCouponByRank(coupons, rank) {
    var ret = [];
    for(var c = 0; c < coupons.length; c++) {
        var coupon = coupons[c];
        if(coupon.rank === rank) {
            ret.push(coupon.code);
        }
    }
    return ret;
}

// 이메일 (데이터)
var message = {
    from: "newsletter@coupondog.co",
    to: "sample@mail.com",
    subject: "Weekly coupons",
    body: "Here are your coupons....",
};

// 구독자가 받을 이메일 계산 (계산)
function emailForSubscriber(subscriber, goods, bests) {
    // subscriber : 구독자 데이터 
    // goods : good 쿠폰 목록 데이터
    // bests : best 쿠폰 목록 데이터

    var rank = subCouponRank(subscriber);
    if(rank === "best")
        return {
            from: "newsletter@coupondog.co",
            to: "sample@mail.com",
            subject: "Weekly coupons",
            body: "Here are your coupons : " + bests.join(", "),
        };
    else 
        return {
            from: "newsletter@coupondog.co",
            to: "sample@mail.com",
            subject: "Weekly coupons",
            body: "Here are your coupons : " + goods.join(", "),
        };
}

// 구독자 전체에게 보낼 이메일 생성 (계산)
function emailForSubscribers(subscribers, goods, bests) {
    var emails = [];
    for(var s = 0; s < subscribers.length; s++) {
        var subscriber = subscribers[s];
        var email = emailForSubscriber(subscriber, goods, bests);
        emails.push(email);
    }
    return emails;
}

// 이메일 보내기 (액션) (이런 식으로 액션은 계산 합쳐서 만듬을 의미)
// 아직 아래 함수는 없음
function sendIssue() {
    var coupons = fetchCouponsFromDB();
    var goodCoupons = selecetCouponsByRank(coupons, "good"); 
    var bestCoupons = selecetCouponsByRank(coupons, "best");
    var subscribers = fetchSubscribersFromDB();
    for(var e = 0; e < emails.length; e++) {
        var email = emails[e];
        emailSystem.send(email);
    }
}
```