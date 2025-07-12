#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>
using namespace std;

//MODEL

struct Card {
    int rank; // 6-14 (6,7,8,9,10,Валет,Дама,Король,Туз)
    int suit; // 0-черви, 1-бубны, 2-трефы, 3-пики
    
    string getRankString() const {
        if (rank >= 6 && rank <= 10) return to_string(rank);
        switch(rank) {
            case 11: return "Валет";
            case 12: return "Дама";
            case 13: return "Король";
            case 14: return "Туз";
            default: return "?";
        }
    }
    
    string getSuitString() const {
        switch(suit) {
            case 0: return "черви";
            case 1: return "бубны";
            case 2: return "трефы";
            case 3: return "пики";
            default: return "?";
        }
    }
    
    string toString() const {
        return getRankString() + " " + getSuitString();
    }
};

class GameModel {
private:
    vector<Card> player1;
    vector<Card> player2;
    vector<Card> table;
    int roundCount;
    bool gameEnded;
    mt19937 rng;
    
public:
    GameModel() : roundCount(0), gameEnded(false), rng(random_device{}()) {}
    
    void initializeDeck(vector<Card>& deck) {
        deck.clear();
        for (int suit = 0; suit < 4; ++suit) {
            for (int rank = 6; rank <= 14; ++rank) {
                deck.push_back({rank, suit});
            }
        }
        shuffle(deck.begin(), deck.end(), rng);
    }
    
    void dealCards(vector<Card>& deck) {
        player1.clear();
        player2.clear();
        table.clear();
        
        for (size_t i = 0; i < deck.size(); ++i) {
            if (i % 2 == 0) player1.push_back(deck[i]);
            else player2.push_back(deck[i]);
        }
    }
    
    int compareCards(const Card& card1, const Card& card2) {
        if (card1.rank > card2.rank) return 1;
        if (card1.rank < card2.rank) return -1;
        return 0; 
    }
    
    void collectCards(vector<Card>& winner) {
        
        shuffle(table.begin(), table.end(), rng);
        winner.insert(winner.end(), table.begin(), table.end());
        table.clear();
    }
    
    bool playRound() {
        if (player1.empty() || player2.empty()) {
            gameEnded = true;
            return false;
        }
        
        
        Card card1 = player1.front();
        Card card2 = player2.front();
        player1.erase(player1.begin());
        player2.erase(player2.begin());
        
        table.push_back(card1);
        table.push_back(card2);
        
        int result = compareCards(card1, card2);
        
        if (result == 1) {
            collectCards(player1);
        } else if (result == -1) {
            collectCards(player2);
        }
        
        
        roundCount++;
        return true;
    }
    
    bool isGameEnded() const {
        return gameEnded || player1.empty() || player2.empty();
    }
    
    int determineWinner() const {
        if (player1.size() > player2.size()) return 1;
        if (player2.size() > player1.size()) return 2;
        return 0;
    }
    
    
    const vector<Card>& getPlayer1Cards() const { return player1; }
    const vector<Card>& getPlayer2Cards() const { return player2; }
    const vector<Card>& getTableCards() const { return table; }
    int getRoundCount() const { return roundCount; }
};

//VIEW

class GameView {
public:
    void displayWelcome() const {
        cout << "============================\n";
        cout << "    Игра 'Пьяница' (Война)\n";
        cout << "============================\n\n";
    }
    
    void displayShuffling() const {
        cout << "Перемешиваем колоду карт...\n";
        delay(1000);
    }
    
    void displayDealing() const {
        cout << "Раздаем карты игрокам...\n";
        delay(1000);
    }
    
    void displayRound(const Card& card1, const Card& card2, int result) const {
        cout << "Игрок 1: " << card1.toString() << "  vs  ";
        cout << "Игрок 2: " << card2.toString() << "  =>  ";
        
        switch(result) {
            case 1: cout << "Выиграл Игрок 1!"; break;
            case -1: cout << "Выиграл Игрок 2!"; break;
            case 0: cout << "НИЧЬЯ! Карты остаются на столе."; break;
        }
        cout << "\n";
        delay(500);
    }
    
    void displayGameState(int round, size_t p1Size, size_t p2Size) const {
        cout << "\nРаунд: " << round << " | ";
        cout << "Карт у Игрока 1: " << p1Size << " | ";
        cout << "Карт у Игрока 2: " << p2Size << "\n";
        cout << "----------------------------------------\n";
    }
    
    void displayGameResult(int winner) const {
        cout << "\n============================\n";
        cout << "       ИГРА ОКОНЧЕНА!\n";
        cout << "============================\n";
        
        if (winner == 0) {
            cout << "НИЧЬЯ! У обоих игроков закончились карты одновременно.\n";
        } else {
            cout << "ПОБЕДИЛ ИГРОК " << winner << "!\n";
        }
    }
    
    void displayDelayBetweenRounds() const {
        delay(100);
    }
    
private:
    void delay(int milliseconds) const {
        this_thread::sleep_for(chrono::milliseconds(milliseconds));
    }
};

//CONTROLLER

class GameController {
private:
    GameModel model;
    GameView view;
    vector<Card> deck;
    
public:
    GameController() {
        srand(static_cast<unsigned int>(time(nullptr)));
    }
    
    void startGame() {
        view.displayWelcome();
        view.displayShuffling();
        
        model.initializeDeck(deck);
        model.dealCards(deck);
        
        view.displayDealing();
    }
    
    void playGame() {
        while (!model.isGameEnded()) {
            
            view.displayGameState(
                model.getRoundCount() + 1,
                model.getPlayer1Cards().size(),
                model.getPlayer2Cards().size()
            );
            
            
            bool roundPlayed = model.playRound();
            
            if (roundPlayed) {
                
                const auto& table = model.getTableCards();
                if (table.size() >= 2) {
                    int result = model.compareCards(table[table.size()-2], table.back());
                    view.displayRound(table[table.size()-2], table.back(), result);
                }
            }
            
            view.displayDelayBetweenRounds();
        }
        
        
        view.displayGameResult(model.determineWinner());
    }
};


int main() {
    SetConsoleOutputCP(CP_UTF8);
    GameController game;
    game.startGame();
    game.playGame();
    
    return 0;
}