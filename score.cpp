#include "score.h"

using namespace std;
using json = nlohmann::json;

void clear() {
	cout << "\x1B[2J\x1B[H";
}

namespace score {
    void board() {
        ifstream scoreFile("data/scoreboard.json");
        json scores = json::parse(scoreFile);
        scoreFile.close();
    }
}