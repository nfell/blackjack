// This is the header file
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <new>

using namespace std;

#ifndef CARD_H
#define CARD_H

class card {
        public:
		card(int i, int j) : value(j), suit(i) {}; //constructor
		void display_card();
		int getValue() {return value;}
		int getSuit() {return suit;}
		
        private:
                int value;
                int suit; // 1 = Hearts, 2 = Clubs, 3 = Spades, 4 = Diamonds
};
#endif

void card::display_card() {
	if (value == 1) 
		cout << "Ace";
	else if (value <= 10)
		cout << value;
	else {
		if (value == 11) {cout << "Jack";}
		else if (value == 12) {cout << "Queen";}
		else {cout << "king";}
	}

	if (suit == 1) 
		cout << " of Hearts" << endl;
	else if (suit == 2) 
		cout << " of Clubs" << endl;
	else if (suit == 3) 
		cout << " of Spades" << endl;
	else
		cout << " of Diamonds" << endl;
}


#ifndef DECK_H
#define DECK_H

class deck {
	public:
		deck(); //constructor
		~deck(); //deconstructor
		void print_deck();
		void shuffle();
		void deal_card(char x);
		void deal();
		void print_hands();
		bool test_loss();
		void winner();
		bool dealer_play();
		bool check_blackjack();

	private:
		vector<card*> Deck, dealer_hand, player_hand;
		int player_tot, dealer_tot;
		int player_aces, dealer_aces;
};

#endif

deck::deck() : player_tot(0), dealer_tot(0), player_aces(0), dealer_aces(0) {
	card* p;
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 14; j++) {
			p = new card(i, j);
			Deck.push_back(p);
		}
	}
}

deck::~deck() {
	for (vector<card*>::iterator it = Deck.begin(); it != Deck.end(); it++)
                delete (*it);
	for (vector<card*>::iterator it = player_hand.begin(); it != player_hand.end(); it++)
                delete (*it);
	for (vector<card*>::iterator it = dealer_hand.begin(); it != dealer_hand.end(); it++)
                delete (*it);
}

void deck::shuffle() {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(Deck.begin(), Deck.end(), default_random_engine(seed));
}

void deck::print_deck() {
	for (vector<card*>::iterator it = Deck.begin(); it != Deck.end(); it++)
		(*it)->display_card();
	cout << endl;
}

void deck::deal_card(char x) {
	if (x == 'p') {
		player_hand.push_back(Deck.back());
		switch (Deck.back()->getValue())
		{
			case (1):
				player_aces += 1;
				player_tot += 11;
				break;
			case (11):
			case (12):
			case (13):
				player_tot += 10;
				break;
			default:
				player_tot += Deck.back()->getValue();
		}
	} else if (x == 'd') {
		dealer_hand.push_back(Deck.back());
		switch (Deck.back()->getValue())
		{
			case (1):
				dealer_aces += 1;
				dealer_tot += 11;
				break;
			case (11):
			case (12):
			case (13):
				dealer_tot += 10;
				break;
			default:
				dealer_tot += Deck.back()->getValue();
		}
	}
	Deck.pop_back();
}

void deck::deal() {
	for (int i = 0; i < 2; i++) {
		deal_card('p');
		deal_card('d');
	}
}		

void deck::print_hands() {
	cout << "Dealer's hand is: " << endl;
	cout << "*HIDDEN*" << endl;
	dealer_hand[1]->display_card();
		
	cout << endl << "Your hand is: " << endl;
	for (int i = 0; i < player_hand.size(); i++) {
		player_hand[i]->display_card();
	}
	cout << endl;
}

bool deck::test_loss() {
	if (player_aces == 0) {
		if (player_tot > 21) {return true;}
		else {return false;}
	} else {
		while (player_aces > 0) {
			if (player_tot > 21) {
				player_tot -= 10;
				player_aces -= 1;
			} else {break;}
		}
		if (player_tot > 21) {return true;}
		else {return false;}
	}
}

void deck::winner() {
	cout << endl << "Dealer's total was " << dealer_tot << " and your total was " << player_tot << ".";
	if (dealer_tot > player_tot) {
		cout << " Dealer wins!" << endl;
	} else if (dealer_tot < player_tot) {
		cout << " You win!" << endl;
	} else {cout << " It's a tie!" << endl;
	}
}

bool deck::dealer_play() {
	cout << "Dealer's hand is: " << endl;
	dealer_hand[0]->display_card();
	dealer_hand[1]->display_card();
	
	while(1) {
		if (dealer_aces == 0) {
			if (dealer_tot > 21) {return false;}
			else if (dealer_tot < 17) {
				deal_card('d');
				dealer_hand.back()->display_card();
			} else {return true;}			// dealer does not hit if they have a hard 17
		} else {
			if (dealer_tot > 21) {
				dealer_tot -= 10;
				dealer_aces -= 1;
			}
			else if (dealer_tot > 17) {return true;}
			else {
				deal_card('d'); 			// dealer hits when they have a soft 17
				dealer_hand.back()->display_card();
			}
		}
	}
}

bool deck::check_blackjack() {
	if (player_tot == 21) {
		if (dealer_hand[1]->getValue() == 1) {
			cout << "Dealer's hand is: " << endl;
			dealer_hand[0]->display_card();
			dealer_hand[1]->display_card();
			if (dealer_tot == 21) {
				cout << "You and the dealer both have Blackjacks! It's a tie!" << endl;
			} else {
				cout << "You have a Blackjack! You win!" << endl;
			}
		} else {
			cout << "You have a Blackjack! You win!" << endl;
		}
		return true;
	} else if (dealer_tot == 21) {
                cout << "Dealer's hand is: " << endl;
                dealer_hand[0]->display_card();
                dealer_hand[1]->display_card();
                cout << endl << "Dealer has a Blackjack! Dealer wins!" << endl;
		return true;
	} else {return false;}
}	
		

