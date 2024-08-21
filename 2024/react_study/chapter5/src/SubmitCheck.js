import {useState} from 'react';

function submitForm(answer) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            let shouldErr = (answer.toLowerCase() !== 'lima');
            if(shouldErr) {
                reject(new Error("Try Again!"));
            } else {
                resolve();
            }
        }, 1000);
    });
}

export default function SubmitCheck() {
    const [answer, setAnswer] = useState('');
    const [error, setError] = useState(null);
    const [status, setStatus] = useState('typing');

    if(status === 'success') {
        return <h1>Correct!</h1>
    }

    async function handleSubmit(e) {
        e.preventDefault();
        setStatus('sumbitting');
        try {
            await submitForm(answer);
            setStatus('success');
        } catch(err) {
            setStatus('typing');
            setError(err);
        }
    }

    function handleTextareaChange(e) {
        setAnswer(e.target.value);
    }

    return (
        <>
            <h2>Quiz</h2>
            <p>
                Lima is answer. Show me your power!!!
            </p>
            <form onSubmit={handleSubmit}>
                <textarea value={answer} onChange={handleTextareaChange} disabled={status === 'submitting'} />
                <br/>
                <button disabled={answer.length === 0 || status === 'submitting'}>
                    Submit!!!
                </button>
                {error !== null && <p className='Error'>{error.message}</p>}
            </form>
        </>
    );
}