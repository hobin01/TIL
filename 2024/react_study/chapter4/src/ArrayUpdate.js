import {useState} from 'react';

// react에서 상태 저장 시 불변으로 취급해야 함
// 즉, state 처리하는 함수가 아닌, 직접적인 배열, 객체 수정은 피해야 한다.
// 피해야 할 메서드 : push, unshift, pop, shift, splice, arr[i] = something, reverse, sort
// 새 배열을 반환하는 메서드 (선호) : concat, ...arr, filter, slice, map, 배열 자체를 복사 

const initialArtists = [
    {idx: 0, name: 'alice'},
    {idx: 1, name: 'bob'},
    {idx: 2, name: 'carol'},
    {idx: 3, name: 'david'}
];

export default function ArrayUpdate() {
    const [artists, setArtists] = useState(initialArtists);
    const [name, setName] = useState('');
    const [idx, setIdx] = useState(0);

    function handleInsertClick() {
        const insertAt = idx;

        if(insertAt < 0 || insertAt > artists.length) {
            alert("dont do that");
            setName('');
            setIdx(0);
            return;
        }

        const nextArtist = [
            ...artists.slice(0, insertAt),
            {idx: insertAt, name: name},
            ...artists.slice(insertAt).map(artist => ({...artist, idx: artist.idx + 1}))
        ];

        setArtists(nextArtist);
        setName('');
        setIdx(0);
    }

    function handleDeleteClick(delIdx) {
        const nextArtist = [
            ...artists.slice(0, delIdx),
            ...artists.slice(delIdx + 1).map(artist => ({...artist, idx: artist.idx - 1}))
        ];

        setArtists(nextArtist);
        setName('');
        setIdx(0);
    }

    return (
        <>
            <h1>Artists!!!!</h1>
            몇 번째? : <input value={idx} onChange={e => setIdx(e.target.value)} />
            name : <input value={name} onChange={e => setName(e.target.value)} />
            <button onClick={handleInsertClick}>Insert</button>
            <ul>
                {artists.map(artist => (
                    <li key={artist.idx}>
                        {artist.idx}{' : '}
                        {artist.name}{' '}
                        <button onClick={() => handleDeleteClick(artist.idx)}>
                        Delete
                        </button>
                    </li>
                ))}
            </ul>
        </>
    );
}