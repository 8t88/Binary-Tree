/*
	Ben Clarke
	PIC 10C
	Professor DeSalvo


	This program implements a templated binary search tree that uses allows us to input different 
	data types and sorts them in a binary search tree. The header file "hw7.h" holds the code for the
	binary tree, and the header file "points.h" holds the code for the Point2D class
*/

#include<iostream>
#include<fstream>
#include<algorithm>
#include<functional>
#include<string>
#include"BinaryTree.h"
#include"Points.h"


int main(){

	BinarySearchTree<int> bst;	

	bst.insert(3); bst.insert(2); bst.insert(11);
	bst.insert(13);	bst.insert(5);	bst.insert(17);

	for(auto x:bst) std::cout<<x<<",";
	std::cout<<std::endl;

	BinarySearchTree<Point2D, PointOrderX> points_by_x;
	points_by_x.insert(Point2D(1,2));
	points_by_x.insert(Point2D(7,3));
	points_by_x.insert(Point2D(2,1));

	for(auto x: points_by_x) std::cout<<x<<",";
	std::cout<<std::endl;

	BinarySearchTree<Point2D, PointOrderY> points_by_y;
	points_by_y.insert(Point2D(1,2));
	points_by_y.insert(Point2D(7,3));
	points_by_y.insert(Point2D(2,1));

	for(auto x: points_by_y) std::cout<<x<<",";
	std::cout<<std::endl;

	BinarySearchTree<std::string, std::greater<std::string>> names;
	names.insert("Luke");
	names.insert("Kanye");
	names.insert("Pentatonix");

	for(auto x:names) std::cout<<x<<",";


	std::cout<<std::endl;


	system("pause");
	return 0;
}
