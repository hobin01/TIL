import Gallery, {Picture} from "./Gallery.js"
import TodoList from "./TodoList.js"
import "./styles.css";

export default function App() {
    return (
        <div>
            <Gallery />
            <Picture className="inline-section"/>
            <TodoList />
        </div>
    );
}