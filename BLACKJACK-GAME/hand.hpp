#include <vector>
#include <numeric>

#include "card.hpp"

using namespace std;


class Hand {
private:

  char const* name_;                                
  vector<Card> hand_;

public:

  Hand(char const* name) : name_(name) {}

  void add(Card const& c) {
    hand_.push_back(c);
  }

  bool is_bust() {
    return value() > 21;
  }

  bool is_soft_17() {
    return value() >= 17;
  }

  int best_value() {
    int low = value(false);
    int high = value(true);
                                                               // No difference so no problem.
    if (low == high) return low;
                                                   // If high is busted use low.
    if (high > 21) return low;
    return high;
  }

  int value(bool ace11 = false) {
    return accumulate(hand_.begin(), hand_.end(), 0, [ace11](int const& v, Card const& c) { return v + c.value(ace11); });
  }

  void dump() {
    string line;
    for (auto& c : hand_) {
      line += c.to_string() + ", ";
    }
    if (!line.empty()) line.erase(line.size()-2);

    cout << name_ << "'s hand: \t\t";
    if (name_ == "Dealer") cout << "\t";
    cout << line << " (";
    int l = value(false);
    int h = value(true);
    cout << l;
    if (l != h) {
      cout << "/" << h;
    } 
    cout << ")";

    if (is_bust()) {
      cout << " Busted";
    }
    cout << endl;
  }
};
