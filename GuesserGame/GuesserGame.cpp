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
	public:
		void save() {}
		void remove() {}
		void board() {
			ifstream scoreFile("assets/scoreboard.rcf");
			json scores = json::parse(scoreFile);
			cout << scores[0];
			sleep(3);
		}
};

/* MENUS */

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
		cout << "SCOREBOARD";
		sleep(1);
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

void devMenu() {

}

/* APP */

// App entry point.

int main() {
	while (true) {
		mainMenu();
	}

	return EXIT_SUCCESS;
}
