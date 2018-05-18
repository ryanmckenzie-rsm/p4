// AUTHOR: Ryan McKenzie
// FILENAME: seer.h
// DATE: May 17, 2018
// REVISION HISTORY: v2.0.0
// PLATFORM: GCC v6.3.0

// CLASS INVARIANT:
// * Failed requests will return empty strings.
// * A seer flips state every _q requests.
// * The seer begins active.
// * _q is determined by the user.

// INTERFACE INVARIANT:
// * The hidden message cannot be changed.
// * The name of the object can be retrieved using name().
// * The seer begins active.
// * The 1-arg constructor determines the max # of times the seer can be
// requested before changing state.
// * A failed request will return empty.

// DESCRIPTION:
// * The seer returns its "secret" message via a public request method.
// * The returned message depends on the seer's active state.

// ASSUMPTIONS:
// * The message is predefined.
// * _q is defined by the client.
// * The user makes a request, passing a string.
// * If the seer is active, the message will be stored in the passed string.
// * If the seer is inactive, the passed string will be emptied.
// * The user must ping the seer object to determine if it is active.
// * The user can request the object's name (useful for templating).
// * A seer begins active.


#ifndef seer_INCLUDED
#define seer_INCLUDED


#include <string>  // string


class seer
{
	public:
		// Constructors

		seer(int q);
		// DESCRIPTION:
		// * Initializes its active state, _q using user input, request
		// count, _message, and _name.
		// * "q" is used to determine how many times the volatileSeer can be
		// requested before it flips state.
		// 
		// PRECONDITIONS:
		// * "q" must be greater than 0.
		// 
		// POSTCONDITIONS:
		// * The object begins active.
		// * _q is initialized using user input.
		// * _requestCount is initialized to 0.
		// * _message is initialized with a predetermined message.
		// * _name is initialized using the class's name.


		// Functionality

		virtual void request(std::string& fetchedMessage);
		// DESCRIPTION:
		// * A request returns the message into the passed string, and then
		// evaulates the object's active state.
		// * Passes out the message if active.
		// * Passes out empty if inactive.
		// 
		// POSTCONDIITONS:
		// * If the request count matches _q, the seer flips state and the
		// request count resets to 0.


		// Accessors

		virtual bool active() const;
		// DESCIPTION:
		// * Checks whether the seer is active.
		// * Returns true if the seer is active.
		// * Returns false if the seer is inactive.

		virtual std::string name() const;
		// DESCRIPTION:
		// * Returns the name of the class, for templating purposes.


	protected:
		// Members

		bool _active;
		// Whether the seer is active or not

		int _q;
		// How many times the user can request the seer.

		unsigned _requestCount;
		// How many times the user has requested the seer.

		std::string _message;
		// The seer's hidden message.
		
		std::string _name;
		// The class's name.
};


inline bool seer::active() const
{
	return _active;
}


inline std::string seer::name() const
{
	return _name;
}


#endif