// AUTHOR: Ryan McKenzie
// FILENAME: tmVolatileSeer.h
// DATE: May 17, 2018
// REVISION HISTORY: v1.0.0
// PLATFORM: GCC v6.3.0

// IMPLEMENTATION INVARIANT:
// * A request has a 50% chance to be rejected.
// * Rejected requests return empty.
// * The hidden message is set to the string passed in request().
// * A tmVolatileSeer will die after 2 * _k cycles.
// * An active seer will randomly mix the case of successful requests.
// * There is a 30% chance to mix a character's case.


#include <string>  // string


#include "../include/tmSeer.h"
#include "../include/tmVolatileSeer.h"
#include "../include/volatileSeer.h"


tmVolatileSeer::tmVolatileSeer(int q):
	seer(q),
	tmSeer(q),
	volatileSeer(q)
{
	_name = "tmVolatileSeer";
}


void tmVolatileSeer::request(std::string& fetchedMessage)
{
	// volatileSeer's message replacement
	_message = fetchedMessage;

	// tmSeer's implementation
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
			tmSeer::invertStringCase(fetchedMessage);
		}
	}

	// volatileSeer's implementation
	if (volatileSeer::genRandNum() < _REJECT_CHANCE) {
		fetchedMessage.clear();
	}
}