import {peopleData, getImageUrl} from "./peopleData.js"

function Item({name, isPacked}) {
    let item = name;
    if(isPacked) {
        item = (
            <del>
                {name} + " O "
            </del>
        );
    }
    return (
        <li className="item">
            {item}
        </li>
    );
}

export default function PackingList() {
    return (
        <section>
            <h1>Sally Ride's Packing List</h1>
            <ul>
                <Item 
                    name={12345}
                    isPacked={true}
                />
                <Item 
                    name="asdsadasd"
                    isPacked={false}
                />
            </ul>
        </section>
    );
}

export function PeopleList() {
    const chemists = peopleData.filter(person => (
        person.profession === "chemist"
    ));
    const items = chemists.map(person => (
        <li key={person.id}>
            <img 
                src={getImageUrl(person)}
                alt={person.name}
            />
            <p>
                <b>{person.name}</b>
                <br/>
                {person.profession} - {person.accomplishment}
            </p>
        </li>
    ));

    return <ul>{items}</ul>;
}