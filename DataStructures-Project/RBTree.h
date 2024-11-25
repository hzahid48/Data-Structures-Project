#pragma once
#include <iostream>
#include <fstream>
#include "queue.h"
#include <string>
#include <stdio.h>
//#include <bits/stdc++.h>
//#include <boost/algorithm/string/erase.hpp>
template<class T>
class RBNode
{
public:
	T data;
	string path;
	int color = 0; //0==red 1==black
	RBNode<T>* RBNode_left;
	RBNode<T>* RBNode_right;
	RBNode<T>* RBNode_parent;
	SLinkedList<string> list;
	string d = "D:";
	string p = "P:";
	string r = "R:";
	string l = "L:";
	string c = "C:";
	string L = "T:";
	string end = "End ";
	string space = " ";
	/*RBNode()
	{
		data = 0;
		color = 0;
		RBNode_left = NULL;
		RBNode_right = NULL;
		RBNode_parent = NULL;
	}*/

	RBNode(T d, string p)
	{
		data = d;
		path = p;
		color = 1;
		RBNode_left = NULL;
		RBNode_right = NULL;
		RBNode_parent = NULL;
	}

	RBNode(T d, string p, bool c)
	{
		data = d;
		path = p;
		color = c;
		RBNode_left = NULL;
		RBNode_right = NULL;
		RBNode_parent = NULL;
	}

	void insertlist(RBNode<T>* n, string id, string path) {
		//n->list->insert(n->line);
		n->list.insert(id, path);
	}
};

template<class T>
class RBTree {
private:
	RBNode<T>* root;
	bool duplicate = false;

public:
	RBTree() {
		root = NULL;
	}

	void LL(RBNode<T>*& tree, RBNode<T>*& node) {

		RBNode<T>* right = node->RBNode_right;
		node->RBNode_right = right->RBNode_left;

		if (node->RBNode_right != NULL) {
			node->RBNode_right->RBNode_parent = node;
		}

		right->RBNode_parent = node->RBNode_parent;

		if (node->RBNode_parent == NULL) {
			tree = right;
		}

		else if (node == node->RBNode_parent->RBNode_left) {
			node->RBNode_parent->RBNode_left = right;
		}

		else {
			node->RBNode_parent->RBNode_right = right;
		}

		right->RBNode_left = node;
		node->RBNode_parent = right;
	}

	void RR(RBNode<T>*& tree, RBNode<T>*& node) {

		RBNode<T>* left = node->RBNode_left;
		node->RBNode_left = left->RBNode_right;

		if (node->RBNode_left != NULL) {
			node->RBNode_left->RBNode_parent = node;
		}

		left->RBNode_parent = node->RBNode_parent;

		if (node->RBNode_parent == NULL) {
			tree = left;
		}

		else if (node == node->RBNode_parent->RBNode_left) {
			node->RBNode_parent->RBNode_left = left;
		}

		else {
			node->RBNode_parent->RBNode_right = left;
		}

		left->RBNode_right = node;
		node->RBNode_parent = left;
	}

	int temp_color;

	void fixviolation(RBNode<T>*& tree, RBNode<T>*& node)       //fixing colours and rotations while inserting
	{

		RBNode<T>* parent = NULL;
		RBNode<T>* grandparent = NULL;

		while ((node != tree) && (node->color != 0) && (node->RBNode_parent->color == 1))
		{
			parent = node->RBNode_parent;
			grandparent = node->RBNode_parent->RBNode_parent;

			//left subtree mein insertion 
			// Case : A
			// Parent is a  left child

			if (parent == grandparent->RBNode_left) {

				RBNode<T>* uncle = grandparent->RBNode_right;

				//Case : Uncle is red, just recolour the parent, grandparent and uncle

				if (uncle != NULL && uncle->color == 1) {
					grandparent->color = 1;
					parent->color = 0;
					uncle->color = 0;
					node = grandparent;
				}

				//Case : Uncle is black
				else
				{
					//Case : right child  (left ke right)
					// left rotation on parent
					// case triangle 

					if (node == parent->RBNode_right)
					{
						LL(tree, parent);
						node = parent;
						parent = node->RBNode_parent;
					}

					//Case : left child  (left ke left)
					//right rotation on grandparent 
					//recolour grandparent and parent
					//case line 

					RR(tree, grandparent);
					temp_color = parent->color;
					parent->color = grandparent->color;
					grandparent->color = temp_color;
					node = parent;
				}
			}

			//right subtree mein insertion
			// Case : B
			// Parent is a right child

			else
			{
				RBNode<T>* uncle = grandparent->RBNode_left;

				//Case : Uncle is red, recolour uncle, parent and grandparent

				if (uncle != NULL && uncle->color == 1) {
					grandparent->color = 1;
					parent->color = 0;
					uncle->color = 0;
					node = grandparent;
				}

				else
				{
					// Case : left child of right  
					// right rotation on parent 
					// case triangle 

					if (node == parent->RBNode_left)
					{
						RR(tree, parent);
						node = parent;
						parent = node->RBNode_parent;
					}

					//Case : right child of right
					//left rotation on grandparent
					// case line

					LL(tree, grandparent);
					temp_color = parent->color;
					parent->color = grandparent->color;
					grandparent->color = temp_color;
					node = parent;
				}
			}
		}

		tree->color = 0;
	}

