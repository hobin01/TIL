function SimpleButton({onClick, children}) {
    return (
        <button onClick={e => {
            // 부모 태그로 이벤트 전파를 중지 (없으면 부모 태그 이벤트도 발생)
            e.stopPropagation();
            onClick();
        }}>
            {children}
        </button>
    );
}

export function SimpleToolbar() {
    return (
        <div className="Toolbar" onClick={() => {
            alert("click toolbar!");
        }}>
            <SimpleButton 
                onClick={() => alert("play movie!!!!")}
                children={"Play Movie"}
            />
            <SimpleButton
                onClick={() => alert("upload image!!!!")}
                children={"Upload Image"}
            />
        </div>
    );
}