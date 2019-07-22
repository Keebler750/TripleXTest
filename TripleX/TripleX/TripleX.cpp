#include <iostream>
#include <chrono>
#include <thread>
// #include <cmath> - decided to remove this for testing purposes.
// #include <string> - removing this for now, too - KL 

using namespace std::chrono_literals;

/*********************************
*  TRIPLE X -                    *
*  A number guessing puzzle game *
*  for GameDev.tv Udemy UE4 C++  *
*  course.                       *
*********************************/

// Global vars
// bool bGameOn;

void PrintTitle()
{
	std::cout << "\n\n";
	std::cout << "########### ##########  ### ##########  ###         ###########                \n";
	std::cout << "########### ########### ### ########### ###         ###########                \n";
	std::cout << "    ###     ###     ### ### ###     ### ###         ###           @@       @   \n";
	std::cout << "    ###     ###     ### ### ###     ### ###         ######          @@   @     \n";
	std::cout << "    ###     ##########  ### ##########  ###         ###               @@       \n";
	std::cout << "    ###     ###    ###  ### ###         ########### ###########     @   @@     \n";
	std::cout << "    ###     ###     ### ### ###         ########### ###########   @       @@   \n\n";

}

// Print intro messages to the console:
void PrintIntroduction()
{

	std::cout	<< "You are a DOJ investigator trying to retrieve"
				<< " hidden information in a rogue computer system.\n";
	std::cout	<< "\nYou must enter the correct code numbers, in any order, to continue...\n";
}

bool PlayGame(int Difficulty)
{
	// Declaration Statments for our variables:
	const int CodeA{ 4 };
	const int CodeB{ 2 };
	const int CodeC{ 5 };

	const int CodeSum{ CodeA + CodeB + CodeC };
	const int CodeProduct{ CodeA * CodeB * CodeC };

	// Print sum and product to the console:
	// std::system("CLS");
	std::cout << "\n\nLEVEL: " << Difficulty << std::endl;
	std::cout << "There are three single digit numbers in the code.\n" << std::endl;
	std::cout << "Sum of the code numbers is: " << CodeSum << std::endl;
	std::cout << "Product of the code numbers is: " << CodeProduct << std::endl;

	int GuessA, GuessB, GuessC;
	int TriesRemaining{ 3 };
	bool bWinCondition = false;

	// Do guesses and test for correct
	while (TriesRemaining > 0)
	{
		std::cout << "\nFor level " << Difficulty << " you have " << TriesRemaining << " guesses remaining." << std::endl;
		std::cout << "Guess your single digit numbers, separated with spaces: ";
		std::cin >> GuessA >> GuessB >> GuessC;
		std::cout << "\n";
		// std::cout << "You entered: " << GuessA << GuessB << GuessC << std::endl;
		int GuessSum = (GuessA + GuessB + GuessC);
		int GuessProduct = (GuessA * GuessB * GuessC);

		if (CodeSum == GuessSum && CodeProduct == GuessProduct)
		{
			std::cout << " -------------------------------\n" << std::endl;
			std::cout << "Yes! You've broken the Auth code! You can now proceed to the next level!!\n";
			bWinCondition = true;
			return true; // Only one win, one level. Change this for multi-level
			// break;      // This break solves the problem of getting the answer right while still having more guesses left.
		}

		else
		{
			std::cout << " -------------------------------\n" << std::endl;
			std::cout << "\nNope! Not the right numbers!\n";
			TriesRemaining--;
		}


		// win condition was here...



	}

	if (TriesRemaining == 0)
	{
		std::system("CLS");
		std::cout << "You've run out of tries. Sorry. You've lost!\n";
		return false;
	}

	return false;
}

int main()
{
	std::system("CLS");
	PrintTitle();
	PrintIntroduction();
	std::this_thread::sleep_for(7s);	// Leaves the title and intro on screen, timed.
	std::system("CLS");


	int LevelDifficulty = 1;
	const int MaxDifficulty = 5;
	// bool bGameOn = true; // "False ends game," said Captain Obvious.


	while (LevelDifficulty <= MaxDifficulty)	// Game loop
	{
		bool NextLevel = PlayGame(LevelDifficulty);
		std::cin.clear();   // clears any errors; failbits.
		std::cin.ignore();  // discards the buffer

		if (NextLevel && LevelDifficulty < MaxDifficulty)	// if we come out of PlayGame as a successful level; TRUE
		{
			LevelDifficulty++;
			// bGameOn = true;
		}

		else if (NextLevel && LevelDifficulty == MaxDifficulty)
		{
			std::system("CLS");
			std::cout << "\n\n\n\n\nCONGRATULATIONS!!!\n\n";
			std::cout << "You've beaten the system and broken in!!\n\n\n";
			break;

		}
	}

	std::cout << "Press ENTER to close this window." << std::endl;
	std::cin.get();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
