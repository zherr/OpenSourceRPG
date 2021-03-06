/*
 * TestInventory.cpp
 *
 *  Created on: May 14, 2013
 *      Author: zherr
 */

#include "TestInventory.hh"
#include "../Model/Item.hh"
#include "../Model/Inventory.hh"
#include <cppunit/extensions/HelperMacros.h>
#include <exception>
#include <list>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(TestInventory);

void TestInventory::setUp(){
	inv0 = Inventory();
	inv1 = Inventory(750);
	inv2 = new Inventory();
	inv3 = new Inventory(800);
	item0 = Item("sword", "a shiny sword", 50);
	item1 = new Item("shield", "a shiny shield", 50);
	item2 = Item("bread", "a loaf of bread", 15);
	heavy = Item("boulder", "a huge boulder", 800);
}

void TestInventory::tearDown(){
	delete inv2;
	delete inv3;
	//delete item1;
	cout << "Done with Inventory tearDown" << endl;
}

void TestInventory::testDefaults(){
	CPPUNIT_ASSERT(inv0.getWeight()==0);
	CPPUNIT_ASSERT(inv0.getCapacity()==500);
	//cout << "Inventory size = " << inv0.listInventory().size() << endl;
	CPPUNIT_ASSERT(inv0.listInventory().size() == 0);
}

void TestInventory::testPDefaults(){
	CPPUNIT_ASSERT(inv2->getWeight()==0);
	CPPUNIT_ASSERT(inv2->getCapacity()==500);
	//cout << "Inventory size = " << inv2->listInventory().size() << endl;
	CPPUNIT_ASSERT(inv2->listInventory().size() == 0);
}

void TestInventory::testFunctions(){
	CPPUNIT_ASSERT(inv1.getCapacity()==750);
	CPPUNIT_ASSERT(inv1.getWeight()==0);
	CPPUNIT_ASSERT(inv1.listInventory().size()==0);
	//
	inv1.addItem(item0);
	CPPUNIT_ASSERT(inv1.listInventory().size()==1);
	CPPUNIT_ASSERT(inv1.getWeight()==50);
	inv1.addItem(*item1);
	inv1.addItem(item2);
	CPPUNIT_ASSERT(inv1.listInventory().size()==3);
	CPPUNIT_ASSERT(inv1.getWeight()==115);
	inv1.removeItem(item0);
	CPPUNIT_ASSERT(inv1.listInventory().size()==2);
	CPPUNIT_ASSERT(inv1.getWeight()==65);
	CPPUNIT_ASSERT_THROW(inv1.addItem(heavy), OverCapacity*);
	CPPUNIT_ASSERT_THROW(inv1.removeItem(item0), ItemNotFound*);
	CPPUNIT_ASSERT(inv1.listInventory().size()==2);
	CPPUNIT_ASSERT(inv1.getWeight()==65);
	inv1.clearInventory();
	CPPUNIT_ASSERT(inv1.listInventory().size()==0);
	CPPUNIT_ASSERT(inv1.getWeight()==0);//TODO

	cout << ":::Before teardown:::" << endl;
	cout << "inv1 size: " << inv1.listInventory().size() << endl;
}

void TestInventory::testPFunctions(){
	CPPUNIT_ASSERT(inv3->getCapacity()==800);
	CPPUNIT_ASSERT(inv3->getWeight()==0);
	CPPUNIT_ASSERT(inv3->listInventory().size()==0);
	//
	inv3->addItem(item0);
	CPPUNIT_ASSERT(inv3->listInventory().size()==1);
	CPPUNIT_ASSERT(inv3->getWeight()==50);
	inv3->addItem(*item1);
	inv3->addItem(item2);
	CPPUNIT_ASSERT(inv3->listInventory().size()==3);
	CPPUNIT_ASSERT(inv3->getWeight()==115);
	inv3->removeItem(item0);
	CPPUNIT_ASSERT(inv3->listInventory().size()==2);
	CPPUNIT_ASSERT(inv3->getWeight()==65);
	CPPUNIT_ASSERT_THROW(inv3->addItem(heavy), OverCapacity*);
	CPPUNIT_ASSERT_THROW(inv3->removeItem(item0), ItemNotFound*);
	CPPUNIT_ASSERT(inv3->listInventory().size()==2);
	CPPUNIT_ASSERT(inv3->getWeight()==65);

	cout << ":::Before teardown:::" << endl;
	cout << "inv3 size: " << inv3->listInventory().size() << endl;
}
