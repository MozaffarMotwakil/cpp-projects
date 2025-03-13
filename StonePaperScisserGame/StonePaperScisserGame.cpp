#include <iostream>
#include <cstdlib>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scisser = 3 };

enum enWinner { Player, Computer, Draw };

struct stRoundResult {
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName = "";
};

struct stGameResult {
	short RaoundsTimes = 0;
	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner Winner;
	string WinnerName = "";
};

void ResetScrean() {
	system("cls");
	system("color 0F");
}

int HowManyRounds() {
	int RoundsCount = 0;

	do
	{
		cout << "Enter a number of the rounds you want to play from 1 to 10 : ";
		cin >> RoundsCount;

	} while (RoundsCount < 1 || RoundsCount > 3);

	return RoundsCount;
}

enGameChoice ReadPlayerChoice() {
	int PlayerChoice = 0;

	do
	{
		cout << "\n[1] Stone, [2] Paper, [3] Scisser, please enter a number of your choice : ";
		cin >> PlayerChoice;

	} while (PlayerChoice < 1 || PlayerChoice > 3);

	return (enGameChoice)PlayerChoice;
}

int RandomNumber(int From, int To) {
	return rand() % (To - From + 1) + From;
}

enGameChoice GetComputerChoice() {
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner RoundWinner(stRoundResult RoundResult) {
	if (RoundResult.PlayerChoice == RoundResult.ComputerChoice)
		return Draw;

	switch (RoundResult.PlayerChoice)
	{
	case Stone :
		if (RoundResult.ComputerChoice == Paper)
			return Computer;
		break;
	case Paper :
		if (RoundResult.ComputerChoice == Scisser)
			return Computer;
		break;
	case Scisser :
		if (RoundResult.ComputerChoice == Stone)
			return Computer;
		break;
	}

	// In case computer don't won, that means the player is winner
	return Player;
}

string WinnerName(enWinner Winner) {
	string Winners[3] = { "Player", "Computer", "No Winner" };
	return Winners[Winner];
}

string ChoiceName(enGameChoice Choice) {
	string Choices[3] = { "Stone", "Paper", "Scisser" };
	return Choices[Choice - 1];
}

void SetWinnerScreanColor(enWinner Winner) {
	switch (Winner)
	{
	case Player:
		system("color 2F"); // Green color
		break;
	case Computer:
		system("color 4F"); // Red color
		cout << "\a";
		break;
	default :
		system("color 6F"); // Yellow color, in case draw
		break;
	}
}

void ShowRoundResult(stRoundResult RoundResult) {
	cout << "\n___________________Round [" << RoundResult.RoundNumber << "]___________________\n";
	cout << "\nPlayer Choice : " << ChoiceName(RoundResult.PlayerChoice);
	cout << "\nComputer Choice : " << ChoiceName(RoundResult.ComputerChoice);
	cout << "\nRound Winner : " << RoundResult.WinnerName;
	cout << "\n_______________________________________________\n";

	SetWinnerScreanColor(RoundResult.Winner);
}

enWinner GameWinner(short PlayerWonTimes, short ComputerWonTimes) {
	if (PlayerWonTimes > ComputerWonTimes)
		return Player;
	else if (ComputerWonTimes > PlayerWonTimes)
		return Computer;
	else
		return Draw;
}

stGameResult FillGameResult(short RoundsTimes, short PlayerWonTimes, short ComputerWonTimes, short DrawTimes) {
	stGameResult GameResult;

	GameResult.RaoundsTimes = RoundsTimes;
	GameResult.PlayerWonTimes = PlayerWonTimes;
	GameResult.ComputerWonTimes = ComputerWonTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.Winner = GameWinner(PlayerWonTimes, ComputerWonTimes);
	GameResult.WinnerName = WinnerName(GameResult.Winner);

	return GameResult;
}

stGameResult PlayGame(short HowManyRound) {
	stRoundResult RoundResult;
	short PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;

	for (short RoundNumber = 1; RoundNumber <= HowManyRound; RoundNumber++)
	{
		cout << "\nRound [" << RoundNumber << "] begains :" << endl;
		RoundResult.RoundNumber = RoundNumber;
		RoundResult.PlayerChoice = ReadPlayerChoice();
		RoundResult.ComputerChoice = GetComputerChoice();
		RoundResult.Winner = RoundWinner(RoundResult);
		RoundResult.WinnerName = WinnerName(RoundResult.Winner);

		if (RoundResult.Winner == Player)
			PlayerWonTimes++;
		else if (RoundResult.Winner == Computer)
			ComputerWonTimes++;
		else
			DrawTimes++;

		ShowRoundResult(RoundResult);
	}

	return FillGameResult(HowManyRound, PlayerWonTimes, ComputerWonTimes, DrawTimes);
}

string Tabs(short TabsCount) {
	string Tab = "";

	for (int i = 1; i <= TabsCount; i++)
	{
		Tab = Tab + "\t";
	}

	return Tab;
}

void ShowGameOverMessage() {
	cout << Tabs(2) << "_______________________________________________\n\n";
	cout << Tabs(2) << "          * * * G a m e  O v e r * * *\n";
	cout << Tabs(2) << "_______________________________________________\n\n";
}

void ShowGameResult(stGameResult GameResult) {
	cout << Tabs(2) << "________________ [Game Result] ________________\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResult.RaoundsTimes << endl;
	cout << Tabs(2) << "Player won times   : " << GameResult.PlayerWonTimes << endl;
	cout << Tabs(2) << "Computer won times : " << GameResult.ComputerWonTimes << endl;
	cout << Tabs(2) << "Draw times         : " << GameResult.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResult.WinnerName << endl;
	cout << Tabs(2) << "_______________________________________________\n";
	
	SetWinnerScreanColor(GameResult.Winner);
}

void StartGame() {
    char PlayAgain = 'Y';

	do
	{
		ResetScrean();
		stGameResult GameResult = PlayGame(HowManyRounds());
		ShowGameOverMessage();
		ShowGameResult(GameResult);

		cout << "\nDo you want play again ? please enter Y/N : ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));	

	StartGame();
}