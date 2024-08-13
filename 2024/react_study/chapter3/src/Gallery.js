import Cat from "./Cat.js"
import "./styles.css";

export default function Gallery() {
    return (
        <section>
            <h1>Amazing Cats!!!!</h1>
            <Cat /><br></br>
            <Cat /><br></br>
            <Cat /><br></br>
        </section>
    )
}

export function Picture({className}) {
    return (
        <section className={className}>
            <h2>Amazing Just One Cat!!!</h2>
            <Cat className="small-image" /><br></br>
        </section>
    )
}