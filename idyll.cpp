//============================================================================
// Name        : idyll.cpp
// Author      : Stephen
// Version     :
// Copyright   : Copyright Stephen Watson December 4th, 2017
// Description : A short, text-based console game where the player
//				 attempts to achieve the highest score possible by
//				 discovering locations and collecting or crafting
//				 in game items.
//============================================================================

/*
 * ToDo:
 * Add blank spaces to Intro so it is separated from the first printMenu
 * Add more activities
 * Add places to find
 * Add things to find
 * Add items to craft
 * Add eating functionality?
 * Added Update Total member function to Items.h to sum all items in counts[]
 * Add new achievements:
 * 		-
 * Add endGame function
 * For Crafting, output list of items the player STILL NEEDS to craft an item (do this after final
 * recipe balancing!)
 * Added functions to Items mineCountup() and getMineCount() for Ooh Shiny achievement
 * 	- tracks total number of items that player obtains from mining
 * Added: main game menu prints ONLY actions that are currently available (e.g. do not print
 * "fish" if player has not discovered the River) -- needs to be tested more
 * Reduced time taken for Fishing
 * Increased Pickaxe bonus
 * Increased chance to find bedroll
 * Rebalanced necklace recipes - may need additional tweaking
 *  - Emerald
 *  - Gold
 *  Revised updateTotal() member of Items to take no arguments
 *  Crafting menu now only outputs currently available recipes
 *  Drop multiple items easily via the Inventory Management menu
 *  Changed exhaustion criteria to 18 (from 16)
 *  Modified time and fatigue costs of Exploring
 * PICKUP: Test all Necklace crafting!
 * PICKUP: Test new fishing and foraging functions!
 *
 * */

/*README:
 *
 * This will eventually go in a 9th menu option to output Info.
 *  - Anytime you see a message like "this may come in handy," it means you have discovered or
 *    crafted an item that boosts your stats or gives bonuses to a certain activity
 *
 * */

#include <iostream>

#include "Game.h"
#include "Items.h"

using namespace std;

int main() {

	// Object Declarations

	Game admin; // This object can call administrative functions, like getInput
	Items inventory; // This object tracks and administrates player's Items

	// Variable Declarations

	char inp[Game::ISIZE] = {};
	char * pInp = inp;

	// Used for extra inputs, e.g. when player wants to drop items

	char inp2[Game::ISIZE] = {};
	char * pInp2 = inp2;

	int aSize; // Actual size of input

	bool validIn; // Record whether input is valid

	// Start game

	Game::printIntro();

	// Main game loop

	while(admin.getTime() < 168) {
		// Reset input flags
		admin.resetFlags();
		// check player fatigue status before each loop
		if(admin.getFatigue() <= 18) {
			admin.recover();
		}
		else if(admin.getFatigue() > 18) {
			admin.exhaust();
		}
		// Do the loopty loop

		admin.printMenu();
		pInp = admin.getInp(inp);
		aSize = admin.setSize(pInp);

		/*cout << "You entered " << aSize << " characters" << endl;
		cout << pInp << endl;*/

		validIn = admin.checkInp(pInp, aSize);

		if(validIn) {
			if((int)pInp[0] - 48 == 1)
			{
				admin.explore();
			}
			else if((int)pInp[0] - 48 == 2)
			{
				admin.sleep(inventory);
			}
			else if((int)pInp[0] - 48 == admin.getInpFish())
			{
				admin.fish(inventory);
			}
			else if((int)pInp[0] - 48 == admin.getInpMine())
			{
				admin.mine(inventory);
			}
			else if((int)pInp[0] - 48 == admin.getInpForage())
			{
				admin.forage(inventory);
			}
			else if((int)pInp[0] - 48 == admin.getInpInv())
			{
				admin.investigate(inventory);
			}
			// CRAFTING!
			else if((int)pInp[0] - 48 == admin.getInpCraft())
			{
				inventory.resetCFlags();
				inventory.printCraftMenu();
				if(inventory.checkCraft())
				{
					pInp = admin.getInp(inp);
									aSize = admin.setSize(pInp);
									validIn = admin.checkInp(pInp, aSize);
									if(validIn) {
										if((int)pInp[0] - 48 == inventory.getFTorch()) {
											admin.craftTorch(inventory);
										}
										else if((int)pInp[0] - 48 == inventory.getFSpear()) {
											admin.craftSpear(inventory);
										}
										else if((int)pInp[0] - 48 == inventory.getFRNeck()) {
											admin.craftRNecklace(inventory);
										}
										else if((int)pInp[0] - 48 == inventory.getFENeck()) {
											admin.craftENecklace(inventory);
										}
										else if((int)pInp[0] - 48 == inventory.getFSNeck()) {
											admin.craftSNecklace(inventory);
										}
										else if((int)pInp[0] - 48 == inventory.getFGNeck()) {
											admin.craftGNecklace(inventory);
										}
										else {
											cout << "I don't know how to make that" << endl;
										}
									}
									else {
										cout << "Invalid input" << endl;
									}
				}

			}
// Inventory Management Loop

			else if((int)pInp[0] - 48 == admin.getInpMan())
			{
				while(true) {

					inventory.printIMenu();
					pInp = admin.getInp(inp);
					aSize = admin.setSize(pInp);
					validIn = admin.checkInp(pInp, aSize);

					if(validIn) {
						if(pInp[0] == '1') {
							inventory.viewItems(inventory);
						}
						else if((int)pInp[0]-48 == 2) {
							if(inventory.getTotal() == 0) {
								inventory.viewItems(inventory);
								continue;
							}
							else {
								inventory.viewItems(inventory);
								cout << "What would you like to drop?\n> " << flush;
								pInp = admin.getInp(inp);
								aSize = admin.setSize(pInp);
								validIn = admin.checkInp(pInp, aSize);
								if(validIn)
								{
										cout << "How many would you like to drop?\n> " << flush;
										pInp2 = admin.getInp(inp2);
										aSize = admin.setSize(pInp2);
										validIn = admin.checkInp(pInp2, aSize);
										if(validIn)
										{
										inventory.dropItem(pInp,pInp2);
										}
										else
										{
											cout << "Invalid input" << endl;
										}
								}
								else
								{
									cout << "Invalid input" << endl;
									continue;
								}
							}
						}
						else if((int)pInp[0]-48 == 3) {
							break;
						}
						else {
							cout << "Invalid input" << endl;
							continue;
						}
					}
					else {
						cout << "Bad input" << endl;
					}
				}
			}

// End Inventory Management Loop

			else
			{
				cout << "Invalid selection" << endl;
			}
		}
		// ~~~End validIn check~~~
		else {
			cout << "Bad input" << endl;
		}

		admin.printStats(inventory);

		if(pInp[0]=='9') {
			break;
		}

	}

	// End game - print final stats and achievements

	cout << "Your time in Idyll is complete." << endl;

	// Achievements

	admin.achievements(inventory);
	admin.printStats(inventory);
	inventory.viewItems(inventory);

	return 0;
}
