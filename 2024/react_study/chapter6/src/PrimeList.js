import {useState, useMemo} from 'react';

function isPrime(num) {
    // 소수 판별 (useMemo 테스트 위해 일부러 비효율적으로)
    if(num <= 1)
        return false;
    for(let i = 2; i <= Math.sqrt(num); i++)
        if(num % i === 0)
            return false;
    return true;
}

function Primes({range}) {
    // useMemo : memoization으로 디펜던시 변하지 않으면 진행하지 않음

    const primeNumbers = useMemo(() => {
        const primes = [];
        for(let i = 2; i <= range; i++) {
            if(isPrime(i)) {
                primes.push(i);
            }
        }
        return primes;
    }, [range]);

    return (
        <>
            <h3>prime numbers up to {range} : </h3>
            <p>{primeNumbers.join(', ')}</p>
        </>
    );
}

export default function PrimeList() {
    const [range, setRange] = useState(1000);

    return (
        <>
            <h1>Prime Number Generator</h1>
            <input type="number" value={range} onChange={e => setRange(Number(e.target.value))} min="1" max="10000" />
            <Primes range={range} />
        </>
    );
}