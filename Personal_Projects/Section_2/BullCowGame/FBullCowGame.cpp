//
#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet"; // must be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{

	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

//recieves valid guess
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;

	//loop through all letters in the hidden word
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 HWChar = 0; HWChar < HiddenWordLength; HWChar++)
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{
			//if they match
			if (Guess[GChar] == MyHiddenWord[HWChar])
			{
				//incriment bulls if they are in the same place
				if (HWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				//incriment cows if not
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen; //setup map
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handles mixed case
		//loop through all the letters
		if (LetterSeen[Letter])				//if the letter is in the map
		{
			return false;						//we do NOT have an isogram
		}
		else								//otherwise
		{
			LetterSeen[Letter] = true;			//add letter to the map
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))// if not a lowercase letter
		return false;
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if guess isn't an isogram, return an error
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	// if guess isn't all lowercase, return error
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	// if guess length is wrong, return error
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
		//otherwise, return OK
	else
	{
		return EGuessStatus::OK;
	}
}
