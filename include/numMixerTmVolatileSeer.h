// AUTHOR: Ryan McKenzie
// FILENAME: volatileSeer.h
// DATE: May 17, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v6.3.0

// CLASS INVARIANT:

// INTERFACE INVARIANT:
// * Pinging a numMixerTmVolatileSeer returns a random selection of integers
// 1-100.
// * The number of integers returned is equal to the size of the passed vector.
// * Requesting a numMixerTmVolatileSeer returns its hidden message.
// * The hidden message is set to the passed string.
// * If a numMixerTmVolatileSeer is inactive, it cannot be pinged/requested.
// * A numMixerTmVolatileSeer will become permanently inactive after a set
// number of pings/requests.

// DESCRIPTION:
// * Combines the functionality of a numMixer, a seer, a volatileSeer, and a
// tmSeer into a single object.

// ASSUMPTIONS:
// * ping() directly implements numMixer's primary functionality.
// * request() implements tmVoaltileSeer's primary functionailty, but also
// merges numMixer's notion of a countdown.
// * A numMixerTmVolatileSeer can no longer be pinged/requested once it is dead.
// * A numMixerTmVolatileSeer dies once its state change count has exceeded
// _k * 2 cycles.
// * A numMixerTmVolatileSeer cna no longer be pinged once its countdown reaches
// 0.
// * Every time a numMixerTmVolatileSeer is pinged/requested, its countdown
// decrements.


#ifndef numMixerTmVolatileSeer_INCLUDED
#define numMixerTmVolatileSeer_INCLUDED


#include <vector>  // vector
#include <string>  // string


#include "../include/numMixer.h"
#include "../include/tmVolatileSeer.h"


class numMixerTmVolatileSeer : public numMixer, public tmVolatileSeer 
{
	public:
		// Constructors

		numMixerTmVolatileSeer(int q);
		// DESCRIPTION:
		// * Assigns _name to the class's name, initializes the state change
		// counter, and invokes the parent constructors.
		// 
		// POSTCONDITIONS:
		// * _stateChangeCount is set to 0.
		// * _name is set to the name of the class.
		// * q is passed to seer and tmVolatileSeer's constructors.
		// * The no-arg constructor for numMixer is invoked.

		numMixerTmVolatileSeer(int q, std::vector<int>& dataset);
		// * Assigns _name to the class's name, initializes the state change
		// counter, and invokes the parent constructors.
		// 
		// POSTCONDITIONS:
		// * _stateChangeCount is set to 0.
		// * _name is set to the name of the class.
		// * q is passed to seer and tmVolatileSeer's constructors.
		// * dataset is passed to numMixer's constructor.

		// Functionality

		bool ping(std::vector<int>& returnValues) override;
		// DESCRIPTION:
		// * Stores a random selection of integers from the dataset into
		// "returnValues".
		// * The amount of integers stored is equal to the size of
		// "returnValues".
		// * The parity of the integers is determined by the controller state.
		// * Returns true if the pinged numMixer is active and the requested
		// parity exists within the dataset.
		// * Returns false if the numMixer is inactive, or if the requested
		// parity does not exist within the dataset.
		//
		// PRECONDITIONS:
		// * The numMixer must be in an active state.
		// * The user must provide a vector of size > 0.
		// * The user must have provided integers of the requested parity at
		// object creation.
		//
		// POSTCONDITIONS:
		// * If the call succeeds, the countdown is decremented.

		void request(std::string& fetchedMesage) override;
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
		// * If the object is not dead, the countdown will decrement.
		

		// Accessors

		bool active() const override;
		// * Forwards the call to isActive().

		bool isActive() const override;
		// DESCRIPTION:
		// * Returns whether the object is active or not.
		// * Returns true if the object is active and the countdown is greater
		// than 0.
		// * Returns false if the object is dead, inactive, or the countdown is
		// less than 0.


	private:
		// Members

		int _stateChangeCount;
		// The number of times the object has changed state, including the
		// controller state (numMixer) and the active state (seer).
};


#endif