	//void insert(T d)
	//{
	//	RBNode<T>* newNode = new RBNode<T>(d);
	//	newNode->RBNode_left = NULL;
	//	newNode->RBNode_right = NULL;

	//	RBNode<T>* temp = root;

	//	if (temp == NULL)
	//	{
	//		root = newNode;
	//	}
	//	else
	//	{
	//		while (temp != NULL)
	//		{
	//			if (d < temp->data)
	//			{
	//				if (temp->RBNode_left == NULL)
	//				{
	//					temp->RBNode_left = newNode;
	//					break;
	//				}
	//				else
	//				{
	//					temp = temp->RBNode_left;
	//				}
	//			}
	//			else if (d >= temp->data)
	//			{
	//				if (temp->RBNode_right == NULL)
	//				{
	//					temp->RBNode_right = newNode;
	//					break;
	//				}
	//				else
	//				{
	//					temp = temp->RBNode_right;
	//				}
	//			}
	//			else
	//			{
	//				break;
	//			}
	//		}
	//	}
	//	
	//	//root = insert(d);
	//	fixviolation(root, newNode);
	//}

	RBNode<T>* insert(RBNode<T>* tree, RBNode<T>* node, string id, string p)
	{

		if (tree == NULL)
			return node;

		if (node->data < tree->data)
		{
			tree->RBNode_left = insert(tree->RBNode_left, node, id, p);
			tree->RBNode_left->RBNode_parent = tree;
		}
		else if (node->data > tree->data)
		{
			tree->RBNode_right = insert(tree->RBNode_right, node, id, p);
			tree->RBNode_right->RBNode_parent = tree;
		}
		else {
			tree->insertlist(tree, id, p);
			duplicate = true;
			return tree;
		}

		return tree;
	}



	RBNode<T>* insert2(RBNode<T>* tree, RBNode<T>* node)
	{

		if (tree == NULL)
			return node;

		if (node->data < tree->data)
		{
			tree->RBNode_left = insert2(tree->RBNode_left, node);
			tree->RBNode_left->RBNode_parent = tree;
		}
		else if (node->data > tree->data)
		{
			tree->RBNode_right = insert2(tree->RBNode_right, node);
			tree->RBNode_right->RBNode_parent = tree;
		}
		/*else {
			tree->insertlist(tree, id, p);
			duplicate = true;
			return tree;
		}*/

		return tree;
	}


	void RBinsert2(RBNode<T>* p)
	{
		RBNode<T>* pt = p;
		root = insert2(root, pt);

		//if (duplicate == false)
		//	fixviolation(root, pt);

		//writefile(root, file);
		//duplicate = false;

	}

	void RBinsert(T d, RBNode<T>* p, fstream& file, string id, string pa)
	{
		RBNode<T>* pt = new RBNode<T>(d, pa);
		root = insert(root, pt, id, pa);

		if (duplicate == false)
			fixviolation(root, pt);

		writefile(root, file);
		duplicate = false;

	}

	void writefile(RBNode<T>* p, fstream& file) {
		//file.open(filename);
		Queue<RBNode<T>*> q;
		if (p == NULL) {
			return;
		}

		q.enqueue(p);

		while (!q.isEmpty()) {
			RBNode<T>* temp = q.Front();
			SLinkedList<string> tem = temp->list;

			file << temp->d << temp->data << endl;
			file << temp->p << temp->path << endl;
			while (tem.head != NULL) {
				file << temp->L;
				file << tem.head->data << ",";
				file << tem.head->path;
				file << temp->space << endl;
				tem.head = tem.head->next;
			}

			cout << endl;
			file << temp->c << temp->color << endl;
			q.dequeue();
			if (temp->RBNode_left != NULL) {
				file << temp->l << temp->RBNode_left->data << endl;
				q.enqueue(temp->RBNode_left);
			}

			if (temp->RBNode_right != NULL) {
				file << temp->r << temp->RBNode_right->data << endl;
				q.enqueue(temp->RBNode_right);
			}

			file << temp->end << endl;

		}
	}

	void levelorder(RBNode<T>* p) {
		Queue<RBNode<T>*> q;

		if (p == NULL) {
			return;
		}

		q.enqueue(p);

		while (!q.isEmpty()) {
			RBNode<T>* temp = q.Front();

			cout << temp->data << " " << temp->path << " ";
			q.dequeue();
			if (temp->RBNode_left != NULL) {
				q.enqueue(temp->RBNode_left);
			}

			if (temp->RBNode_right != NULL) {
				q.enqueue(temp->RBNode_right);
			}
		}
	}

	RBNode<T>* MinNode(RBNode<T>* node)
	{
		while (node->RBNode_left != NULL)
		{
			node = node->RBNode_left;
		}
		return node;
	}

