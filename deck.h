#pragma once
#include <vector>
#include <stack>
#include <random>
#include "card.h"

class Deck{
    public:
        Deck(); // Constructor to initialize the deck with 52 cards
        ~Deck(); // Destructor to clean up the deck and clears from the heap

        void shuffle(); // Shuffles the deck and clears it from the stack then repopulates it
        Card* draw(); // Draws a card from the top of the deck and returns a pointer to it
    
    private:
        std::vector<Card*> cards; // Vector to store pointers to the cards in the deck
        std::stack<Card*> shuffledDeck; // Stack to store pointers to the shuffled cards
        std::mt19937 rng; // Random number generator for shuffling
};