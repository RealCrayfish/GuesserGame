// assets.cpp : App asset manager. Handles most variable content including custom data

#include "assets.h"
#include <filesystem>

using namespace std;
using json = nlohmann::json;
namespace fs = filesystem;

// Variables

string pack;

// THIS MUST STAY AT THE TOP
void loadPACK() {
	ifstream packDATA("assets/test.txt");
	getline(packDATA, pack);
}

void setPACK() { }

void loadOPTIONS() {
	loadPACK();
	ifstream optionFile("assets/" + pack + "/data/options.rcf");
	auto options = json::parse(optionFile);
	cout << options["numRange"]["min"];
}
