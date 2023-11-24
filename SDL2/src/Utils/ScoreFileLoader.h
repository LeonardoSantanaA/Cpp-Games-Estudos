#pragma once

#include <fstream>
#include <string>
#include <vector>


static const int NAME_SIZE = 3;

struct Score {
	char name[NAME_SIZE];
	int score;
};

class ScoreFileLoader {
public:
	void LoadScoreFileLoader(const std::string& scorePath); 
	bool VerifyScoreToWrite(int& index, int score);
	std::string PrintName(const char* name);
	void SaveScoreToFile(const std::string& scorePath, const char* name, int score); 

private:
	static const int SCORES_TO_SHOW = 10;
	static const int SCORES_REAL_SIZE = SCORES_TO_SHOW + 1;
	Score scores[SCORES_REAL_SIZE];
};