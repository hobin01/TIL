import {useState} from 'react';

export default function Pointer() {
    const [pointer, setPointer] = useState({x:0, y:0});
    
    return (
        <div onPointerMove={e => {
            setPointer({
                x: e.clientX,
                y: e.clientY
            });
        }}
        style={{
            position: 'relative',
            width: '100vw',
            height: '100vh',
        }} >
            <div style={{
                position: 'absolute',
                backgroundColor: 'red',
                borderRadius: '50%',
                transform: `translate(${pointer.x}px, ${pointer.y}py)`,
                left: -10,
                top: -10,
                width: 20,
                height: 20,
            }} />
        </div>
    );
}