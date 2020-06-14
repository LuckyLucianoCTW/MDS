const boards = [];

const initBoard = (handler) => {
    newBoard = {
        room: handler,
        board: [
            ["br","bk","bb","bq","bk","bb","bk","br"],
            ["bm","bm","bm","bm","bm","bm","bm","bm"],
            [" "," "," "," "," "," "," "," "],
            [" "," "," "," "," "," "," "," "],
            [" "," "," "," "," "," "," "," "],
            [" "," "," "," "," "," "," "," "],
            ["wm","wm","wm","wm","wm","wm","wm","wm"],
            ["wr","wk","wb","wq","wk","wb","wk","wr"]
        ],
        turn: "w"
    }

    const b_index = boards.findIndex(board => board.room === handler)
    if(b_index === -1){
        boards.push(newBoard)
    }

    console.log("Boards db")
    console.log(boards)
};

const removeBoard = (handler) => {
    const b_index = boards.findIndex(board => board.room === handler)
    if(b_index !== -1){
        boards.splice(b_index, 1)
    }
    
    console.log("Boards db")
    console.log(boards)
};

const makeMove = (newBoard, player, handler) => {
    const b_index = boards.findIndex(board => board.room === handler);

    const templateBoard = {
        room: handler,
        board: newBoard,
        turn: (player === "w")? "b" : "w"
    }

    const errors = {
        message: "",
        hasError: false,
    }

    if(b_index !== -1){
        boards[b_index] = templateBoard;
    }
    else{
        errors.message = "Board could not be found";
        errors.hasError = true;
    }
    
    console.log("Boards db")
    console.log(boards)
    return {errors, templateBoard};
}

exports.initBoard = initBoard;
exports.removeBoard = removeBoard;
exports.makeMove = makeMove;
