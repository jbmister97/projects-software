//main executable program
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//make syntax unreal engine friendly
using FText = std::string;
using int32 = int;

//function prototypes
void Intro();
void Play();
FText GetValidGuess();
bool PlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // create a new game

int main()
{
	do
	{
		Intro();
		Play();
	} 
	while (PlayAgain() == 1);
	
	return 0; 
}

// Gameplay
void Play()
{
	BCGame.Reset(); //Resets the tries and current try
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while the game
	//is NOT won and there are tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		// Get the guess
		FText Guess = GetValidGuess();

		// Print valid guess
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}

	PrintGameSummary();
	return;
}

bool PlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << std::endl;
		std::cout << "Congratulations! You won!\n";
	}
	else
	{
		std::cout << "You lost!\n";
	}
}

// introduction
void Intro()
{
	const int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "\n\nWelcome to Bulls and Cows!\n";
	std::cout << std::endl;
	std::cout << "          }   {            ___ " << std::endl;
	std::cout << "          (o o)           (o o) " << std::endl;
	std::cout << "   /-------\\ /             \\ /-------\\ " << std::endl;
	std::cout << "  / | Bull |O               O| Cow  | \\ " << std::endl;
	std::cout << " *  |----- |                 |------|  * " << std::endl;
	std::cout << "    ^      ^                 ^      ^ " << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH << " letter word I am thinking of?\n";
	std::cout << std::endl;
	return;
}

// Player guesses the word
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << std::endl;
		std::cout << "Try #" << CurrentTry << " of " << BCGame.GetMaxTries() << ", Enter your guess:";
		getline(std::cin, Guess);

		//check validity of the guess
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please do not use repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "All letters must be lowercase.\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK); //Keep looping until no errors
	return Guess;
}
