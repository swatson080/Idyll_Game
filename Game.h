/*
 * Game.h
 *
 *  Created on: Dec 4, 2017
 *      Author: joe
 *  Defines class Game, which is used to administrate the game:
 *  	- Takes user input, and processes it
 *  	- Tracks game time
 *  	- Tracks player fatigue
 *  	- Defines the maximum user input size
 *  	- prints intro, outro, and menu options
 */

#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <time.h>

#include "Items.h"

using namespace std;

class Game {
private:

	int gTime;
	int fatigue;
	int score;

	// Activity variables
	int inpFish;
	int inpMine;
	int inpForage;
	int inpInvestigate;
	int inpCraft;
	int inpManage;


	// Location variables

	bool cave;
	bool river;
	bool vista;
	bool grove;
	bool cabin;

	// Player state (exhausted or not exhausted, depends on fatigue level)

	bool fatigued;

	// Tracks whether player becomes fatigued throughout the game
	bool neverFatigued;

	// Tracks how many locations player discovers

	static int lCount;

	// Tracks how often player sleeps for Misguided Vigilance

	static int sCount;

public:

	Game();

	virtual ~Game();

	const static int ISIZE = 2;

	// Constant activity variables

	const int inpExplore = 1;

	const int inpSleep = 2;

	void static printIntro();

	void printMenu();

	void printStats(Items & inv);

	// Menu Flags and Management

	void resetFlags();

	int getInpFish();

	int getInpMine();

	int getInpForage();

	int getInpInv();

	int getInpCraft();

	int getInpMan();

	char * getInp(char * pInp);

	int setSize(char * pInp);

	bool checkInp(char * pInp, int aSize);

	int getTime();

	void setTime(int gTime);

	int getFatigue();

	void setFatigue(int fatigue);

	void exhaust();

	void recover();

	int getScore();

	void setScore(int score);

/*
 * Implementing activities in the Game class for now, because it seems simpler to
 * directly update time, fatigue, and discovered locations from within the same class.
 */

	void explore();

	void sleep(Items & inv);

	void fish(Items & inv);

	void mine(Items & inv);

	void forage(Items & inv);

	void investigate(Items & inv);

	// Crafting Functions

	void craftTorch(Items & inv);

	void craftSpear(Items & inv);

	// Craft Ruby Necklace
	void craftRNecklace(Items & inv);

	// Craft Emerald Necklace
	void craftENecklace(Items & inv);

	// Craft Silver Neckalce
	void craftSNecklace(Items & inv);

	// Craft Gold Necklace
	void craftGNecklace(Items & inv);

	//void manage(Items & inv);

	void achievements(Items & inv);

};

#endif /* GAME_H_ */
