import {useState} from 'react';

export default function Fullname() {
    const [firstname, setFirstname] = useState('');
    const [lastname, setLastname] = useState('');

    /*
    // fullname의 state가 중복으로 처리됨 
    // 동시에 입력이 발생되면 처리 못 할 수도 있음
    const [fullname, setFullname] = useState('');
    function handleFirstnameChange(e) {
        setFirstname(e.target.value);
        setFullname(e.target.value + ' ' + lastname);
    }
    function handleLastnameChange(e) {
        setLastname(e.target.value);
        setFullname(firstname + ' ' + e.target.value);
    }
    */

    // 어짜피 state 바뀌는 값 내용에 맞게 할당된 변수가 렌더링되므로 
    // 아래와 같이 코드 작성하는게 버그 줄이는데 도움
    const fullname = firstname + ' ' + lastname;

    function handleFirstnameChange(e) {
        setFirstname(e.target.value);
    }
    function handleLastnameChange(e) {
        setLastname(e.target.value);
    }

    return (
        <>
            <label>
                First name : 
                <input value={firstname} onChange={handleFirstnameChange} />
            </label>
            <lable>
                Last name : 
                <input value={lastname} onChange={handleLastnameChange} />
            </lable>
            <p>Full name : {fullname}</p>
        </>
    );
}