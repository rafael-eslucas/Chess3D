let boards = document.querySelectorAll(".board2d");


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
            }
        }
        z++
    });
}

drawBoard();
async function drawPieces() {
    let squares = document.querySelectorAll(".square");
    const response = await fetch("http://localhost:18080/getspace");
    const space = await response.json();
    let z = 0;
    boards.forEach(Board => {
        for (let x = 0; x < 6; x++) {
            for (let y = 0; y < 6; y++) {
                let id = space[x][y][z];
                if (id !== null) {
                    let minid = id.slice(0,2)
                    console.log(minid);
                    let image = document.createElement("img");
                    image.src = `/assets/textures/${minid}.png`;
                    squares.forEach(square => {
                        if (Number(square.dataset.x) === x &&
                            Number(square.dataset.y) === y &&
                            Number(square.dataset.z) === z ){
                            square.appendChild(image);
                        }
                    })
                }
            }
        }
        z++;
    });
}

drawPieces();