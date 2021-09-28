/**
 * @file player.cc
 * @author y3285wan
 * 
 */


#include <fstream>
#include <vector>

#include "player.h"


void _createFile() {
    std::ofstream savedata;
    savedata.open(PLAYERINFO_STORAGE_PATH);
    savedata.close();
}


PlayerSaveData _createPlayer(std::string &name) {
    std::ofstream savedata;
    savedata.open(PLAYERINFO_STORAGE_PATH, std::ios_base::app);
    savedata << name << " 0\n";
    savedata.close();
    return {
        name, 0
    };
}


PlayerSaveData _findPlayer(std::string &name) {
    std::ifstream savedata;
    savedata.open(PLAYERINFO_STORAGE_PATH);
    if (!savedata.is_open()) {
        _createFile();
    }
    std::string thename;
    int score;
    while (savedata >> thename >> score) {
        if (thename == name) {
            savedata.close();
            return {
                thename, score
            };
        }
    }
    savedata.close();
    throw util::PlayerNotFound{};
}


PlayerSaveData queryPlayer(std::string &name) {
    try {
        return _findPlayer(name);
    }
    catch (const util::PlayerNotFound &err) {
        return _createPlayer(name);
    }
}

#include <iostream>
bool updatePlayerHiScore(std::string &name, int score) {
    std::ifstream savedata;
    savedata.open(PLAYERINFO_STORAGE_PATH);
    std::vector<std::pair<std::string, int>> entires;
    std::string thename;
    int thescore;
    while (savedata >> thename >> thescore) {
        if (thename == name) {
            thescore = score;
        }
        entires.emplace_back(std::pair<std::string, int>{thename, thescore});
    }
    savedata.close();

    std::ofstream savedata2;
    savedata2.open(PLAYERINFO_STORAGE_PATH);
    for (auto &p: entires) {
        savedata2 << p.first.c_str() << " " << p.second << "\n";
    }
    savedata2.close();
}




