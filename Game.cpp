/*
 * Game.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: joe
 */

#include "Game.h"

int Game::lCount = 0;
int Game::sCount = 0;

Game::Game() : gTime(0), fatigue(0), score(0) {

	// Set to 10, because input can never equal 10
	inpFish = 10;
	inpMine = 10;
	inpForage = 10;
	inpInvestigate = 10;
	inpCraft = 10;
	inpManage = 10;

	cave = false;
	river = false;
	vista = false;
	grove = false;
	cabin = false;
	fatigued = false;
	neverFatigued = true;
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::printIntro() {
	cout << "Finally, you're on your own in a vast expanse of nature." << endl;
	cout << "You're not just going to stand there, are you?" << endl;
	cout << "========================================================\n" << endl;
}

void Game::printMenu() {
	int n = 1;
	cout << "What do you want to do?" << endl;
	cout << n << ". Explore" << endl;
	n++;
	cout << n << ". Sleep" << endl;
	n++;
	if(river)
	{
		cout << n << ". Go fishing" << endl;
		inpFish = n;
		n++;
	}
	if(cave)
	{
		cout << n << ". Go mining" << endl;
		inpMine = n;
		n++;
	}
	if(vista || grove)
	{
		cout << n << ". Forage" << endl;
		inpForage = n;
		n++;
	}
	if(cabin)
	{
		cout << n << ". Investigate" << endl;
		inpInvestigate = n;
		n++;
	}
	cout << n << ". Craft Items" << endl;
	inpCraft = n;
	n++;
	cout << n << ". Manage Inventory" << endl;
	inpManage = n;
	cout << "Enter selection > " << flush;
}

void Game::printStats(Items & inv) {
	cout << "\n===========================================================" << endl;
	cout << "FATIGUE: " << fatigue << "\t\tTIME: " << gTime << "\t\tSCORE: " << score << endl;
	cout << "LOCATIONS DISCOVERED: " << lCount << endl;
	if(inv.checkPack()) {
		cout << "CURRENT INVENTORY TOTAL: " << inv.getTotal() << "/"
		<< inv.UMAX << endl;
	}
	else if(!inv.checkPack()) {
		cout << "CURRENT INVENTORY TOTAL: " << inv.getTotal() << "/"
		<< inv.MAX << endl;
	}
	cout << "===========================================================\n" << endl;
}

// Menu Flags and Management

void Game::resetFlags() {
	// Set to 10 because game structure does not allow player to input 10 as a value
	inpFish = 10;
	inpMine = 10;
	inpForage = 10;
	inpInvestigate = 10;
	inpCraft = 10;
	inpManage = 10;
}

int Game::getInpFish() {
	return inpFish;
}

int Game::getInpMine() {
	return inpMine;
}

int Game::getInpForage() {
	return inpForage;
}

int Game::getInpInv() {
	return inpInvestigate;
}

int Game::getInpCraft() {
	return inpCraft;
}

int Game::getInpMan() {
	return inpManage;
}

// User Input

char * Game::getInp(char * pInp) {
	cin.getline(pInp,ISIZE);
	if(cin.fail()) {
		cin.clear();
		cin.ignore(1000,'\n');
	}
		return pInp;
}

int Game::setSize(char * pInp) {
	int aSize = 0;
	for(int i = 0; i < ISIZE; i++) {
		if(pInp[i] == '\0') {
			aSize = i;
			break;
		}
	}
	return aSize;
}

bool Game::checkInp(char * pInp, int aSize) {
	for(int i = 0; i < aSize; i++) {
		if(pInp[i] > '0' && pInp[i] <= '9') {
			continue;
		}
		else if(i > 0 && pInp[i] == '0') {
			return true;
		}
		else {
			return false;
		}
	}
}

// Stats Management

int Game::getTime() {
	return gTime;
}

void Game::setTime(int gTime) {
	this->gTime=gTime;
}

int Game::getFatigue() {
	return fatigue;
}

void Game::setFatigue(int fatigue) {
	this->fatigue = fatigue;
}

void Game::exhaust() {
	fatigued = true;
	neverFatigued = false;
	cout << "\nGotta get some sleep..." << endl;
}

void Game::recover() {
	if(fatigued) {
		cout << "\nI feel well rested now" << endl;
	}
	fatigued = false;
}

int Game::getScore() {
	return score;
}

void Game::setScore(int score) {
	this->score = score;
}

/*
 * Implementing activities in the Game class for now, because it seems simpler to
 * directly update time, fatigue, and discovered locations from within the same class.
 */

void Game::explore() {
	srand(time(NULL));
	int x = 1+rand()%100;
	int n = 0;
	// Set time cost and fatigue cost higher if player is fatigued
	if(fatigued) {
		n = 2;
	}

	setTime(getTime()+2+n);
	setFatigue(getFatigue()+3+n);
	cout << "Explore result: " << x << endl;
	cout << "I went on a nice hike" << flush;
	if((x >= 1 && x <= 30) && !cave) {
		cave = true;
		lCount++;
		score++;
		cout << " and found a CAVE." << endl;
	}
	else if((x > 30 && x <= 55) && !river) {
		river = true;
		lCount++;
		score++;
		cout << " and found a RIVER." << endl;
	}
	else if((x > 55 && x <= 75) && !vista) {
		vista = true;
		lCount++;
		score++;
		cout << " and found a beautiful MOUNTAIN VISTA." << endl;
	}
	else if((x > 75 && x <= 90) && !cabin) {
		cabin = true;
		lCount++;
		score++;
		cout << " and found an ABANDONED CABIN." << endl;
	}
	else if((x > 90 && x <= 95) && !grove) {
		grove = true;
		lCount++;
		score+=2;
		cout << " and found a peaceful SECLUDED GROVE." << endl;
	}
	else {
		cout << "." << endl;
	}
}

void Game::sleep(Items & inv) {
	int n = 0;
	if(inv.checkRoll() == true) {
		n = 2;
	}

	if(getFatigue() == 0) {
		cout << "I couldn't fall asleep..." << endl;
		return;
	}
	else if(getFatigue() <= 6 + n) {
		cout << "Good night..." << endl;
		setFatigue(0);
		setTime(getTime() + 6);
		sCount++;
		return;
	}
	else {
		cout << "Good night..." << endl;
		setFatigue(getFatigue()-(6 + n));
		setTime(getTime() + 6);
		sCount++;
	}
}

void Game::fish(Items & inv) {

	if(river) {
		// Used to compare with total at end of function, if player does not catch anything
		int start = inv.getTotal();
		// Used to increase time/fatigue costs if player is fatigued
		int n = 0;
		if(fatigued) {
				n = 1;
			}

		setTime(getTime()+1+n);
		setFatigue(getFatigue()+2+n);

		int bonus = 0;
		if(inv.getCount(13) >= 1) {
			bonus = 20;
			cout << "My " << inv.names[13] << " will make fishing much easier! (Bonus:" << bonus << ")" << endl;
		}

		srand(time(NULL));
		int reeds = 1 + rand() % 100;
		int stone = 1 + rand() % 100;
		int catfish = 1 + rand() % 100;
		int trout = 1 + rand() % 100;

		cout << "\n            Fishing Results           " << endl;
		cout << "======================================" << endl;
		// REEDS
		if(((reeds >= 50) && (inv.getTotal() < inv.MAX && inv.checkPack()==false))
		|| ((reeds >= 50) && (inv.getTotal() < inv.UMAX && inv.checkPack() == true)))
		{
			cout << "I gathered some " << inv.names[6] << endl;
			inv.plusCount(6,1);
			//inv.plusTotal(1);
			inv.updateTotal();
/*
 * Code below checks whether the player has collected the Pack from the cabin,
 * as well as whether they have reached the limit of their inventory (determined
 * by whether or not they have the Pack). Potentially replaced by above logic in
 * if statement -- still needs testing!!
 *

			if(inv.checkPack()) {
				if(inv.getTotal() < inv.UMAX) {
					inv.plusCount(6,2);
					//inv.plusTotal(2);
					inv.updateTotal(inv);
				}
				else if(inv.getTotal() >= inv.UMAX) {
					cout << "My pack is full..." << endl;
				}
			}
			else if(!inv.checkPack()) {
				if(inv.getTotal() < inv.MAX) {
					inv.plusCount(6,1);
					inv.plusTotal(1);
				}
				else if(inv.getTotal() >= inv.MAX) {
					cout << "My pack is full..." << endl;
				}
			}
*/
		}
		else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
				(inv.getTotal() == inv.UMAX && inv.checkPack() == true))
		{
			cout << "I can't carry anything else right now." << endl;
			cout << "======================================" << endl;
			return;
		}
		// STONE
		if(((stone >= 50) && (inv.getTotal() < inv.MAX && inv.checkPack()==false))
		|| ((stone >= 50) && (inv.getTotal() < inv.UMAX && inv.checkPack() == true)))
		{
			cout << "I found a " << inv.names[5] << endl;
			inv.plusCount(5,1);
			//inv.plusTotal(1);
			inv.updateTotal();
		}
		else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
				(inv.getTotal() == inv.UMAX && inv.checkPack() == true))
		{
			cout << "I can't carry anything else right now." << endl;
			cout << "======================================" << endl;
			return;
		}
		// CATFISH
		if(((catfish + bonus >= 70) && (inv.getTotal() < inv.MAX && inv.checkPack()==false))
		|| ((catfish + bonus >= 70) && (inv.getTotal() < inv.UMAX && inv.checkPack() == true)))
		{
			cout << "I caught a " << inv.names[7] << "!" << endl;
			inv.plusCount(7,1);
			//inv.plusTotal(1);
			inv.plusFish();
			inv.updateTotal();
			score += 2;
		}
		else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
				(inv.getTotal() == inv.UMAX && inv.checkPack() == true))
		{
			cout << "I can't carry anything else right now." << endl;
			cout << "======================================" << endl;
			return;
		}
		// TROUT
		if(((trout + bonus >= 85) && (inv.getTotal() < inv.MAX && inv.checkPack()==false))
		|| ((trout + bonus >= 85) && (inv.getTotal() < inv.UMAX && inv.checkPack() == true))
		) {
			cout << "Wow! I caught a rare " << inv.names[8] << "!" << endl;
			inv.plusCount(8,1);
			//inv.plusTotal(1);
			inv.plusFish();
			inv.updateTotal();
			score+=16;
		}
		else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
				(inv.getTotal() == inv.UMAX && inv.checkPack() == true))
		{
			cout << "I can't carry anything else right now." << endl;
			cout << "======================================" << endl;
			return;
		}
		if(start != inv.getTotal()) {
			cout << "======================================" << endl;
		}
		else
		{
			cout << "No luck this time" << endl;
			cout << "======================================" << endl;
		}
	}
	else {
		cout << "I can go fishing if I find a river." << endl;
	}
}

