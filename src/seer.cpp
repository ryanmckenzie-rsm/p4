// AUTHOR: Ryan McKenzie
// FILENAME: seer.cpp
// DATE: May 17, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v6.3.0

// IMPLEMENTATION INVARIANT:
// * The seer begins active.
// * The user determines _q.
// * The hidden message is predetermined in the constructor.
// * A seer flips state everytimes _stateChangeCount matches _q.
// * State change is evaluated AFTER the message is retrieved (so an active
// seer will return a message even if it flips to inactive during the call).
// * Invalid requests return empty strings.


#include <string>  // string


#include "../include/seer.h"


seer::seer(int q):
	_active(true),
	_q(q),
	_requestCount(0),
	_message("Be Sure To Drink Your Ovaltine."),
	_name("seer")
{
}


void seer::request(std::string& fetchedMessage)
{
	if (_active) {
		fetchedMessage = _message;
	} else {
		fetchedMessage.clear();
	}

	++_requestCount;
	if (_requestCount == _q) {
		_active = !_active;
		_requestCount = 0;
	}
}