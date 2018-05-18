// AUTHOR: Ryan McKenzie
// FILENAME: tmVolatileSeer.h
// DATE: May 17, 2018
// REVISION HISTORY: v1.0.0
// PLATFORM: GCC v6.3.0

// CLASS INVARIANT:
// * Rejected requests return empty.
// * Requests are randomly rejected.
// * The user can change the hidden message.
// * The tmVolatileSeer "dies" after so many cycles.
// * A tmVolatileSeer will mix the case of the hidden message.

// INTERFACE INVARIANT:
// * The hidden message can be changed with request's 1-arg.
// * The tmVolatileSeer will randomly reject requests independant of state.
// * The tmVolatileSeer will "die" after a certain amount of cycles.
// * When the tmVolatileSeer is "dead", requests will always return empty.
// * A "dead" tmVolatileSeer is considered inactive.
// * Successful requests will mix the case of the message.

// DESCRIPTION:
// * Combines the functionality of both a tmSeer and a volatileSeer into a
// single class.

// ASSUMPTIONS:
// * The user can replace the message using the reference parameter of
// request().
// * A cycle is determined as turning on and off (i.e. 2 state changes == 1
// cycle).
// * When a tmVolatileSeer has exceeded its cycles, it is "dead" and can no
// longer be requested.
// * All requests to a "dead" tmVolatileSeer return empty;
// * The returned message is mixed arbitrarily via a random number generator.
// * It iterates through the string and has a 30% chance to mix that character's
// case.
// * All requests have a 50% chance to be rejected reagrdless of state.


#ifndef tmVolatileSeer_INCLUDED
#define tmVolatileSeer_INCLUDED


#include <string>  // string


#include "../include/tmSeer.h"
#include "../include/volatileSeer.h"


class tmVolatileSeer : public tmSeer, public volatileSeer
{
	public:
		// Constructors

		tmVolatileSeer(int q);
		// DESCRIPTION:
		// * Initializes the name.
		// 
		// POSTCONDITIONS:
		// * _name is set to the name of the class.
		// * All other values are inherited from the parent constuctors


		// Functionality

		void request(std::string& fetchedMessage) override;
		// DESCRIPTION:
		// * Assigns _message to the fetchedMessage.
		// * If the tmSeer is not "dead" then it will fetch its hidden message,
		// dependant on it active state.
		// * If the state is active, the case of the message is arbitrarily
		// mixed.
		// * If the state is inactive, the message is returned as empty.
		// * If the state changes, the state change count increments.
		// * If the tmSeer is dead, the message will always be returned empty.
		// * Has a 50% chance of passing out empty regardless of state.
		// 
		// PRECONDITIONS:
		// * fetchedMessage must not be empty.
		// 
		// POSTCONDITIONS:
		// * _message is set to fetchedMessage.
		// * If the request count matches _q, the state flips, and the request
		// count is reset.
		// * If the state flips, the state change count increments.
		// * If the state change count increments, the object will be
		// determined "dead" if the count matches twice _k.
};


#endif