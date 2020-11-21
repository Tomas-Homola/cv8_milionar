#pragma once

class Player
{
private:
	QString playerName = "";
	double playerScore = -1.0;
public:
	Player() {}
	Player(QString playerName, double playerScore) { this->playerName = playerName; this->playerScore = playerScore; }
	
	void setPlayerName(QString newPlayerName) { playerName = newPlayerName; }
	void setPlayerScore(double newPlayerScore) { playerScore = newPlayerScore; }
	
	QString getPlayerName() { return playerName; }
	double getPlayerScore() { return playerScore; }

	
};