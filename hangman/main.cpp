//
//  main.cpp
//  hangman
//
//  Created by Finlay Turner on 16/06/2024.
//

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <random>

bool game( int *score);
bool checkans(std::string &guess, std::string &answer);


int main(int argc, const char * argv[]) {
    int score = 0;
    
    while(game(&score));
    
    std::cout << std::endl << "Thanks for playing!" << std::endl << "You won " << score;
    if (score == 1)
    {
        std::cout << " game" << std::endl;
    }
    else
    {
        std::cout << " games" << std::endl;
    }
    
    return 0;
}

bool game(int *score)
{
    std::ifstream wordsFile;
    wordsFile.open("random-words.txt");
    if (!wordsFile)
    {
        std::cerr << "Unable to open or find random-words.txt" << std::endl;
        exit(1);
    }
    
    int lineTarget;
    std::string line;
    int maxLines = 2643;
    
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, maxLines); // define the range
    lineTarget = distr(gen);
    
    for (int i = 0; i < lineTarget; i++)
    {
        std::getline(wordsFile, line);
    }
    wordsFile.close();
    
    std::string ans = line;
    std::string wordProgress;
    std::string currentGuess;
    bool isGameOver = false;
    bool userHasWon = false;
    int maxGuesses = 8;
    int guessCount = 0;
    
    /** Initialize string for current progress of guesses with '_' characters for each letter
    /in the answer (spaces are left as spaces) **/
    for (int i = 0; i < ans.length(); i++)
    {
        if (ans[i] != ' ')
        {
            wordProgress += '_';
        }
        else
        {
            wordProgress += ' ';
        }
    }
    
    while (!isGameOver && !userHasWon)
    {
        std::cout << "Word: " << wordProgress << std::endl;
        std::cout << "Enter your guess!" << std::endl;
        std::getline(std::cin, currentGuess);
        
        if (currentGuess.length() < 2)
        {
            bool correctGuess = false;
            // User has guessed a letter. Check if the letter exists within the word.
            for (int i = 0; i < ans.length(); i++)
            {
                if (std::tolower(ans[i]) == std::tolower(currentGuess[0]))
                {
                    wordProgress[i] = ans[i];
                    correctGuess = true;
                }
            }
            if (correctGuess)
            {
                std::cout << "Nice guess!" << std::endl;
            }
            else
            {
                std::cout << "Try guessing a different letter." << std::endl;
            }
        }
        
        else
        {
            // User has guessed a word. Check if their guess is correct.
            if (checkans(currentGuess, ans))
            {
                userHasWon = true;
            };
        }
        
        guessCount++;
        
        if (guessCount >= maxGuesses && !userHasWon)
        {
            isGameOver = true;
            std::cout <<"Word: " << wordProgress << std::endl;
            std::cout << "Please enter your final guess!" << std::endl;
            std::getline(std::cin, currentGuess);
            
            if (checkans(currentGuess, ans))
            {
                userHasWon = true;
            }
        }
    }
    
    if (userHasWon)
    {
        std::string response;
        *score = *score + 1;
        std::cout << std::endl << "Correct! The answer was " << ans << std::endl <<  "Would you like to play again? (y/n)";
        std::getline(std::cin, response);
        
        if (response[0] == 'y' or response[0] == 'Y')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    else
    {
        std::string response;
        std::cout << std::endl << "You lose!" << std::endl << "The words was: " << ans << std::endl << "Would you like to play again? (y/n)";
        std::getline(std::cin, response);
        
        if (response[0] == 'y' or response[0] == 'Y')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool checkans(std::string &guess, std::string &answer)
{
    std::string guessLower;
    std::string answerLower;
    
    // Convert guess into lowercase
    for (int i = 0; i < guess.length(); i++)
    {
        guessLower += std::tolower(guess[i]);
    }
    
    // Convert answer into lowercase
    for (int i = 0; i < answer.length(); i++)
    {
        answerLower += static_cast<char>(std::tolower(answer[i]));
    }
    
    // Compare answer to guess
    if (guessLower == answerLower)
    {
        return true;
    }
    return false;
}
