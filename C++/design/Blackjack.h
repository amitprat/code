#pragma once
#include "../header.h"


class Card {
public:
    enum class Suite { DIAMOND, SPADE, HEART, CLUB };
    enum class Type { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

    const unordered_map<Suite, string> suiteStrings = {
        {Suite::DIAMOND, "Diamond"},
        {Suite::SPADE, "Spade"},
        {Suite::HEART, "Heart"},
        {Suite::CLUB, "Club"},
    };

    Suite suite;
    Type type;
    int val = -1;

    Card() {}
    Card(Suite suite, Type type) : suite(suite), type(type) {}
    Card(Suite suite, Type type, int val) : suite(suite), type(type), val(val) {}

    bool operator ==(const Card& that) {
        return this->suite == that.suite && this->type == that.type;
    }

    void operator =(const Card& that) {
        this->suite = that.suite;
        this->type = that.type;
        this->val = that.val;
    }
    string to_string() {
        return "(" + suiteStrings.at(suite) + ":" + std::to_string((int)type) + ")";
    }
};

class CardDeck {
public:
    enum class Pos { TOP };

private:
    vector<Card> cards;
    const int DECK_SIZE = 52;
public:
    CardDeck() {
        srand(time(nullptr));
        init();
    }

    void shuffle() {
        for (int i = DECK_SIZE - 1; i >= 0; i--) {
            int r = rand() % (i + 1);
            swap(cards[i], cards[r]);
        }
    }

    virtual int getValue(int i, int j) {
        if (j > 0 && j < 10) return 1;
        if (j == 10) return 2;
        if (j == 11) return 3;
        if (j == 12) return 4;
        if (j == 0) return 5;
    }

    Card withdraw(Pos pos) {
        switch (pos) {
            case Pos::TOP:
            default:
                auto res = cards.back();
                cards.pop_back();
                return res;
        }
    }

    void putBack(vector<Card> cur) {
        cards.insert(cards.end(), cur.begin(), cur.end());
    }

    string to_string() {
        stringstream ss;
        ss << "Cards: {";
        for (auto& card : cards) {
            ss << card.to_string() << ", ";
        }
        ss.seekg(-2, std::ios_base::end);
        ss << '\0';
        ss << "}";
        return ss.str();
    }

    int size() {
        return cards.size();
    }

private:
    void init() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cards.push_back({ Card::Suite(i), Card::Type(j),getValue(i,j) });
            }
        }
    }
};

class BlackjackCardDeck : public CardDeck {
public:
    int getValue(int i, int j) override {
        if (j > 0 && j < 10) return j + 1;
        if (j == 10) return 10;
        if (j == 11) return 10;
        if (j == 12) return 10;
        if (j == 0) return 11;
    }
};

class Hand {
public:
    vector<Card> cards;
    void add(vector<Card> cards) {
        for (auto& card : cards) {
            this->cards.push_back(card);
        }
    }

    string to_string() {
        stringstream ss;
        ss << "{";
        for (auto& card : cards) {
            ss << card.to_string() << ", ";
        }
        ss << "}";
        return ss.str();
    }

    int value() {
        int val = 0;
        for (auto& card : cards) {
            if (card.val == 1 && val + card.val + 10 <= 21) val += 11;
            else val += card.val;
        }
        return val;
    }
};

class Player {
    bool done = false;

public:
    Hand hand;
    string name;
    double chips;

    Player() {
        name = "default";
        chips = 100;
    }
    Player(string name) : name(name) {}
    Player(string name, int chips) : name(name), chips(chips) {}

    void addToHand(vector<Card> cards) {
        hand.add(cards);
        setDone();
    }

    void resetHand(BlackjackCardDeck& deck) {
        deck.putBack(hand.cards);
    }

    string to_string() {
        stringstream ss;
        ss << "Player: " << name << ", Chips: " << chips << endl;
        ss << "Hand: " << hand.to_string() << endl;
        return ss.str();
    }

    void setDone() {
        done = (rand() % 2 == 1);
    }
    bool isDone() {
        return done;
    }

    void withdrawChips(double chips) {
        this->chips -= chips;
    }

    void addChips(double chips) {
        this->chips += chips;
    }

    bool wantToPlay() {
        return true;
    }
};

