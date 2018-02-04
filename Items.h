/*
 * Items.h
 *
 *  Created on: Dec 10, 2017
 *      Author: joe
 */

#ifndef ITEMS_H_
#define ITEMS_H_

#include <iostream>
#include <string>

using namespace std;

class Items {
public:

	// Number of items in the game
	const static int NITEMS = 18;


private:

	// Crafting Flags
	int fTorch, fSpear, fRNeck, fENeck, fSNeck, fGNeck;
	bool craftAble;

	int mineCount;

	// Track how many fish the player has caught
	int kingFisher;

	// Track how many necklaces the player makes
	int jeweler;

	// Track how many items total the player has
	int total;

	// Array containing amounts of each item
	int counts[NITEMS];

	// Found at cave -- +2 score, +3 score, +5 score, +6 score, +7 score

	// Found at river -- catfish is Common, sturgeon is Rare

	// Found at the cabin -- allow new player abilities
	bool pickaxe;
	bool pack;
	bool bedroll;
	//bool fishRod;

	// Found anywhere while foraging

	// Crafted item

public:

	Items();
	virtual ~Items();

	// Inventory Management

	void viewItems(Items & obj);

	void printIMenu();

	// Crafting Menus, Flags, etc.

	void printCraftMenu();

	void resetCFlags();

	bool checkCraft();

	int getFTorch();

	int getFSpear();

	int getFRNeck();

	int getFENeck();

	int getFSNeck();

	int getFGNeck();

	// Maximum number of items that a player can hold
	const int MAX = 10;
	// Maximum number of items that a player can hold with a pack
	const int UMAX = 20;

	// Array containing names of each item
	const string names[NITEMS] = {"Clear Gem", "Red Gem", "Green Gem", "Silver", "Gold",
								  "Stone", "Reeds", "Catfish", "Trout",
								  "Bark", "Stick", "Vine",
								  "Torch", "Spear",
								  "Ruby Necklace", "Emerald Necklace", "Silver Necklace",
								  "Gold Necklace"};

	// Members

	int getTotal();

	void plusTotal(int x);

	void minusTotal(int x);

	void updateTotal();

	int getCount(int index);

	void plusCount(int index, int x);

	void minusCount(int index, int x);

	void dropItem(char * pInp, char * pInp2);

	// One member for all 3 cabin items

	void cabinFind(int n);

	// For inventory max limit check

	bool checkPack();

	// For checking if player has collected the pickaxe from the cabin

	bool checkAxe();

	// For sleep fatigue adjustment

	bool checkRoll();

	// For king fisher achievement

	void plusFish();

	int checkFish();

	void plusJewelry();

	int checkJewelry();

	void mineCountup();

	int getMineCount();

};

#endif /* ITEMS_H_ */
