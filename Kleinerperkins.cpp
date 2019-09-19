//KleinerPerkins.cpp
//
#include <iostream>
#include "kp.hpp"
using namespace std;

// MAKE A FUNCTION TO DELETE THE ALLOCATED SPACE
int main(void) {

while (1) {
	bool p = true;
	deck Deck;
	Deck.shuffle();
	Deck.deal();
	Deck.print_hands();
	if (Deck.check_blackjack()) {p = false;}

	while (p) {
		char input;
		
		if (Deck.test_loss()) {
			cout << "Bust! " << endl;
			break;
		}
		
		cout << "Would you like to hit? Yes(y) or No(n)?" << endl;
		cin >> input;
		cout << endl;
		if (input == 'y') {
			Deck.deal_card('p');
			Deck.print_hands();
		} else if (input == 'n') {
			break;
		} else {cerr << "Please enter either y or n" << endl;}
	}

	cout << endl;

	if (p) {
		if (!Deck.dealer_play()) {
			if (!Deck.test_loss()) {cout << endl << "Dealer bust! You win!" << endl;}
			else {cout << endl << "Dealer bust too! There is no winner." << endl;}
		} else {
			if (!Deck.test_loss()) {Deck.winner();}
			else {cout << endl << "The dealer wins!" << endl;}
		}
	}

	while (1) {
		char input;
		cout << "Do you want to play again? Yes(y) or No(n)?" << endl;
		cin >> input;
		cout << endl;
		if (input == 'n') {return 0;}
		else if (input == 'y') {break;}
		else {cerr << "Please enter either y or n" << endl;}
	}
	cin.clear();
	
}
return 0;
}

