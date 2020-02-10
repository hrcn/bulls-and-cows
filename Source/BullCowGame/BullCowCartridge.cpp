#include "BullCowCartridge.h"

// game starts
void UBullCowCartridge::BeginPlay() {
    Super::BeginPlay();

    SetupGame();

    // PrintLine(TEXT("The hidden word is: %s."), *HiddenWord);
}

// player hits enter
void UBullCowCartridge::OnInput(const FString& Input) {
    if (bGameOver) {
        ClearScreen();
        SetupGame();
    } else {
        if (Input == HiddenWord) {
            PrintLine(TEXT("You have won!"));
            EndGame();
        } else {
            --Lives;
            PrintLine(TEXT("Lost a life!"));
            if (Lives > 0) {
                if (Input.Len() != HiddenWord.Len()) {
                PrintLine(TEXT("Sorry, try again! \nYou have %i lives left."), Lives);
                }
            } else {
                PrintLine(TEXT("YOU DIED"));
                EndGame();
            }
        }
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