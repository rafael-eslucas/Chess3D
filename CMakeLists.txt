cmake_minimum_required(VERSION 4.1)
project(Chess3D)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib CONFIG REQUIRED)

#add_executable(chess main.cpp
#        src/Piece.cpp
#        include/Piece.h
#        src/Board.cpp
#        include/Board.h
#        src/Move.cpp
#        include/Move.h
#        include/Vector.h
#        src/Position.cpp
#        include/Position.h
#        include/Side.h
#        src/pieces/Rook.cpp
#        include/pieces/Rook.h
#        include/Type.h
#        src/pieces/Bishop.cpp
#        include/pieces/Bishop.h
#        src/Vector.cpp
#        src/pieces/Queen.cpp
#        include/pieces/Queen.h
#        src/pieces/Knight.cpp
#        include/pieces/Knight.h
#        src/pieces/King.cpp
#        include/pieces/King.h
#        src/pieces/Pawn.cpp
#        include/pieces/Pawn.h
#        src/Rules.cpp
#        include/Rules.h
#        include/Last.h
#        include/Last.h
#        src/Screen.cpp
#        src/Game.cpp
#        include/Game.h
#        utils/utils.cpp
#        utils/utils.h
#)

add_library(chess_engine STATIC
        src/engine/Piece.cpp
        include/engine/Piece.h
        src/engine/Board.cpp
        include/engine/Board.h
        src/engine/Move.cpp
        include/engine/Move.h
        include/engine/Vector.h
        src/engine/Position.cpp
        include/engine/Position.h
        include/engine/Side.h
        src/pieces/Rook.cpp
        include/pieces/Rook.h
        include/engine/Type.h
        src/pieces/Bishop.cpp
        include/pieces/Bishop.h
        src/engine/Vector.cpp
        src/pieces/Queen.cpp
        include/pieces/Queen.h
        src/pieces/Knight.cpp
        include/pieces/Knight.h
        src/pieces/King.cpp
        include/pieces/King.h
        src/pieces/Pawn.cpp
        include/pieces/Pawn.h
        src/engine/Rules.cpp
        include/engine/Rules.h
        include/engine/Last.h
        include/engine/Last.h
        src/engine/Game.cpp
        include/engine/Game.h
        utils/utils.h
        include/engine/Player.h
)

add_executable(chess_desktop apps/chess_desktop.cpp
        include/graphics/Screen.h
        src/graphics/Screen.cpp
)

target_link_libraries(chess_desktop PRIVATE
        chess_engine
        raylib
)

add_executable(chess_server apps/chess_server.cpp)

target_link_libraries(chess_server PRIVATE
        chess_engine
)


#target_include_directories(chessDesktop PRIVATE include)
#target_include_directories(chessServer PRIVATE include)
target_include_directories(chess_engine PUBLIC include)

#target_link_options(chess PRIVATE
#        -static-libgcc
#        -static-libstdc++
#)