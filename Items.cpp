/*
 * Items.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: joe
 */

#include "Items.h"

Items::Items() {
	total = 0;

	kingFisher = 0;

	jeweler = 0;

	mineCount = 0;

	for(int i = 0; i < NITEMS; i++) {
		counts[i] = 0;
	}

	fTorch = 10;
	fSpear = 10;
	fRNeck = 10;
	fENeck = 10;
	fSNeck = 10;
	fGNeck = 10;
	craftAble = false;

	// Found at the cabin -- allow new player abilities
	pickaxe = false;
	pack = false;
	bedroll = false;
	//bool fishRod = false;

}

Items::~Items() {
	// TODO Auto-generated destructor stub
}

void Items::viewItems(Items & obj) {
	int n = 1;
	cout << "\n======================" << endl;
	if(obj.getTotal() == 0) {
		cout << "Inventory is Empty" << endl;
	}
	else {
		for(int i = 0; i < obj.NITEMS; i++) {
				if(obj.getCount(i) > 0) {
					cout << n << ". " << obj.names[i]  << ": " << obj.getCount(i) << endl;
					n++;
				}
			}
		if(obj.checkPack()) {
			cout << "Total Items: " << obj.getTotal() << "/" << obj.UMAX << endl;
		}
		else {
			cout << "Total Items: " << obj.getTotal() << "/" << obj.MAX << endl;
		}
	}
	cout << "======================" << endl;
}

void Items::printIMenu() {
	cout << "\n=======================" << endl;
	cout << "What do you want to do?" << endl;
	cout << "1. View inventory" << endl;
	cout << "2. Drop item(s)" << endl;
	cout << "3. Go back" << endl;
	cout << "> " << flush;
}

void Items::printCraftMenu() {
	int n = 1;
	int flag = 0;
	cout << "\n====================================" << endl;
	//cout << "What do you want to do?" << endl;
	if(counts[6] >= 1 && counts[9] >= 2 && counts[10] >= 1)
	{
		cout << n << ". Craft Torch" << endl;
		fTorch = n;
		n++;
		flag++;
		craftAble = true;
	}
	if(counts[5] >= 1 && counts[10] >= 1 && counts[11] >= 1)
	{
		cout << n << ". Craft Fishing Spear" << endl;
		fSpear = n;
		n++;
		flag++;
		craftAble = true;
	}
	if(counts[0] >= 1 && counts[1] >= 2 && counts[11] >= 1)
	{
		cout << n  << ". Craft Ruby Necklace" << endl;
		fRNeck = n;
		n++;
		flag++;
		craftAble = true;
	}
	if(counts[0] >= 1 && counts[2] >= 2 && counts[11] >= 1)
	{
		cout << n << ". Craft Emerald Necklace" << endl;
		fENeck = n;
		n++;
		flag++;
		craftAble = true;
	}
	if(counts[0] >= 2 && counts[3] >= 2 && counts[11] >= 1)
	{
		cout << n << ". Craft Silver Necklace" << endl;
		fSNeck = n;
		n++;
		flag++;
		craftAble = true;
	}
	if(counts[0] >= 2 && counts[4] >= 2 && counts[11] >= 1)
	{
		cout << n << ". Craft Gold Necklace" << endl;
		fGNeck = n;
		n++;
		flag++;
		craftAble = true;
	}
	if(flag != 0)
	{
		cout << "What would you like to craft?\n> " << flush;
	}
	else if(flag == 0)
	{
		cout << "Gather more materials to craft items" << endl;
		cout << "====================================" << endl;
		return;
	}
}

void Items::resetCFlags()
{
	fTorch = 10;
	fSpear = 10;
	fRNeck = 10;
	fENeck = 10;
	fSNeck = 10;
	fGNeck = 10;
	craftAble = false;
}

bool Items::checkCraft()
{
	return craftAble;
}

int Items::getFTorch()
{
	return fTorch;
}

int Items::getFSpear()
{
	return fSpear;
}

int Items::getFRNeck()
{
	return fRNeck;
}

int Items::getFENeck()
{
	return fENeck;
}

int Items::getFSNeck()
{
	return fSNeck;
}

int Items::getFGNeck()
{
	return fGNeck;
}

int Items::getTotal() {
	return total;
}

void Items::plusTotal(int x) {
	total += x;
}

void Items::minusTotal(int x) {
	total -= x;
}

// Need to test!!
void Items::updateTotal() {
	total = 0;
	for(int i = 0; i < NITEMS; i++) {
		total += counts[i];
	}
}

int Items::getCount(int index) {
	return counts[index];
}

void Items::plusCount(int index, int x) {
	counts[index] += x;
}

void Items::minusCount(int index, int x) {
	counts[index] -= x;
}

void Items::dropItem(char * pInp, char * pInp2) {
	for(int i = 0, n = 0; i < NITEMS; i++) {
		if(counts[i] > 0)
		{
			n++;
		}

		if(n == (int)pInp[0] - 48 && counts[i] >= ((int)pInp2[0] - 48))
		{
			minusCount(i,(pInp2[0]-48));
			//obj.minusTotal(1);
			updateTotal();
			cout << names[i] << " dropped" << endl;
			break;
		}
		else if(n == (int)pInp[0] - 48 && counts[i] < ((int)pInp2[0] - 48))
		{
			cout << "I'm not carrying that many of those..." << endl;
			break;
		}
		// In case player tries to drop an item they are not carrying
		if(i == NITEMS-1)
		{
			cout << "I'm not carrying any of those..." << endl;
		}
	}
}

void Items::cabinFind(int n) {
	if(n == 1) {
		pickaxe = true;
	}
	else if(n == 2) {
		pack = true;
	}
	else if(n == 3) {
		bedroll = true;
	}
}

bool Items::checkPack()  {
	return pack;
}

bool Items::checkAxe() {
	return pickaxe;
}

bool Items::checkRoll() {
	return bedroll;
}

void Items::plusFish() {
	kingFisher++;
}

int Items::checkFish() {
	return kingFisher;
}

void Items::plusJewelry()
{
	jeweler++;
}

int Items::checkJewelry()
{
	return jeweler;
}

void Items::mineCountup() {
	mineCount++;
}

int Items::getMineCount() {
	return mineCount;
}
