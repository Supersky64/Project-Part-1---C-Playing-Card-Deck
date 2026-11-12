#include "blackjack.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>


Blackjack::Blackjack() {}

void slowPrint(const std::string &text, int delay = 50) {
  for (char c : text) {
    std::cout << c << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
}

int Blackjack::handValue(const std::vector<Card *> &hand) const {
  int value = 0;
  int aceCount = 0;

  for (const Card *card : hand) {
    value += card->getValue();
    if (card->getRank() == Rank::ACE) {
      aceCount++;
    }
  }

  // Adjust for Aces if value exceeds 21
  while (value > 21 && aceCount > 0) {
    value -= 10; // Count Ace as 1 instead of 11
    aceCount--;  // Decrease the count of Aces to adjust
  }
  return value;
}

// function to check if a hand is a blackjack (two cards totaling 21)
bool Blackjack::isBlackJack(const std::vector<Card *> &hand) const {
  return hand.size() == 2 && handValue(hand) == 21;
}

// function to check if a hand is bust (value exceeds 21)
bool Blackjack::isBust(const std::vector<Card *> &hand) const {
  return handValue(hand) > 21;
}

void Blackjack::clearHands() {
  playerHand.clear(); // Clear the player's hand
  dealerHand.clear(); // Clear the dealer's hand
}

void Blackjack::dealInitialCards() {
  clearHands();   // Clear any existing cards in the hands
  deck.shuffle(); // Shuffle the deck before dealing

  // Deal two cards to the player and two cards to the dealer in alternating
  // order
  playerHand.push_back(deck.draw());
  dealerHand.push_back(deck.draw());
  playerHand.push_back(deck.draw());
  dealerHand.push_back(deck.draw());
}

void Blackjack::showHand(const std::vector<Card *> &hand) const {
  for (std::size_t i = 0; i < hand.size(); ++i) {
    slowPrint("Card " + std::to_string(i + 1) + ": "); // Print the card number
    hand[i]->print(); // Print the card's rank and suit
    if (i + 1 < hand.size()) {
      slowPrint(", "); // Print a comma between cards
    }
  }
}

void Blackjack::showHands(bool revealDealer) {
  slowPrint("\nYour Hand: ");
  showHand(playerHand);
  slowPrint(" (Value: " + std::to_string(handValue(playerHand)) + ")\n");

  slowPrint("Dealer's Hand: ");
  if (revealDealer) {
    showHand(dealerHand);
    slowPrint(" (value: " + std::to_string(handValue(dealerHand)) + ")\n");
  } else {
    dealerHand[0]->print(); // Show only the first card of the dealer's hand
    slowPrint(", [???]\n"); // Indicate that the second card is hidden
  }
}

void Blackjack::playerTurn() {
  while (handValue(playerHand) < 21) {
    std::string choices;
    slowPrint("\nWill you (H)it or (S)tand?: ");
    std::cin >> choices;

    std::transform(choices.begin(), choices.end(), choices.begin(),
                   [](unsigned char c) {
                     return std::tolower(c);
                   }); // Convert input to lowercase
    if (choices == "h" || choices == "hit") {
      Card *newCard = deck.draw(); // Draw a new card from the deck

      if (newCard == nullptr) {
        slowPrint("The deck is empty. Cannot draw more cards.\n");
        break; // Exit the loop if the deck is empty
      }

      playerHand.push_back(newCard); // Add the new card to the player's hand
      slowPrint("You drew: ");
      newCard->print();
      slowPrint("\n");

      showHands(false); // Show the updated hands

      if (isBust(playerHand)) {
        slowPrint("You busted!\n"); // Inform the player that they have busted
        return;                     // End the player's turn
      }
    } else if (choices == "s" || choices == "stand") {
      slowPrint("You chose to stand.\n");
      return; // End the player's turn
    } else {
      slowPrint(
          "Invalid choice. Please enter 'H' to hit or 'S' to stand.\n"); // Prompt for valid input                                                                    
    }
  }
}

void Blackjack::dealerTurn() {
  slowPrint("\nThe Dealer's card is revealed!\n");
  showHands(true); // Show the dealer's hand with both cards revealed

  while (handValue(dealerHand) < 17) {
    Card *newCard = deck.draw(); // Draw a new card for the dealer

    if (newCard == nullptr) {
      slowPrint("The deck is empty. Cannot draw more cards.\n");
      break; // Exit the loop if the deck is empty
    }

    dealerHand.push_back(newCard); // Add the new card to the dealer's hand
    slowPrint("Dealer hits and drew: ");
    newCard->print();
    slowPrint("\nDealer's Value: " + std::to_string(handValue(dealerHand)) +
              "\n"); // Show the dealer's new hand value
  }

  if (handValue(dealerHand) >= 17) {
    slowPrint("Dealer stands.\n"); // Inform that the dealer has chosen to stand
  }
}

void Blackjack::winner() {
  int playerValue = handValue(playerHand); // Get the player's hand value
  int dealerValue = handValue(dealerHand); // Get the dealer's hand value

  slowPrint("\nFinal Results:\n");
  slowPrint("Your Hand Value: " + std::to_string(playerValue) + "\n");
  slowPrint("Dealer's Hand Value: " + std::to_string(dealerValue) + "\n");

  if (isBust(playerHand)) {
    slowPrint("You busted! Dealer wins. Tough luck!\n"); // Player busts, dealer wins
    if(allIn) {
        slowPrint("Ouch! That's unlucky! Maybe think about your choices next time buddy...\n");
    } // Add a special message if the player went all in
    cash -= bet; // Deduct the bet from the player's cash
  } else if (isBust(dealerHand)) {
    slowPrint("Dealer busted! You win!\n"); // Dealer busts, player wins
    if(allIn) {
        slowPrint("WOW! Had me sweating there haha! You have balls of steel for that bet! Here's your cash!\n");
    } // Add a special message if the player went all in
    cash += bet;                            // Add the bet to the player's cash
  } else if (playerValue > dealerValue) {
    slowPrint("You win!\n"); // Player has a higher hand value, player wins
    if(allIn) {
        slowPrint("WOW! That was a close one! You had me going there with that all in bet! Here's your cash!\n");
    } // Add a special message if the player went all in
    cash += bet;             // Add the bet to the player's cash
  } else if (playerValue < dealerValue) {
    slowPrint("Yikes! Dealer wins.\n"); // Dealer has a higher hand value, dealer wins
    if(allIn) {
        slowPrint("Yikes! Ah so close! Sorry buddy...\n");
    } // Add a special message if the player went all in
    cash -= bet;                  // Deduct the bet from the player's cash
  } else {
    slowPrint("PUSH! It's a tie! Your cash remains: $" + std::to_string(cash) +"\n"); // Both have the same hand value, it's a tie
    if(allIn) {
        slowPrint("Phew! That was a close one! You may want to take this as a sign from on high...\n");
    } // Add a special message if the player went all in
  }

  slowPrint("Your remaining cash: $" + std::to_string(cash) +
            "\n"); // Show the player's remaining cash
}

void Blackjack::play() {
  char playAgain = 'y'; // Variable to control the game loop

  std::cout << R"(
  .------.            _     _            _    _            _
|A_  _ |.          | |   | |          | |  (_)          | |
|( \/ ).-----.     | |__ | | __ _  ___| | ___  __ _  ___| | __
| \  /|K /\  |     | '_ \| |/ _` |/ __| |/ / |/ _` |/ __| |/ /
|  \/ | /  \ |     | |_) | | (_| | (__|   <| | (_| | (__|   <
`-----| \  / |     |_.__/|_|\__,_|\___|_|\_\ |\__,_|\___|_|\_\\
      |  \/ K|                            _/ |
      `------'                           |__/
    )" << '\n';

  slowPrint("Welcome to Blackjack!\n");
  slowPrint("Your starting cash is: $" + std::to_string(cash) + "\n");

  while (playAgain == 'y' || playAgain == 'Y') {
    if (cash <= 0) {
      slowPrint("You are out of cash! Game over.\n");
      break; // End the game if the player has no cash left
    }

    slowPrint("How much will you bet? $");
    std::cin >> bet;

    while (bet <= 0 || bet > cash) {
      slowPrint("Invalid bet amount. Please enter a positive amount not "
                "exceeding your cash: $");
      std::cin >> bet;
    }

    if (bet == cash) {
      slowPrint("EHH?! All in! This will be exciting!\n");
    } else {
      slowPrint("You bet: $" + std::to_string(bet) + "\n");
    }

    allIn = (bet == cash); // Check if the player is going all in

    dealInitialCards(); // Deal the initial cards to the player and dealer
    showHands(false);   // Show the hands with the dealer's second card hidden

    if (isBlackJack(dealerHand) && !isBlackJack(playerHand)) {
      slowPrint("Uh oh! The dealer has a Blackjack!\n");
      showHands(true); // Reveal the dealer's hand
      slowPrint("You lose this round.\n");
      return; // End the game if the dealer has a blackjack and the player does
              // not
    }

    if (isBlackJack(playerHand)) {
      slowPrint("BWAH?! You got a Blackjack! Congratulations!\n");
    }

    playerTurn(); // Handle the player's turn

    if (handValue(playerHand) > 21) {
      winner(); // Determine the winner if the player busts
    } else {
      dealerTurn(); // Handle the dealer's turn
      winner();     // Determine and announce the winner of the game
    }

    if (cash <= 0) {
      slowPrint("You are out of cash! Game over.\n");
      break; // End the game if the player has no cash left
    }

    slowPrint("Do you want to play again? (y/n): ");
    std::cin >> playAgain; // Get the player's choice to play again or not
  }
}