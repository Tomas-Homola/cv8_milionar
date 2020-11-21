#pragma once

#include <string>

class QandA
{
private:
	std::string question = "";
	std::string answers[4] = { "","","","" };
	std::string correctAnswer = "";

public:
	QandA() {}
	QandA(std::string question, std::string correctAnswer, std::string wrongAnswer1, std::string wrongAnswer2, std::string wrongAnswer3) { this->question = question; answers[0] = correctAnswer; answers[1] = wrongAnswer1; answers[2] = wrongAnswer2; answers[3] = wrongAnswer3; this->correctAnswer = answers[0]; }

	void setQestion(std::string newQuestion) { question = newQuestion; }
	void setAnswer(int index, std::string answer) { this->answers[index] = answer; }
	void setCorrectAnswer(std::string correctAnswer) { this->correctAnswer = correctAnswer; }

	std::string getQuestion() { return question; }
	std::string getAnswer(int index) { return answers[index]; }
	std::string getCorrectAnswer() { return correctAnswer; }

};