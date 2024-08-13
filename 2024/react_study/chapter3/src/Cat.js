import catImg from "./img/cat.jpeg";

export default function Cat({ className }) {
    const description = "Cat!!!";
    return <img src={catImg} alt={description} className={className} />;
}