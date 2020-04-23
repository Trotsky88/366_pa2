//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "common.hpp"
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
    return(0);
}

char p1Board[BOARD_SIZE][BOARD_SIZE];
char p2Board[BOARD_SIZE][BOARD_SIZE];


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){
    this -> board_size = board_size;
    if(board_size != BOARD_SIZE){
        throw ServerException("Wrong");
    }

    if("player_1.setup_board.txt" != p1_setup_board or "player_2.setup_board.txt" != p2_setup_board){
        throw ServerException("Wrong");
    }

    int i = 0;
    int j = 0;

    ifstream p1File (p1_setup_board);
    ifstream p2File (p2_setup_board);

    if(p1File.is_open()){
        for(i =0; i <BOARD_SIZE; i++) {
            for (j = 0; j < BOARD_SIZE; j++) {
                p1File >> p1Board[i][j];
            }
        }
    }

    if(p2File.is_open()){
        for(i =0; i <BOARD_SIZE; i++) {
            for (j = 0; j < BOARD_SIZE; j++) {
                p2File >> p2Board[i][j];
            }
        }
    }
}


Server::~Server() {
}


BitArray2D *Server::scan_setup_board(string setup_board_name) {
    p1_setup_board = new BitArray2D(BOARD_SIZE, BOARD_SIZE);
    p2_setup_board = new BitArray2D(BOARD_SIZE, BOARD_SIZE);

    for (int i = 0; i < BOARD_SIZE; i++) {
        for ( int j = 0; j < BOARD_SIZE; j++){
            if(p2Board[i][j] != '_'){
                p2_setup_board->set(i,j);
            }
        }
    }

}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    if(player >2 or player < 1){
        throw ServerException("Wrong");
    }

    if(x >= BOARD_SIZE or y >= BOARD_SIZE){
        return OUT_OF_BOUNDS;
    }

    if (player == 1){
        if(p2Board[y][x] == '_'){
            return MISS;
        }
        else {
            return HIT;
        }
    }
}


int Server::process_shot(unsigned int player) {
    int x;
    int y;

    if(player > 2 || player <1){
        throw ServerException("Wrong");
    }

    ifstream sFile("player_1.shot.json");
    cereal::JSONInputArchive arch(sFile);
    arch(x,y);
    //sFile.close();
    int result = evaluate_shot(player,x,y);

    ofstream outFile("player_1.result.json");

    cereal::JSONOutputArchive archiveOut(outFile);

    archiveOut(CEREAL_NVP(result));

    remove("player_1.shot.json");

    return NO_SHOT_FILE;
}