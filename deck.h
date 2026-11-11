// This header file defines the Deck class, which represents a deck of playing cards.
// It includes member functions to shuffle the deck and draw cards from it.
// The Deck class uses a vector to store pointers to Card objects and a stack to manage the shuffled cards.
// The point of a header file is to provide a declaration of the class and its members,
// allowing other parts of the program to use the Deck class without needing to know the implementation details

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