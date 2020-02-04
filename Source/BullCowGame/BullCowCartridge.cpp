#include "BullCowCartridge.h"

// game starts
void UBullCowCartridge::BeginPlay() {
    Super::BeginPlay();
    PrintLine(TEXT("Hi there!"));
    PrintLine(TEXT("Guess the 4 letter word..."));
    PrintLine(TEXT("Press Enter to continue..."));

    InitGame();
}

// player hits enter
void UBullCowCartridge::OnInput(const FString& Input) {
    ClearScreen();
    if (Input == HiddenWord) {
        PrintLine(TEXT("Right!"));
    } else {
        PrintLine(TEXT("Wrong!"));
    }
}

void UBullCowCartridge::InitGame() {
    HiddenWord = TEXT("cake");
    Lives = 4;
}