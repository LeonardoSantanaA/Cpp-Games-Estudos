#include "ScoreFileLoader.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm> //for swap and sort functions

void ScoreFileLoader::LoadScoreFileLoader(const std::string& scorePath) {
	std::ifstream inFile;
	inFile.open(scorePath, std::ios::binary);

	if (inFile.is_open()) {	
		inFile.read(reinterpret_cast<char*>(scores), sizeof(scores));		
		inFile.close();
	}else {
	 std::cerr << "Cannot open the file, the score file will be created. path: " << scorePath << std::endl;
	}

	std::cout << "//Loading Score File//" << std::endl;
	std::cout << "Show info:" << std::endl;
	for (int i = 0; i < SCORES_TO_SHOW; ++i) {
		std::cout << PrintName(scores[i].name) << " - " << scores[i].score << std::endl;
	}

}

bool ScoreFileLoader::VerifyScoreToWrite(int& index, int score) {
	for (int i = 0; i < SCORES_REAL_SIZE; ++i) {
		if (scores[i].score == NULL || (i == SCORES_REAL_SIZE - 1 && score > scores[i].score)) {
			index = i;
			return true;
		}
	}

	return false;
}


std::string ScoreFileLoader::PrintName(const char* name) {
	int i = 0;
	std::string strName = "";
	while (name[i] != '\0') {
		strName += name[i];
		i++;
	}
	return strName;
}

void ScoreFileLoader::SaveScoreToFile(const std::string& scorePath, const char* name, int score) {
	Score newScore;
	for (int i = 0; i < NAME_SIZE; i++) {
		newScore.name[i] = name[i];
	}
	newScore.score = score;
	int index;

	if (VerifyScoreToWrite(index, score)) {
		scores[index] = newScore;
		std::cout << "valor a ser redimensionado: " << scores[0].score << std::endl;
		std::cout << "valor a ser adicionado: " << scores[index].score << "index " << index << std::endl;

		std::sort(&scores[0], &scores[index+1], [](Score& scoreA, Score& scoreB) {
			return scoreA.score > scoreB.score;
			});

		std::ofstream outFile;

		outFile.open(scorePath, std::ios::binary);
		if (outFile.is_open()) {
			outFile.write(reinterpret_cast<char*>(scores), sizeof(scores));
			outFile.close();
		}
	}

	std::cout <<  "/////Print After Save/////" << std::endl;
	for (int i = 0; i < SCORES_TO_SHOW; ++i) {
		std::cout << PrintName(name) << " - " << scores[i].score << std::endl;
	}
	std::cout << "////////////////////" << std::endl;
}