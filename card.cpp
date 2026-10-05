#include "card.h"

// Implementation of the Card class methods.
Card::Card(Suit suit, Rank rank) : suit(suit), rank(rank) {}

// Returns the suit of the card and the rank of the card.
Suit Card::getSuit() const { return suit; }
Rank Card::getRank() const { return rank; }

// Returns the value of the card based on its rank. Face cards are worth 10, aces are worth 11, and numbered cards are worth their rank.
int Card::getValue() const {
    switch (rank) {
        case Rank::JACK:
        case Rank::QUEEN:
        case Rank::KING:
            return 10;
        case Rank::ACE:
            return 11;
        default:
            return static_cast<int>(rank);
    }
}

// Compares the value of this card with another card. Returns true if the values are equal, false otherwise.
bool Card::valueEquals(const Card& other) const {
    return getValue() == other.getValue();
}
// Compares the value of this card with another card. Returns true if this card's value is greater, false otherwise. 
bool Card::valueGreaterThan(const Card& other) const {
    return getValue() > other.getValue();
}
// Compares the value of this card with another card. Returns true if this card's value is less, false otherwise.
bool Card::valueLessThan(const Card& other) const {
    return getValue() < other.getValue();
}

// Returns the name of the rank of the card as a string.
// For numbered cards, it returns the number as a string.
std::string Card::rankName() const {
    switch (rank) {
        case Rank::JACK: return "Jack";
        case Rank::QUEEN: return "Queen";
        case Rank::KING: return "King";
        case Rank::ACE: return "Ace";
        default: return std::to_string(static_cast<int>(rank));
    }
}

// Returns the name of the suit of the card as a string.
// Returns "?" if the suit is not recognized.
std::string Card::suitName() const {
    switch (suit) {
        case Suit::HEARTS: return "Hearts";
        case Suit::DIAMONDS: return "Diamonds";
        case Suit::CLUBS: return "Clubs";
        case Suit::SPADES: return "Spades";
    }
    return "?";
}

//Prints the cards rank (2 for example) and the suit (Hearts) and outputs to the console (2 of Hearts).
void Card::print(std::ostream& os) const {
    os << rankName() << " of " << suitName();
}