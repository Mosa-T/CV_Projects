#ifndef _FIELD_
#define _FIELD_
#include <iostream>
#include <vector>
#include "CGPoints.h"
#include "Tree.h"
#include "Forwards.h"
#include "Defensemen.h"
#include "Goalie.h"
using namespace std;

class Field {
private:
	int lengthMax;
	int widthMax;
	int lengthMin;
	int widthMin;
	CGPoints targetPoint;
	TreeNode<Player *> *root;
	int playersOnField;
	int playerSettingCounter;
	CGPoints *globalBest;
	bool setFirstGlobal;
public:

	Field(const Field &a) {
		setFirstGlobal = a.setFirstGlobal;
		this->lengthMax = a.lengthMax;
		widthMax = a.widthMax;
		lengthMin = a.lengthMin;
		widthMin = a.widthMin;
		playerSettingCounter = a.playerSettingCounter;
		globalBest = new CGPoints();
		globalBest = a.globalBest;
		root = new TreeNode<Player *>();
		root = (a.root);
	}

	Field&operator=(const Field &a) {
		setFirstGlobal = a.setFirstGlobal;
		this->lengthMax = a.lengthMax;
		widthMax = a.widthMax;
		lengthMin = a.lengthMin;
		widthMin = a.widthMin;
		playerSettingCounter = a.playerSettingCounter;
		globalBest = new CGPoints();
		globalBest = a.globalBest;
		root = new TreeNode<Player *>();
		root = (a.root);
		return *this;
	}

	Field() {
		setFirstGlobal = false;
		this->lengthMax = 61;
		 widthMax = 30;
		lengthMin = 0;
		widthMin = 0;
		playerSettingCounter = 0;
		globalBest = new CGPoints(-100, -100);
		root = new TreeNode<Player *>;
	}
	Field(int a,int b,int c,int d,int e) {
		setFirstGlobal = false;
		this->lengthMax = a;
		widthMax = b;
		lengthMin = c;
		widthMin = d;
		playerSettingCounter = e;
		globalBest = new CGPoints(-100,-100);
		root = new TreeNode<Player *>;
	}

	Field(CGPoints givenTarget,int playerCount) { 
		setFirstGlobal = false;
		targetPoint = givenTarget;
		root = new TreeNode<Player *>;
		playersOnField = playerCount;
		lengthMax = 61;
		widthMax = 30;
		lengthMin = 0;
		widthMin = 0;
		playerSettingCounter = 0;
		globalBest = new CGPoints(-100, -100);
	}
	~Field() { 
		root->clear((root->getHead()));
		delete root;
		root = NULL;
		delete globalBest;
		globalBest = NULL;
	}
	
	
	
	//sets a player into a node as data
	void setPlayer(CGPoints posInput, vector<double> v,char type) {
		if (type == 'F') {
			Player *newT = (new Forwards(posInput, targetPoint, v, type, root->getId()));
			//Forwards *f = dynamic_cast<Forwards*>(newT);
			//f = dynamic_cast<Forwards*>(newT);
			root->Insert(newT);
		}else if (type == 'D') {
			Player *newT2 = (new Defensemen(posInput, targetPoint, v, type, root->getId()));
			//Defensemen *d = dynamic_cast<Defensemen*>(newT2);
			root->Insert(newT2);
		} else if (type == 'G') {
			Player *newT3 = (new Goalie(posInput, targetPoint, v, type, root->getId()));
			//Goalie *g = dynamic_cast<Goalie*>(newT3);
			root->Insert(newT3);
		}
	}


	void update(BstNode<Player *> *node) {

		if (node == NULL) return;

		if (*globalBest == targetPoint) return;

		if ((node)->getData()->getdistancePlayer() <= globalBest->distanceFrom(targetPoint)) {
			*globalBest = (node)->getData()->getPos();
		}

		update(((node)->getLeft())); //go left on the tree
		 
		if (*globalBest == targetPoint) return;
		
		(node)->getData()->update(globalBest, targetPoint); //update stats of current node

		//keeps positions in given field limits
		if (node->getData()->getPos().GetX() >= lengthMax) {
			node->getData()->setPosX((double)lengthMax);
		}
		if (node->getData()->getPos().GetX() <= lengthMin) {
			node->getData()->setPosX((double)lengthMin);
		}
		if (node->getData()->getPos().GetY() <= widthMin) {
			node->getData()->setPosY((double)widthMin);
		}
		if (node->getData()->getPos().GetY() >= widthMax) {
			node->getData()->setPosY((double)widthMax);
		}

		node->getData()->getDist().setDist(node->getData()->getPos(), targetPoint);

		if (node->getData()->getdistancePlayer() <= globalBest->distanceFrom(targetPoint)) {
			*globalBest = node->getData()->getPos();
		}

		update((((node)->getRight()))); //go right on the tree

		if (*globalBest == targetPoint) return;

	}

	//update position, speed and global best, calls the update function above to recursivly update every node's stats
	void updateStats() {
		BstNode<Player *> *node = (root->getHead());
		setFirstGlobalOnce(node);
		update(node);
	}

	CGPoints getGlobalBest() {
		return *globalBest;
	}

	//set the global best for the first iteration
	void setFirstGlobalOnce(BstNode<Player *> *node) {
		if (!node) return;
		if (!setFirstGlobal) {
			setFirstGlobalOnce(((node)->getLeft()));
			if ((node)->getData()->getdistancePlayer() < globalBest->distanceFrom(targetPoint)) {
				*globalBest = node->getData()->getPos();
			}
			setFirstGlobalOnce(((node)->getRight()));
		}
		setFirstGlobal = true;
	}

	void printAll() {
	 (root)->print();
	}

	TreeNode<Player *> *getRoot() {
		return root;
	}

	//search function, calls the BstNode search function to go through all nodes and find Player by it's implemented operator==
	BstNode<Player *>* searches(Player *value) {
		return root->search(value);
	}

	//find and remove a node and update the tree
	void remove(Player *p) {
		root->remove(p);
	}
	//clear all nodes, end up with an empty tree
	void clearTree() {
		root->clear((root->getHead()));
	}

};

#endif
