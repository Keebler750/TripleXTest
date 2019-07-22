#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std::chrono_literals;	// this is added to time-pause the title

/*********************************
*  TRIPLE X -                    *
*  A number guessing puzzle game *
*  for GameDev.tv Udemy UE4 C++  *
*  course.                       *
*********************************/

void PrintTitle()
{
	std::cout << "\n\n";
	std::cout << "########### ##########  ### ##########  ###         ###########                \n";
	std::cout << "########### ########### ### ########### ###         ###########                \n";
	std::cout << "    ###     ###     ### ### ###     ### ###         ###           @@       @   \n";
	std::cout << "    ###     ###     ### ### ###     ### ###         ######          @@   @     \n";
	std::cout << "    ###     ##########  ### ##########  ###         ###               @@       \n";
	std::cout << "    ###     ###    ###  ### ###         ########### ###########     @   @@     \n";
	std::cout << "    ###     ###     ### ### ###         ########### ###########   @       @@   \n";

}

// Print intro messages to the console:
void PrintIntroduction()
{
	std::cout	<< "\n\n\n";
	std::cout	<< "You are a DOJ investigator trying to\n"
				<< "retrieve hidden information in\n"
				<< "Hillary Clinton's illegal computer server.\n"
				<< "\nYou must enter the correct code numbers, in any order.\n"
				<< "\nGame is starting now....\n";
}

bool PlayGame(int Difficulty, int RandSize)
{

	srand(time(NULL));	//initialating the pseudo-rand generizer!!!
	
	// Level variables from 1 to RandSize, which is passed in:
	const int CodeA = rand() % RandSize + 1; 
	const int CodeB = rand() % RandSize + 1;
	const int CodeC = rand() % RandSize + 1;

	const int CodeSum{ CodeA + CodeB + CodeC };
	const int CodeProduct{ CodeA * CodeB * CodeC };

	// Inform player of sum and product:
	std::cout << "\nLEVEL: " << Difficulty << std::endl;
	std::cout << "There are three single digit numbers in the code.\n" << std::endl;
	std::cout << "Sum of the code numbers is: " << CodeSum << std::endl;
	std::cout << "Product of the code numbers is: " << CodeProduct << std::endl;

	int GuessA, GuessB, GuessC;
	int TriesRemaining{ 3 };

	// Do guesses and test for correct
	while (TriesRemaining > 0)
	{
		std::cout << "\nFor level " << Difficulty << " you have " << TriesRemaining << " guesses remaining." << std::endl;
		std::cout << "Guess your single digit numbers, separated with spaces: ";
		std::cin >> GuessA >> GuessB >> GuessC;
		std::cout << "\n";
		int GuessSum = (GuessA + GuessB + GuessC);
		int GuessProduct = (GuessA * GuessB * GuessC);

		if (CodeSum == GuessSum && CodeProduct == GuessProduct)
		{
			std::cout << " -------------------------------\n" << std::endl;
			std::cout << "Yes! You've broken the Auth code! You can now proceed to the next level!!\n";
			return true; // Tell MAIN to continue the game loop
		}
		else
		{
			std::cout << " -------------------------------\n" << std::endl;
			std::cout << "\nNope! Not the right numbers!\n";
			TriesRemaining--;
		}
	}

	if (TriesRemaining == 0)
	{
		std::system("CLS");
		std::cout << "You can't complete your mission. You've lost the data!!!\n";
		return false;
	}

	return false;
}

int main()
{
	std::system("CLS");
	PrintTitle();
	PrintIntroduction();
	std::this_thread::sleep_for(8s);	// title and intro on screen is timed.
	std::system("CLS");

	int LevelDifficulty = 1;
	const int MaxDifficulty = 6;
	int RandSize = 4;

	while (LevelDifficulty < MaxDifficulty)	// Game loop
	{
		bool NextLevel = PlayGame(LevelDifficulty, RandSize);	// PlayGame returns true only if player is continuing.
		std::cin.clear();   // clears any errors; failbits.
		std::cin.ignore();  // discards the buffer

		if (NextLevel && LevelDifficulty < MaxDifficulty)	// if we come out of PlayGame as a successful level; TRUE
		{
			LevelDifficulty++;
			RandSize++;
			// bGameOn = true;
		}

		else if (NextLevel && LevelDifficulty == MaxDifficulty)	// Beat last level AND maxxed the Levels. We're done!
		{
			std::system("CLS");
			std::cout << "\n\n\n\n\n ****** CONGRATULATIONS!!! ******\n\n";
			std::cout << "You've beaten the system and broken in!!\n\n\n\n\n\n\n";
			// break;	// I don't like this break

		}
	}

	std::cout << "Press ENTER to close this window." << std::endl;
	std::cin.get();

	return 0;
}


/* 
DEBUG the game end conditions and messages with that BREAK on 125. Grr.
*/