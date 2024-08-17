import {useState} from 'react';

export default function AddThree() {
    const [score, setScore] = useState(0);

    function notIncrement() {
        // 기존 score 값의 state 가 최종 리턴되기 전까지는 바뀌지 않으므로
        // 아무리 많이 호출해도 +1 결과가 됨
        setScore(score + 1);
    }

    function increment() {
        // state를 직접 바꾸기 때문에 리턴되기 전에 state가 변경되어
        // 정상적으로 호출한만큼 +1 됨
        setScore(s => s + 1);
    }

    return (
        <>
            <button onClick={() => increment()}> +1 </button>
            <button onClick={() => {
                notIncrement();
                notIncrement();
                notIncrement();
            }}> +3 (but +1) </button>
            <button onClick={() => {
                increment();
                increment();
                increment();
            }}> +3 </button>
            <h1>score : {score}</h1>
        </>
    );
}