const socket = new WebSocket("/ws");

let turn;

let boards = document.querySelectorAll(".board2d");

let ip = "192.168.3.138";

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
    turn = await getTurn();
    drawBoard();
    drawPieces();
    drawText(turn);
}
socket.onclose = (event) => {
    console.log("CONNECTION CLOSED");
}
socket.onmessage = async (event) => {
    const message = JSON.parse(event.data);
    turn = await getTurn();
    drawPieces();
    drawText(turn);
}
socket.onerror = (error) => {
    console.log("Deu erro aqui", error);
}

async function getTurn() {
    let turn = await fetch("/getturn");
    console.log(turn);
    return turn.text();
}


function makeSquareAButton (square) {
    console.log("MAKING IT A BUTTON");
    square.addEventListener("click", () => {
        console.log("CLICKED");
        select(square);
    });
}

function select (square) {
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
    const response = await fetch(`/getspace`);
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
    turntext.textContent = turn;
    console.log("Text drawn");
}