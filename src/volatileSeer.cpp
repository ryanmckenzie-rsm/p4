// AUTHOR: Ryan McKenzie
// FILENAME: volatileSeer.cpp
// DATE: May 17, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v6.3.0

// IMPLEMENTATION INVARIANT:
// * A request has a 50% chance to be rejected.
// * Rejected requests return empty.
// * The hidden message is set to the string passed in request().


#include <ctime>  // time
#include <random>  // uniform_int_distribution
#include <string>  // string


#include "../include/volatileSeer.h"


volatileSeer::volatileSeer(int q):
	seer(q),
	_eng()
{
	_name = "volatileSeer";
	int seed = time(0);
	_eng.seed(seed);
}


void volatileSeer::request(std::string& fetchedMessage)
{
	_message = fetchedMessage;
	seer::request(fetchedMessage);
	if (genRandNum() < _REJECT_CHANCE) {
		fetchedMessage.clear();
	}
}


int volatileSeer::genRandNum()
{
	const int MAX_ROLL = 9;
	std::uniform_int_distribution<> distr(0, MAX_ROLL);
	return distr(_eng);
}