#include "NormalDeclare.h"

using namespace std;


vector<string>suits = { "hearts", "diamonds", "clubs", "spades" };
vector<string>ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "ace" };

struct PointSuit {
	map<string, int> pointSuit;
	PointSuit();
} PS;

PointSuit::PointSuit() {
	pointSuit["spades"] = 0;
	pointSuit["clubs"] = 1;
	pointSuit["diamonds"] = 2;
	pointSuit["hearts"] = 3;
}

point P;

static bool Comp(Card a, Card b)
{
	int rankA = P.Point[a.rank];
	int rankB = P.Point[b.rank];

	if (rankA != rankB)
	{
		return rankA < rankB;
	}

	return PS.pointSuit[a.suit] < PS.pointSuit[b.suit];
}

int compareHand(Hand a, Hand b) // Compares when the strength of two hand is equal
{                                    // hand array[5]
	sort(a.cards, a.cards + 5, Comp); // sort hand 1
	sort(b.cards, b.cards + 5, Comp); // tang dan

	//	cout << "sorted HandA: ";
	//	for(auto i : a.cards) 
	//		cout << i.suit << "_" << i.rank << " ";
	//	cout << "\nsorted HandB: ";
	//	for(auto i : b.cards) 
	//		cout << i.suit << "_" << i.rank << " ";
	//	cout << "\n";

	for (int i = 4; i >= 0; i--)
	{
		if (P.Point[a.cards[i].rank] < P.Point[b.cards[i].rank])
		{
			//cout << "This cards is the highest: " << b.cards[i].suit << "_" << b.cards[i].rank << "\n";
			return 2;
		}
		else if (P.Point[a.cards[i].rank] > P.Point[b.cards[i].rank])
		{
			//cout << "This cards is the highest: " << a.cards[i].suit << "_" << a.cards[i].rank << "\n";
			return 1;
		}
	}
	return 0; // draw
}

// Determines winner
int determineHandWin(Hand* Hands)
{
	if (check_strength(Hands[0]) > check_strength(Hands[1]))
		return 1;
	else if (check_strength(Hands[0]) < check_strength(Hands[1]))
		return 2;
	else
	{
		int comp = compareHand(Hands[0], Hands[1]);

		if (comp == 0)
			return 0; // Draw
		else if (comp == 1)
			return 1; // Hand 1 wins
		else
			return 2; // Hand 2 wins
	}
}

// Swaps hands
void swapHand(Hand* a, Hand* b)
{
	Hand tmp = *b;
	*b = *a;
	*a = tmp;
}

void playerVsEnvironment() {
	//Creates and shuffle the deck
	Card deck[52];
	int index = 0;

	// Creates the deck
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j)
			deck[index++] = { suits[i], ranks[j] };
	}

	shuffle_cards(deck, 52);

	//Deals card for player and computer
	Hand* Hands = dealing_cards(deck, 2);

	// Randoms a number to determine winner
	bool playerWin;

	srand(time(0));
	int random = rand() % 100 + 1; // Give a random number from 1 to 100
	if (random > 40)
	{
		playerWin = false;
	}
	else
	{
		playerWin = true;
	}

	cout << "playerWin = " << playerWin << "\n";

	// Determines the winner
	Card card1, card2; // Computer's hand, Player's hand
	int res;
	int tmp = determineHandWin(Hands);
	if (tmp == 0)
		res = 0; // Hands are equal
	else if (tmp == 1 && !playerWin) // Hand A wins and player loses so computer will win
		res = 1;
	else if (tmp == 1 && playerWin) // Hand A wins and player wins so swap hands for player wins
	{
		swapHand(&Hands[0], &Hands[1]);
		res = 2;	 // PLayer wins
	}
	else if (tmp == 2 && !playerWin) // Hand B wins and player loses so swap hands for computer wins
	{
		swapHand(&Hands[0], &Hands[1]);
		res = 1; // Computer wins
	}
	else if (tmp == 2 && playerWin) // Hand B wins and player wins so player wins
		res = 2;

	// Displays cards and winner
	cout << "Computer's hand: ";
	for (int i = 0; i < 5; i++)
		cout << Hands[0].cards[i].suit << "_" << Hands[0].cards[i].rank << " ";
	cout << "\nPlayer's hand: ";
	for (int i = 0; i < 5; i++)
		cout << Hands[1].cards[i].suit << "_" << Hands[1].cards[i].rank << " ";
	cout << "\n";
	switch (res)
	{
	case 0:
		cout << "This round is tie!!!\n";
		break;
	case 1:
		cout << "The computer is winner in this round!!!\nIt win with "
			<< type_of_card(check_strength(Hands[0])) << "\n";
		break;
	case 2:
		cout << "You are winner in this round!!!\nYou win with "
			<< type_of_card(check_strength(Hands[1])) << "\n";
		break;
	}

	// Deallocates memory
	delete[] Hands;
}

//int main()
//{
//	int playerCount;
//	char cont = 'y';
//	do
//	{
//		playerVsEnvironment();
//		cout << "\nDo you want to play again? (Y/N):  ";
//		cin >> cont;
//	} while (cont == 'y' || cont == 'Y');
//	return 0;
//}