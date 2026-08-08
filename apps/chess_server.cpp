#include <crow.h>
#include "engine/Game.h"

int main () {
    crow::SimpleApp app;

    Game game;

    CROW_ROUTE(app, "/") ([]() {
        return "Hello World";
    });

    /*CROW_ROUTE(app, "/whoshere").methods(crow::HTTPMethod::Post) ([&](const crow::request& req) {

        auto json = crow::json::load(req.body);

        std::string id = json["piece"].s();
        int x = json["position"][0].i();
        int y = json["position"][1].i();
        int z = json["position"][2].i();

        Position pos(x, y, z);

        crow::json::wvalue answer;

        crow::json::wvalue space;
        Piece* piece;
        for (int z = 0; z < 6; z++) {
            for (int y = 0; y < 6; y++) {
                for (int x = 0; x < 6; x++) {
                    piece = game.getBoard()->whatIsInSpaceAt(x, y, z);
                    answer["space"][x][y][z] = piece->getId();
                }
            }
        }

        answer["status"] = valid;

        return answer;
    });*/

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

        return space;
    });

    CROW_ROUTE(app, "/move").methods(crow::HTTPMethod::POST) ([&](const crow::request& req) {
        auto json = crow::json::load(req.body);
        crow::json::wvalue answer;

        if (!json) {
            return crow::response(400, "JSON inválido");
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

        if (!piece) {
            answer["success"] = false;
            return crow::response(400, answer);
        }

        Move move(piece->getId(), to);

        bool success = game.getBoard()->play(move, game.getTurn());

        answer["success"] = success;

        return crow::response(answer);
    });

    app.port(18080).multithreaded().run();
}