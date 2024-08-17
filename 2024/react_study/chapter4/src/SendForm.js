import {useState} from 'react';

const nameList = ['Alice', 'Bob', 'Carol', 'David'];

export default function SendForm() {
    const [to, setTo] = useState(nameList[0]);
    const [message, setMessage] = useState('Hello');

    function handleSubmit(evt) {
        evt.preventDefault();
        setTimeout(() => {
            alert(`Send message "${message}" to "${to}"`);
        }, 5000);
    }

    return(
        <form onSubmit={handleSubmit}>
            <label>
                To : {' '}
                <select value={to} onChange={e => setTo(e.target.value)}>
                    {nameList.map((name, idx) => (
                        <option key={idx} value={name}>{name}</option>
                    ))}
                </select>
            </label>
            <br/>
            <textarea placeholder='message' value={message} onChange={e => setMessage(e.target.value)} />
            <button type="submit">Send</button>
        </form>
    );
}