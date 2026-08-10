const socket = new WebSocket("/ws");

let turn = null;
let id = null;
let ip = "192.168.3.138";

let boards = document.querySelectorAll(".board2d");
let move = {
    from: {
        x: null,
        y: null,
        z: null
    },
    to: {
        x: null,
        y: null,
        z: null
    }
}

socket.onopen = async () => {
    console.log("CONNECTED!!!");
    while (true) {
        let whattodo = prompt("Type 'new' to create a new room or type 'join' to join an existing one");
        if (whattodo === "new") {
            newGame();
            move["color"] = "WHITE";
            break;
        } else if (whattodo === "join") {
            joinGame();
            move["color"] = "BLACK";
            break;
        }
    }
}
socket.onclose = () => {
    console.log("CONNECTION CLOSED");
}
socket.onmessage = async (event) => {
    console.log("RECEBI:", event.data);
    const message = JSON.parse(event.data);

    if (message.type === "new" && message.success) {
        console.log("CRIANDO JOGO, ID =", message.id);
        id = message.id;
        move["id"] = id;
        console.log("ID: ", id);
        console.log("CALLING DRAWBOARD");
        drawBoard();
        turn = await getTurn();
        await drawPieces();
        drawText(turn.turn);
    }

    if (message.type === "join" && message.success) {
        console.log("JOINING");
        id = message.id;
        move["id"] = id;
        console.log("ID: ", id);
        console.log("CALLING DRAWBOARD");
        images = document.querySelectorAll(".square img");
        images.forEach(img => {
            img.remove();
        });
        squares = document.querySelectorAll(".square");
        squares.forEach(square => {
            square.remove();
        });
        drawBoard();
        turn = await getTurn();
        await drawPieces();
        drawText(turn.turn);
        console.log("JOINED");
    }

    if (message.type === "move" && message.success) {
        console.log("MOVED! REDRAWING...");
        drawPieces();
        turn = getTurn();
        drawText(turn);
    }
}
socket.onerror = (error) => {
    console.log("Deu erro aqui", error);
}

function newGame() {
    let message = {
        "type": "new",
    }
    console.log("NEWING");
    socket.send(JSON.stringify(message));
    console.log("NEWED");
}

function joinGame() {
    id = prompt("Digite o ID da partida");
    let message = {
        "type": "join",
        "id": id,
    }
    socket.send(JSON.stringify(message));
}
async function getTurn() {
    let turn = await fetch(`/getturn/${id}`);
    let data = await turn.json();
    console.log(turn);
    return data["turn"];
}

function makeSquareAButton (square) {
    console.log("MAKING IT A BUTTON");
    square.addEventListener("click", () => {
        console.log("CLICKED");
        select(square);
    });
}

async function select (square) {
    console.log("SELECTING");
    const x = Number(square.dataset.x);
    const y = Number(square.dataset.y);
    const z = Number(square.dataset.z);

    if (move["from"]["x"] === null &&
        move["from"]["y"] === null &&
        move["from"]["z"] === null ){
            console.log("FROM");
            move["from"]["x"] = x;
            move["from"]["y"] = y;
            move["from"]["z"] = z;
            return;
    } else {
        console.log("TO");
        move["to"]["x"] = x;
        move["to"]["y"] = y;
        move["to"]["z"] = z;

        play();

        move["from"]["x"] = null;
        move["from"]["y"] = null;
        move["from"]["z"] = null;
    }
}

async function play () {
    console.log(JSON.stringify(move));
    const response = await fetch(`/move`, {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify(move)
    });
    const answer = await response.json();
}

function drawBoard() {
    console.log("DRAWINGBOARDING")
    let z = 0;
    boards.forEach(board => {
        for (let x = 0; x < 6; x++) {
            const line = document.createElement("div");
            line.classList.add("line");

            board.appendChild(line);

            for (let y = 0; y < 6; y++) {
                const square = document.createElement("div");

                square.classList.add("square");

                if ((x + y) % 2 == 0) {
                    square.classList.add("white");
                } else {
                    square.classList.add("black");
                }

                square.dataset.x = x;
                square.dataset.y = y;
                square.dataset.z = z;

                line.appendChild(square);

                makeSquareAButton(square);
            }
        }
        z++
    });
}

async function drawPieces() {
    const response = await fetch(`/getspace/${id}`);
    const space = await response.json();

    for (let z = 0; z < 6; z++) {
        for (let y = 0; y < 6; y++) {
            for (let x = 0; x < 6; x++) {
                let square = document.querySelector(`.square[data-x="${x}"][data-y="${y}"][data-z="${z}"]`);
                let oldimage = square.querySelector("img");
                if (oldimage) {
                    oldimage.remove();
                }
                let id = space[x][y][z];
                console.log(id);
                if (id !== null) {
                    let minid = id.slice(0,2);

                    let image = document.createElement("img");
                    image.src = `/assets/textures/${minid}.png`;

                    if (square) {
                        square.appendChild(image);
                    }
                }
            }
        }
    }
}

async function drawText(turn) {
    let turntext = document.getElementById("turn");
    let youretext = document.getElementById("youre");
    let gameidtext = document.getElementById("game");
    gameidtext.textContent = id;
    youretext.textContent = move["color"];
    turntext.textContent = turn;
    console.log("Turn: ", turn);
    console.log("Text drawn");
}
