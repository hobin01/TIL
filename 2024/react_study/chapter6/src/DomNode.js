import {forwardRef, useRef} from 'react';

export default function FocusNode() {
    const inputRef = useRef(null);

    function handleClick() {
        inputRef.current.focus();
    }

    return (
        <>
            <input ref={inputRef} />
            <button onClick={handleClick}>
                Focus the input
            </button>
        </>
    );
}

// DOM 노드 직접 만드는 경우, 바로 ref 적용 안 됨
// forwardRef로 ref를 사용항 DOM 노드로 지정해줘야 함
const MyInput = forwardRef((props, ref) => {
    return <input {...props} ref={ref} />;
});

export function CustomFocusNode() {
    const inputRef = useRef(null);

    function handleClick() {
        inputRef.current.focus();
    }

    return (
        <>
            <MyInput ref={inputRef} />
            <button onClick={handleClick}>
                Custom : Focus the input
            </button>
        </>
    )
}