import {useState} from 'react';

function calculateWinner(squares) {
    // 이기는 케이스들
    const lines = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]];
    for(let i = 0; i < lines.length; i++) {
        const [a,b,c] = lines[i];
        if(squares[a] && squares[a] === squares[b] && squares[a] === squares[c])
            return [squares[a], [a,b,c]];
    }

    // 빈 값 있는 지 체크
    for(let i = 0; i < 3; i++) {
        for(let j = 0; j < 3; j++) {
            const idx = 3 * i + j;
            if(!squares[idx])
                return [null, []];
        }
    }

    // 빈 거 없으면 draw
    return ["draw", []];
}

function Square({value, onSquareClick, isWinnerSquare}) {
    // 이긴 경우 칸 highlight class 추가
    return (
        <button className={`square ${isWinnerSquare ? 'highlight' : ''}`} onClick={onSquareClick}>
            {value}
        </button>
    );
}

function Board({xIsNext, squares, onPlay}) {

    function handleClick(i) {
        // 끝났거나 (null 아닌 경우) 해당 칸 이미 뭐 있는 경우
        const [isOver] = calculateWinner(squares);
        if(isOver || squares[i]) {
            return;
        }

        // 현재 보드 칸 정보 복사
        const nextSquares = squares.slice();
        // 클릭된 칸 X, O 채우기
        if(xIsNext) {
            nextSquares[i] = 'X';
        } else {
            nextSquares[i] = 'O';
        }
        // 채워진 보드 넘기기
        onPlay(nextSquares);
    }

    // winner 있는 지 계산 
    const [isWinning, winner] = calculateWinner(squares);
    let status;
    if(isWinning === null) {
        // 아직 안 끝남
        status = "Next Player : " + (xIsNext ? "X" : "O");
    } else if(isWinning === "draw") {
        // 비김
        status = "Draw";
    } else {
        // 이김
        status = "Winner : " + isWinning;
    }

    return(
        <>
            <div className="status">{status}</div>
            {Array(3).fill(null).map((_, rowIdx) => (
                <div key={rowIdx} className='board-row'>
                    {Array(3).fill(null).map((_, colIdx) => {
                        const idx = rowIdx * 3 + colIdx;
                        const isWinnerSquare = winner.includes(idx);
                        return (
                            <Square 
                                key={idx} 
                                value={squares[idx]} 
                                onSquareClick={() => handleClick(idx)} 
                                isWinnerSquare={isWinnerSquare}
                            />
                        );
                    })}
                </div>
            ))}
        </>
    );
}

export default function Game() {
    // history : 진행된 보드 기록 관리
    // currentMove : 현재까지 진행된 클릭 횟수 (보드 기록 index 관리)
    // isAscending : 기록 오름차순 정렬 여부
    const [history, setHistory] = useState([Array(9).fill(null)]);
    const [currentMove, setCurrentMove] = useState(0);
    const [isAscending, setIsAscending] = useState(true);

    // xIsNext : X 차례 유무
    // currentSquares : 현재 보드 정보
    const xIsNext = currentMove % 2 === 0;
    const currentSquares = history[currentMove];

    // nextSquares에 저장된 보드 기록 추가
    function handlePlay(nextSquares) {
        const nextHistory = [...history.slice(0, currentMove + 1), nextSquares];
        setHistory(nextHistory);
        setCurrentMove(nextHistory.length - 1);
    }

    // 보드 기록 index 로 이동하여 현재 index 변경
    function jumpTo(nextMove) {
        setCurrentMove(nextMove);
    }

    // 기록 오름차순 유무 변경
    function changeSorting() {
        setIsAscending(!isAscending);
    }

    // 보드 기록 내용 list
    const moves = history.map((squares, move) => {
        const description = move > 0 ? 'Go to move #' + move : 'Go to game start';
        
        return (
            <li key={move}>
                <button onClick={() => jumpTo(move)}>{description}</button>
            </li>
        );
    });

    // 보드 기록 내림차순으로 변경
    if(!isAscending) {
        moves.reverse();
    }

    return (
        <div className='game'>
            <div className='game-board'>
                <Board xIsNext={xIsNext} squares={currentSquares} onPlay={handlePlay} />
            </div>
            <div className='game-info'>
                <button onClick={changeSorting}>
                    {isAscending ? 'Change to Descending' : 'Change to Ascending'}
                </button>
                <ol>
                    {moves}
                </ol>
            </div>
        </div>
    );
}