import wombat from "./img/wombat.png"

export default function TodoList() {
    return (
        <>
            <h1>Todo List!!!</h1>
            <img 
                src={wombat}
                alt="wombat!!!"
                className="photo"
            />
            <ul>
                <li>todo1 : wombat!!!</li>
                <li>todo2 : wombat!!!</li>
                <li>todo3 : wombat!!!</li>
            </ul>
        </>
    );
}