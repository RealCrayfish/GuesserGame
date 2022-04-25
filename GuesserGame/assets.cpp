// assets.cpp : App asset manager. Handles most variable content including custom data

#include "assets.h"
#include <filesystem>

using namespace std;
using json = nlohmann::json;
namespace fs = filesystem;

// PACK Functions

void genPACK() {
	string pack;
	cout << "PACK NAME: ";
	getline(cin, pack);
	// Gen directories.
	fs::create_directories("assets/" + pack + "/data");
	fs::create_directories("assets/" + pack + "/resources/lang");
	// Gen data.
	ofstream optionsFile("assets/" + pack + "/data/options.rcf");
	optionsFile.write("{\"numRange\": {\"min\": 1, \"max\": 10}}");
}