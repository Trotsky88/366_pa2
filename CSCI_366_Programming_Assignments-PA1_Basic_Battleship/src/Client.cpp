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
#include "Client.hpp"

Client::~Client() {
}


void Client::initialize(unsigned int player, unsigned int board_size){
    if(player > 2 || player <1){
        throw ClientException("Wrong");
    }else initialized = true;


    vector<vector<int>> vec(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    ofstream array_ofp("player_1.action_board.json"); // create an output file stream
    cereal::JSONOutputArchive write_archive(array_ofp); // initialize an archive on the file
    write_archive(cereal::make_nvp("board", vec)); // serialize the data giving it a name

}


void Client::fire(unsigned int x, unsigned int y) {
    ofstream outFile("player_1.shot.json");
    cereal::JSONOutputArchive archiveOut(outFile);

    archiveOut(CEREAL_NVP(x), CEREAL_NVP(y));
}


bool Client::result_available() {

}


int Client::get_result() {
    int result;

    ifstream sFile("player_1.result.json");
    cereal::JSONInputArchive arch(sFile);
    arch(result);


    if(result <-1 or result >1){
        throw ClientException("wrong");
    }
    remove("player_1.result.json");
    return result;

}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
    vector<vector<int>> vec2(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));

    vec2[y][x] = result;

    ofstream array_ofp("player_1.action_board.json"); // create an output file stream
    cereal::JSONOutputArchive write_archive(array_ofp); // initialize an archive on the file
    write_archive(cereal::make_nvp("board", vec2)); // serialize the data giving it a name


}


string Client::render_action_board(){
}