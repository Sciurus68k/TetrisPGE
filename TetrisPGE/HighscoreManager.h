#pragma once
#include <string>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
struct Score {
	std::string name = "AAAAAAAAA";
	int score = 0;
};

class HighscoreManager
{

private:
	std::string file;
public:

	Score scores[10];
	
	HighscoreManager() {
#ifdef __EMSCRIPTEN__
		file = "/store/highscore.txt";
#else
		file = "highscore.txt";
#endif	
	}

	void Load() {
		
		std::fstream highscoreFile;
		highscoreFile.open(file, std::ios::in);
		if (!highscoreFile) {
			Save();
			return;
		}

		std::string line;
		int lineCount = 0;
		int sepIndex = -1;
		while (getline(highscoreFile, line)) {
			sepIndex = line.find('|');
			if (sepIndex > -1)
			{
				scores[lineCount].name = line.substr(0, sepIndex);
				scores[lineCount].score = atoi(line.substr(sepIndex + 1).c_str());
				lineCount++;
			}
		}

		highscoreFile.close();
	}

	void Save() {
		std::fstream highscoreFile;
		highscoreFile.open(file, std::ios::out);

		if (!highscoreFile) return;

		for (int i = 0; i < 10; i++) {
			highscoreFile << scores[i].name << "|" << scores[i].score << "\n";
		}

		highscoreFile.close();

#ifdef __EMSCRIPTEN__
		EM_ASM(
			FS.syncfs(function(err) {
				if (err) alert("Error on syncing FS: " + err);
			});
		);
#endif
	}

	bool IsInList (int score) {
		return scores[9].score < score; // assume that the highscore list is ordered ;) 
	}

	void AddScore(std::string name, int score) {
		int pos = 0; 
		for (int i = 0; i < 10; i++) {
			if (scores[i].score < score) {
				pos = i;
				break;
			}
		}

		for (int j = 9; j > pos; j--) {
			scores[j].name = scores[j - 1].name;
			scores[j].score = scores[j - 1].score;
		}

		scores[pos].name = name;
		scores[pos].score = score;
		Save();
	}
};

