#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <cstring>

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
    char *name;

public:
    Deck() {
        std::cout<<"Object Created!" <<std::endl;

        for (int s = Hearts; s <= Spades; ++s) {
            for (int r = Ace; r <= King; ++r) {
                cards.push_back({static_cast<Suit>(s), static_cast<Rank>(r)});
            }
        }
    }
    
    Deck (const char *deckname){
        name = new char[strlen(deckname)+1]; //need a spare mem byte for EOL character
        strcpy(name,deckname);
    }
    
    
    
    
    //just random stuff
    Deck(Suit su, Rank ra) : startingCard{su, ra} {
        for (int s = Hearts; s <= Spades; ++s) {
            for (int r = Ace; r <= King; ++r) {
                cards.push_back({static_cast<Suit>(su), static_cast<Rank>(ra)});
            }
        }
        
    }
    
    //copy constructor
    Deck(const Deck &d){
        for(auto const x : d.cards){
            cards.push_back(x);
        }
        
        //name = d.name; //shallow copy, stores same address
        
        //hence need to be replaced with the following for deep copy
        name = new char[strlen(d.name)+1]; //dynamic allocation
        strcpy(name,d.name);
        
    }
    //shallow copy - copying only the member values
    
    
    
    //implicit copy constructor created by compiler if no user copy constructor provided
    //it would do member wise initialisation
    
     
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
    ~Deck(){
        std::cout<<"Object Destroyed!" <<std::endl;
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
    
    Card startingCard;
};

int main() {
    Deck myDeck;
    std::cout << "Initial deck:" << std::endl;
    myDeck.print();

    myDeck.shuffle();
    std::cout << "\nShuffled deck:" << std::endl;
    myDeck.print();

    //initialisation by copy
    Deck testDeck = Deck(Deck::Suit::Spades, Deck::Rank::Ace);
    
    //direct
    Deck nocopyDeck(Deck::Suit::Spades, Deck::Rank::Ace);
    
    Deck newDeck = nocopyDeck; //copy constructor -> or newDeck(nocopyDeck) direct initialisation
    
    
    Deck *ptrDeck = new Deck();
    delete ptrDeck;
    
    int n = 10;
    int* p = new int[n];
    delete[] p;
    
    Deck d1("MyNewDeck");//each char points to read only location.
    Deck d2("MySecondDeck"); //this overwrites d1, and both d1 d2 point to the same location.
    //when one is changed, the other is affected
    
    //deep copy - copying actual content pointed by the pointer , not the address
    
    
    
    return 0;
}
