#include <iostream>
// #include <cmath> - decided to remove this for testing purposes.
#include <string>

/*********************************
*  TRIPLE X -                    *
*  A number guessing puzzle game *
*  for GameDev.tv Udemy UE4 C++  *
*  course.                       *
*********************************/

// Global vars
bool bGameOn = true; // "False ends game," said Captain Obvious.


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

    std::cout << "You are a DOJ investigator trying to retrieve hidden information in a rogue computer system.\n";
    std::cout << "You must enter the correct code numbers, in any order, to continue...\n";
}

bool PlayGame()
{
    PrintIntroduction();

    // Declaration Statments for our variables:
    const int CodeA {4};
    const int CodeB {2};
    const int CodeC {5};

    const int CodeSum {CodeA + CodeB + CodeC};
    const int CodeProduct {CodeA * CodeB * CodeC};

    // Print sum and product to the console:
    std::cout << "\nThere are three single digit numbers in the code.\n";
    std::cout << "Sum of the code numbers is: " << CodeSum << std::endl;
    std::cout << "Product of the code numbers is: " << CodeProduct << std::endl;

    int GuessA, GuessB, GuessC;
    int TriesRemaining {3};
    bool bWinCondition = false;

    // Do guesses and test for correct
    while (TriesRemaining > 0)
    {
        std::cout << "\nGuess your single digit numbers, separated with spaces: ";
        std::cin >> GuessA >> GuessB >> GuessC;
        std::cout << "\n";
        // std::cout << "You entered: " << GuessA << GuessB << GuessC << std::endl;
        int GuessSum = (GuessA + GuessB + GuessC);
        int GuessProduct = (GuessA * GuessB * GuessC);

        std::system ("CLS");

        if (CodeSum == GuessSum && CodeProduct == GuessProduct)
        {
            std::cout << "Yes! You've broken the Auth code! You can now access the data!!\n";
            bWinCondition = true;
            bGameOn = false; // Only one win, one level. Change this for multi-level
            break;      // This break solves the problem of getting the answer right while still having more guesses left.
        }

        else
        {
            std::cout << "\nNope! Not the right numbers!\n";
        }

        TriesRemaining--;

        return bWinCondition;
       

    }
    
    if (bWinCondition == false)
    {
        std::cout << "You've run out of tries. Sorry. You've lost!\n";
        bGameOn = false;
    }
}

int main()
{
    std::system ("CLS");
    PrintTitle();

    int LevelDifficulty = 1; 

    while (bGameOn)
    {
        bool NextLevel = PlayGame();
        std::cin.clear();   // clears any errors; failbits.
        std::cin.ignore();  // discards the buffer
    }
    

    return 0;
}
