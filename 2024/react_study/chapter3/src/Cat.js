import catImg from "./img/cat.jpeg";

export default function Cat({ className }) {
    return <img src={catImg} alt="Cat!!!" className={className} />;
}