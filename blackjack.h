#pragma once

#include "deck.h"
#include <vector>


class Blackjack {
    public:
        Blackjack(); // Constructor to initialize the game
        void play(); // Function to start the game

    private:
        Deck deck; // Deck of cards for the game
        std::vector<Card*> playerHand; // Vector to store the player's hand
        std::vector<Card*> dealerHand; // Vector to store the dealer's hand
        
        int handValue(const std::vector<Card*> &hand) const; // Function to calculate the value of a hand
        int cash = 500; // Player's starting cash
        int bet = 0; // Player's current bet
        bool allIn = false; // Flag to indicate if the player is all in
        void dealInitialCards(); // Function to deal the initial cards to the player and dealer
        void playerTurn(); // handle the player's turn
        void dealerTurn(); // handle the dealer's turn
        void showHands(bool revealDealer = false); // display the hands of the player and dealer
        void showHand(const std::vector<Card*> &hand) const; // display a specific hand
        void clearHands(); // clear the hands of the player and dealer
        void winner(); // determine the winner of the game
        bool isBlackJack(const std::vector<Card*> &hand) const; // check if a hand is a blackjack
        bool isBust(const std::vector<Card*> &hand) const; // check if a hand is bust
};


        