#include <iostream>
#include <string>
#include "blackjack.h"

Blackjack::Blackjack() {}

int Blackjack::handValue(const std::vector<Card*> &hand) const{ 
    int value = 0;
    int aceCount = 0;

    for (const Card* card : hand) {
        value += card->getValue();
        if (card->getRank() == Rank::ACE) {
            aceCount++;
        }
    }

    // Adjust for Aces if value exceeds 21
    while (value > 21 && aceCount > 0) {
        value -= 10; // Count Ace as 1 instead of 11
        aceCount--; // Decrease the count of Aces to adjust
    }
    return value;
}

// function to check if a hand is a blackjack (two cards totaling 21)
bool Blackjack::isBlackJack(const std::vector<Card*> &hand) const { 
    return hand.size() == 2 && handValue(hand) == 21;
}

// function to check if a hand is bust (value exceeds 21)
bool Blackjack::isBust(const std::vector<Card*> &hand) const { 
    return handValue(hand) > 21;
}

void Blackjack::clearHands() {
    playerHand.clear(); // Clear the player's hand
    dealerHand.clear(); // Clear the dealer's hand
}

void Blackjack::dealInitialCards() {
    clearHands(); // Clear any existing cards in the hands
    deck.shuffle(); // Shuffle the deck before dealing

    // Deal two cards to the player and two cards to the dealer in alternating order
    playerHand.push_back(deck.draw());
    dealerHand.push_back(deck.draw());
    playerHand.push_back(deck.draw());
    dealerHand.push_back(deck.draw());
}

void Blackjack::showHand(const std::vector<Card*> &hand) const {
    for (std::size_t i = 0; i < hand.size(); ++i) {
        std::cout << "Card " << (i + 1) << ": "; // Print the card number
        hand[i]->print(); // Print the card's rank and suit
        if (i + 1 < hand.size()) {
            std::cout << ", "; // Print a comma between cards
        }
    }
}

void Blackjack::showHands(bool revealDealer) {
    std::cout << "\nYour Hand: ";
    showHand(playerHand);
    std::cout << " (Value: " << handValue(playerHand) << ")\n";

    std::cout << "Dealer's Hand: ";
    if (revealDealer) {
        showHand(dealerHand);
        std::cout << " (value: " << handValue(dealerHand) << ")\n";
    } else {
        dealerHand[0]->print(); // Show only the first card of the dealer's hand
        std::cout << ", [???]\n"; // Indicate that the second card is hidden
    }
}

void Blackjack::playerTurn() {
    while (handValue(playerHand) < 21) {
        std::string choices;
        std::cout << "\nWill you (H)it or (S)tand?: ";
        std::cin >> choices;

        std::transform(choices.begin(), choices.end(), choices.begin(), 
            [](unsigned char c) { return std::tolower(c); }); // Convert input to lowercase
        if (choices == "h" || choices == "hit"){
            Card* newCard = deck.draw(); // Draw a new card from the deck

            if(newCard == nullptr){
                std::cout << "The deck is empty. Cannot draw more cards.\n";
                break; // Exit the loop if the deck is empty
            }

            playerHand.push_back(newCard); // Add the new card to the player's hand
            std::cout << "You drew: "; newCard->print(); std::cout << "\n";

            showHands(false); // Show the updated hands

            if (isBust(playerHand)) {
                std::cout << "You busted!\n"; // Inform the player that they have busted
                return; // End the player's turn
            }
        } else if (choices == "s" || choices == "stand") {
            std::cout << "You chose to stand.\n";
            return; // End the player's turn
        } else {
            std::cout << "Invalid choice. Please enter 'H' to hit or 'S' to stand.\n"; // Prompt for valid input
        }
    }
}

void Blackjack::dealerTurn() {
    std::cout << "\nThe Dealer's card is revealed!\n";
    showHands(true); // Show the dealer's hand with both cards revealed

    while (handValue(dealerHand) < 17) {
        Card* newCard = deck.draw(); // Draw a new card for the dealer

        if(newCard == nullptr){
            std::cout << "The deck is empty. Cannot draw more cards.\n";
            break; // Exit the loop if the deck is empty
        }

        dealerHand.push_back(newCard); // Add the new card to the dealer's hand
        std::cout << "Dealer hits and drew: "; newCard->print();
        std::cout << "\nDealer's Value: " << handValue(dealerHand) << "\n"; // Show the dealer's new hand value
    }

    if (handValue(dealerHand) >= 17){
        std::cout << "Dealer stands.\n"; // Inform that the dealer has chosen to stand
    }
}

void Blackjack::winner() const {
    int playerValue = handValue(playerHand); // Get the player's hand value
    int dealerValue = handValue(dealerHand); // Get the dealer's hand value

    std::cout << "\nFinal Results:\n";
    std::cout << "Your Hand Value: " << playerValue << "\n";
    std::cout << "Dealer's Hand Value: " << dealerValue << "\n";

    if (isBust(playerHand)) {
        std::cout << "You busted! Dealer wins. Tough luck!\n"; // Player busts, dealer wins
    } else if (isBust(dealerHand)) {
        std::cout << "Dealer busted! You win!\n"; // Dealer busts, player wins
    } else if (playerValue > dealerValue) {
        std::cout << "You win!\n"; // Player has a higher hand value, player wins
    } else if (playerValue < dealerValue) {
        std::cout << "Dealer wins.\n"; // Dealer has a higher hand value, dealer wins
    } else {
        std::cout << "PUSH! It's a tie!\n"; // Both have the same hand value, it's a tie
    }
}