void Game::mine(Items & inv) {
	if(cave) {
		// Checks if player found any items during mining and outputs unique message if not
		int start = inv.getTotal();
		int n = 0;
		if(fatigued) {
				n = 2;
			}
		setTime(getTime()+2+n);
		setFatigue(getFatigue()+4+n);

		srand(time(NULL));
		int clear, red, green, silver, gold, bonus = 0;
		if(inv.checkAxe()) {
			bonus += 10;
		}
		// Not sure about below "else" statement
		/*else {
			bonus = 0;
		}*/
		if(inv.getCount(12) >= 1) {
			bonus += 5;
		}
		cout << "BONUS: " << bonus << endl;
		clear = 1+rand()%100;
		red = 1+rand()%100;
		green = 1+rand()%100;
		silver = 1+rand()%100;
		gold = 1 + rand()%100;

		cout << "\n            Mining Results            " << endl;
		cout << "======================================" << endl;

		// Clear Gem
		if((clear + bonus > 35 && inv.getTotal() < inv.MAX && inv.checkPack() == false) ||
			(clear + bonus > 35 && inv.getTotal() < inv.UMAX && inv.checkPack() == true)) {
			inv.plusCount(0,1);
			//inv.plusTotal(1);
			inv.updateTotal();
			inv.mineCountup();
			cout << "I found a " << inv.names[0] << "!" << endl;
			}
			else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
				(inv.getTotal() == inv.UMAX && inv.checkPack() == true)) {
				cout << "I can't carry anything else right now." << endl;
				cout << "======================================" << endl;
				return;
			}

			// Red Gem
			if((red + bonus > 60 && inv.getTotal() < inv.MAX && inv.checkPack() == false) ||
				(red + bonus > 60 && inv.getTotal() < inv.UMAX && inv.checkPack() == true))
			{
				inv.plusCount(1,1);
				//inv.plusTotal(1);
				inv.updateTotal();
				inv.mineCountup();
				cout << "I found a " << inv.names[1] << "!" << endl;
			}
			else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
					(inv.getTotal() == inv.UMAX && inv.checkPack() == true)) {
				cout << "I can't carry anything else right now." << endl;
				cout << "======================================" << endl;
				return;
			}

			// Green Gem
			if((green + bonus > 75 && inv.getTotal() < inv.MAX && inv.checkPack() == false) ||
				(green + bonus > 75 && inv.getTotal() < inv.UMAX && inv.checkPack() == true)) {
				inv.plusCount(2,1);
				//inv.plusTotal(1);
				inv.updateTotal();
				inv.mineCountup();
				cout << "I found a " << inv.names[2] << "!" << endl;
				score += 2;
			}
			else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
					(inv.getTotal() == inv.UMAX && inv.checkPack() == true)) {
				cout << "I can't carry anything else right now." << endl;
				cout << "======================================" << endl;
				return;
			}

			// Silver
			if((silver + bonus > 80 && inv.getTotal() < inv.MAX && inv.checkPack() == false) ||
				(silver + bonus > 80 && inv.getTotal() < inv.UMAX && inv.checkPack() == true))
				{
					inv.plusCount(3,1);
					//inv.plusTotal(1);
					inv.updateTotal();
					inv.mineCountup();
					cout << "I found some " << inv.names[3] << "!" << endl;
					score += 2;
				}
				else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
						(inv.getTotal() == inv.UMAX && inv.checkPack() == true)) {
					cout << "I can't carry anything else right now." << endl;
					cout << "======================================" << endl;
					return;
				}

			// Gold
			if((gold + bonus >= 85 && inv.getTotal() < inv.MAX && inv.checkPack() == false) ||
				(gold + bonus >= 85 && inv.getTotal() < inv.UMAX && inv.checkPack() == true))
				{
					inv.plusCount(4,1);
					//inv.plusTotal(1);
					inv.updateTotal();
					inv.mineCountup();
					cout << "I found some " << inv.names[4] << "!" << endl;
					score += 6;
				}
				else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
						(inv.getTotal() == inv.UMAX && inv.checkPack() == true)) {
					cout << "I can't carry anything else right now." << endl;
					cout << "======================================" << endl;
					return;
				}
			// May be able to change below to start == inv.getTotal()
			if(start == inv.getTotal()) {
				cout << "No luck this time..." << endl;
			}

			cout << "======================================" << endl;
	}
	else {
		cout << "Maybe I can find a cave somewhere around here..." << endl;
	}
}

