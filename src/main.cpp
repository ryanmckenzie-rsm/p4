// AUTHOR: Ryan McKenzie
// FILENAME: main.cpp
// DATE: May 17, 2018
// REVISION HISTORY: v1.0.0
// PLATFORM: GCC v6.3.0

// DESCRIPTION:
// * Opens a log file to write output.
// * Initializes a numMixerTmVolatileSeer object with a random q value.
// * Pings the numMixerTmVolatileSeer in all valid parities (as if it were a
// numMixer).
// * Prints how many times the numMixerTmVolatileSeer changed state and whether
// it's still active or not.
// * Requests the numMixerTmVolatileSeer's hidden message (as if it were a
// seer).
// * Closes the log file.

// ASSUMPTIONS:
// * The numMixerTmVolatileSeer assumes the functionality of all seer objects as
// well as a numMixer object.
// * Tests are implemented in 2 stages.
// * First the numMixerTmVolatileSeer's numMixer functionality is tested and
// printed to the log.
// * Second the numMixerTmVolatileSeer's seer functionality is tested and
// printed to the log.


#include <cmath>  // floor, ceil
#include <ctime>  // time
#include <vector>  // vector
#include <fstream>  // ofstream
#include <ostream>  // endl
#include <random>  // mt19937, uniform_int_distribution
#include <string>  // string


#include "../include/numMixer.h"
#include "../include/numMixerTmVolatileSeer.h"
#include "../include/seer.h"


struct Stats
{
	int activeCount;
	int inactiveCount;
	int rejectCount;
};


void writeHeader(std::string header, std::ofstream& ofs);

int genRandNum();

void requestSeer(seer* seerObj, unsigned count, std::ofstream& ofs);

void testStateActive(bool lastState, std::string message, Stats& stats,
                     std::ofstream& ofs);

void testStateChanged(bool& lastState, seer* seerObj, std::ofstream& ofs);

void pingMixer(numMixer* numMixerObj,
               numMixer::OutputController parity,
			   std::ofstream& ofs);

void printStats(numMixer* numMixerObj, std::ofstream& ofs);


int main()
{
	const char* FILE_NAME = "log.txt";
	std::ofstream ofs;
	ofs.open(FILE_NAME);

	numMixerTmVolatileSeer numMixerTmVolatileSeerObj(genRandNum());

	pingMixer(&numMixerTmVolatileSeerObj, numMixer::MIX, ofs);
	pingMixer(&numMixerTmVolatileSeerObj, numMixer::EVEN, ofs);
	pingMixer(&numMixerTmVolatileSeerObj, numMixer::ODD, ofs);

	printStats(&numMixerTmVolatileSeerObj, ofs);
	
	const int PING_COUNT = 30;
	writeHeader(numMixerTmVolatileSeerObj.name(), ofs);
	requestSeer(&numMixerTmVolatileSeerObj, PING_COUNT, ofs);

	ofs.close();
	return 0;
}
// DESCRIPTION:
// * Opens a log file to write output.
// * Initializes a numMixerTmVolatileSeer object with a random q value.
// * Pings the numMixerTmVolatileSeer in all valid parities (as if it were a
// numMixer).
// * Prints how many times the numMixerTmVolatileSeer changed state and whether
// it's still active or not.
// * Requests the numMixerTmVolatileSeer's hidden message (as if it were a
// seer).
// * Closes the log file.


void writeHeader(std::string header, std::ofstream& ofs)
{
	const int WIDTH = 24;
	std::string border(WIDTH, '#');
	border = "#" + border + "#";
	std::string padding(WIDTH, ' ');
	padding = "#" + padding + "#";
	double dynWidth = WIDTH - header.length();
	int widthLeft = std::floor(dynWidth / 2);
	int widthRight = std::ceil(dynWidth / 2);
	std::string headerLeft(widthLeft, ' ');
	std::string headerRight(widthRight, ' ');
	std::string headerLine = "#" + headerLeft + header + headerRight + "#";
	ofs << border << std::endl;
	ofs << padding << std::endl;
	ofs << headerLine << std::endl;
	ofs << padding << std::endl;
	ofs << border << std::endl;
}
// DESCRIPTION:
// * Writes a header using the ofstream object:
// ##########################
// #                        #
// #     EXAMPLE HEADER     #
// #                        #
// ##########################
//
// Preconditions:
// * Supplied header must be short enough to fit within header box.