class Dealer : public Player {
private:
    bool isFirstServe = true;
    int countsInFirstServe = 2;
    int followupServes = 1;

public:
    Dealer() : Player() {}
    Dealer(string name) : Player(name) {}
    bool deal(BlackjackCardDeck& deck, vector<Player>& players) {
        if (deck.size() < players.size() + 1) return false;
        bool res = false;
        vector<Card> cards;
        int count = -1;
        if (isFirstServe) {
            count = countsInFirstServe;
            isFirstServe = false;
        }
        else {
            count = followupServes;
        }

        for (auto& player : players) {
            if (!player.isDone()) {
                player.addToHand(getCards(deck, count));
                res = true;
            }
        }
        if (res) this->addToHand(getCards(deck, count));

        return res;
    }

private:
    vector<Card> getCards(BlackjackCardDeck& deck, int count) {
        vector<Card> cards;
        for (int i = 0; i < count; i++) {
            cards.push_back(deck.withdraw(BlackjackCardDeck::Pos::TOP));
        }
        return cards;
    }
};

class Blackjack {
private:
    Dealer dealer;
    vector<Player> players;
    BlackjackCardDeck cardDeck;
    int betVal = 5;
    const int BLACK_JACK = 21;

public:
    void registerPlayer(Player player) {
        players.push_back(player);
    }
    void resetGame(vector<Player>& activePlayers) {
        for (auto& player : activePlayers) player.resetHand(cardDeck);
        dealer.resetHand(cardDeck);
        cardDeck.shuffle();
    }

    void startGame(vector<Player>& activePlayers) {
        dealer.deal(cardDeck, activePlayers);
        bool gameNotOver = true;
        while (gameNotOver) {
            gameNotOver = dealer.deal(cardDeck, activePlayers);
        }
        for (auto& player : activePlayers) {
            if (player.hand.value() == BLACK_JACK) {
                dealer.withdrawChips(betVal);
                player.addChips(1.5 * (double)betVal);
            }
            else if (player.hand.value() < dealer.hand.value()) {
                player.withdrawChips(betVal);
                dealer.addChips(betVal);
            }
            else {
                dealer.withdrawChips(betVal);
                player.addChips(betVal);
            }
        }
    }
    void showStats(vector<Player>& activePlayers) {
        cout << "Dealer: " << dealer.to_string() << endl;
        for (auto& player : activePlayers) cout << player.to_string() << endl;
    }

    bool continueGame(vector<Player>& activePlayersSet) {
        return !activePlayersSet.empty() && dealer.hand.value() >= betVal;
    }

    vector<Player> getActivePlayersSet() {
        vector<Player> res;
        for (auto& player : players) {
            if (player.wantToPlay() && player.hand.value() < betVal) {
                res.push_back(player);
            }
        }
        return res;
    }
};

class BlackjackGame {
public:
    static void test() {
        Blackjack game;
        game.registerPlayer(Player("player1", 50));
        game.registerPlayer(Player("player2", 100));

        auto activePlayers = game.getActivePlayersSet();
        bool play = !activePlayers.empty();

        while (play) {
            cout << "Starting game play" << endl;
            cout << "------------------" << endl;
            game.startGame(activePlayers);
            game.showStats(activePlayers);
            cout << "==================" << endl << endl;

            game.resetGame(activePlayers);
            activePlayers = game.getActivePlayersSet();
            play = game.continueGame(activePlayers);
        }
    }
};

class BlackjackCardDeckTest {
public:
    static void test() {
        BlackjackCardDeck deck;
        deck.shuffle();
        cout << deck.to_string();
    }
};

class BlackjackCardDealerTest {
public:
    static void test() {
        BlackjackCardDeck deck;
        deck.shuffle();
        Dealer dealer("dealer1");
        vector<Player> players;
        players.push_back(Player("player1"));
        players.push_back(Player("player2"));
        players.push_back(Player("player3"));
        players.push_back(Player("player4"));
        players.push_back(Player("player5"));
        players.push_back(Player("player6"));
        dealer.deal(deck, players);
        dealer.deal(deck, players);
        dealer.deal(deck, players);
        dealer.deal(deck, players);
        dealer.deal(deck, players);
        dealer.deal(deck, players);
        dealer.deal(deck, players);

        cout << dealer.to_string() << endl;
        for (auto& player : players) {
            cout << player.to_string() << endl;
        }
        unordered_set<string> set;
        for (auto& card : dealer.hand.cards) {
            assert(set.insert(card.to_string()).second);
        }
        for (auto& player : players) {
            for (auto& card : player.hand.cards) {
                assert(set.insert(card.to_string()).second);
            }
        }
    }
};