void Game::forage(Items & inv) {
	if(vista || grove) {
		int start = inv.getTotal();
		int n = 0;
		if(fatigued) {
			n = 1;
		}

		setTime(getTime()+1+n);
		setFatigue(getFatigue()+1+n);

		srand(time(NULL));
		int bark = 1 + rand() % 100;
		int stick = 1 + rand() % 100;
		int vine = 1 + rand() % 100;

		cout << "\n                Forage Results                " << endl;
		cout << "================================================" << endl;

		// BARK
		if(((bark >= 50) && (inv.getTotal() < inv.MAX && inv.checkPack()==false))
		|| ((bark >= 50) && (inv.getTotal() < inv.UMAX && inv.checkPack() == true)))
		{
			inv.plusCount(9,1);
			//inv.plusTotal(1);
			inv.updateTotal();
			cout << "I gathered some " << inv.names[9] << "." << endl;
		}
		else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
			(inv.getTotal() == inv.UMAX && inv.checkPack() == true))
		{
			cout << "I can't carry anything else right now." << endl;
			cout << "================================================" << endl;
			return;
		}

		// STICK
		if(((stick >= 50) && (inv.getTotal() < inv.MAX && inv.checkPack()==false))
		|| ((stick >= 50) && (inv.getTotal() < inv.UMAX && inv.checkPack() == true)))
		{
			inv.plusCount(10,1);
			//inv.plusTotal(1);
			inv.updateTotal();
			cout << "I gathered a " << inv.names[10] << "." << endl;
		}
		else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
			(inv.getTotal() == inv.UMAX && inv.checkPack() == true))
		{
			cout << "I can't carry anything else right now." << endl;
			cout << "================================================" << endl;
			return;
		}

		// VINE
		if(((vine >= 45) && (inv.getTotal() < inv.MAX && inv.checkPack()==false))
		|| ((vine >= 45) && (inv.getTotal() < inv.UMAX && inv.checkPack() == true)))
		{
			inv.plusCount(11,1);
			//inv.plusTotal(1);
			inv.updateTotal();
			cout << "I gathered some " << inv.names[11] << "." << endl;
		}
		else if((inv.getTotal() == inv.MAX && inv.checkPack() == false) ||
			(inv.getTotal() == inv.UMAX && inv.checkPack() == true))
		{
			cout << "I can't carry anything else right now." << endl;
			cout << "================================================" << endl;
			return;
		}
		if(start != inv.getTotal())
		{
			cout << "================================================" << endl;
		}
		else
		{
			cout << "I foraged about, but didn't find anything useful" << endl;
			cout << "================================================" << endl;
		}
	}
	else {
		cout << "I haven't found anywhere to forage in..." << endl;
	}
}

