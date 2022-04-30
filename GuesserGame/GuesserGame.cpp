// GuesserGame.cpp : The app core.

#include "GuesserGame.h";

using namespace std;
using namespace chrono;
using json = nlohmann::json;

/* GUESSERGAME */

void clear() {
	system("cls");
}

void sleep(int time) {
	this_thread::sleep_for(seconds(time));
}

// ASCII Art

class ASCII {
	public:
		void gameLogo() {
			cout << "\n";
			cout << "   _____                                _____                      " << endl;
			cout << "  / ____|                              / ____|                     " << endl;
			cout << " | |  __ _   _  ___  ___ ___  ___ _ __| |  __  __ _ _ __ ___   ___ " << endl;
			cout << " | | |_ | | | |/ _ \\/ __/ __|/ _ \\ '__| | |_ |/ _` | '_ ` _ \\ / _ \\" << endl;
			cout << " | |__| | |_| |  __/\\__ \\__ \\  __/ |  | |__| | (_| | | | | | |  __/" << endl;
			cout << "  \\_____|\\__,_|\\___||___/___/\\___|_|   \\_____|\\__,_|_| |_| |_|\\___|" << endl;
			cout << "\n\n";
		}

		void scoreLogo() {
			cout << "\n";
			cout << "   _____                    _                         _ " << endl;
			cout << "  / ____|                  | |                       | |" << endl;
			cout << " | (___   ___ ___  _ __ ___| |__   ___   __ _ _ __ __| |" << endl;
			cout << "  \\___ \\ / __/ _ \\| '__/ _ \\ '_ \\ / _ \\ / _` | '__/ _` |" << endl;
			cout << "  ____) | (_| (_) | | |  __/ |_) | (_) | (_| | | | (_| |" << endl;
			cout << " |_____/ \\___\\___/|_|  \\___|_.__/ \\___/ \\__,_|_|  \\__,_|" << endl;
			cout << "\n\n";
		}

		void exitLogo() {
			cout << "\n";
			cout << "  _______ _                 _          ______           _____  _             _             " << endl;
			cout << " |__   __| |               | |        |  ____|         |  __ \\| |           (_)            " << endl;
			cout << "    | |  | |__   __ _ _ __ | | _____  | |__ ___  _ __  | |__) | | __ _ _   _ _ _ __   __ _ " << endl;
			cout << "    | |  | '_ \\ / _` | '_ \\| |/ / __| |  __/ _ \\| '__| |  ___/| |/ _` | | | | | '_ \\ / _` |" << endl;
			cout << "    | |  | | | | (_| | | | |   <\\__ \\ | | | (_) | |    | |    | | (_| | |_| | | | | | (_| |" << endl;
			cout << "    |_|  |_| |_|\\__,_|_| |_|_|\\_\\___/ |_|  \\___/|_|    |_|    |_|\\__,_|\\__, |_|_| |_|\\__, |" << endl;
			cout << "                                                                        __/ |         __/ |" << endl;
			cout << "                                                                       |___/         |___/ " << endl;
			cout << "\n\n";
		}
};

/* MODULES */

class Score {
	ASCII ASCII;
	public:
		void save() {
			ifstream scoreIfFile("assets/scoreboard.rcf"); json scores = json::parse(scoreIfFile); scoreIfFile.close();

			ofstream scoreOfFile("assets/scoreboard.rcf"); ; scoreOfFile.close();
		}
		void remove(int id) {
			ifstream scoreIfFile("assets/scoreboard.rcf"); json scores = json::parse(scoreIfFile); scoreIfFile.close();
			ofstream scoreOfFile("assets/scoreboard.rcf"); scores.erase(id); scoreOfFile.close();
		}
		void board() {
			ifstream scoreFile("assets/scoreboard.rcf"); json scores = json::parse(scoreFile); scoreFile.close();
			string hold;

			clear();
			ASCII.scoreLogo();

			sleep(1);
			for (int i = 0; i < size(scores); i++) {
				hold = scores[i]["username"];
				cout << "   " << hold << "     " << scores[i]["score"] << endl << endl;
				sleep(1);
			}

			cout << "   Press any key to continue...";
			save();
			getch();
		}
};

/* MENUS */

void devMenu() {

}

void mainMenu() {
	ASCII ASCII;
	Score Score;
	
	clear();
	ASCII.gameLogo();

	cout << "   P: New Game\n";
	cout << "   S: Scoreboard\n";
	cout << "   E: Exit Game\n";

	cout << "\n";
	char uChoice = getch();

	switch (uChoice)
	{
	case 'p':
		cout << "NEW GAME";
		sleep(1);
		break;
	case 's':
		Score.board();
		break;
	case 'e':
		clear();
		ASCII.exitLogo();
		sleep(1);
		clear();
		exit(EXIT_SUCCESS);
		break;
	default:
		clear();
		ASCII.gameLogo();
		cout << "   Invalid Option. Try Again";
		sleep(1);
		break;
	}
}

/* APP */

// App entry point.

int main() {
	while (true) {
		mainMenu();
	}

	return EXIT_SUCCESS;
}
