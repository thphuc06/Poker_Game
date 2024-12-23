#include "HoldEmDeclare.h"


Hand3 makeDeck() {
    Hand3 deck;
    for (int i = 0; i < Rank.size(); ++i) {
        for (int j = 0; j < 4; ++j) {
            deck.push_back({ Rank[i], static_cast<Suit>(j) });
        }
    }
    return deck;
}

void shuffle(Hand3& deck) {
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(static_cast<unsigned>(time(0))));
}

void showHand(Hand3& hand) {
    for (int i = 0; i < hand.size(); ++i) {
        std::cout << hand[i].Rank << " of " << Suit_name[hand[i].suit_name] << " ";
    }
    std::cout << std::endl;
}

int Ranking(Hand3& hand) {
    std::vector<int> rank_Value;
    std::map<std::string, int> rank_count;
    bool is_Flush = true, is_Straight = true;
    Suit suit = hand[0].suit_name;

    for (int i = 0; i < hand.size(); ++i) {
        rank_Value.push_back(Rank_value.at(hand[i].Rank));
        ++rank_count[hand[i].Rank];
        if (hand[i].suit_name != suit) {
            is_Flush = false;
        }
    }

    sort(rank_Value.begin(), rank_Value.end());
    for (int i = 0; i < rank_Value.size() - 1; ++i) {
        if (rank_Value[i] != rank_Value[i + 1] - 1) {
            is_Straight = false;
        }
    }

    if (is_Flush && is_Straight) return 8;
    if (rank_count.size() == 2) {
        auto it = rank_count.begin();
        if (it->second == 4 || (++it)->second == 4) return 7;
        return 6;
    }
    if (is_Flush) return 5;
    if (is_Straight) return 4;
    if (rank_count.size() == 3) {
        auto it = rank_count.begin();
        if (it->second == 3 || (++it)->second == 3 || (++it)->second == 3) return 3;
        return 2;
    }
    if (rank_count.size() == 4) return 1;
    return 0;
}

Hand3 drawcard(Hand3& deck, int num) {
    Hand3 hand;
    for (int i = 0; i < num; ++i) {
        hand.push_back(deck.back());
        deck.pop_back();
    }
    return hand;
}

// tiebreak
int tiebreak(const Hand3& hand1, const Hand3& hand2) {
    // Collect card value and frquency
    map<int, int> count1, count2;

    for (auto& card : hand1) {
        int value = Rank_value.at(card.Rank);
        ++count1[value];
    }
    for (auto& card : hand2) {
        int value = Rank_value.at(card.Rank);
        ++count2[value];
    }

    // Sort the values of the cards by Priority 1: Frequency, Priority 2: Value 
    vector<pair<int, int>> sorted1, sorted2;

    for (auto& entry : count1) {
        sorted1.push_back(entry);
    }
    for (auto& entry : count2) {
        sorted2.push_back(entry);
    }

    sort(sorted1.begin(), sorted1.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.second == b.second) {
            return a.first > b.first;  // In case of a tie, pick the higher value
        }
        return a.second > b.second;  // Sort by frequency first
        });

    sort(sorted2.begin(), sorted2.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.second == b.second) {
            return a.first > b.first;  // In case of a tie, pick the higher value
        }
        return a.second > b.second;  // Sort by frequency first
        });


    // Compare sorted cards
    for (size_t i = 0; i < 5; ++i) {
        if (sorted1[i].second > sorted2[i].second) return 1;
        if (sorted1[i].second < sorted2[i].second) return 2;  // Hand 2 wins
        if (sorted1[i].first > sorted2[i].first) return 1;   // Hand 1 wins
        if (sorted1[i].first < sorted2[i].first) return 2;  // Hand 2 wins
    }

    // tie
    return 0;
}

// strongest
// Function to generate the next combination of k elements in a set of n elements
static bool next_combination(vector<int>& comb, int n, int k) {
    int i = k - 1;
    while (i >= 0 && comb[i] == n - k + i) {
        --i;
    }

    if (i < 0) {
        return false; // No more combinations
    }

    ++comb[i];
    for (int j = i + 1; j < k; ++j) {
        comb[j] = comb[j - 1] + 1;
    }

    return true;
}

