#include "deck.h"
#include "card.h"
#include <algorithm> // For std::shuffle

Deck::Deck() : rng(std::random_device{}()) {
  const Suit suits[] = {Suit::HEARTS, Suit::DIAMONDS, Suit::CLUBS,
                        Suit::SPADES};
  cards.reserve(52); // Reserve space for 52 cards

  // create the deck of 52 cards
  for (Suit s : suits) {
    // iterate through all ranks for the current suit
    for (int r = static_cast<int>(Rank::TWO); r <= static_cast<int>(Rank::ACE);
         ++r) {
      // creates a new card with the current suit and rank and add it to the
      // deck
      cards.push_back(new Card(s, static_cast<Rank>(r)));
    }
  }
}

// Destructor for the Deck class.
Deck::~Deck() {
  for (Card *card : cards) {
    delete card;
  }
}

// Shuffle the deck of cards.
void Deck::shuffle() {
    shuffledDeck = std::stack<Card*>(); // Reset the shuffled deck
    std::vector<Card*> tempCards(cards); // copy the pointers only
    std::shuffle(tempCards.begin(), tempCards.end(), rng); // Shuffle the temporary vector of card pointers
    
    // Push the shuffled cards onto the stack
    for (Card* card : tempCards) {
        shuffledDeck.push(card);
    }
}

Card* Deck::draw() {
    if (shuffledDeck.empty()) {
        return nullptr; // Return nullptr if the deck is empty
    }
    Card* topCard = shuffledDeck.top();
    shuffledDeck.pop();
    return topCard;
}
