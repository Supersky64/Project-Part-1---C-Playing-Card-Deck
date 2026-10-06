#include "deck.h"
#include <iostream>

int main() {
    Deck deck; // Create a deck of cards
    deck.shuffle(); // Shuffle the deck of cards

    Card* card1 = deck.draw(); // Draw the first card from the deck
    Card* card2 = deck.draw(); // Draw the second card from the deck

    //print the drawn cards
    std::cout << "Card 1: "; card1 -> print(); std::cout << std::endl;
    std::cout << "Card 2: "; card2 -> print(); std::cout << std::endl;

    // calculate the sum
    int sum = card1->getValue() + card2->getValue();
    std::cout << "The sum of the cards is: " << sum << std::endl;

    // calculate the alternative sum if an Ace is present
    if (card1->getRank() == Rank::ACE || card2->getRank() == Rank::ACE) {
        std::cout << "In another timeline where the Ace was worth 1, this is the sum: " 
        << (sum -10) <<std::endl;
    }
    return 0; // End of program
}