int genRandNum()
{
	int MIN_ROLL = 10;
	int MAX_ROLL = 20;
	int seed = time(0);
	std::mt19937 eng;
	std::uniform_int_distribution<> distr(MIN_ROLL, MAX_ROLL);
	return distr(eng);
}
// DESCRIPTION:
// * Returns a random number between and including the MIN_ROLL and MAX_ROLL.


void requestSeer(seer* seerObj, unsigned count, std::ofstream& ofs)
{
	ofs << "Requesting messages...\r\n" << std::endl;
	ofs << "== " << seerObj->name() << " is now active. ==" << std::endl;
	std::string message;
	Stats stats;
	stats.activeCount = 0;
	stats.inactiveCount = 0;
	stats.rejectCount = 0;
	bool lastState;
	while (count--) {
		message = "Lorem ipsum dolor.";
		lastState = seerObj->active();
		seerObj->request(message);
		testStateActive(lastState, message, stats, ofs);
		testStateChanged(lastState, seerObj, ofs);
	}
	ofs << "\r\n" << seerObj->name() << " was inactive for \""
	    << stats.inactiveCount << "\" requests." << std::endl;
	ofs << seerObj->name() << " was active for \"" << stats.activeCount
	    << "\" requests and rejected \"" << stats.rejectCount
		<< "\" of them.\r\n" << std::endl;
}
// DESCRIPTION:
// * Requests a seer objects.
// * Tracks state changes in the seer object and prints data on how often it
// was active, inactive, and how many requests it rejected.
// 
// PRECONDITIONS:
// * "count" should be > 0.
// * The seer object should not be null.
// 
// POSTCONDITIONS:
// * The seer object may be in a different state than when it was passed.


void testStateActive(bool lastState, std::string message, Stats& stats,
                     std::ofstream& ofs)
{
	if (lastState) {
		if (!message.empty()) {
			ofs << message << std::endl;
		} else {
			ofs << "Rejected..." << std::endl;
			++stats.rejectCount;
		}
		++stats.activeCount;
	} else {
		ofs << "Inactive..." << std::endl;
		++stats.inactiveCount;
	}
}
// DESCRIPTION:
// * Checks if the state of the seer object changed, and records data depending
// on the results.


void testStateChanged(bool& lastState, seer* seerObj, std::ofstream& ofs)
{
	if (lastState != seerObj->active()) {
		if (seerObj->active()) {
			ofs << "\r\n== " << seerObj->name() << " is now active. =="
				<< std::endl;
		} else {
			ofs << "\r\n== " << seerObj->name() << " is now inactive. =="
				<< std::endl;
		}
	}
}
// DESCRIPTION:
// * Lets the client know how the state of the seerObj has changed.
// 
// PRECONDITIONS:
// * seerObj must not be null.


void pingMixer(numMixer* numMixerObj,
               numMixer::OutputController parity,
			   std::ofstream& ofs)
{
	if (parity == numMixerObj->getControllerState()) {
		writeHeader("PING " + numMixerObj->getControllerStateName(), ofs);
		ofs << "State change failed (already set)." << std::endl;
	} else {
		numMixerObj->setControllerState(parity);
		writeHeader("PING " + numMixerObj->getControllerStateName(), ofs);
		ofs << "State set to " << numMixerObj->getControllerStateName() << "."
		    << std::endl;
	}

	const int SIZE = 10;
	std::vector<int> pingedData(SIZE);
	if (numMixerObj->ping(pingedData)) {
		ofs << "Ping successful (" << SIZE << " elements requested):"
		    << std::endl;
		for (auto& num : pingedData) {
			ofs << num << std::endl;
		}
	} else {
		ofs << "Ping failed." << std::endl;
	}

	ofs << "\n\n" << std::endl;
}
// DESCRIPTION:
// * Tests the numMixer object with the passed state.
// * Attempts to set the controller state to "parity", reporting its success.
// * Pings the numMixer and prints returned values, if it succeeds.
//
// PRECONDITIONS:
// * numMixerObj must not be null.
// * numMixerObj must have a dataset containing the requested parity.
//
// POSTCONDITIONS:
// * numMixer may no longer be active.


void printStats(numMixer* numMixerObj, std::ofstream& ofs)
{
	writeHeader("STATS", ofs);
	ofs << "Output controller state change count: " << numMixerObj->stateChangeCount()
	    << "." << std::endl;
	std::string state = "Output controller is ";
	if (numMixerObj->isActive()) {
		state += "active";
	} else {
		state += "inactive.";
	}
	ofs << state << "\n\n" << std::endl;
}
// DESCRIPTION:
// * Prints the number of times the output controller has changed state and
// whether the numMixer object is active/inactive.