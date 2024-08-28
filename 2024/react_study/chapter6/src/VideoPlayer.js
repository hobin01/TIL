import {useState, useRef, useEffect} from 'react';

// ref: 6.3

function Player({src, isPlaying}) {
    const ref = useRef(null);

    useEffect(() => {
        if(isPlaying)
            ref.current.play();
        else 
            ref.current.pause();
    });

    // useEffect 는 모든 요소 렌더링 완료된 후 실행 
    // 즉, 렌더링 완료 전에 useEffect로 실행될 내용이 DOM에 반영되지 않음
    // useEffect 없이 그냥 if 문 작성 시, DOM crash error 발생

    // useEffect : 외부와의 연결이 반드시 필요한 경우 아니면 굳이 사용 안 해도 됨
    // 그리고 렌더링 이후에 해당 함수 실행되므로 state 변경과 같이 렌더링 발생하는 것과 같이 사용 시 무한루프 발생 가능
    // const [count, setCount] = useState(0);
    // useEffect(() => {setCount(count + 1);}); 같은 거하면 무한루프 발생

    return <video ref={ref} src={src} loop playsInline width={"250px"}/>
}

export default function VideoPlayer() {
    const [isPlaying, setIsPlaying] = useState(false);
    return (
        <>
            <button onClick={() => setIsPlaying(!isPlaying)}>
                {isPlaying ? 'Pause': 'Play'}
            </button>
            <Player isPlaying={isPlaying} src="https://interactive-examples.mdn.mozilla.net/media/cc0-videos/flower.mp4" />
        </>
    )
}

// 종속성 관리
// useEffect(() => {...}); : 모든 렌더링 이후에 실행 
// useEffect(() => {...}, []); : 마운트 될 때 (컴포넌트가 처음 나타날 때) 만 실행
// useEffect(() => {...}, [...]) : 마운트 될 때 + [...] 에 있는 것이 마지막 렌더링 이후 변경된 경우에도 실행
