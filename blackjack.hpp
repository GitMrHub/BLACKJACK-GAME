#include <vector>
#include <thread>
#include <windows.h>

#include "card.hpp"
#include "hand.hpp"
#include "deck.hpp"

using namespace std;


static bool ask_hit_or_stand() {
   while(true) {
        cout <<"\n  HIT(Press H)/STAND(Press S)?\n";

        char c = getchar();
        char ch;

        while ((ch = getchar()) != '\n' && ch != EOF) continue;                     // hit or stand
        if (c == 'h' || c == 'H') {
            return true;
        }

        if (c == 's' || c == 'S') {
            return false;
         }
    }
  return false;
}

enum PlayResult {
  PLAY_RESULT_TIE = 0,
  PLAY_RESULT_DEALER_WIN,
  PLAY_RESULT_PLAYER_WIN,
};

char const* to_friendly_string(PlayResult r) {                                             // show result
  if (r == PLAY_RESULT_TIE) return "Tie!";
  if (r == PLAY_RESULT_DEALER_WIN) return "Dealer win =(";
  if (r == PLAY_RESULT_PLAYER_WIN) return "Player win $$$";
  return "?";
}

class Blackjack {                                                           // logic BJ
private:
  
  Deck deck_;                                                                           // my deck
  int rounds_ = 0;                                                               // Counter of rounds.
  int result_counters_[3] = {0, 0, 0};                                       // counters of results
  int sleep_between_actions_ms_ = 500;                                               // default wait between each action 500 ms

public:

  Blackjack() {
    deck_.shuffle();
  }
 
  void play() {
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    rounds_ += 1;
    cout << endl << "\t\t\t\t\t\t P";
    SetConsoleTextAttribute(h, 36);
    cout << "L";
    SetConsoleTextAttribute(h, 32);
    cout << "A";
    SetConsoleTextAttribute(h, 36);
    cout << 'Y';
    SetConsoleTextAttribute(h, 32);
    cout << 'I';
    SetConsoleTextAttribute(h, 36);
    cout << 'N';
    SetConsoleTextAttribute(h, 32);
    cout << 'G';
    SetConsoleTextAttribute(h, 36);
    cout << " R";
    SetConsoleTextAttribute(h, 32);
    cout << 'O';
    SetConsoleTextAttribute(h, 36);
    cout << "U";
    SetConsoleTextAttribute(h, 32);
    cout << 'N';
    SetConsoleTextAttribute(h, 36);
    cout << "D ";
    SetConsoleTextAttribute(h, 32);
    cout << rounds_ <<  endl;
    if ((rounds_ % 6) == 0) {
      SetConsoleTextAttribute(h, 36);
      cout << "\n   \t\t\t\t\t\tR";
      SetConsoleTextAttribute(h, 32);
      cout << 'E';
      SetConsoleTextAttribute(h, 36);
      cout << 'S';
      SetConsoleTextAttribute(h, 32);
      cout << 'H';
      SetConsoleTextAttribute(h, 36);
      cout << "U";
      SetConsoleTextAttribute(h, 32);
      cout << 'F';
      SetConsoleTextAttribute(h, 36);
      cout << "F";
      SetConsoleTextAttribute(h, 32);
      cout << 'L';
      SetConsoleTextAttribute(h, 36);
      cout << "E....";
      SetConsoleTextAttribute(h, 32);
      cout << endl;
      wait();
      deck_ = Deck();
      deck_.shuffle();
    }

    Hand dealer("Dealer");
    Hand player("Player one");
                                                                                                   // give player a card.
    Card c = deck_.draw();
    SetConsoleTextAttribute(h, 36);
    cout << " =";
    SetConsoleTextAttribute(h, 32);
    cout << "=";
    SetConsoleTextAttribute(h, 36);
    cout << ">";
    SetConsoleTextAttribute(h, 32);
    cout << " Player draw " << c.to_string() << " ..." << endl;
    if (c.invalid()) return;
    player.add(c);
    wait();
                                                                                                         // give dealer a card
    c = deck_.draw();
    SetConsoleTextAttribute(h, 36);
    cout << " =";
    SetConsoleTextAttribute(h, 32);
    cout << "=";
    SetConsoleTextAttribute(h, 36);
    cout << ">";
    SetConsoleTextAttribute(h, 32);
    cout << " Dealer draw "  << c.to_string() << " ..." << endl;
    if (c.invalid()) return;
    dealer.add(c);
    wait();
                                                                                                    // Give player a card.
    c = deck_.draw();
    SetConsoleTextAttribute(h, 36);
    cout << " =";
    SetConsoleTextAttribute(h, 32);
    cout << "=";
    SetConsoleTextAttribute(h, 36);
    cout << ">";
    SetConsoleTextAttribute(h, 32);
    cout << " Player draw " << c.to_string() << " ..." << endl;
    if (c.invalid()) return;
    player.add(c);
    wait();

    cout << endl;                                                                                                // Show player their hand.
    player.dump();
                                                                                                    // Show dealer their hand.
    dealer.dump();
                                                                                                        // Player turn.
    while (ask_hit_or_stand()) {
                                                                                                                // hit
      c = deck_.draw();
      SetConsoleTextAttribute(h, 36);
      cout << " =";
      SetConsoleTextAttribute(h, 32);
      cout << "=";
      SetConsoleTextAttribute(h, 36);
      cout << ">";
      SetConsoleTextAttribute(h, 32);
      cout << " Player draw " << c.to_string() << " ..." << endl;
      if (c.invalid()) return;
      player.add(c);
      wait();
      cout << endl;
      player.dump();
    
      if (player.is_bust()) {
                                                                   // Player loss.
        record_result(PLAY_RESULT_DEALER_WIN);
        return;
      }
    }
                                                                        // Dealer turn.
    while (!dealer.is_soft_17()) {
      c = deck_.draw();
      cout << endl;
      SetConsoleTextAttribute(h, 36);
      cout << " =";
      SetConsoleTextAttribute(h, 32);
      cout << "=";
      SetConsoleTextAttribute(h, 36);
      cout << ">";
      SetConsoleTextAttribute(h, 32);
      cout << " Dealer draw " << c.to_string() << " ..." << endl;
      if (c.invalid()) return;
      dealer.add(c);
      wait();
      dealer.dump();
    }

    if (dealer.is_bust()) {
                                                            // dealer is over 21, loss.
      record_result(PLAY_RESULT_PLAYER_WIN);
      return;
    }
  
    wait();
    if (dealer.best_value() == player.best_value()) {
      record_result(PLAY_RESULT_TIE);
    }
    else if (dealer.best_value() > player.best_value()) {
      record_result(PLAY_RESULT_DEALER_WIN);
    }
    else {
      record_result(PLAY_RESULT_PLAYER_WIN);
    }
  }
                                                                                            // leaderboard.
  void dump_leaderboard() {
    dump_leaderboard_line("PLAYER", PLAY_RESULT_PLAYER_WIN);
    dump_leaderboard_line("DEALER", PLAY_RESULT_DEALER_WIN);
    dump_leaderboard_line("TIE", PLAY_RESULT_TIE);
  }

private:

