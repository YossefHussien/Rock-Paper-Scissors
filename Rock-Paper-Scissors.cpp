#include <iostream>
using namespace std;

enum enGameItem {Rock = 1, Paper = 2, Scissors = 3};
enum enGameStatus { UserWin = 1, ComputerWin = 2, Draw = 3 };

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;  // Return the generated random number.
}

int NumberOfRounds()
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


enGameStatus GetResult(enGameItem UserChoice, enGameItem ComputerChoice)
{
	if (UserChoice == ComputerChoice)
		return enGameStatus::Draw;
	if (UserChoice == enGameItem::Rock && ComputerChoice == enGameItem::Scissors)
		return enGameStatus::UserWin;
	if (UserChoice == enGameItem::Paper && ComputerChoice == enGameItem::Rock)
		return enGameStatus::UserWin;
	if(UserChoice == enGameItem::Scissors && ComputerChoice == enGameItem::Paper)
		return enGameStatus::UserWin;

	return enGameStatus::ComputerWin;

}

void counter(enGameStatus GameStatus, int& UserWin, int& ComputerWin,int& Draw)
{
	switch (GameStatus) {
   case enGameStatus::Draw:
	   system("color 6f");
	   Draw++;
	   break;
   case enGameStatus::UserWin:
	   system("color 2f");
	   UserWin++;
	   break;
   case enGameStatus::ComputerWin:
	   system("color 4f");
	   cout << "\a";
	   ComputerWin++;
	   break;

	}

}

string GameStatusToString(enGameStatus Result)
{
	switch (Result) {
	case enGameStatus::UserWin:     return "User Win";
	case enGameStatus::ComputerWin: return "Computer Win";
	case enGameStatus::Draw:        return "Draw";
	}
}

string GameItemToString(enGameItem Item)
{
	switch (Item) 
	{
		case enGameItem::Rock: 
			return "Rock";
		case enGameItem::Paper:
			return "Paper";
		case enGameItem::Scissors:
			return "Scissors";

    }

}


void ShowRoundResult(enGameItem UserChoice, enGameItem ComputerChoice, enGameStatus Result)
{
	switch (Result) {
	case enGameStatus::UserWin:     system("color 2f"); break;
	case enGameStatus::ComputerWin: system("color 4f"); cout << "\a"; break;
	case enGameStatus::Draw:        system("color 6f"); break;
	}
	
	cout << "Player Choice : " << GameItemToString(UserChoice) << endl;
	cout << "Computer Choice : " << GameItemToString(ComputerChoice) << endl;
	cout << "Round Winner : " << GameStatusToString(Result) << endl;
}

void PrintGameResult(int NumberOfRounds, int UserWin, int ComputerWin, int Draw) 
{
	cout << "Games Round : " << NumberOfRounds << endl;
	cout << "Player Won times : " << UserWin << endl;
	cout << "Computer Won times : " << ComputerWin << endl;
	cout << "Draw times : " << Draw << endl;

	if(Draw > UserWin && Draw > ComputerWin)
		cout << "Final Winner : Draw" << endl;
	else if (Draw == UserWin && UserWin == ComputerWin)
		cout << "Final Winner : Draw" << endl;
	else if (UserWin > ComputerWin)
		cout << "Final Winner : Player " << endl;
	else
		cout << "Final Winner : Computer " << endl;
	


}


void StartRound()
{
	int UserWin = 0, ComputerWin = 0, Draw = 0;

	enGameStatus Result;
	int Rounds = NumberOfRounds();

	for (int i = 1; i <= Rounds; i++)
	{
		enGameItem PlayerMove = ReadPlayerMove();
		enGameItem ComputerMove = RandomComputerMove();

		Result = GetResult(PlayerMove, ComputerMove);

		counter(Result, UserWin, ComputerWin, Draw);
		
		cout << "___________________________Round [" << i << "]" << "___________________________________" << endl;
		ShowRoundResult(PlayerMove, ComputerMove, Result);
		cout << "_____________________________________________________" << endl << endl;
	}

	PrintGameResult(Rounds, UserWin, ComputerWin, Draw);
}

void StartGame()
{
	bool PlayAgain = true;
	do 
	{
		system("cls");  
		system("color 0f");  
		StartRound();

		cout << "\nDo you want to play again? [1]: Yes,  [0]: No" << endl;
		cin >> PlayAgain;
	} while (PlayAgain);


}
int main()
{
	srand((unsigned)time(NULL));

	StartGame();
}