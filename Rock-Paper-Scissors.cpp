#include <iostream>
using namespace std;

enum enGameItem {Rock = 1, Paper = 2, Scissors = 3};
enum enGameStatus { UserWin = 1, ComputerWin = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameItem PlayerChoice;
	enGameItem ComputerChoice;
	enGameStatus Winner;
	string WinnerName;
};

struct stGameResults
{
	short GameRounds = 0;        
	short Player1WinTimes = 0;  
	short ComputerWinTimes = 0;  
	short DrawTimes = 0;         
	enGameStatus GameWinner;
	string WinnerName = "";      
};

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;  // Return the generated random number.
}

int ReadHowManyRounds()
{
	int NumberOfRounds;
	do {
		cout << "How many rounds from 1 to 10 ?" << endl;
		cin >> NumberOfRounds;
	} while (NumberOfRounds < 1 || NumberOfRounds > 10); 
	return NumberOfRounds;
}

enGameItem ReadPlayerMove()
{
	int Choice;
	do {
		cout << "Your Choice : [1]: Rock , [2]: Paper, [3]: Scissors ?" << endl;
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return enGameItem(Choice);
}


enGameItem RandomComputerMove() {
	return enGameItem(RandomNumber(1, 3));
}

enGameStatus WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.ComputerChoice == RoundInfo.PlayerChoice)
		return enGameStatus::Draw;

	switch(RoundInfo.PlayerChoice)
	{
	case  enGameItem::Rock:
		if (RoundInfo.ComputerChoice == enGameItem::Paper)
			return enGameStatus::ComputerWin;
		break;
	case  enGameItem::Paper:
		if (RoundInfo.ComputerChoice == enGameItem::Scissors)
			return enGameStatus::ComputerWin;
		break;
	case  enGameItem::Scissors:
		if (RoundInfo.ComputerChoice == enGameItem::Rock)
			return enGameStatus::ComputerWin;
		break;

	}

	return enGameStatus::UserWin;

}

enGameStatus WhoWonTheGame(short UserWinTimes, short ComputerWinTimes, short DrawTimes)
{
	if (UserWinTimes > ComputerWinTimes && UserWinTimes > DrawTimes)
		return enGameStatus::UserWin;
	if (ComputerWinTimes > UserWinTimes && ComputerWinTimes > DrawTimes)
		return enGameStatus::ComputerWin;
	else
		return enGameStatus::Draw;
}

string ChoiceName(enGameItem Choice)
{
	string arrGameChoices[3] = { "Rock", "Paper", "Scissors" };
	return arrGameChoices[Choice - 1];
}

string WinnerName(enGameStatus Winner)
{
	string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
	return arrWinnerName[Winner - 1];
}

void SetWinnerScreenColor(enGameStatus Winner)
{
	switch (Winner)
	{
	case enGameStatus::UserWin:
		system("color 2f");
		break;
	case enGameStatus::ComputerWin:
		system("color 4f");
		cout << "\a";
		break;
	default:
		system("color 6f");
		break;

	}

}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
	cout << "Player1 Choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "_________________________________________\n" << endl;

	SetWinnerScreenColor(RoundInfo.Winner);
	
}

stGameResults FillGameResults(int GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes, enGameStatus GameWinner, string WinnerNameStr)
{
	stGameResults GameResults;
	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = PlayerWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = GameWinner;
	GameResults.WinnerName = WinnerNameStr;

	return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerMove();
		RoundInfo.ComputerChoice = RandomComputerMove();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enGameStatus::UserWin)
			PlayerWinTimes++;
		else if (RoundInfo.Winner == enGameStatus::ComputerWin)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}
	enGameStatus GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes, DrawTimes);
	return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes,
		GameWinner, WinnerName(GameWinner));
}

string Tabs(short NumberOfTabs)
{
	string Tab = "";
	for(int i =1; i < NumberOfTabs;i++)
	{
		Tab = Tab + "\t";
	}

	return Tab;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "_________________________________________________________\n\n";
	cout << Tabs(2) << "                    +++ G a m e  O v e r  +++\n";
	cout << Tabs(2) << "_________________________________________________________\n\n";
}

void ResetScreen()
{
	system("cls");
	system("color 0f");
}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "_____________________________[Game Results ]_________________________\n\n";
	cout << Tabs(2) << "Game Rounds : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player Won Times : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer Won Times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw Times : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "_________________________________________________________________________\n\n";
	SetWinnerScreenColor(GameResults.GameWinner);
}


void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds()); 
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << Tabs(3) << "Do you want to play again? (Y/N): ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
	srand((unsigned)time(NULL));

	StartGame();
}