  void dump_leaderboard_line(char const* name, PlayResult res) {

    streamsize ss = cout.precision();
    cout.precision(2);
    cout << endl;
    cout << "       " << name << ":\t"  << result_counters_[res] << "\t";
    if (rounds_ == 0) {
      cout << "0%" << endl;
    }
    else {
      cout << fixed << (float)result_counters_[res] / rounds_ * 100.0f  << "%" <<endl;
    }
    cout.precision(ss);
  }

  PlayResult record_result(PlayResult res) {
    result_counters_[(int)res] += 1;
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\nR";
    SetConsoleTextAttribute(h, 36);
    cout << "o";
    SetConsoleTextAttribute(h, 32);
    cout << "u";
    SetConsoleTextAttribute(h, 36);
    cout << 'n';
    SetConsoleTextAttribute(h, 32);
    cout << 'd';
    SetConsoleTextAttribute(h, 36);
    cout << " r";
    SetConsoleTextAttribute(h, 32);
    cout << 'e';
    SetConsoleTextAttribute(h, 36);
    cout << "s";
    SetConsoleTextAttribute(h, 32);
    cout << 'u';
    SetConsoleTextAttribute(h, 36);
    cout << "l";
    SetConsoleTextAttribute(h, 32);
    cout << "t: ";
    SetConsoleTextAttribute(h, 32);
    if (res == PLAY_RESULT_PLAYER_WIN);
    else if (res == PLAY_RESULT_DEALER_WIN);
    else if (res == PLAY_RESULT_TIE);
    cout << to_friendly_string(res) << endl << endl;

    return res;
  }
 
  void wait() {
    if (sleep_between_actions_ms_ > 0) {
      this_thread ::sleep_for(chrono::milliseconds(sleep_between_actions_ms_));
    }
  }
};