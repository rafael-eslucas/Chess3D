#include <crow.h>
#include <crow/middlewares/cors.h>
#include "engine/Game.h"

#include <fstream>

#include "engine/Player.h"

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    return std::string(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
}
Game* findGame(std::string id, std::vector<Game*>& games) {
    for (auto game : games) {
        if (game->getId() == id) {
            return game;
        }
    } return nullptr;
}
Game* newGame (std::vector<Game*>& games, int n) {
    Game* game = new Game();
    game->setId(n);
    games.push_back(game);
    return game;
};

int main () {
    std::vector<OnlinePlayer*> players;
    int gameAmount = 1;
    std::vector<Game*> games;

    crow::App<crow::CORSHandler> app;
    std::cout << std::filesystem::current_path() << '\n';

    auto& cors = app.get_middleware<crow::CORSHandler>();

    cors.global()
        .headers("Content-Type")
        .methods("GET"_method, "POST"_method);


    CROW_ROUTE(app, "/")([] {
        crow::response response(readFile("apps/web/index.html"));
        response.set_header("Content-Type", "text/html");
        return response;
    });

    CROW_ROUTE(app, "/index.html")([] {
        crow::response response(readFile("apps/web/index.html"));
        response.set_header("Content-Type", "text/html");
        return response;
    });
    //bychatgpt
    CROW_ROUTE(app, "/assets/<path>") ([](std::string path) {
        std::string filename = "apps/web/assets/" + path;

        std::ifstream file(filename, std::ios::binary);

        if (!file) {
            return crow::response(404);
        }

        std::string data(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );

        crow::response response(data);

        if (path.ends_with(".png")) {
            response.set_header("Content-Type", "image/png");
        }

        return response;
    });

    CROW_ROUTE(app, "/script.js")([] {
        crow::response response(readFile("apps/web/script.js"));
        response.set_header("Content-Type", "application/javascript");
        return response;
    });

    CROW_ROUTE(app, "/style.css")([] {
        crow::response response(readFile("apps/web/style.css"));
        response.set_header("Content-Type", "text/css");
        return response;
    });

    CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onopen([&](crow::websocket::connection& conn) {
            std::cout <<"aaaa"<<std::endl;
        })
        .onmessage([&](crow::websocket::connection& conn,
                       const std::string& msg,
                       bool is_binary) {
            auto json = crow::json::load(msg);

            if (json["type"] == "new") {
                /* ==========  Cria o jogo  ========== */
                Game* game = newGame(games, gameAmount);
                std::cout << "game created " << game->getId() << std::endl;
                gameAmount++;

                /* ==========  Cria o jogador branco  ========== */
                OnlinePlayer* player = new OnlinePlayer(*game, conn, Side::White);
                players.push_back(player);
                game->setWhitePlayer(player);
                crow::json::wvalue answer;
                answer["success"] = true;
                answer["type"] = "new";
                answer["id"] = game->getId();
                crow::response response(200, answer);
                conn.send_text(answer.dump());
                std::cout << "SENT: " << answer.dump();
                return;
            }

            if (json["type"] == "join") {
                /* ==========  Encontra o jogo  ========== */
                Game* game = findGame(json["id"].s(), games);
                /* ==========  Erro se nao existir  ========== */
                if (!game || game->getBlackPlayer()) {
                    std::cout << "Game" << json["id"].s() << "not found" << std::endl;
                    std::cout << "The games are ";
                    for (auto game : games) {
                        std::cout << game->getId() << " ";
                    }
                    crow::json::wvalue answer;
                    answer["success"] = false;
                    answer["type"] = "join";
                    crow::response response(204, answer);
                    conn.send_text(answer.dump());
                    std::cout << "SENT: " << answer.dump();
                    return;
                } if (game) {
                    /* ==========  Cria o jogador preto  ========== */
                    std::cout << "Game " << game->getId() << " found" << std::endl;
                    OnlinePlayer* player = new OnlinePlayer(*game, conn, Side::Black);
                    players.push_back(player);
                    game->setBlackPlayer(player);
                    crow::json::wvalue answer;
                    answer["success"] = true;
                    answer["type"] = "join";
                    answer["id"] = game->getId();
                    crow::response response(200, answer);
                    conn.send_text(answer.dump());
                    std::cout << "SENT: " << answer.dump();
                    return;
                }
            }
            std::cout << "Connected!";
        })
        .onclose([&](crow::websocket::connection& conn,
                     const std::string& reason,
                     uint16_t code) {
            std::cout << reason << std::endl;
            for (auto it = players.begin(); it != players.end(); ++it) {
                if (&(*it)->conn == &conn) {
                    Game& game = (*it)->game;
                    if (game.getBlackPlayer() == *it) {
                        game.setBlackPlayer(nullptr);
                    } if (game.getWhitePlayer() == *it) {
                        game.setWhitePlayer(nullptr);
                    }
                    delete *it;
                    players.erase(it);
                    std::cout << "disconnected";
                    break;
                }
            }
        });

    CROW_ROUTE(app, "/getspace/<string>") ([&](std::string id) {
        Game* game = findGame(id, games);
        if (!game) {
            crow::json::wvalue answer;
            answer["success"] = false;
            crow::response response(204, answer);
            return response;
        }
        crow::json::wvalue space;
        Piece* piece;

        for (int z = 0; z < 6; z++) {
            for (int y = 0; y < 6; y++) {
                for (int x = 0; x < 6; x++) {
                    piece = game->getBoard()->whatIsInSpaceAt(x, y, z);
                    if (piece) {
                        space[x][y][z] = piece->getId();
                    } else {
                        space[x][y][z] = nullptr;
                    }
                }
            }
        }
        crow::response response(space);
        response.set_header("Access-Control-Allow-Origin", "*");
        return response;
    });

    CROW_ROUTE(app, "/getturn/<string>") ([&](std::string id) {
        Game* game = findGame(id, games);
        if (!game) {
            crow::json::wvalue answer;
            answer["success"] = false;
            crow::response response(204, answer);
            return response;
        }

        std::string turn = game->getTurn() == Side::White ? "WHITE" : "BLACK";
        crow::json::wvalue answer;
        answer["success"] = true;
        answer["turn"] = turn;
        crow::response response(200, answer);
        return response;
    });

    CROW_ROUTE(app, "/move").methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS) ([&](const crow::request& req) {
        auto json = crow::json::load(req.body);
        crow::json::wvalue answer;
        Game* game = findGame(json["id"].s(), games);

        if (!game) {
            answer["success"] = false;
            answer["type"] = "move";
            crow::response response(204, answer);
            return response;
        }

        if (!json) {
            answer["success"] = false;
            crow::response response(400, answer);
            std::cout << "JSON inválido" << std::endl;
            return response;
        }

        Position from(
            json["from"]["x"].i(),
            json["from"]["y"].i(),
            json["from"]["z"].i()
        );
        Position to(
            json["to"]["x"].i(),
            json["to"]["y"].i(),
            json["to"]["z"].i()
        );

        Piece* piece = game->getBoard()->whatIsInSpaceAt(from.x, from.y, from.z);
        std::cout << from.x << " " << from.y << " " << from.z << std::endl;

        if (!piece) {
            answer["success"] = false;
            answer["type"] = "move";
            std::cout << "Nenhuma peça aqui" << std::endl;
            crow::response response(400, answer);
            response.set_header("Access-Control-Allow-Origin", "*");
            return response;
        }

        Move move(piece->getId(), to);

        Side color = json["color"] == "WHITE" ? Side::White : Side::Black;
        bool success = game->play(move, color);

        if (success) {
            crow::json::wvalue answer;

            answer["success"] = true;
            answer["type"] = "move";
            answer["turn"] = game->getTurn() == Side::White ? "WHITE" : "BLACK";

            for (auto player : players) {
                player->conn.send_text(answer.dump());
            }
        }

        answer["success"] = success;
        answer["type"] = "move";
        crow::response response(answer);
        response.set_header("Access-Control-Allow-Origin", "*");

        return response;
    });

    app.port(18080).multithreaded().run();
}