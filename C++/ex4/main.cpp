//****************************************************************************//
//============================================================================//
// Name        : hw3c++.cpp													  //
// Author      : Mosa Thoukwho 311590707									  //
// Description : Hocky game simulator										  //
//============================================================================//
//****************************************************************************//



#include "init.h"
int main(int argc, char **argv)
{
	init(argc, argv);
	return 0;
}

























/*
int main(int argc, char **argv)
{
	TreeNode<Player> *root = new TreeNode<Player>;
	//m_Tree<Player> *root = new m_Tree<Player>;
	CGPoints *a = new CGPoints(2, 3);
	std::vector<double> b = { 5, 6 };
	CGPoints *c = new CGPoints(7, 8);
	Player *p = new Player(*a, *c, b);
	CGPoints *aa = new CGPoints(20, 30);
	std::vector<double> bb = { 50, 60 };
	CGPoints *cc = new CGPoints(70, 80);
	Player *pp = new Player(*aa, *cc, bb);
	CGPoints *aaa = new CGPoints(1, 1);
	std::vector<double> bbb = { 2, 2 };
	CGPoints *ccc = new CGPoints(3, 3);
	Player *ppp = new Player(*aaa, *ccc, bbb);
	root->Insert(*p);
	root->Insert(*pp);
	root->Insert(*ppp);
	(root)->print();
	//BstNode<Player> *nodd = new BstNode<Player>(*pp, 2);
   // BstNode<Player> *nod= new BstNode<Player>(*p,1);
	//if (nod < nodd) {
		// *pp = nodd->getData();
	//}
	
	//(*root).Insert(p);

	//(*root).Insert(pp);

	//root->remove(*pp);
	//root->remove( *pp);
	return 0;
}
*/