all: KleinerPerkins

KleinerPerkins: KleinerPerkins.cpp kp.hpp
	g++ -Wall -Werror -std=c++11 KleinerPerkins.cpp -o KleinerPerkins

clean:
	rm -f KleinerPerkins
