#include <crow.h>
#include <crow/middlewares/cors.h>
#include "engine/Game.h"

#include <fstream>

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    return std::string(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
}

int main () {
    std::vector<crow::websocket::connection*> players;

    crow::App<crow::CORSHandler> app;
    std::cout << std::filesystem::current_path() << '\n';

    auto& cors = app.get_middleware<crow::CORSHandler>();

    cors.global()
        .headers("Content-Type")
        .methods("GET"_method, "POST"_method);

    Game game;

    CROW_ROUTE(app, "/")([] {
        crow::response response(readFile("apps/web/index.html"));
        response.set_header("Content-Type", "text/html");
        return response;
    });

    CROW_ROUTE(app, "/assets/<path>")
([](std::string path) {
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
            players.push_back(&conn);
            std::cout << "Connected!";
        })
        .onmessage([&](crow::websocket::connection& conn,
                       const std::string& msg,
                       bool is_binary) {
            std::cout << msg << std::endl;
        })
        .onclose([&](crow::websocket::connection& conn,
                     const std::string& reason,
                     uint16_t code) {
            std::cout << reason << std::endl;
            for (auto it = players.begin(); it != players.end(); ++it) {
                if (*it == &conn) {
                    players.erase(it);
                    std::cout << "disconnected";
                    break;
                }
            }
        });

    CROW_ROUTE(app, "/getspace") ([&]() {
        crow::json::wvalue space;
        Piece* piece;
        for (int z = 0; z < 6; z++) {
            for (int y = 0; y < 6; y++) {
                for (int x = 0; x < 6; x++) {
                    piece = game.getBoard()->whatIsInSpaceAt(x, y, z);
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

    CROW_ROUTE(app, "/getturn") ([&]() {
        std::string turn = game.getTurn() == Side::White ? "WHITE" : "BLACK";
        return turn;
    });

    CROW_ROUTE(app, "/move").methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS) ([&](const crow::request& req) {
        auto json = crow::json::load(req.body);
        crow::json::wvalue answer;

        if (!json) {
            crow::response response(400, "JSON inválido");
            std::cout << "JSON inválido" << std::endl;
            response.set_header("Access-Control-Allow-Origin", "*");
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

        Piece* piece = game.getBoard()->whatIsInSpaceAt(from.x, from.y, from.z);
        std::cout << from.x << " " << from.y << " " << from.z << std::endl;

        if (!piece) {
            answer["success"] = false;
            std::cout << "Nenhuma peça aqui" << std::endl;
            crow::response response(400, answer);
            response.set_header("Access-Control-Allow-Origin", "*");
            return response;
        }

        Move move(piece->getId(), to);

        bool success = game.play(move, game.getTurn());

        if (success) {
            crow::json::wvalue answer;

            answer["success"] = true;
            answer["turn"] = game.getTurn() == Side::White ? "WHITE" : "BLACK";

            for (auto player : players) {
                player->send_text(answer.dump());
            }
        }

        answer["success"] = success;
        crow::response response(answer);
        response.set_header("Access-Control-Allow-Origin", "*");

        return response;
    });

    app.port(18080).multithreaded().run();
}