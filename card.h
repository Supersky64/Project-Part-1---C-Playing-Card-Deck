#pragma once

#include <iostream>
#include <string>

enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };

enum Rank {
  TWO = 2,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  ACE
};

class Card {
public:
  Card(Suit suit, Rank rank); // Constructor to initialize the card with a suit and rank

  // Accessor functions for the suit and rank of the card
  Suit getSuit() const;
  Rank getRank() const;

  // Function to get the value of the card based on its rank
  int getValue() const;
  
  // Comparison functions based on the card's value
  bool valueEquals(const Card& other) const;
  bool valueGreaterThan(const Card& other) const;
  bool valueLessThan(const Card& other) const;

  // Functions to get the names of the suit and rank as strings
  std::string suitName() const;
  std::string rankName() const;
  void print(std::ostream& os = std::cout) const;

private:
  // Member variables to store the suit and rank of the card
  const Suit suit;
  const Rank rank;

  // const ensures that the suit and rank of a card cannot be changed after initialization
};