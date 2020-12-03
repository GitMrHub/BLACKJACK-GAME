#include <vector>
#include <random>

#include "card.hpp"

using namespace std;


class Deck {
private:
    vector<Card> deck_;

public:
  Deck() {
    for (int i = SUIT_CLUB; i <= (int)SUIT_SPADE; i++) {
      for (int y = FACE_ACE; y <= (int)FACE_KING; y++) {                           // Create the initial deck.
        deck_.push_back(Card((Face)y, (Suit)i));
      }
    }
  }

  void shuffle() {
    static random_device rd;                           //Randmoly shuffle deck.
    static mt19937 g(rd()); 
    
    std::shuffle(deck_.begin(), deck_.end(), g);
  }

  Card draw() {
    if (!deck_.empty()) {
      Card c = deck_.back();                               // Draw one card from the deck.
      deck_.pop_back();
      return c;
    }
  }
};
