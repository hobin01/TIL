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