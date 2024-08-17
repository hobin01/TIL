import {useState, useEffect} from "react";

import Gallery, {Picture} from "./Gallery.js"
import TodoList from "./TodoList.js"
import KoreaDateTime, {DateTime} from "./Datetime.js"
import Clock from "./Clock.js"
import PackingList from "./PackingList.js";

import "./styles.css";

export default function App() {
    return (
        <div>
            <Gallery />
            <Picture className="inline-section"/>
            <TodoList />
        </div>
    );
}

export function DateApp({lang}) {
    if(!lang) {
        return <KoreaDateTime />;
    }

    return <DateTime lang={lang} />;
}

function useTime() {
    const [time, setTime] = useState(() => new Date());
    useEffect(() => {
        const id = setInterval(() => {
            setTime(new Date());
        }, 1000);
        return () => clearInterval(id);
    }, []);
    return time;
}

export function TimeApp() {
    const time = useTime();
    const [color, setColor] = useState('lightcoral');
    return (
        <>
            <p>
                Pick a color: 
                <select value={color} onChange={e => setColor(e.target.value)}>
                    <option value="lightcoral">lightcoral</option>
                    <option value="midnightblue">midnightblue</option>
                    <option value="rebeccapurple">rebeccapurple</option>
                </select>
            </p>
            <Clock color={color} time={time.toLocaleTimeString()} />
        </>
    );
}

export function PackingListApp() {
    return <PackingList />;
}