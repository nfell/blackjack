all: blackjack

blackjack: blackjack.cpp blackjack.hpp
	g++ -Wall -Werror -std=c++11 blackjack.cpp -o blackjack

clean:
	rm -f blackjack
