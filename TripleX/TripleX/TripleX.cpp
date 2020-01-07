#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <windows.h> // to change windows console colors, etc.

using namespace std::chrono_literals;	// functionality added to time-pause screen info.

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

// Print intro storyline to console:
void PrintIntroduction()
{
	std::cout << "\n\n\nYou are a DOJ investigator trying to\n"
		<< "retrieve hidden information in\n"
		<< "Mallory Clanton's illegal computer server.\n"
		<< "\nYou must enter the correct code numbers, in any order.\n"
		<< "\nGame is starting now....\n";
}

// Inform player of sum and product each attempt so they don't have to look for info up the page:
void PrintCodeInfo(int Difficulty, const int CodeSum, const int CodeProduct, const int CodeA, const int CodeB, const int CodeC)
{
	std::system("CLS");
	std::cout << "\n\n-------------- LEVEL: " << Difficulty << " ---------------\n\n";
	std::cout << "\nThere are three single digit numbers in the code.\n";
	std::cout << "\nSum of the code numbers is: " << CodeSum;
	std::cout << "\nProduct of the code numbers is: " << CodeProduct;
	/** Debug only - print the code numbers **/
	// std::cout << "\n\n***** DEBUG: " << CodeA << ", " << CodeB << ", " << CodeC << " *****\n";
}

int Modulus(int iN, int iMod)
{
	int iQ = (iN / iMod);
	return iN - (iQ*iMod);
}

char GetChar(int iGenerator, char cBase, int iRange)
{
	return (cBase + Modulus(iGenerator, iRange));
}

void WinGenerator()
{
	// Color code set to green
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);

	char caRow[80] = { 0 };
	int j = 7;
	int k = 2;
	int l = 5;
	int m = 1;
	int iterations = 200;

	while (iterations >= 0)
	{
		// Output a random row of characters
		for (int i = 0; i < 80; ++i)
		{
			if (caRow[i] != ' ')
			{
				caRow[i] = GetChar(j + i * i, 33, 30);
				if (((i*i + k) % 71) == 0)
				{
					SetConsoleTextAttribute(hConsole, 7);
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 2);
				}
			}
			std::cout << caRow[i];
			SetConsoleTextAttribute(hConsole, 2);
		}
		j = (j + 31);
		k = (k + 17);
		l = (l + 47);
		m = (m + 67);
		caRow[Modulus(j, 80)] = '-';
		caRow[Modulus(k, 80)] = ' ';
		caRow[Modulus(l, 80)] = '-';
		caRow[Modulus(m, 80)] = ' ';

		Sleep(10); // Delay
		iterations--; // don't want it to go on forever...
	}

	// Color code reset to white
	SetConsoleTextAttribute(hConsole, 7);
}

// Game is played here; guesses, checks and math:
bool PlayGame(int Difficulty)
{
	srand(time(NULL));	//initialating the pseudo-rand generizer!!!

	// 'Random' variables created, between 1 and Difficulty expression (which is passed in)
	const int CodeA = rand() % (Difficulty + 4) + 1;
	const int CodeB = rand() % (Difficulty + 4) + 1;
	const int CodeC = rand() % (Difficulty + 4) + 1;

	const int CodeSum{ CodeA + CodeB + CodeC };
	const int CodeProduct{ CodeA * CodeB * CodeC };

	int GuessA, GuessB, GuessC;
	int GuessesRemaining{ 3 };

	// Do guesses and checks
	while ((GuessesRemaining > 0) && (Difficulty <= 5))
	{
		// Show player the current code info:
		PrintCodeInfo(Difficulty, CodeSum, CodeProduct, CodeA, CodeB, CodeC);

		// Generate the guesses and math required
		std::cout << "\n\nFor this level you have only " << GuessesRemaining << " guesses remaining.\n";
		std::cout << "Guess your single digit numbers, separated with spaces: ";
		std::cin >> GuessA >> GuessB >> GuessC;
		std::cout << "\n";
		int GuessSum = (GuessA + GuessB + GuessC);
		int GuessProduct = (GuessA * GuessB * GuessC);
		GuessesRemaining--;	// decrementing guesses here powers the guess checker below...

		// following are multiple game condition checks
		if (((CodeSum == GuessSum) && (CodeProduct == GuessProduct)) && (Difficulty == 5)) // if the guesses are correct on last level:
		{
			std::system("CLS");
			std::cout << "Code verfied - ACCESS GRANTED\n";
			std::this_thread::sleep_for(2s);	// pause to read message

			//Call a screen generator function here to mimic a download or data etc...
			WinGenerator();
			std::cout << "\n\n...DOWNLOAD COMPLETE";
			std::this_thread::sleep_for(2s);	// pause to read message
			std::system("CLS");
			std::cout << "\n\n\n\n\n ****** CONGRATULATIONS!!! ******\n\n";
			std::cout << "You've broken the security codes and accessed the data!!\n"
				<< "Now escape before you are caught!\n\n\n\n\n\n\n";
			std::this_thread::sleep_for(3s);	// pause to read message
			return false; // Tell MAIN to end the game loop
		}
		if ((CodeSum == GuessSum) && (CodeProduct == GuessProduct)) // if the guesses are correct: 
		{
			std::cout << "\nYes! You've broken the Auth code!\n";
			std::cout << "You can now proceed to the next level!!\n";
			return true; // Tell MAIN to continue the game loop
		}
		if ((CodeSum != GuessSum) && (CodeProduct != GuessProduct)) // if the guesses are NOT correct:
		{
			std::cout << "\n\n-------------------------------\n\n";
			std::cout << "\nNope! Not the right numbers!\n";
			std::this_thread::sleep_for(2s);	// pause to read message
		}
		if (GuessesRemaining == 0) // if player ran out of guesses:
		{
			std::system("CLS");
			std::cout << "\n\n\nYou've run out of guesses and can't complete your mission. You've lost the data!!!\n\n\n\n";
			std::this_thread::sleep_for(3s);	// pause to read message
			return false;	// Tell MAIN you're done.
		}
	}
}

int main()
{
	std::system("CLS");
	PrintTitle();
	PrintIntroduction();
	std::this_thread::sleep_for(7s);	// title and intro on screen is timed.
	std::system("CLS");

	int LevelDifficulty = 1;
	const int MaxDifficulty = 5;

	// Game loop
	while (LevelDifficulty <= MaxDifficulty)
	{
		// PlayGame returns true only if player is continuing.
		bool bLevelComplete = PlayGame(LevelDifficulty);
		std::cin.clear();   // clears any errors; failbits.
		std::cin.ignore();  // discards the buffer
		std::this_thread::sleep_for(4s);	// pause to read message

		if (bLevelComplete)	// if true go to next difficulty level
		{
			LevelDifficulty++; // increase difficulty affects RANGE of rand generator.
		}
		else
		{
			std::system("CLS");
			std::cout << "\n\n\n\n\nGame Over\n";
			break;
		}
	}

	std::cout << "\nPress ENTER to close this window.\n\n";
	std::cin.get();
	return 0;
}
