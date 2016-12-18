#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "headers.h"
#include "game.h"
#include "player.h"

namespace pkr {
        
    enum Suit {
        s, p, d, f
    };
    std::ostream& operator<<(std::ostream& out, const Suit& suit);
    
    enum Rank{
        _2, _3, _4, _5, _6, _7, _8, _9, T, J, Q, K, A
    };
    std::ostream& operator<<(std::ostream& out, const Rank& rank);
    
    struct Card {
    public:
        Rank rank;
        Suit suit;
        Card(Rank rank, Suit suit);
    private:
        Card();        
    friend std::ostream& operator<<(std::ostream& out, const Card& card);
    };
    
    struct Hand {
    public:
        Card c1;
        Card c2;
        Hand(Card c1, Card c2s);
    private:
        Hand();        
    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);
    };
    
    class Deck {
    public:
        Deck();
        void shuffle();
        Card popCard();
        int size();
    private:
        std::vector<Card> cards;
    };
    
    enum class Street {
        preflop, flop, turn, river
    };
    std::ostream& operator<<(std::ostream& out, const Street& street);
    
    class Action {
    public:      
        class ActionBuilder {
        public:
            //TODO return reference instead of pointers            
            ActionBuilder& setPlayer(std::string player);
            ActionBuilder& setMoney(int money);
            ActionBuilder& setStreet(Street street);
            Action build();
        private:
            std::string player;
            Street street;
            int money = 0;
            
            bool playerSet = false;
            bool streetSet = false;
            bool moneySet = false;    
        };
        
        int getMoney();
        std::string getPlayer();
        Street getStreet();
    private:
        Action(int money, Street street, std::string player);
        
        int money;
        Street street;
        std::string player;
        
    friend std::ostream& operator<<(std::ostream& out, const Action& action);
    };

    class Player;
    class PlayerData {
    friend class Game; 
    /*
     * Game class is friend for it to being able 
     * to assign a hand and prevent other classes from reading this hand
     */
    private: 
        Hand hand;
    public:
        std::shared_ptr<Player> player;        
        std::vector<Action> actions;
        int money;       
    };
}

#endif /* DATA_STRUCTURES_H */