void Game::investigate(Items & inv) {
	if(cabin) {

		int n = 0;
		if(fatigued) {
			n = 1;
		}

		setTime(getTime()+1+n);
		setFatigue(getFatigue()+1+n);

		srand(time(NULL));
		int x = 1 + rand()%100;
		if(x <= 30 && inv.checkAxe() == false) {
			inv.cabinFind(1);
			cout << "I investigated the basement and found a pickaxe." << endl;
			cout << "This might come in handy somewhere..." << endl;
			if(inv.checkAxe() == true && inv.checkPack() == true && inv.checkRoll() == true) {
				cout << "There's nothing else useful in there." << endl;
			}
		}
		else if(x > 30 && x <=  60 && inv.checkPack() == false) {
			inv.cabinFind(2);
			cout << "I investigated the downstairs and found a backpack." << endl;
			cout << "This might be useful..." << endl;
			if(inv.checkAxe() == true && inv.checkPack() == true && inv.checkRoll() == true) {
				cout << "There's nothing else useful in there." << endl;
			}
		}
		else if(x > 60 && x <= 95 && inv.checkRoll() == false) {
			inv.cabinFind(3);
			cout << "I investigated the upstairs and found a bedroll." << endl;
			cout << "This should make sleeping more comfortable..." << endl;
			if(inv.checkAxe() == true && inv.checkPack() == true && inv.checkRoll() == true) {
				cout << "There's nothing else useful in there." << endl;
			}
		}
		else if(inv.checkAxe() == true && inv.checkPack() == true && inv.checkRoll() == true) {
			cout << "There's nothing else useful in there." << endl;
		}
		else {
			cout << "I'm sure there's useful items in here, but I didn't find any." << endl;
		}
	}
	else {
		cout << "I haven't found anywhere interesting to investigate." << endl;
	}
}

