import { useEffect } from "react";
import { createConnection } from "./chat";

export default function ChatRoom() {
    useEffect(() => {
        const connection = createConnection();
        connection.connect();

        // StrictMode 에서는 검사를 위해 마운트된 effect 한 번 더 호출하게 됨
        // 따라서 아래 부분 없으면 connect 2번 발생 (clean up 함수)
        // 연결 끝나면 연결 해제함을 명시하는 것
        return () => {connection.disconnect();};
    }, []);

    return <h1>Welcome!</h1>;
}