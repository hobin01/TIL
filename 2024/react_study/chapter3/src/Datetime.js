export default function KoreaDateTime() {
    const datetime = new Intl.DateTimeFormat(
        'ko',
        {dateStyle: "long"}
    ).format(new Date());

    return <h2>{datetime}</h2>;
}

export function DateTime({lang}) {
    const today = new Date();
    const datetime = new Intl.DateTimeFormat(
        lang,
        {dateStyle: "long"}
    ).format(today);

    return <h2>{datetime}</h2>;
}