export function Recipe({drinkers}) {
    return (
        <ol>
            <li>Boil {drinkers} cups of water.</li>
            <li>Add {drinkers} spoons of tea.</li>
            <li>Add {0.5 * drinkers} cups of milk.</li>
        </ol>
    );
}