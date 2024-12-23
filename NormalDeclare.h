#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace std;

struct Card
{
    string suit;    // Stores the suit of the card (hearts, diamonds, clubs, spades)
    string rank;    // Stores the rank of the card (2-10, jack, queen, king, ace)
};

struct Hand
{
    Card cards[5];  // Array of 5 cards representing a poker hand
};

struct point
{
    map<string, int> Point;  // Maps card ranks and suits to numerical values for comparison
    point();
};


/**
 * Shuffles the deck of cards randomly
 */
void shuffle_cards(Card deck[], int n);

/**
 * Deals cards to players from the deck
 */
Hand* dealing_cards(Card desk[52], int num_players);

/**
 * Poker hand evaluation functions - each returns true if the hand matches that type
 */
bool straight_flush(Hand player);   // Five cards in sequence, all of the same suit
bool four_of_a_kind(Hand player);   // Four cards of the same rank
bool full_house(Hand player);       // Three of a kind plus a pair
bool flush(Hand player);            // Any five cards of the same suit
bool straight(Hand player);         // Five cards in sequence
bool three_of_a_kind(Hand player);  // Three cards of the same rank
bool two_pair(Hand player);         // Two different pairs
bool one_pair(Hand player);         // Two cards of the same rank

/**
 * Compares two hands to determine which is stronger
 * return 2 if b > a, return 1 if a > b, return 0 if equal.
 */
int compare_hand(Hand a, Hand b);

/**
 * Converts a numerical score to a string description of the hand type
 * (e.g., "full house", "straight flush")
 * easy for graphic showcase
 */
string type_of_card(int score);

/**
 * Determines the winner among multiple players
 * it will return a pair contain a pair and int
 * the pair.first as a pair will contain the position of win player, if 2 player tie it will contain 2 pos respectively, else it store the player win pos at first and second will be -1
 * the pair.second is represented for hand strength
 */
pair<pair<int,int>, int> get_winner(Hand* players, int num_players);

/**
 * Statistics and player data management functions
 */
void update_player_data(const string player_name, bool win, int hand_type);
void update_player_win_rate(const string player_name, float win_rate);
void update_player_win_game(const string player_name, int win_game);
float get_win_rate(const string player_name);
int get_win_game(const string player_name);

int check_strength(Hand hand);  // Returns numerical value representing hand strength
//this funtion will return the value of pair (pair, 4 card, 3 card...)

pair<int, pair<int, int>> take_pair(Hand a);  // Identifies pairs in a hand



//Mode 4: PVE mode
int determineHandWin(Hand* Hands);
void playerVsEnvironment();