	void fixDelete(RBNode<T>* x)
	{
		RBNode<T>* w;    //sibling of x

		if (x == NULL)
			return;
		while (x != root && x->color == 0 && x != NULL)     //only when the node is black
		{
			if (x == NULL)
				break;
			if (x == x->RBNode_parent->RBNode_left)
			{
				w = x->RBNode_parent->RBNode_right;

				// Case : W is red
				if (w->color == 1)
				{
					w->color = 0;     //changed the color to black
					x->RBNode_parent->color = 1;
					//rotating the parent
					LL(root, x->RBNode_parent);
					w = x->RBNode_parent->RBNode_right;
				}

				//Case : both children of W are black

				if (w->RBNode_left->color == 0 && w->RBNode_right->color == 0)
				{
					w->color = 1;                 //changed the color to red
					x = x->RBNode_parent;
				}
				else
				{
					//Case : right child of W is black
					if (w->RBNode_right->color == 0)
					{
						w->RBNode_left->color = 0;
						w->color = 1;
						RR(root, w);        //right rotation on w
						w = x->RBNode_parent->RBNode_right;      //reset w as x ka sibling
					}

					//Case : 
					w->color = x->RBNode_parent->color;
					x->RBNode_parent->color = 0;
					w->RBNode_right->color = 0;
					LL(root, x->RBNode_parent);      //left rotation on parent
					x = root;           //set x as tree's root
				}

			}
			if (x == NULL)
				break;

		}
		x->color = 0;           //set colour of x to black
	}


	void transplant(RBNode<T>* tree, RBNode<T>* node)   //helps move subtrees within the tree
	{
		if (tree->RBNode_parent == NULL)    //root
		{
			root = node;
		}

		else if (tree == tree->RBNode_parent->RBNode_left)       //left child
		{
			tree->RBNode_parent->RBNode_left = node;
		}
		else    //right child
		{
			tree->RBNode_parent->RBNode_right = node;
		}

		if (node != NULL)
			node->RBNode_parent = tree->RBNode_parent;
	}

	void deleteNodeHelper(RBNode<T>* node, T d)
	{
		// find the node containing key
		RBNode<T>* temp = NULL;
		RBNode<T>* a;
		RBNode<T>* b;

		while (node != NULL)
		{
			if (node->data == d)
			{
				temp = node;
			}

			if (node->data <= d)
			{
				node = node->RBNode_right;
			}
			else
			{
				node = node->RBNode_left;
			}
		}

		if (temp == NULL)
		{
			return;
		}

		b = temp;
		int original_color = b->color;

		//Case : left child is NIL
		//has only right child
		//right child parent ka child ban jaye ga

		if (temp->RBNode_left == NULL)
		{
			a = temp->RBNode_right;
			transplant(temp, temp->RBNode_right);
		}

		//Case : right child is NIL
		//has only left child
		//left  child parent ka child ban jaye ga

		else if (temp->RBNode_right == NULL)
		{
			a = temp->RBNode_left;
			transplant(temp, temp->RBNode_left);
		}

		//Case : has both children
		else
		{
			//finds min in the right subtree
			b = MinNode(temp->RBNode_right);
			original_color = b->color;
			a = b->RBNode_right;
			if (b->RBNode_parent == temp)
			{
				a->RBNode_parent = b;
			}
			else
			{
				transplant(b, b->RBNode_right);
				b->RBNode_right = temp->RBNode_right;
				b->RBNode_right->RBNode_parent = b;
			}

			transplant(temp, b);
			b->RBNode_left = temp->RBNode_left;
			b->RBNode_left->RBNode_parent = b;
			b->color = temp->color;
		}

		delete temp;
		if (original_color == 0)
		{
			//if(a->data!=NULL)
			fixDelete(a);
		}
	}

	void deleteNode(T data)
	{
		deleteNodeHelper(this->root, data);
	}

	RBNode<T>* getroot()
	{
		return root;
	}

