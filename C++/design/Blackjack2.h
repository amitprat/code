#include <random>

#include "../header.h"

class Blackjack2 {
    enum class Suit { Hearts,
                      Diamonds,
                      Clubs,
                      Spades };
    enum class Rank { Two = 2,
                      Three,
                      Four,
                      Five,
                      Six,
                      Seven,
                      Eight,
                      Nine,
                      Ten,
                      Jack = 11,
                      Queen = 12,
                      King = 13,
                      Ace = 14 };

    struct Card {
        Suit suit;
        Rank rank;

        int getValue() const {
            return static_cast<int>(rank);
        }

        void print() const {
            std::string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
            std::string suits[] = {"H", "D", "C", "S"};
            int rankVal = getValue();
            std::string rankStr;
            switch (rank) {
                case Rank::Jack:
                    rankStr = "J";
                    break;
                case Rank::Queen:
                    rankStr = "Q";
                    break;
                case Rank::King:
                    rankStr = "K";
                    break;
                case Rank::Ace:
                    rankStr = "A";
                    break;
                default:
                    rankStr = std::to_string(rankVal);
                    break;
            }
            std::cout << rankStr << suits[(int)suit] << " ";
        }
    };

    class Deck {
        std::vector<Card> cards;
        std::mt19937 rng;

       public:
        Deck() {
            rng.seed(static_cast<unsigned>(std::time(nullptr)));
            for (int s = 0; s < 4; ++s) {
                for (int r = 2; r <= 14; ++r) {
                    if (r <= 10)
                        cards.push_back({(Suit)s, (Rank)r});
                    else if (r == 11)
                        cards.push_back({(Suit)s, Rank::Jack});
                    else if (r == 12)
                        cards.push_back({(Suit)s, Rank::Queen});
                    else if (r == 13)
                        cards.push_back({(Suit)s, Rank::King});
                    else
                        cards.push_back({(Suit)s, Rank::Ace});
                }
            }
        }

        void shuffle() {
            std::shuffle(cards.begin(), cards.end(), rng);
        }

        Card deal() {
            Card c = cards.back();
            cards.pop_back();
            return c;
        }
    };

    class Hand {
        std::vector<Card> cards;

       public:
        void add(Card c) {
            cards.push_back(c);
        }

        int getValue() const {
            int total = 0;
            int aceCount = 0;

            for (const auto& c : cards) {
                int val = c.getValue();
                if (val == 11) aceCount++;
                total += val;
            }

            while (total > 21 && aceCount > 0) {
                total -= 10;  // count Ace as 1 instead of 11
                aceCount--;
            }

            return total;
        }

        void print() const {
            for (const auto& c : cards) c.print();

            std::cout << " (" << getValue() << ")\n";
        }

        bool isBusted() const {
            return getValue() > 21;
        }
    };

    class Player {
       protected:
        Hand hand;

       public:
        virtual void play(Deck& deck) {
            while (hand.getValue() < 17) {
                hand.add(deck.deal());
            }
        }

        void addCard(Card c) {
            hand.add(c);
        }

        void showHand(const std::string& name) const {
            std::cout << name << "'s hand: ";
            hand.print();
        }

        bool isBusted() const {
            return hand.isBusted();
        }

        int getValue() const {
            return hand.getValue();
        }
    };

    class BlackjackGame {
        Deck deck;
        Player dealer;
        Player player;

       public:
        void play() {
            deck.shuffle();

            // Initial deal
            player.addCard(deck.deal());
            dealer.addCard(deck.deal());
            player.addCard(deck.deal());
            dealer.addCard(deck.deal());

            player.showHand("Player");
            dealer.showHand("Dealer");

            // Player's turn
            while (!player.isBusted()) {
                char choice;
                std::cout << "Hit (h) or Stand (s)? ";
                std::cin >> choice;
                if (choice == 'h') {
                    player.addCard(deck.deal());
                    player.showHand("Player");
                } else {
                    break;
                }
            }

            if (player.isBusted()) {
                std::cout << "Player busts! Dealer wins.\n";
                return;
            }

            // Dealer's turn
            std::cout << "\nDealer's turn:\n";
            dealer.showHand("Dealer");
            dealer.play(deck);
            dealer.showHand("Dealer");

            // Outcome
            if (dealer.isBusted() || player.getValue() > dealer.getValue()) {
                std::cout << "Player wins!\n";
            } else if (player.getValue() < dealer.getValue()) {
                std::cout << "Dealer wins!\n";
            } else {
                std::cout << "Push (tie).\n";
            }
        }
    };

   public:
    static void test() {
        BlackjackGame game;
        game.play();
    }
};