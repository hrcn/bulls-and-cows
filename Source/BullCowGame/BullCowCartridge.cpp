#include "BullCowCartridge.h"
#include "HiddenWordList.h"

// Game starts
void UBullCowCartridge::BeginPlay() {
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    PrintLine(TEXT("The number of valid words is %i"), GetValidWords(Words).Num());
    PrintLine(TEXT("The hidden word is: %s."), *HiddenWord);
}

// Player hits enter
void UBullCowCartridge::OnInput(const FString& Input) {
    if (bGameOver) {
        ClearScreen();
        SetupGame();
    } else {
        // Check player guess
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame() {
    PrintLine(TEXT("Hi there!"));

    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word..."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \nPress Enter to continue..."));
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(FString Guess) {
    if (Guess == HiddenWord) {
        PrintLine(TEXT("You have won!"));
        EndGame();
        return;
    } 

    // Check right number of characters
    if (Guess.Len() != HiddenWord.Len()) {
        PrintLine(TEXT("The hidden word is %i letter long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try again! \nYou have %i lives left."), Lives);
        return;
    }

    // Check if isogram
    if (!bIsIsogram(Guess)) {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    // Remove life
    PrintLine(TEXT("Lost a life!"));
    --Lives;

    // Check if Lives > 0
    if (Lives <= 0) {
        ClearScreen();
        PrintLine(TEXT("YOU DIED"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }
    
    // Show the player bulls and cows
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::bIsIsogram(FString Word) const {
    for (int32 Index = 0; Index < Word.Len(); Index++) {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++) {
            if (Word[Index] == Word[Comparison]) {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const {
    TArray<FString> ValidWords;

    for (FString Word : WordList) {
        if (Word.Len() >= 4 && Word.Len() <= 8 && bIsIsogram(Word)) {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}