	RBTree<T> ReadTree(RBTree<T> tree, fstream& file) {

		string line;
		T data;
		bool colour = 0;
		string path;
		string list_id;
		string list_path;
		string path_list;
		string id_list;
		int j;
		int counter = 0;
		RBNode<T>* temp = new RBNode<T>(data, path, colour);

		cout << "Run readtree func\n";
		while (!file.eof()) {

			j = 0;
			getline(file, line, '\n');
			//cout << "line\n"<<line;
			if (line[0] == 'D') {
				//cout << "Run readtree func\n";
				data = line;
				for (j = 0; data[j + 2] != '\0'; j++) {
					data[j] = data[j + 2];
				}
				data[j] = data[j + 1] = '\0';
				cout << "DATA:" << data << endl;

				counter++;
			}

			if (line[0] == 'P') {
				path = line;
				//path[i]=path[i + 1] = '\0';
				for (j = 0; path[j + 2] != '\0'; j++) {
					path[j] = path[j + 2];
				}
				//line[0] = line[1] = '\0';
				//cout << "PATH:" << path << endl;
				counter++;
			}

			if (line[0] == 'C') {
				if (line[2] == '1')
					colour = 1;
				else
					colour = 0;
				//cout << "COLOUR:" << colour << endl;
				counter++;
			}


			if (line[0] == 'L') {

			}

			if (line[0] == 'R') {

			}

			if (line[0] == 'T') {
				list_id = line;
				list_path = line;
				list_id[0] = list_id[1] = '\0';
				list_path[0] = list_path[1] = '\0';
				for (j = 2; line[j] != ',' && line[j] != '\0'; j++) {
					/*list_id[j - 2] = line[j];
					cout << "line: " << line[j]<<endl;
					cout << "list j: " << list_id[j - 2] << endl;*/
					list_path[j] = '\0';
				}

				list_path[j] = '\0';
				for (; line[j] != '\0'; j++) {
					list_id[j] = '\0';
				}

				for (int i = 2; list_id[i] != '\0'; i++) {
					list_id[i - 2] = list_id[i];
					list_id[i] = '\0';
				}

				for (int i = 4; list_path[i] != '\0'; i++) {
					list_path[i - 4] = list_path[i];
					list_path[i] = '\0';
				}

				temp->insertlist(temp, list_id, list_path);
				//cout << "id" << list_id << endl;
				//cout << "path:" << list_path << endl;
			}

			if (counter == 3) {
				if (temp->list.head != NULL)
					temp->list.print();
				temp = new RBNode<T>(data, path, colour);
				counter = 0;
				tree.RBinsert2(temp);
			}

		}

		cout << "TREE:";
		tree.levelorder(tree.getroot());

		return tree;
	}

