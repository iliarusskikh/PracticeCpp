#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

class Deck {
public:
    enum Suit { Hearts, Diamonds, Clubs, Spades };
    enum Rank { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

    struct Card {
        Suit suit;
        Rank rank;
    };

private:
    std::vector<Card> cards;

public:
    Deck() {
        for (int s = Hearts; s <= Spades; ++s) {
            for (int r = Ace; r <= King; ++r) {
                cards.push_back({static_cast<Suit>(s), static_cast<Rank>(r)});
            }
        }
    }

    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    void print() const {
        for (const auto& card : cards) {
            std::cout << rankToString(card.rank) << " of " << suitToString(card.suit) << std::endl;
        }
    }

private:
    std::string rankToString(Rank r) const {
        switch (r) {
            case Ace:   return "Ace";
            case Two:   return "Two";
            case Three: return "Three";
            case Four:  return "Four";
            case Five:  return "Five";
            case Six:   return "Six";
            case Seven: return "Seven";
            case Eight: return "Eight";
            case Nine:  return "Nine";
            case Ten:   return "Ten";
            case Jack:  return "Jack";
            case Queen: return "Queen";
            case King:  return "King";
            default:    return "Unknown";
        }
    }

    std::string suitToString(Suit s) const {
        switch (s) {
            case Hearts:   return "Hearts";
            case Diamonds: return "Diamonds";
            case Clubs:    return "Clubs";
            case Spades:   return "Spades";
            default:       return "Unknown";
        }
    }
};

int main() {
    Deck myDeck;
    std::cout << "Initial deck:" << std::endl;
    myDeck.print();

    myDeck.shuffle();
    std::cout << "\nShuffled deck:" << std::endl;
    myDeck.print();

    return 0;
}