// Crafting Functions - Initally tried to put in invects class

void Game::craftTorch(Items & inv) {

	int n = 0;
	if(fatigued) {
		n = 1;
	}

	if(inv.getCount(6) >= 1 && inv.getCount(9) >= 2 && inv.getCount(10) >= 1) {

		setTime(getTime()+1+n);
		setFatigue(getFatigue()+1+n);

		inv.minusCount(6,1);
		inv.minusCount(9,2);
		inv.minusCount(10,1);

		inv.plusCount(12,1);
		inv.updateTotal();
		//inv.minusTotal(3);

		cout << inv.names[12] << " crafted! This should come in handy." << endl;
	}
	else {
		cout << "I need one " << inv.names[6] << ", two " << inv.names[9] << ", and one "
			<< inv.names[10] << " to make a " << inv.names[12] << endl;
	}
}

void Game::craftSpear(Items & inv) {

	int n = 0;
	if(fatigued) {
		n = 1;
	}

	if(inv.getCount(5) >= 1 && inv.getCount(10) >= 1 && inv.getCount(11) >= 1) {

		setTime(getTime()+1+n);
		setFatigue(getFatigue()+1+n);

		score += 4;

		inv.minusCount(5,1);
		inv.minusCount(10,1);
		inv.minusCount(11,1);

		inv.plusCount(13,1);
		inv.updateTotal();
		cout << inv.names[13] << " crafted!" << endl;
		//inv.minusTotal(2);
	}
	else {
		cout << "I need one " << inv.names[5] << ", one " << inv.names[10] << ", and one "
			<< inv.names[11] << " to make a " << inv.names[13] << endl;
	}
}

// Craft Ruby Necklace
void Game::craftRNecklace(Items & inv) {

	int n = 0;
	if(fatigued) {
		n = 1;
	}

	if(inv.getCount(0) >= 1 && inv.getCount(1) >= 2 && inv.getCount(11) >= 1) {

		setTime(getTime()+1+n);
		setFatigue(getFatigue()+1+n);

		score += 4;

		inv.minusCount(0,1);
		inv.minusCount(1,2);
		inv.minusCount(11,1);

		inv.plusCount(14,1);
		inv.updateTotal();
		cout << inv.names[14] << " crafted!" << endl;
		inv.plusJewelry();
	}
	else {
		cout << "I need one " << inv.names[0] << ", two " << inv.names[1] << "s, and one "
				<< inv.names[11] << " to make a " << inv.names[14] << endl;
	}
}

