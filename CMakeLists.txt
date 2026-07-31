cmake_minimum_required(VERSION 4.1)
project(Chess3D)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib CONFIG REQUIRED)

add_executable(chess src/main.cpp
        src/Piece.cpp
        include/Piece.h
        src/Board.cpp
        include/Board.h
        src/Move.cpp
        include/Move.h
        include/Vector.h
        src/Position.cpp
        include/Position.h
        include/Side.h
        src/pieces/Rook.cpp
        include/pieces/Rook.h
        include/Type.h
        src/pieces/Bishop.cpp
        include/pieces/Bishop.h
        src/Vector.cpp
        src/pieces/Queen.cpp
        include/pieces/Queen.h
        src/pieces/Knight.cpp
        include/pieces/Knight.h
        src/pieces/King.cpp
        include/pieces/King.h
        src/pieces/Pawn.cpp
        include/pieces/Pawn.h
        src/Rules.cpp
        include/Rules.h
        include/Last.h
        include/Last.h
        src/Screen.cpp
        include/Screen.h
        include/Screen.h
        src/Game.cpp
        include/Game.h
        utils/utils.cpp
        utils/utils.h
)


target_include_directories(chess PRIVATE include)
target_include_directories(chess PRIVATE include/pieces)

target_link_libraries(chess PRIVATE raylib)