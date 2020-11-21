#pragma once

#include <string>

class QandA
{
private:
	std::string question = "";
	std::string answers[4] = { "","","","" };
	std::string correctAnswer = "";
	
	/*std::string correctAnswer = "";
	std::string wrongAnswer1 = "";
	std::string wrongAnswer2 = "";
	std::string wrongAnswer3 = "";*/
public:
	QandA() {}
	//QandA(std::string question, std::string correctAnswer, std::string wrongAnswer1, std::string wrongAnswer2, std::string wrongAnswer3) { this->question = question; this->correctAnswer = correctAnswer; this->wrongAnswer1 = wrongAnswer1; this->wrongAnswer2 = wrongAnswer2; this->wrongAnswer3 = wrongAnswer3; }
	QandA(std::string question, std::string correctAnswer, std::string wrongAnswer1, std::string wrongAnswer2, std::string wrongAnswer3) { this->question = question; answers[0] = correctAnswer; answers[1] = wrongAnswer1; answers[2] = wrongAnswer2; answers[3] = wrongAnswer3; this->correctAnswer = answers[0]; }

	void setQestion(std::string newQuestion) { question = newQuestion; }
	void setAnswer(int index, std::string answer) { this->answers[index] = answer; }

	/*void setCorrectAnswer(std::string newCorrectAnswer) { correctAnswer = newCorrectAnswer; }
	void setWrongAnswer1(std::string newWrongAnswer) { wrongAnswer1 = newWrongAnswer; }
	void setWrongAnswer2(std::string newWrongAnswer) { wrongAnswer2 = newWrongAnswer; }
	void setWrongAnswer3(std::string newWrongAnswer) { wrongAnswer3 = newWrongAnswer; }*/

	std::string getQuestion() { return question; }
	std::string getAnswer(int index) { return answers[index]; }
	std::string getCorrectAnswer() { return answers[0]; }

	/*std::string getCorrectAnswer() { return correctAnswer; }
	std::string getWrongAnser1() { return wrongAnswer1; }
	std::string getWrongAnser2() { return wrongAnswer2; }
	std::string getWrongAnser3() { return wrongAnswer3; }*/

};