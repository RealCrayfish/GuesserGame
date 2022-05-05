// GuesserGame.cpp : The app core.

#include "GuesserGame.h";

using namespace std;
using namespace chrono;
using json = nlohmann::json;

/* GUESSERGAME */

bool dev_viewNumber = false;

int MIN;
int MAX;

int score;

void clear() {
	cout << "\x1B[2J\x1B[H";
}

void sleep(int time) {
	this_thread::sleep_for(seconds(time));
}

// Options

void loadOptions() {
	ifstream optionsIfFile("assets/options.rcf");
	json options = json::parse(optionsIfFile);
	optionsIfFile.close();
	
	MIN = options["numRange"]["min"];
	MAX = options["numRange"]["max"];
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

		void devLogo() {
			cout << "\n";
			cout << "  _____               __  __           _      " << endl;
			cout << " |  __ \\             |  \\/  |         | |     " << endl;
			cout << " | |  | | _____   __ | \\  / | ___   __| | ___ " << endl;
			cout << " | |  | |/ _ \\ \\ / / | |\\/| |/ _ \\ / _` |/ _ \\" << endl;
			cout << " | |__| |  __/\\ V /  | |  | | (_) | (_| |  __/" << endl;
			cout << " |_____/ \\___| \\_/   |_|  |_|\\___/ \\__,_|\\___|" << endl;
			cout << "\n\n";
		}
};

/* MODULES */

class Score {
	ASCII ASCII;
public:
	void save(string username, int score) {
		ifstream scoreIfFile("assets/scoreboard.rcf"); json scores = json::parse(scoreIfFile); scoreIfFile.close();
		scores.insert(scores.end(), json::parse("{\"username\": \"" + username + "\", \"score\": " + to_string(score) + " }"));
		ofstream scoreOfFile("assets/scoreboard.rcf"); scoreOfFile << scores.dump(4); scoreOfFile.close();
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
		getch();
	}
};

class Game {
	ASCII ASCII;
	Score Score;
	public:
		void nextGuess() {
			int cAns = rand() % MAX + MIN;
			int points = 10;

			while (bool hold = true) {
				clear();
				ASCII.gameLogo();

				if (dev_viewNumber) {
					cout << "   Answer: " << cAns << endl;
				}
				cout << "   Guess a number between " << MIN << " and " << MAX << endl << endl << "   ";

				string uString;
				getline(cin, uString);
				int uAns = stoi(uString);

				if (uAns == cAns) {
					clear();
					ASCII.gameLogo();
					score += points;
					cout << "   Correct! +" << points << " points" << endl;
					sleep(3);
					hold = false;
					break;
				}
				else {
					if (points > 0) {
						points--;
					}
					clear();
					ASCII.gameLogo();
					cout << "   Incorrect. Try again.";
					sleep(1);
				}

				sleep(3);
			}
		}
		void newGame() {
			clear();
			ASCII.gameLogo();
			score = 0;

			cout << "   Enter Your Initials:\n" << endl;
			char charInitials;
			string initials;

			charInitials = toupper(getch());
			cout << "      " << charInitials;
			initials += toupper(charInitials);

			charInitials = toupper(getch());
			cout << charInitials;
			initials += toupper(charInitials);

			charInitials = toupper(getch());
			cout << charInitials;
			initials += toupper(charInitials);

			sleep(3);
			clear();
			ASCII.gameLogo();

			cout << "   How To Play:\n" << endl;
			cout << "      You have to guess a number between " << MIN << " and " << MAX << "for 10 rounds." << endl;
			cout << "      For each round, you have the chance to earn up to 10 points." << endl;
			cout << "      Your goal is to aim for 100 points.\n" << endl;
		
			cout << "   Press any key to continue...";
			getch();

			for (int i = 0; i < 10; i++) {
				nextGuess();
			}

			clear();
			ASCII.gameLogo();
			cout << "   Final Score: " << score << endl << endl;
			cout << "   Would you like to save your score? (Y/N)" << endl;
			char saveScore = getch();

			if (tolower(saveScore) == 'y') {
				clear();
				ASCII.gameLogo();
				Score.save(initials, score);
				cout << "   Score Saved! Returning to Main Menu...";
				sleep(3);
			}
			else {
				clear();
				ASCII.gameLogo();
				cout << "   Score Discarded. Returning to Main Menu...";
				sleep(3);
			}
			sleep(5);
		}
};

