#include <iostream>
#include<cstdlib>

using namespace std;

 

enum en_GameChoice {Rock = 1, Paper = 2, Scissor = 3};
enum en_Winner { Player = 1, Computer = 2, Draw = 3 };

struct st_RoundInfo
{
	short RoundNumber = 0;
	en_GameChoice Player_Choice;
	en_GameChoice Computer_Choice;
	en_Winner Winner;
	string WinnerName;
};

struct st_GameResults
{
	short GameRounds = 0;
	short PlayerWin_Times = 0;
	short ComputerWin_Times = 0;
	short Draw_Times = 0;
	en_Winner GameWinner;
	string WinnerName = "";
};


int Random_Number(int From, int To)
{
	int Random_Number = rand() % (To - From + 1) + From;
	return Random_Number;
}

string WinnerName(en_Winner Winner)
{
	string ArrwinnerName[3] = { "Player", "Computer", "No Winner" };
	return ArrwinnerName[Winner - 1];
}

en_Winner WhoWon_TheRound(st_RoundInfo RoundInfo)
{
	if (RoundInfo.Player_Choice ==  RoundInfo.Computer_Choice)
	{
		return en_Winner::Draw;
	}

	switch (RoundInfo.Player_Choice)
	{
	case en_GameChoice::Rock:
		if (RoundInfo.Computer_Choice == en_GameChoice::Paper)
		{
			return en_Winner::Computer;
		}
		break;

	case en_GameChoice::Paper:
		if (RoundInfo.Computer_Choice == en_GameChoice::Scissor)
		{
			return en_Winner::Computer;
		}
		break;

	case en_GameChoice::Scissor:
		if (RoundInfo.Computer_Choice == en_GameChoice::Rock)
		{
			return en_Winner::Computer;
		}
		break;

	}
	// If you reach here then the player is the winner.

	return en_Winner::Player;

}

string ChoiceName(en_GameChoice Choice)
{
	string arrGameChoice[3] = { "Rock", "Paper", "Scissor" };

	return arrGameChoice[Choice - 1];
}

void SetwinnerScreenColor(en_Winner winner)
{
	switch (winner)
	{
	case en_Winner::Player:
		system("color 2F");// Turn Screen to Green
		break;

	case en_Winner::Computer:
		system("color 4F"); // Turn Scrren to Red
		cout << "\a";
		break;
	default:
		system("color 6F"); // Turn Screen to yellow
		break;


	}
}

void Print_RoundResult(st_RoundInfo RoundInfo)
{
	cout << "\n------------- Round [" << RoundInfo.RoundNumber << "] -------------\n\n";
	cout << "Player Choice: " << ChoiceName(RoundInfo.Player_Choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.Computer_Choice) << endl;
	cout << "Round Winner:  [ " << RoundInfo.WinnerName << "]\n" << endl;
	cout << "-----------------------------------------------\n" << endl;

	SetwinnerScreenColor(RoundInfo.Winner);
}

en_Winner Who_wonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
		return en_Winner::Player;
	else if (PlayerWinTimes < ComputerWinTimes)
		return en_Winner::Computer;
	else
		return en_Winner::Draw;
}

st_GameResults Fill_GameResults(short GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	st_GameResults Game_Results;

	Game_Results.GameRounds = GameRounds;
	Game_Results.PlayerWin_Times = PlayerWinTimes;
	Game_Results.ComputerWin_Times = ComputerWinTimes;
	Game_Results.Draw_Times = DrawTimes;
	Game_Results.GameWinner = Who_wonTheGame(PlayerWinTimes, ComputerWinTimes);
	Game_Results.WinnerName = WinnerName(Game_Results.GameWinner);

	return Game_Results;
}

en_GameChoice Read_PlayerChoice()
{
	short Choice = 1;
	do
	{
		cout << "\n Your Choose Rock[1], Paper[2], Scissor[3] ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);
	return (en_GameChoice)Choice;

}

en_GameChoice Get_ComputerChoice()
{
	return (en_GameChoice) Random_Number(1, 3);
}
 

st_GameResults PlayGame(short HowManyRounds)
{
	st_RoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawWinTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] Begins: \n" << endl;
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player_Choice = Read_PlayerChoice();
		RoundInfo.Computer_Choice = Get_ComputerChoice();
		RoundInfo.Winner = WhoWon_TheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		// Increase win/draw Counters

		if (RoundInfo.Winner == en_Winner::Player)

			PlayerWinTimes++;

		else if (RoundInfo.Winner == en_Winner::Computer)

			ComputerWinTimes++;
		else
			DrawWinTimes++;

		Print_RoundResult(RoundInfo);
	}

	return Fill_GameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawWinTimes);

}

 
string Tabs(short NumberOfTaps)
{
	string t = "";

	for (int i = 0; i < NumberOfTaps; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}


void Show_GameOverScreen()
{
	cout << Tabs(2) << "---------------------------------\n\n";
	cout << Tabs(2) << "    ++ G a m e   O v e r ++\n";
	cout << Tabs(2) << "---------------------------------\n\n";


}

void Show_FinalGameResults(st_GameResults GameResults)
{
	cout << Tabs(2) << "------------------------[Game Results]---------------------------\n\n ";
	cout << Tabs(2) << "Game Rounds       :" << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player Won Times       :" << GameResults.PlayerWin_Times << endl;
	cout << Tabs(2) << "Computer Won Times       :" << GameResults.ComputerWin_Times << endl;
	cout << Tabs(2) << "Draw Times      :" << GameResults.Draw_Times << endl;
	cout << Tabs(2) << "Final winner       :" << GameResults.WinnerName << endl;
	cout << Tabs(2) << "-----------------------------------------------------------------------\n" << GameResults.GameRounds << endl;

	SetwinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRounds()
{
	short Gamerounds = 1;
	do
	{
		cout << "How Many Rounds [1 to 10] \n";
		cin >> Gamerounds;
	} while (Gamerounds < 1 || Gamerounds > 10);

		return Gamerounds;
}

void Reset_Screen()
{
	system("cls");
	system("color 0F");
}

void Start_Game()
{
	char playagain = 'Y';

	do
	{
	
		Reset_Screen();
		st_GameResults GameResults = PlayGame(ReadHowManyRounds());
		Show_GameOverScreen();
		Show_FinalGameResults(GameResults);

		cout << endl << Tabs(3) << "Do You Want to Play Again Y/N";
		cin >> playagain;
		
	} while (playagain == 'Y' || playagain == 'y');
}



 

int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));

	Start_Game();

	return 0;

}

 