// Craft Emerald Necklace
void Game::craftENecklace(Items & inv) {
	int n = 0;
	if(fatigued) {
		n = 1;
	}

	if(inv.getCount(0) >= 1 && inv.getCount(2) >= 2 && inv.getCount(11) >= 1) {

		setTime(getTime()+1+n);
		setFatigue(getFatigue()+1+n);

		score += 8;

		inv.minusCount(0,1);
		inv.minusCount(2,2);
		inv.minusCount(11,1);

		inv.plusCount(15,1);

		inv.updateTotal();

		cout << inv.names[15] << " crafted!" << endl;
		inv.plusJewelry();
	}
	else {
		cout << "I need one " << inv.names[0] << ", two " << inv.names[2] << "s, and one "
				<< inv.names[11] << " to make a " << inv.names[15] << endl;
	}


}

// Craft Silver Necklace
void Game::craftSNecklace(Items & inv){
	int n = 0;
	if(fatigued) {
		n = 1;
	}

	if(inv.getCount(0) >= 2 && inv.getCount(3) >= 2 && inv.getCount(11) >= 1) {

		setTime(getTime()+1+n);
		setFatigue(getFatigue()+1+n);

		score += 8;

		inv.minusCount(0,2);
		inv.minusCount(3,2);
		inv.minusCount(11,1);

		inv.plusCount(16,1);

		inv.updateTotal();

		cout << inv.names[16] << " crafted!" << endl;
		inv.plusJewelry();
	}
	else {
		cout << "I need two " << inv.names[0] << "s, two " << inv.names[3] << ", and one "
				<< inv.names[11] << " to make a " << inv.names[16] << endl;
	}
}

// Craft Gold Necklace!
void Game::craftGNecklace(Items & inv) {
	int n = 0;
	if(fatigued) {
		n = 1;
	}

	if(inv.getCount(0) >= 2 && inv.getCount(4) >= 2 && inv.getCount(11) >= 1) {

		setTime(getTime()+1+n);
		setFatigue(getFatigue()+1+n);

		score += 16;

		inv.minusCount(0,2);
		inv.minusCount(4,2);
		inv.minusCount(11,1);

		inv.plusCount(17,1);

		inv.updateTotal();

		cout << inv.names[17] << " crafted!" << endl;
		inv.plusJewelry();
	}
	else {
		cout << "I need two " << inv.names[0] << "s, two " << inv.names[4] << ", and one "
				<< inv.names[11] << " to make a " << inv.names[17] << endl;
	}
}

void Game::achievements(Items & inv) {
	cout << "ACHIEVEMENTS: " << endl;
		if(Game::sCount == 0) {
			score++;
			cout << "\nMisguided Vigilance" << endl;
			cout << "- Finished the game without sleeping" << endl;
		}
		if(Game::lCount == 5) {
			score+=2;
			cout << "\nExplorer" << endl;
			cout << "- Discovered all locations" << endl;
		}
		if(inv.checkFish() >= 3) {
			score+=6;
			cout << "\nKing Fisher" << endl;
			cout << "- Caught 3 fish" << endl;
		}
		if(inv.getMineCount() >= 6) {
			score += 6;
			cout << "\nOoh, Shiny" << endl;
			cout << "- Collected 6 items from the cave" << endl;
		}
		if(inv.checkAxe() == true && inv.checkPack() == true && inv.checkRoll() == true) {
			score += 2;
			cout << "\nFinders Keepers" << endl;
			cout << "- Collected all items from the CABIN" << endl;
		}
		if(neverFatigued == true) {
			score += 5;
			cout << "\nHealthy, Wealthy, and Wise" << endl;
			cout << "- Completed the game without becoming fatigued" << endl;
		}
		if(inv.getCount(12) >= 1 && inv.getCount(13) >= 1) {
			score += 5;
			cout << "\nCrafty" << endl;
			cout << "- Crafted a " << inv.names[12] << " and a " << inv.names[13] << endl;
		}
		if(inv.checkJewelry() >= 3) {
			score += 8;
			cout <<"\nJeweler" << endl;
			cout <<"- Crafted  3 necklaces" << endl;
		}
}