/* DEV MODE */

class Dev {
	ASCII ASCII;
	Score Score;

	public:
		void numRange() {
			ifstream optionsIfFile("assets/options.rcf"); json devOptions = json::parse(optionsIfFile); optionsIfFile.close();
			
			clear();
			ASCII.devLogo();
			cout << "   Enter new minimum number:\n\n   ";
			string newStringMin;
			getline(cin, newStringMin);
			devOptions["numRange"]["min"] = stoi(newStringMin);

			clear();
			ASCII.devLogo();
			cout << "   Enter new maximum number:\n\n   ";
			string newStringMax;
			getline(cin, newStringMax);
			devOptions["numRange"]["max"] = stoi(newStringMax);

			ofstream optionsOfFile("assets/options.rcf"); optionsOfFile << devOptions.dump(4); optionsOfFile.close();
		}
		void scoreboard() {
			ifstream scoreIfFile("assets/scoreboard.rcf"); json devScores = json::parse(scoreIfFile); scoreIfFile.close();
			string hold;

			clear();
			ASCII.scoreLogo();

			sleep(1);
			for (int i = 0; i < size(devScores); i++) {
				hold = devScores[i]["username"];
				cout << "   " << hold << "      " << devScores[i]["score"] << "      ID: " << i << endl << endl;
				sleep(1);
			}

			cout << "   Enter ID to remove or any non-ID number to cancel\n\n   ";
			string strID;
			getline(cin, strID);
			int ID = stoi(strID);

			sleep(1);
			devScores.erase(ID);
			ofstream scoreOfFile("assets/scoreboard.rcf"); scoreOfFile << devScores.dump(4); scoreOfFile.close();

			Score.board();
		}

		void devMenu() {

			while (bool hold = true) {
				clear();
				ASCII.devLogo();
				string fUsername;
				string fStrScore;

				cout << "   N: Number Range\n";
				cout << "   S: Scoreboard\n";
				cout << "   F: Create Fake Score\n";
				cout << "   E: Exit Dev Mode\n";

				cout << "\n";
				char uChoice = tolower(getch());

				switch (uChoice)
				{
				case 'n':
					numRange();
					break;
				case 's':
					scoreboard();
					break;
				case 'f':
					clear();
					ASCII.devLogo();
					int fScore;
					cout << "   Enter Fake Username: ";
					getline(cin, fUsername);
					cout << "   Enter Fake Score: ";
					getline(cin, fStrScore);
					fScore = stoi(fStrScore);
					Score.save(fUsername, fScore);
					cout << "   Fake Score Saved";
					sleep(3);
					break;
				case 'e':
					clear();
					ASCII.devLogo();
					hold = false;
					cout << "   Returning to Main Menu...";
					sleep(3);
					return;
					break;
				default:
					clear();
					ASCII.devLogo();
					cout << "   Invalid Option. Try Again";
					sleep(1);
					break;
				}
			}
		}
};

/* MAIN MENU */

void mainMenu() {
	Game Game;
	ASCII ASCII;
	Score Score;
	Dev Dev;
	
	clear();
	ASCII.gameLogo();

	cout << "   P: New Game\n";
	cout << "   S: Scoreboard\n";
	cout << "   E: Exit Game\n";

	cout << "\n";
	char uChoice = tolower(getch());

	switch (uChoice)
	{
	case 'p':
		Game.newGame();
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
	case 'd':
		Dev.devMenu();
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
	loadOptions();

	while (true) {
		mainMenu();
	}

	return EXIT_SUCCESS;
}