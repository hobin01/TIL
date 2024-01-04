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