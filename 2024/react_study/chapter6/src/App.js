import Clickme from "./Clickme";
import StopWatch from "./StopWatch"

export default function App() {
    return (
        <>
            <Clickme />
            <StopWatch />
        </>
    );
}

// ref : 기억해야할 정보가 있지만 해당 정보로 새로운 렌더링이 발생하고 싶지 않을 때 사용
// state : 설정 시 컴포넌트가 다시 렌더링됨. 하지만 ref는 변경 후에도 다시 렌더링되지 않음
