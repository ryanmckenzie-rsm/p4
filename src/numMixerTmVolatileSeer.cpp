// AUTHOR: Ryan McKenzie
// FILENAME: seer.cpp
// DATE: May 17, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v6.3.0

// IMPLEMENTATION INVARIANT:
// * A numMixerTmVolatileSeer's active state is a merged notion of numMixer's
// coutndown, seer's active state, and tmSeer's dead state.
// * The active state is used to determine if calls are valid or not.
// * All calls decrement numMixer's countdown.
// * Otherwise, functions are implemented as defined in their parents.


#include <vector>  // vector
#include <string>  // string


#include "../include/numMixer.h"
#include "../include/numMixerTmVolatileSeer.h"
#include "../include/tmVolatileSeer.h"


numMixerTmVolatileSeer::numMixerTmVolatileSeer(int q):
	numMixer(),
	seer(q),
	tmVolatileSeer(q),
	_stateChangeCount(0)
{
	_name = "numMixerTmVolatileSeer";
}


numMixerTmVolatileSeer::numMixerTmVolatileSeer(int q,
                                               std::vector<int>& dataset):
	numMixer(dataset),
	seer(q),
	tmVolatileSeer(q),
	_stateChangeCount(0)
{
	_name = "numMixerTmVolatileSeer";
}


bool numMixerTmVolatileSeer::ping(std::vector<int>& returnValues)
{
	// numMxier's implementation
	if (isActive() && numMixer::checkStateValid()) {
		for (auto& val : returnValues) {
			val = numMixer::genRandNum();
		}
		--_countDown;
		return true;
	} else {
		return false;
	}
}


void numMixerTmVolatileSeer::request(std::string& fetchedMessage)
{
	// tmVolatileSeer's implementation
	_message = fetchedMessage;
	if (!isActive()) {
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
		// numMixer's countdown
		--_countDown;
	}
	if (volatileSeer::genRandNum() < _REJECT_CHANCE) {
		fetchedMessage.clear();
	}
}


bool numMixerTmVolatileSeer::active() const
{
	return isActive();
}


bool numMixerTmVolatileSeer::isActive() const
{
	if (_dead) {
		return false;
	} else if (_active) {
		return (_countDown);
	} else {
		return false;
	}
}