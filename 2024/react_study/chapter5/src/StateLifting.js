import {useState} from 'react';

// 2개 이상의 컴포넌트가 특정 state를 공유해야 하는 경우 : state lifting 사용 (상태 끌어올리기)
// state를 공유하는 컴포넌트의 최소 공통 조상 컴포넌트로 이동 후, 
// 공유하는 state를 props로 자식 컴포넌트 (state를 공유하는 컴포넌트) 에게 전달하여 
// state를 공유하도록 함

// state 공유 필요 시 react에서 일반적으로 수행하는 기법 

function Panel({title, children, isActive, onShow}) {
    return (
        <section className='panel'>
            <h3>{title}</h3>
            {isActive ? (<p>{children}</p>) : (<button onClick={onShow}>show</button>)}
        </section>
    );
}

export default function StateLifting() {
    // activeIndex 라는 state를 공유
    const [activeIndex, setActiveIndex] = useState(0);

    return (
        <>
            <h2>Almaty, Kazakhstan</h2>
            <Panel title="About" isActive={activeIndex === 0} onShow={() => setActiveIndex(0)}>
            With a population of about 2 million, Almaty is Kazakhstan's largest city. From 1929 to 1997, it was its capital city.
            </Panel>
            <Panel title="Etymology" isActive={activeIndex === 1} onShow={() => setActiveIndex(1)}>
            The name comes from <span lang="kk-KZ">алма</span>, the Kazakh word for "apple" and is often translated as "full of apples". In fact, the region surrounding Almaty is thought to be the ancestral home of the apple, and the wild <i lang="la">Malus sieversii</i> is considered a likely candidate for the ancestor of the modern domestic apple.
            </Panel>
        </>
    );
}