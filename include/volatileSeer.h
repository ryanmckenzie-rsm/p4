// AUTHOR: Ryan McKenzie
// FILENAME: volatileSeer.h
// DATE: May 17, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v6.3.0

// CLASS INVARIANT:
// * Rejected requests return empty.
// * Requests are randomly rejected.
// * The user can change the hidden message.

// INTERFACE INVARIANT:
// * The hidden message can be changed with request's 1-arg.
// * The volatile seer will randomly reject requests independant of state.
// * Otherwise acts just like a seer.

// DESCRIPTION:
// * The volatileSeer acts like a seer, but randomly rejects requests.

// ASSUMPTIONS:
// * The user can replace the message using the reference parameter of
// request().
// * The volatileSeer randomly rejects requests using a random number generator.
// * there is a 50% chance to reject a request.
// * If a request is rejected, the string passed in request() is set to empty.


#ifndef volatileSeer_INCLUDED
#define volatileSeer_INCLUDED


#include <random>  // mt19937
#include <string>  // string


#include "../include/seer.h"


class volatileSeer : public virtual seer
{
	public:
		// Constructors
		
		volatileSeer(int q);
		// DESCRIPTION:
		// * Initializes the name and the random number generator.
		// * "q" is used to determine how many times the volatileSeer can be
		// requested before it flips state.
		// 
		// POSTCONDITIONS:
		// * The random number generator is initialized.
		// * _name is initialized with the name of the class.
		// * All other inherited values are determined by their parent
		// constructor.


		// Functionality

		void request(std::string& fetchedMessage) override;
		// DESCRIPTION:
		// * Fetches a message using the parent method, and then determines
		// whether to reject the request or not.
		// * Passes out the message if active.
		// * Passes out empty if inactive.
		// * Has a 50% chance of passing out empty regardless of state.
		// 
		// PRECONDITIONS:
		// * fetchedMessage must not be empty.
		// 
		// POSTCONDITIONS:
		// * _message is set to fetchedMessage.


	protected:
		// Members

		static const int _REJECT_CHANCE = 5;
		// Chance to reject a request.


		// Utility

		int genRandNum();
		// DESCRIPTION:
		// * Generates a random number between and including 0 and the maximum
		// roll.


	private:
		// Members

		std::mt19937 _eng;
		// A random number generator used to randomly reject requests.
};


#endif