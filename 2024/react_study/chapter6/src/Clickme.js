import {useRef} from 'react';

export default function Clickme() {
    let ref = useRef(0);

    function handleClick() {
        ref.current = ref.current + 1;
        alert(ref.current + "clicked!!!!");
    }

    return (
        <>
            <button onClick={handleClick}>
                click me!
            </button>
        </>
    );
}

// ref : alert와 같이 재렌더링이 발생될 때만 사용
// 그렇지 않다면 아무 반응 없을 것임 (ex. 그냥 return에 ref.current 출력 등)
// 일반적으로 react 외부 api와 통신하는 경우 사용 
// ex. timeout id 저장, dom 요소 저장 및 조작, jsx 계산하는데 필요하지 않은 다른 객체 저장
