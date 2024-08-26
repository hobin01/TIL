import {useState, useRef} from 'react';

export default function StopWatch() {

    const [startTime, setStartTime] = useState(null);
    const [now, setNow] = useState(null);
    const [isPaused, setIsPaused] = useState(false);
    const [pausedTime, setPausedTime] = useState(0);
    const [records, setRecords] = useState([]);

    const intervalRef = useRef(null);

    function handleStart() {
        if(startTime != null && !isPaused)
            return;

        if(isPaused) {
            // 현재 pause된 상태 
            // Date.now()를 기준으로 계산 중이므로, pausedTime 만큼 빼서 pause된 시간을 대상으로 계산
            setStartTime(Date.now() - pausedTime);
            setIsPaused(false);
        } else {
            setStartTime(Date.now());
        }

        setNow(Date.now());

        clearInterval(intervalRef.current);
        intervalRef.current = setInterval(() => {
            setNow(Date.now());
        }, 10);
    }

    function handlePause() {
        clearInterval(intervalRef.current);
        setPausedTime(now - startTime);
        setIsPaused(true);
    }

    function handleRecord() {
        let record = null;
        if(startTime != null && now != null)
            record = (now - startTime) / 1000;

        if(record != null)
            setRecords((prev) => [...prev, record]);
    }

    function handleClear() {
        setStartTime(null);
        setNow(null);
        setIsPaused(false);
        setPausedTime(0);
        setRecords([]);
    }

    let secondsPassed = 0;
    if(startTime != null && now != null) {
        secondsPassed = (now - startTime) / 1000;
    }

    return (
        <>
            <h1>Time passed: {secondsPassed.toFixed(3)}</h1>
            <button onClick={handleStart}>
                Start
            </button>
            <button onClick={handlePause}>
                Pause
            </button>
            <button onClick={handleRecord}>
                Record
            </button>
            <button onClick={handleClear}>
                Clear
            </button>
            <p>records : </p>
            {records.map((record, index) => (
                <p key={index}>{record.toFixed(3)}</p>
            ))}
        </>
    );
}