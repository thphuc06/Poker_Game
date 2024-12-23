#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <sstream>
#include <numeric>
using namespace std;

enum Suit {
    Hearts,
    Diamond,
    Clubs,
    Spades
};

const std::vector<string> Suit_name{
    "hearts", "diamonds", "clubs", "spades" 
};

const std::vector<string> Rank{
    "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "ace"
};

const std::map<string, int> Rank_value{
    {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8},
    {"9", 9}, {"10", 10}, {"jack", 11}, {"queen", 12}, {"king", 13}, {"ace", 14}
};

struct Card3 {
    std::string Rank;
    Suit suit_name;
};

using Hand3 = vector<Card3>;

Hand3 makeDeck();
void shuffle(Hand3& deck);
void showHand(Hand3& hand);
int Ranking(Hand3& hand);
Hand3 drawcard(Hand3& deck, int num);
Hand3 getStrongest(Hand3& playerCards, const Hand3& communityCards);
std::string compareHands(vector<Hand3>& player_hands,vector<bool>& active_players,const Hand3& communityCards);
void showCommunityCards(Hand3& communityCards, int stage);
void playPoker();
