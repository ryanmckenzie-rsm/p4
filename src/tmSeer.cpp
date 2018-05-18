// AUTHOR: Ryan McKenzie
// FILENAME: tmSeer.cpp
// DATE: May 17, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v6.3.0

// IMPLEMENTATION INVARIANT:
// * A tmSeer will die after 2 * _k cycles.
// * An active seer will randomly mix the case of successful requests.
// * There is a 30% chance to mix a character's case.


#include <ctime>  // time
#include <random>  // uniform_int_distribution
#include <string>  // string


#include "../include/tmSeer.h"


tmSeer::tmSeer(int q):
	seer(q),
	_dead(false),
	_k(q * _Q_MULT),
	_stateChangeCount(0),
	_eng()
{
	_name = "tmSeer";
	int seed = time(0);
	_eng.seed(seed);
}


void tmSeer::request(std::string& fetchedMessage)
{
	if (_dead) {
		fetchedMessage.clear();
	} else {
		bool lastState = _active;
		seer::request(fetchedMessage);
		if (lastState != _active) {
			++_stateChangeCount;
			if (_stateChangeCount == _k * 2) {
				_dead = true;
			}
		}
		if (!fetchedMessage.empty()) {
			invertStringCase(fetchedMessage);
		}
	}
}


bool tmSeer::active() const
{
	if (_dead) {
		return false;
	} else {
		return seer::active();
	}
}


void tmSeer::invertStringCase(std::string& toInvert)
{
	for (auto& c : toInvert) {
		const int MIX_CHANCE = 3;
		if (genRandNum() < 10 - MIX_CHANCE) {
			continue;
		} else {
			if (isupper(c)) {
				c = tolower(c);
			} else {
				c = toupper(c);
			}
		}
	}
}


int tmSeer::genRandNum()
{
	const int MAX_ROLL = 9;
	std::uniform_int_distribution<> distr(0, MAX_ROLL);
	return distr(_eng);
}