// GetBestHand of Player
Hand3 getStrongest(Hand3& playerCards, const Hand3& communityCards) {
    Hand3 bestHand;
    int bestRank = -1;

    // Combine all
    Hand3 allCards = playerCards;
    allCards.insert(allCards.end(), communityCards.begin(), communityCards.end());

    // Generate all 5-card combinations from the 7 available cards
    vector<int> comb(5);  // Combination of 5 elements
    iota(comb.begin(), comb.end(), 0); // Fill with {0, 1, 2, 3, 4}

    do {
        Hand3 currentHand;
        // Create bestHand
        for (int i = 0; i < 5; ++i) {
            currentHand.push_back(allCards[comb[i]]);
        }

        // Rank the current hand
        int rank = Ranking(currentHand);

        // If the current hand has a higher rank, update the best hand
        if (rank > bestRank) {
            bestRank = rank;
            bestHand = currentHand;  // Set the current hand as the best hand
        }
        // If hands have the same rank, break ties
        else if (rank == bestRank) {
            if (tiebreak(currentHand, bestHand) == 1) {
                bestHand = currentHand;
            }
        }
    } while (next_combination(comb, 7, 5));  // Generate next combination of 5 out of 7

    return bestHand;
}

string compareHands(vector<Hand3>& player_hands, vector<bool>& active_players, const Hand3& communityCards) {
    int best_rank = -1;
    int winning_player = -1;
    vector<int> tied_players;

    // Store the best hands for each player
    vector<Hand3> bestHands(3);
    for (int i = 0; i < 3; ++i) {
        if (active_players[i]) {
            bestHands[i] = getStrongest(player_hands[i], communityCards);
        }
    }

    // Loop through all players and determine the best hand
    for (int i = 0; i < 3; ++i) {
        if (!active_players[i]) continue; // Skip folded players

        int current_rank = Ranking(bestHands[i]);

        if (current_rank > best_rank) {
            best_rank = current_rank;
            winning_player = i;
            tied_players = { i }; // Reset tie list
        }
        else if (current_rank == best_rank) {
            if (tiebreak(bestHands[i], bestHands[winning_player]) == 1) {
                winning_player = i;
                tied_players = { i }; // Player i wins the tie, reset tie list
            }
            else if (tiebreak(bestHands[i], bestHands[winning_player]) == 0) {
                tied_players.push_back(i); // Add player i to the tie list
            }
        }
    }

    // If there are tied players, return a tie message
    if (tied_players.size() > 1) {
        string s = "It's a tie between players:";
        for (int i = 0; i < tied_players.size(); ++i) {
            s += " " + to_string(tied_players[i] + 1);
        }
        return s;
    }

    // If no players are active, return "No players remain."
    if (winning_player == -1) return "No players remain.";

    // Winner
    return "Player " + to_string(winning_player + 1) + " wins!";
}

void showCommunityCards(Hand3& communityCards, int stage) {
    std::cout << std::endl;
    std::cout << "Community Cards: ";
    for (int i = 0; i < stage; ++i) {
        std::cout << communityCards[i].Rank << " of " << Suit_name[communityCards[i].suit_name] << " ";
    }
    std::cout << std::endl;
}

void playPoker() {
    std::vector<Card3> deck = makeDeck();
    shuffle(deck);

    std::cout << "Welcome to 3-Player Texas Hold'em Poker!" << std::endl;

    std::vector<Hand3> playerHoleCards = {
        drawcard(deck, 2),
        drawcard(deck, 2),
        drawcard(deck, 2)
    };

    Hand3 communityCards = drawcard(deck, 5);

    for (int i = 0; i < playerHoleCards.size(); ++i) {
        std::cout << std::endl << "Player " << i + 1 << "'s cards: ";
        showHand(playerHoleCards[i]);
    }

    std::vector<bool> activePlayers = { true, true, true };

    for (int stage = 3; stage <= 5; stage++) {
        if (stage == 3) std::cout << "\n--- The Flop ---\n";
        else if (stage == 4) std::cout << "\n--- The Turn ---\n";
        else std::cout << "\n--- The River ---\n";

        showCommunityCards(communityCards, stage);

        for (int i = 0; i < activePlayers.size(); ++i) {
            if (activePlayers[i]) {
                char choice;
                std::cout << "Player " << i + 1 << ", do you want to fold? (y/n): ";
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    activePlayers[i] = false;
                    std::cout << "Player " << i + 1 << " has folded." << std::endl;
                }
            }
        }

        int activeCount = std::count(activePlayers.begin(), activePlayers.end(), true);
        if (activeCount <= 1) break;
    }

    std::vector<Hand3> playerBestHands;
    for (int i = 0; i < playerHoleCards.size(); ++i) {
        if (activePlayers[i]) {
            playerBestHands.push_back(getStrongest(playerHoleCards[i], communityCards));
        }
        else {
            playerBestHands.push_back({});
        }
    }

    for (int i = 0; i < playerBestHands.size(); ++i) {
        if (activePlayers[i]) {
            std::cout << std::endl << "Player " << i + 1 << "'s best hand: ";
            showHand(playerBestHands[i]);
        }
    }

    //std::cout << std::endl << compareHands(playerBestHands, activePlayers) << std::endl;
}