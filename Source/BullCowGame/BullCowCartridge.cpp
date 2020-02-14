#include "BullCowCartridge.h"
#include "HiddenWordList.h"

// Game starts
void UBullCowCartridge::BeginPlay() {
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

    SetupGame();
}

// Player hits enter
void UBullCowCartridge::OnInput(const FString& PlayerInput) {
    if (bGameOver) {
        ClearScreen();
        SetupGame();
    } else {
        // Check player guess
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame() {
    PrintLine(TEXT("Hi there!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    // Debug line
    PrintLine(TEXT("The hidden word is: %s."), *HiddenWord);

    PrintLine(TEXT("Guess the %i letter word..."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \nPress Enter to continue..."));
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess) {
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
    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::bIsIsogram(const FString& Word) const {
    for (int32 Index = 0; Index < Word.Len(); Index++) {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++) {
            if (Word[Index] == Word[Comparison]) {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const {
    TArray<FString> ValidWords;

    for (FString Word : WordList) {
        if (Word.Len() >= 4 && Word.Len() <= 8 && bIsIsogram(Word)) {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const {
    FBullCowCount Count;

    for (int32 i = 0; i < Guess.Len(); i++) {
        if (Guess[i] == HiddenWord[i]) {
            Count.Bulls++;
            continue;
        }

        for (int32 j = 0; j < Guess.Len(); j++) {
            if (Guess[i] == HiddenWord[j]) {
                Count.Cows++;
                break;
            }
        }
    }

    return Count;
}