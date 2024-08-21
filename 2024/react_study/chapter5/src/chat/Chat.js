import {useState} from 'react';
import ChatMessage from './ChatMessage';
import ContactList from './ContactList';

export default function Chat() {
    const userList = [
        {name : 'Alice', email : 'alice@alice.com'},
        {name : 'Bob', email : 'bob@bob.com'},
        {name : 'Carol', email : 'carol@carol.com'}
    ]

    const [to, setTo] = useState(userList[0]);

    return (
        <>
            <ContactList selectedContact={to} contacts={userList} onSelect={user => setTo(user)} />
            <ChatMessage key={to.email} contact={to} />
        </>
    )
}