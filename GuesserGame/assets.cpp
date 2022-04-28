// assets.cpp : App asset manager. Handles most variable content including custom data

#include "assets.h"
#include <filesystem>

using namespace std;
using json = nlohmann::json;
namespace fs = filesystem;

// PACK Functions

void genPACK() {
	string pack;
	json genJSON;
	json testJSON;
	cout << "PACK NAME: ";
	getline(cin, pack);
	// Gen directories.
	fs::create_directories("assets/" + pack + "/data");
	fs::create_directories("assets/" + pack + "/resources/lang");
	// Gen data.
	ofstream genOptionsFile("assets/" + pack + "/data/options.rcf"); genOptionsFile << "{\"numRange\": {\"min\": 1, \"max\": 10}}"; genOptionsFile.close();
	ofstream genScoreFile("assets/" + pack + "/data/scoreboard.rcf"); genScoreFile << "{{\"username\": \"UMR\", \"score\": 100}, {\"username\": \"TSF\", \"score\": 99}}"; genScoreFile.close();
	ofstream genLangFile("assets/" + pack + "/resources/lang/lang.rcf"); genLangFile << "{\"English\": \"en_uk.rlf\"}"; genLangFile.close();
	ofstream genLang_EN_UK("assets/" + pack + "/resources/lang/en_uk.rlf"); genLang_EN_UK << "{\"WIP\": \"WORK IN PROGESS\"}"; genLang_EN_UK.close();
}