	void selectQueryState(RBTree<T> tree, T key)
	{
		ofstream search;
		search.open("Search_Query.csv", ios::trunc);
		search.close();
		search.open("Search_Query.csv", ios::app);
		
		search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;

			

			

			
			while (!file.eof())
			{

				num--;
				getline(file, id, ',');
				getline(file, year, ',');
				getline(file, cause1a, ',');

				getline(file, cause2, ',');
				getline(file, state, ',');
				getline(file, deaths, ',');
				getline(file, rate, '\n');

				if (key == state)
				{
					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//string cause1 = cause1a + "," + cause1b;
					search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

				}
			}
		}
	}

	void selectQueryID(RBTree<T> tree, T key) {

		ofstream search;
		search.open("Search_Query.csv", ios::trunc);
		search.close();
		search.open("Search_Query.csv", ios::app);


		search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";
		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{

				num--;
				getline(file, id, ',');
				getline(file, year, ',');
				getline(file, cause1a, ',');
				//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
				//{
				//	getline(inFile, cause1b, ',');
				//	cause1b = " ";
				//}
				//else
				//{
				//	getline(file, cause1b, ',');
				//}

				getline(file, cause2, ',');
				//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
				//f_cause = cause1a + cause1b + cause2;
				getline(file, state, ',');
				getline(file, deaths, ',');
				getline(file, rate, '\n');
				//cout << state << " ";
				if (key == id)
				{
					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//string cause1 = cause1a + "," + cause1b;

					search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
			}
		}
	}

	void selectQueryYear(RBTree<T> tree, T key) {

		ofstream search;
		search.open("Search_Query.csv", ios::trunc);
		search.close();
		search.open("Search_Query.csv", ios::app);

		search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);



			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{

				num--;
				getline(file, id, ',');
				getline(file, year, ',');
				getline(file, cause1a, ',');
				//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
				//{
				//	//getline(inFile, cause1b, ',');
				//	cause1b = " ";
				//}
				//else
				//{
				//	getline(file, cause1b, ',');
				//}

				getline(file, cause2, ',');
				//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
				//f_cause = cause1a + cause1b + cause2;
				getline(file, state, ',');
				getline(file, deaths, ',');
				getline(file, rate, '\n');
				//cout << state << " ";
				if (key == year)
				{
					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//string cause1 = cause1a + "," + cause1b;

					search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
			}
		}
	}

	void selectQueryRate(RBTree<T> tree, T key) 
	{
		ofstream search;
		search.open("Search_Query.csv", ios::trunc);
		search.close();
		search.open("Search_Query.csv", ios::app);

		search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);
			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{

				num--;
				getline(file, id, ',');
				getline(file, year, ',');
				getline(file, cause1a, ',');
				//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
				//{
				//	//getline(inFile, cause1b, ',');
				//	cause1b = " ";
				//}
				//else
				//{
				//	getline(file, cause1b, ',');
				//}

				getline(file, cause2, ',');
				//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
				//f_cause = cause1a + cause1b + cause2;
				getline(file, state, ',');
				getline(file, deaths, ',');
				getline(file, rate, '\n');
				//cout << state << " ";
				if (key == rate)
				{
					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//string cause1 = cause1a + "," + cause1b;

					search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
			}
		}
	}

	void selectQueryCause(RBTree<T> tree, T key)
	{

		ofstream search;
		search.open("Search_Query.csv", ios::trunc);
		search.close();
		search.open("Search_Query.csv", ios::app);

		search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{

				num--;
				getline(file, id, ',');
				getline(file, year, ',');
				getline(file, cause1a, ',');
				//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
				//{
				//	//getline(inFile, cause1b, ',');
				//	cause1b = " ";
				//}
				//else
				//{
				//	getline(file, cause1b, ',');
				//}

				getline(file, cause2, ',');
				//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
				//f_cause = cause1a + cause1b + cause2;
				getline(file, state, ',');
				getline(file, deaths, ',');
				getline(file, rate, '\n');
				//cout << state << " ";
				string cause1 = cause1a + "," + cause1b;
				if (key == cause2 || key == cause1a)
				{
					search << "ID,Year,Cause1,Cause2,State,Deaths, Rate,\n";
					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//string cause1 = cause1a + "," + cause1b;

					search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

				}
			}
		}
	}

	void selectQueryDeath(RBTree<T> tree, T key) {

		ofstream search;
		search.open("Search_Query.csv", ios::trunc);
		search.close();
		search.open("Search_Query.csv", ios::app);

		search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{

				num--;
				getline(file, id, ',');
				getline(file, year, ',');
				getline(file, cause1a, ',');
				//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
				//{
				//	//getline(inFile, cause1b, ',');
				//	cause1b = " ";
				//}
				//else
				//{
				//	getline(file, cause1b, ',');
				//}

				getline(file, cause2, ',');
				//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
				//f_cause = cause1a + cause1b + cause2;
				getline(file, state, ',');
				getline(file, deaths, ',');
				getline(file, rate, '\n');
				//cout << state << " ";
				if (key == deaths)
				{
					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//string cause1 = cause1a + "," + cause1b;

					search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
			}
		}
	}

	void rangeQueryID(RBTree<T> tree, string start, string end)
	{
		ofstream range;
		range.open("Range_Query.csv", ios::trunc);
		range.close();
		range.open("Range_Query.csv", ios::app);

		range << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		//RBNode<T>* temp = search(tree, start);

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);
			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			bool heading = true;

			int st = stoi(start);
			int en = stoi(end);
			int idint = 0;

			while (!file.eof())
			{
				getline(file, id, ',');
				if (id == "")
					break;
				getline(file, year, ',');
				getline(file, cause1a, ',');
				getline(file, cause2, ',');
				getline(file, state, ',');
				getline(file, deaths, ',');
				getline(file, rate, '\n');

				if (heading == false) {
					//cout << "string ID: " << id;
					idint = stoi(id);
					//cout << "int id: " << idint << endl;
				}

				if (idint >= st && idint <= en && heading == false)
				{
					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					range << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}

				heading = false;
				//st++;
			}
		}
	}

		void rangeQueryYEAR(RBTree<T> tree, string start, string end)
		{
			ofstream range;
			range.open("Range_Query.csv", ios::trunc);
			range.close();
			range.open("Range_Query.csv", ios::app);

			range << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

			for (int filenum = 0; filenum < 2; filenum++)
			{
				//string address = searchpath(tree.getroot(), key);               //path for excel
				ifstream file;

				string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
				path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
				path += ".csv";

				//cout << "PATH: " << address << endl;
				file.open(path);

				if (file.is_open())
					cout << "opened" << endl;
				string id;
				string year;
				string state;
				string cause1a;
				string cause1b;
				string cause2;
				string deaths;
				string rate;
				bool heading = true;

				int st = stoi(start);
				int en = stoi(end);
				int yearint = 0;

				while (!file.eof())
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');

					if (heading == false) {
						//cout << "string ID: " << id;
						yearint = stoi(year);
						//cout << "int id: " << idint << endl;
					}

					if (yearint >= st && yearint <= en && heading == false)
					{
						cout << "ID: " << id << " ";
						cout << "year: " << year << " ";
						cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
						cout << "state: " << state << " ";
						cout << "deaths: " << deaths << " ";
						cout << "rate: " << rate << endl;

						range << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
					}

					heading = false;
					//st++;
				}
			}
		}

	void rangeQueryDEATHS(RBTree<T> tree, string start, string end)
	{
		ofstream range;
		range.open("Range_Query.csv", ios::trunc);
		range.close();
		range.open("Range_Query.csv", ios::app);

		range << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);
			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			bool heading = true;

			int st = stoi(start);
			int en = stoi(end);
			int deathsint = 0;

			while (!file.eof())
			{
				getline(file, id, ',');
				getline(file, year, ',');
				getline(file, cause1a, ',');
				getline(file, cause2, ',');
				getline(file, state, ',');
				getline(file, deaths, ',');
				getline(file, rate, '\n');

				if (heading == false) {
					//cout << "string ID: " << id;
					deathsint = stoi(deaths);
					//cout << "int id: " << idint << endl;
				}

				if (deathsint >= st && deathsint <= en && heading == false)
				{
					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					range << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}

				heading = false;
				//st++;
			}
		}
	}

	void rangeQueryRATE(RBTree<T> tree, string start, string end)
	{
		ofstream range;
		range.open("Range_Query.csv", ios::trunc);
		range.close();
		range.open("Range_Query.csv", ios::app);

		range << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			bool heading = true;

			float st = stof(start);
			float en = stof(end);
			float rateint = 0;

			while (!file.eof())
			{
				getline(file, id, ',');
				getline(file, year, ',');
				getline(file, cause1a, ',');
				getline(file, cause2, ',');
				getline(file, state, ',');
				getline(file, deaths, ',');
				getline(file, rate, '\n');
				if (rate == "")
					break;

				if (heading == false) {
					//cout << "string ID: " << id;
					rateint = stof(rate);
					//cout << "int id: " << idint << endl;
				}

				if (rateint >= st && rateint <= en && heading == false)
				{
					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					range << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}

				heading = false;
				//st++;
			}
		}
	}

	void deleteQueryID(RBTree<T> tree, T key)
	{
		ofstream del;
		del.open("Delete_Query.csv", ios::trunc);
		del.close();
		del.open("Delete_Query.csv", ios::app);

		del << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);
			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
					//{
					//	//getline(inFile, cause1b, ',');
					//	cause1b = " ";
					//}
					//else
					//{
					//	getline(file, cause1b, ',');
					//}

					getline(file, cause2, ',');
					//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
					//f_cause = cause1a + cause1b + cause2;
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
					//cout << state << " ";
					if (id == key)
					{
						getline(file, id, ',');
						getline(file, year, ',');
						getline(file, cause1a, ',');
						//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
						//{
						//	//getline(inFile, cause1b, ',');
						//	cause1b = " ";
						//}
						//else
						//{
						//	getline(file, cause1b, ',');
						//}

						getline(file, cause2, ',');
						//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
						//f_cause = cause1a + cause1b + cause2;
						getline(file, state, ',');
						getline(file, deaths, ',');
						getline(file, rate, '\n');
					}

					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//string cause1 = cause1a + "," + cause1b;

					del << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}

		}
	}

	void deleteQueryYear(RBTree<T> tree, T key)
	{
		ofstream del;
		del.open("Delete_Query.csv", ios::trunc);
		del.close();
		del.open("Delete_Query.csv", ios::app);

		del << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
					//{
					//	//getline(inFile, cause1b, ',');
					//	cause1b = " ";
					//}
					//else
					//{
					//	getline(file, cause1b, ',');
					//}

					getline(file, cause2, ',');
					//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
					//f_cause = cause1a + cause1b + cause2;
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
					//cout << state << " ";
					while (year == key)
					{
						getline(file, id, ',');
						getline(file, year, ',');
						getline(file, cause1a, ',');
						//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
						//{
						//	//getline(inFile, cause1b, ',');
						//	cause1b = " ";
						//}
						//else
						//{
						//	getline(file, cause1b, ',');
						//}

						getline(file, cause2, ',');
						//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
						//f_cause = cause1a + cause1b + cause2;
						getline(file, state, ',');
						getline(file, deaths, ',');
						getline(file, rate, '\n');
					}

					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//string cause1 = cause1a + "," + cause1b;

					del << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}
		}
	}

	void deleteQueryCause(RBTree<T> tree, T key)
	{
		ofstream del;
		del.open("Delete_Query.csv", ios::trunc);
		del.close();
		del.open("Delete_Query.csv", ios::app);

		del << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
					//{
					//	//getline(inFile, cause1b, ',');
					//	cause1b = " ";
					//}
					//else
					//{
					//	getline(file, cause1b, ',');
					//}

					getline(file, cause2, ',');
					//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
					//f_cause = cause1a + cause1b + cause2;
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');

					//string cause1 = cause1a + "," + cause1b;
					//cout << state << " ";
					while (cause2 == key)
					{
						getline(file, id, ',');
						getline(file, year, ',');
						getline(file, cause1a, ',');
						//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
						//{
						//	getline(inFile, cause1b, ',');
						//	cause1b = " ";
						//}
						//else
						//{
						//	getline(file, cause1b, ',');
						//}

						getline(file, cause2, ',');
						//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
						//f_cause = cause1a + cause1b + cause2;
						getline(file, state, ',');
						getline(file, deaths, ',');
						getline(file, rate, '\n');
					}

					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//cause1 = cause1a + "," + cause1b;

					del << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}
		}
	}

	void deleteQueryState(RBTree<T> tree, T key)
	{
		ofstream del;
		del.open("Delete_Query.csv", ios::trunc);
		del.close();
		del.open("Delete_Query.csv", ios::app);

		del << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
					//{
					//	//getline(inFile, cause1b, ',');
					//	cause1b = " ";
					//}
					//else
					//{
					//	getline(file, cause1b, ',');
					//}

					getline(file, cause2, ',');
					//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
					//f_cause = cause1a + cause1b + cause2;
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
					//cout << state << " ";
					while (state == key)
					{
						getline(file, id, ',');
						getline(file, year, ',');
						getline(file, cause1a, ',');
						//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
						//{
						//	//getline(inFile, cause1b, ',');
						//	cause1b = " ";
						//}
						//else
						//{
						//	getline(file, cause1b, ',');
						//}

						getline(file, cause2, ',');
						//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
						//f_cause = cause1a + cause1b + cause2;
						getline(file, state, ',');
						getline(file, deaths, ',');
						getline(file, rate, '\n');
					}


					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//string cause1 = cause1a + "," + cause1b;

					del << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}
		}
	}

	void deleteQueryDeath(RBTree<T> tree, T key)
	{
		ofstream del;
		del.open("Delete_Query.csv", ios::trunc);
		del.close();
		del.open("Delete_Query.csv", ios::app);

		del << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
					//{
					//	//getline(inFile, cause1b, ',');
					//	cause1b = " ";
					//}
					//else
					//{
					//	getline(file, cause1b, ',');
					//}

					getline(file, cause2, ',');
					//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
					//f_cause = cause1a + cause1b + cause2;
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
					//cout << state << " ";
					while (deaths == key)
					{
						getline(file, id, ',');
						getline(file, year, ',');
						getline(file, cause1a, ',');
						//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
						//{
						//	//getline(inFile, cause1b, ',');
						//	cause1b = " ";
						//}
						//else
						//{
						//	getline(file, cause1b, ',');
						//}

						getline(file, cause2, ',');
						//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
						//f_cause = cause1a + cause1b + cause2;
						getline(file, state, ',');
						getline(file, deaths, ',');
						getline(file, rate, '\n');
					}

					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//string cause1 = cause1a + "," + cause1b;

					del << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}
		}
	}

	void deleteQueryRate(RBTree<T> tree, T key)
	{
		ofstream del;
		del.open("Delete_Query.csv", ios::trunc);
		del.close();
		del.open("Delete_Query.csv", ios::app);

		del << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
					//{
					//	//getline(inFile, cause1b, ',');
					//	cause1b = " ";
					//}
					//else
					//{
					//	getline(file, cause1b, ',');
					//}

					getline(file, cause2, ',');
					//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
					//f_cause = cause1a + cause1b + cause2;
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
					//cout << state << " ";
					while (rate == key)
					{
						getline(file, id, ',');
						getline(file, year, ',');
						getline(file, cause1a, ',');
						//if (cause1a == "All Causes" || /*cause1a == "Unintentional injuries " ||*/ cause1a == "Alzheimer's disease (G30)" || cause1a == "All causes" || cause1a == "Alzheimer's disease")
						//{
						//	//getline(inFile, cause1b, ',');
						//	cause1b = " ";
						//}
						//else
						//{
						//	getline(file, cause1b, ',');
						//}

						getline(file, cause2, ',');
						//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
						//f_cause = cause1a + cause1b + cause2;
						getline(file, state, ',');
						getline(file, deaths, ',');
						getline(file, rate, '\n');
					}

					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					//string cause1 = cause1a + "," + cause1b;

					del << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}

		}

	}

	void updateQueryID(RBTree<T> tree, T old, T replace)
	{
		ofstream upd;
		upd.open("Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("Update_Query.csv", ios::app);

		upd << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
					//f_cause = cause1a + cause1b + cause2;
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');

					//string cause1 = cause1a + "," + cause1b;
					//cout << state << " ";
					if (id == old)
					{
						id = replace;
					}

					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					upd << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}
		}
	}

	void updateQueryYear(RBTree<T> tree, T old, T replace)
	{
		ofstream upd;
		upd.open("Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("Update_Query.csv", ios::app);

		upd << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);
			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
					//f_cause = cause1a + cause1b + cause2;
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');

					//string cause1 = cause1a + "," + cause1b;
					//cout << state << " ";
					if (year == old)
					{
						year = replace;
					}

					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					upd << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}

		}
		//remove(address);

		// renaming the updated file with the existing file name
		//rename("Update_Query.csv", "abc.csv");

	}

	void updateQueryCause(RBTree<T> tree, T old, T replace)
	{
		ofstream upd;
		upd.open("Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("Update_Query.csv", ios::app);

		upd << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
					//f_cause = cause1a + cause1b + cause2;
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');

					//string cause1 = cause1a + "," + cause1b;
					//cout << state << " ";
					if (cause1a == old)
					{
						cause1a = replace;
					}
					if (cause2 == old)
					{
						cause2 = replace;
					}
					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					upd << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}
		}
	}

	void updateQueryState(RBTree<T> tree, T old, T replace)
	{
		ofstream upd;
		upd.open("Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("Update_Query.csv", ios::app);

		upd << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
					//f_cause = cause1a + cause1b + cause2;
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');

					//string cause1 = cause1a + "," + cause1b;
					//cout << state << " ";
					if (state == old)
					{
						state = replace;
					}

					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					upd << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}
		}
	}

	void updateQueryDeath(RBTree<T> tree, T old, T replace)
	{
		ofstream upd;
		upd.open("Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("Update_Query.csv", ios::app);

		upd << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
					//f_cause = cause1a + cause1b + cause2;
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');

					//string cause1 = cause1a + "," + cause1b;
					//cout << state << " ";
					if (deaths == old)
					{
						deaths = replace;
					}

					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					upd << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}
		}
	}

	void updateQueryRate(RBTree<T> tree, T old, T replace)
	{
		string path = searchpath(tree.getroot(), old);

		ofstream upd;
		upd.open("Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("Update_Query.csv", ios::app);

		upd << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');

					//string cause1 = cause1a + "," + cause1b;
					//cout << state << " ";
					if (rate == old)
					{
						rate = replace;
					}

					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					upd << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}
		}
	}

	RBNode<T>* searchNode(RBNode<T>* root, T key)
	{
		if (root == NULL)
			return NULL;


		RBNode<T>* temp = root;

		if (temp->data == key) {
			return temp;
		}

		else if (temp->data > key) {
			return searchNode(temp->RBNode_left, key);
		}

		else
			return searchNode(temp->RBNode_right, key);
	}
	string searchpath(RBNode<T>* root, T key)
	{

		if (root == NULL)
			return NULL;


		RBNode<T>* temp = root;

		if (temp->data == key) {
			return temp->path;
		}

		else if (temp->data > key) {
			return searchpath(temp->RBNode_left, key);
		}

		else
			return searchpath(temp->RBNode_right, key);
	}


	void Bonus_idwherestate(RBTree<T> tree, T key, T where)
	{

		string path = searchpath(tree.getroot(), key);

		ofstream bonus("Bonus.csv");
		bonus.open("Bonus.csv", ios::trunc);
		bonus.close();
		bonus.open("Bonus.csv", ios::app);

		bonus << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{

				num--;
				getline(file, id, ',');
				getline(file, year, ',');
				getline(file, cause1a, ',');
				getline(file, cause2, ',');
				getline(file, state, ',');
				getline(file, deaths, ',');
				getline(file, rate, '\n');

				if (key == id && where == state)
				{
					bonus << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
			}
		}

	}

	void Bonus_yearwherestate(RBTree<T> tree, T key, T where)
	{

		//string path = searchpath(tree.getroot(), key);

		ofstream bonus("Bonus.csv");
		//ofstream bonus;
		bonus.open("Bonus.csv", ios::trunc);
		bonus.close();
		bonus.open("Bonus.csv", ios::app);

		bonus << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			int num = 10;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			while (!file.eof())
			{

				num--;
				getline(file, id, ',');
				getline(file, year, ',');
				getline(file, cause1a, ',');
				getline(file, cause2, ',');
				getline(file, state, ',');
				getline(file, deaths, ',');
				getline(file, rate, '\n');
				//cout << state << " ";
				if (key == year && where == state)
				{
					bonus << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
			}
		}

	}

	void bonusdel_idwherestate(RBTree<T> tree, T key, T where)
	{
		string path;// = searchpath(tree.getroot(), key);

		ofstream del;
		del.open("Bonus_del.csv", ios::trunc);
		del.close();
		del.open("Bonus_del.csv", ios::app);

		del << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			//int num = 10;

			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');

					while (key == id && where == state)
					{
						getline(file, id, ',');
						getline(file, year, ',');
						getline(file, cause1a, ',');
						getline(file, cause2, ',');
						getline(file, state, ',');
						getline(file, deaths, ',');
						getline(file, rate, '\n');
					}

					del << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}
		}
	}

	void bonusdel_yearwherestate(RBTree<T> tree, T key, T where)
	{
		string path;// = searchpath(tree.getroot(), key);

		ofstream del;
		del.open("Bonus_del.csv", ios::trunc);
		del.close();
		del.open("Bonus_del.csv", ios::app);

		del << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			//string address = searchpath(tree.getroot(), key);               //path for excel
			ifstream file;

			path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//cout << "PATH: " << address << endl;
			file.open(path);

			//int num = 10;
			if (file.is_open())
				cout << "opened" << endl;
			string id;
			string year;
			string state;
			string cause1a;
			string cause1b;
			string cause2;
			string deaths;
			string rate;
			int num = 10;
			while (!file.eof())
			{
				if (num != 10)
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');

					while (key == year && where == state)
					{
						getline(file, id, ',');
						getline(file, year, ',');
						getline(file, cause1a, ',');
						getline(file, cause2, ',');
						getline(file, state, ',');
						getline(file, deaths, ',');
						getline(file, rate, '\n');
					}

					del << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

				}
				else
				{
					getline(file, id, ',');
					getline(file, year, ',');
					getline(file, cause1a, ',');
					getline(file, cause2, ',');
					getline(file, state, ',');
					getline(file, deaths, ',');
					getline(file, rate, '\n');
				}
				num--;
			}
		}
	}

	RBNode<T>* UpdateNode(RBNode<T>* node, T key, T rep)
	{
		if (node == NULL)
		{
			return NULL;
		}

		if (key < node->data)
		{
			node->RBNode_left = UpdateNode(node->RBNode_left, key, rep);
		}
		else if (key > node->data)
		{
			node->RBNode_right = UpdateNode(node->RBNode_right, key, rep);
		}
		else
		{
			node->data = rep;
		}

		return node;
	}

	void removeTree(RBNode<T>* node)
	{
		if (node != NULL)
		{
			removeTree(node->RBNode_left);
			removeTree(node->RBNode_right);
			delete node;
		}
	}

	~RBTree()
	{
		removeTree(root);
	}
};
