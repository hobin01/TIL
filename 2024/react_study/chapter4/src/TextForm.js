import {useState} from 'react';

export default function TextForm() {
    // js의 객체도 상태로 이용 가능
    const [person, setPerson] = useState({
        name: 'abcd',
        artwork: {
            title: 'blue nana',
            city: 'hamburg',
            image: 'https://i.imgur.com/Sd1AgUOm.jpg',
        }
    });

    function handleNameChange(e) {
        setPerson({
            ...person,
            name: e.target.value
        });
    }

    function handleTitleChange(e) {
        setPerson({
            ...person,
            artwork: {
                ...person.artwork,
                title: e.target.value
            }
        });
    }

    function handleCityChange(e) {
        setPerson({
            ...person,
            artwork: {
                ...person.artwork,
                city: e.target.value
            }
        });
    }

    return(
        <>
            <label>
                Name: <input value={person.name} onChange={handleNameChange} />
            </label>
            <label>
                Title: <input value={person.artwork.title} onChange={handleTitleChange} />
            </label>
            <label>
                City: <input value={person.artwork.city} onChange={handleCityChange} />
            </label>
            <div>
                <p>
                    Title : <i>{person.artwork.title}</i><br/>
                    by : <i>{person.name}</i><br/>
                    city : <i>{person.artwork.city}</i><br/>
                </p>
                <img src={person.artwork.image} alt={person.artwork.title} />
            </div>
        </>
    )
}