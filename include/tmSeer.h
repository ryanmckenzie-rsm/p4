// AUTHOR: Ryan McKenzie
// FILENAME: tmSeer.h
// DATE: May 17, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v6.3.0

// CLASS INVARIANT:
// * The tmSeer "dies" after so many cycles.
// * A tmSeer will mix the case of the hidden message.

// INTERFACE INVARIANT:
// * The tmSeer will "die" after a certain amount of cycles.
// * When the tmSeer is "dead", requests will always return empty.
// * A "dead" tmSeer is considered inactive.
// * Successful requests will mix the case of the message.

// DESCRIPTION:
// * The tmSeer acts like a seer, but cannot change state after a certain
// number of cycles.

// ASSUMPTIONS:
// * k is defined as twice q.
// * A cycle is determined as turning on and off (i.e. 2 state changes == 1
// cycle).
// * When a tmSeer has exceeded its cycles, it is "dead" and can no longer be
// requested.
// * All requests to a "dead" tmSeer return empty;
// * The returned message is mixed arbitrarily via a random number generator.
// * It iterates through the string and has a 30% chance to mix that character's
// case.


#ifndef tmSeer_INCLUDED
#define tmSeer_INCLUDED


#include <random>  // mt19937
#include <string>  // string


#include "../include/seer.h"


class tmSeer : public virtual seer
{
	public:
		// Constructors
		
		tmSeer(int q);
		// DESCRIPTION:
		// * Initializes _dead, _k, the state change count, the random number
		// generator, and the name.
		// * "q" is used to determine how many times the volatileSeer can be
		// requested before it flips state.
		// 
		// PRECONDITIONS:
		// * "q" must be greater than 0.
		// 
		// POSTCONDITIONS:
		// * _dead (whether the object can still change states) begins false.
		// * _k is set to a predetermined multiplier.
		// * The state change count begins at 0.
		// * The random number generator is initialized.
		// * _name is set to the class's name.
		// * All other inherited values are determined by their parent
		// constructor.
		

		// Functionality

		void request(std::string& fetchedMessage) override;
		// DESCRIPTION:
		// * If the tmSeer is not "dead" then it will fetch its hidden message,
		// dependant on it active state.
		// * If the state is active, the case of the message is arbitrarily
		// mixed.
		// * If the state is inactive, the message is returned as empty.
		// * If the state changes, the state change count increments.
		// * If the tmSeer is dead, the message will always be returned empty.
		// 
		// POSTCONDITIONS:
		// * If the request count matches _q, the state flips, and the request
		// count is reset.
		// * If the state flips, the state change count increments.
		// * If the state change count increments, the object will be
		// determined "dead" if the count matches twice _k.


		// Accessors

		bool active() const override;
		// DESCRIPTION:
		// * Checks whether the tmSeer is active.
		// * Returns true if the tmSeer is alive and active.
		// * Returns false if the tmSeer is dead or inactive.


	protected:
		// Members

		bool _dead;
		// Determines whether the tmSeer can still be requested.

		int _k;
		// How many times the tmSeer can cycle through states.

		int _stateChangeCount;
		// The number of times the state has changed.


		// Utility

		void invertStringCase(std::string& toInvert);
		// DESCRIPTION:
		// * Inverts the case of the passed string.
		// * Interates through the string, and has a 30% chance to flip its
		// case.

	private:
		// Members

		std::mt19937 _eng;
		// A random number generator used to mix the message case.

		static const int _Q_MULT = 2;
		// Multiplier used to determines _k's values


		// Utility

		int genRandNum();
		// DESCRIPTION:
		// * Generates a random number between and including 0 and the maximum
		// roll.
};


#endif