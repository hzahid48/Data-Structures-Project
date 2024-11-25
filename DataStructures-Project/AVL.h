#include <iostream>
using namespace std;

template <class T>
class AVLNode {
public:
	AVLNode<T>* left;
	AVLNode<T>* right;
	T data;
	string path;
	int Height;
	SLinkedList<string> list;
	string d = "D:";
	string p = "P:";
	string r = "R:";
	string l = "L:";
	string L = "T:";
	string end = "End ";
	string space = " ";
	AVLNode(T d) {
		left = right = NULL;
		data = d;
		Height = 0;
	}
	AVLNode(T d, string p) {
		left = right = NULL;
		data = d;
		path = p;
		Height = 0;
	}
	void insertlist(AVLNode<T>* n, string id, string path) {

		n->list.insert(id, path);
	}
};

template <class T>
class AVLTree {
public:
	AVLNode<T>* root;

	bool duplicate = false;

	AVLTree() {
		this->root = NULL;
	}
	AVLNode<T>* getroot()
	{
		return root;
	}
	void insert(AVLNode<T>* X) {
		AVLNode<T>* temp = root;
		AVLNode<T>* newnode;
		newnode = new AVLNode<T>(X);
	}
	void Printing(AVLNode<T>* temp) {
		if (!root || !temp)
			return;
		else {
			Printing(temp->left);
			cout << temp->data << endl;
			Printing(temp->right);
		}
	}
	void display() {
		AVLNode<T>* temp = this->root;
		Printing(temp);
	}
	AVLNode<T>* InsertAVL2(T X, AVLNode<T>* A) { //insert2
		if (!A)
			A = new AVLNode<T>(X);
		else if (X < A->data) {
			A->left = InsertAVL2(X, A->left);
			if (Height(A->left) - Height(A->right) == 2)
				(X < A->left->data) ? A = RR(A) : A = RL(A);
		}
		else if (X > A->data) {
			A->right = InsertAVL2(X, A->right);
			if (Height(A->right) - Height(A->left) == 2)
				(X > A->right->data) ? A = LL(A) : A = LR(A);
		}
		return A;
	}
	AVLNode<T>* InsertAVL(AVLNode<T>* X, AVLNode<T>* A, string id, string p) { //insert2
		if (A == NULL)
			return X;
		//A = new AVLNode<T>(X,p);

		else if (X->data < A->data) {
			A->left = InsertAVL(X, A->left, id, p);
			/*if (Height(A->left) - Height(A->right) == 2)
				(X->data < A->left->data) ? A = RR(A) : A = LR(A);*/
		}
		else if (X->data > A->data) {
			A->right = InsertAVL(X, A->right, id, p);
			/* if (Height(A->right) - Height(A->left) == 2)
				 (X->data > A->right->data) ? A = LL(A) : A = RL(A);*/
		}
		else {
			A->insertlist(A, id, p);
			duplicate = true;
			return A;
		}

		A->Height = 1 + max(Height(A->left), Height(A->right));

		if (Height(A->left) - Height(A->right) > 1) {
			if (X->data < A->left->data) {
				return RR(A);
			}

			else if (X->data > A->left->data) {
				A->left = LL(A->left);
				return RR(A);
			}
		}

		else if (Height(A->left) - Height(A->right) < -1) {
			if (X->data > A->right->data) {
				return LL(A);
			}

			else if (X->data > A->right->data) {
				A->right = RR(A->right);
				return LL(A);
			}
		}

		return A;
	}


	void Insert(T d, AVLNode<T>* p, fstream& file, string id, string pa)

	{
		AVLNode<T>* pt = new AVLNode<T>(d, pa);
		root = InsertAVL(pt, p, id, pa);

		AVLwritefile(root, file);
		duplicate = false;

	}
	void AVLwritefile(AVLNode<T>* p, fstream& file) {
		Queue<AVLNode<T>*> q;
		if (p == NULL) {
			return;
		}

		q.enqueue(p);

		while (!q.isEmpty()) {
			AVLNode<T>* temp = q.Front();
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
			q.dequeue();
			if (temp->left != NULL) {
				file << temp->l << temp->left->data << endl;
				q.enqueue(temp->left);
			}

			if (temp->right != NULL) {
				file << temp->r << temp->right->data << endl;
				q.enqueue(temp->right);
			}

			file << temp->end << endl;

		}
	}

	void insertAVL1(RBNode<T>* p)
	{
		RBNode<T>* pt = p;
		root = insert2(root, pt);

	}

	void ReadTree(AVLTree<T> tree, fstream& file) {

		string line;
		T data;
		string path;
		string list_id;
		string list_path;
		string path_list;
		string id_list;
		int j;
		int counter = 0;
		AVLNode<T>* temp = new AVLNode<T>(data, path);

		while (!file.eof()) {
			j = 0;
			getline(file, line, '\n');

			if (line[0] == 'D') {
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

				for (j = 0; path[j + 2] != '\0'; j++) {
					path[j] = path[j + 2];
				}
				counter++;
			}

			if (line[0] == 'T') {
				list_id = line;
				list_path = line;
				list_id[0] = list_id[1] = '\0';
				list_path[0] = list_path[1] = '\0';
				for (j = 2; line[j] != ',' && line[j] != '\0'; j++) {
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
			}

			if (counter == 3) {
				if (temp->list.head != NULL)
					temp->list.print();
				temp = new AVLNode<T>(data, path);
				counter = 0;
				tree.InsertAVL2(data, temp);
			}

		}

		cout << "TREE:";
		tree.display();
	}

	int Height(AVLNode<T>* P) {
		if (P == NULL)
			return 0;
		return P->Height;
	}
	AVLNode<T>* RR(AVLNode<T>* K1) {
		/* AVLNode<T>* K2;
		 K2 = K1->left;
		 K1->left = K2->right;
		 K2->right = K1;
		 return K2;*/
		AVLNode<T>* x = K1->left;
		AVLNode<T>* t2 = x->right;
		x->right = K1;
		K1->left = t2;
		K1->Height = max(Height(K1->left), Height(K1->right) + 1);
		x->Height = max(Height(x->left), Height(x->right) + 1);

		return x;
	}

	AVLNode<T>* LL(AVLNode<T>* K1) {
		AVLNode<T>* y = K1->right;
		AVLNode<T>* t2 = y->left;
		y->left = K1;
		K1->right = t2;
		K1->Height = max(Height(K1->left), Height(K1->right) + 1);
		y->Height = max(Height(y->left), Height(y->right) + 1);

		return y;
	}
	AVLNode<T>* LR(AVLNode<T>* K1) {
		K1->right = RR(K1->right);
		return LL(K1);
	}
	AVLNode<T>* RL(AVLNode<T>* K3) {
		K3->left = LL(K3->left);
		return RR(K3);
	}
	AVLNode<T>* minValueNode(AVLNode<T>* node)
	{
		AVLNode<T>* current = node;

		while (current->left != NULL)
			current = current->left;

		return current;
	}

	int max(int a, int b)
	{
		return (a > b) ? a : b;
	}

	AVLNode<T>* rightRotate(AVLNode<T>* y)
	{
		AVLNode<T>* x = y->left;
		AVLNode<T>* T2 = x->right;

		x->right = y;
		y->left = T2;


		y->Height = max(Height(y->left),
			Height(y->right)) + 1;
		x->Height = max(Height(x->left),
			Height(x->right)) + 1;
		return x;
	}

	AVLNode<T>* leftRotate(AVLNode<T>* x)
	{
		AVLNode<T>* y = x->right;
		AVLNode<T>* T2 = y->left;

		y->left = x;
		x->right = T2;

		x->Height = max(Height(x->left),
			Height(x->right)) + 1;
		y->Height = max(Height(y->left),
			Height(y->right)) + 1;

		return y;
	}


	AVLNode<T>* deleteNode(T data, AVLNode<T>* root)
	{

		if (root == NULL)
			return root;

		if (data < root->data)
			root->left = deleteNode(data, root->left);

		else if (data > root->data)
			root->right = deleteNode(data, root->right);

		else
		{
			if ((root->left == NULL) ||
				(root->right == NULL))
			{
				AVLNode<T>* temp = root->left ?
					root->left :
					root->right;

				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else
					*root = *temp;
				free(temp);
			}
			else
			{
				AVLNode<T>* temp = minValueNode(root->right);

				root->data = temp->data;
				root->right = deleteNode(temp->data, root->right);
			}
		}

		if (root == NULL)
			return root;
		root->Height = 1 + max(Height(root->left),
			Height(root->right));

		int balance = getBalance(root);

		if (balance > 1 &&
			getBalance(root->left) >= 0)
			return rightRotate(root);


		if (balance > 1 &&
			getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}


		if (balance < -1 &&
			getBalance(root->right) <= 0)
			return leftRotate(root);


		if (balance < -1 &&
			getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}
	int getBalance(AVLNode<T>* N)
	{
		if (N == NULL)
			return 0;
		return Height(N->left) -
			Height(N->right);
	}

	//void AVL_SelectID(AVLTree<T> tree, T key)
	//{
	//	ofstream search;
	//	search.open("AVL_Search_Query.csv", ios::trunc);
	//	search.close();
	//	search.open("AVL_Search_Query.csv", ios::app);


	//	search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";
	//	for (int filenum = 0; filenum < 2; filenum++)
	//	{
	//		//string address = searchpath(tree.getroot(), key);               //path for excel
	//		ifstream file;

	//		string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
	//		path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
	//		path += ".csv";

	//		//cout << "PATH: " << address << endl;
	//		file.open(path);
	//		string id;
	//		string year;
	//		string state;
	//		string cause1a;
	//		string cause1b;
	//		string cause2;
	//		string deaths;
	//		string rate;
	//		int num = 10;
	//		while (!file.eof())
	//		{

	//			num--;
	//			getline(file, id, ',');
	//			getline(file, year, ',');
	//			getline(file, cause1a, ',');
	//			getline(file, cause2, ',');
	//			getline(file, state, ',');
	//			getline(file, deaths, ',');
	//			getline(file, rate, '\n');

	//			if (key == id)
	//			{
	//				cout << "ID: " << id << " ";
	//				cout << "year: " << year << " ";
	//				cout << "cause: " << cause1a << cause2 << " ";
	//				cout << "state: " << state << " ";
	//				cout << "deaths: " << deaths << " ";
	//				cout << "rate: " << rate << endl;


	//				search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
	//			}
	//		}
	//	}
	//}

	void AVL_SelectID(AVLTree<T> tree, T key)
	{
		ofstream search;
		search.open("AVL_Search_Query.csv", ios::trunc);
		search.close();
		search.open("AVL_Search_Query.csv", ios::app);

		search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		AVLNode<T>* temp = searchNode(tree.getroot(), key);
		string path = temp->path;

		ifstream file;
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

			if (key == id)
			{
				cout << "ID: " << id << " ";
				cout << "year: " << year << " ";
				cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
				cout << "state: " << state << " ";
				cout << "deaths: " << deaths << " ";
				cout << "rate: " << rate << endl;

				search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
			}


		}
	}


	void AVL_SelectState(AVLTree<T> tree, T key)
	{
		ofstream search;
		search.open("AVL_Search_Query.csv", ios::trunc);
		search.close();
		search.open("AVL_Search_Query.csv", ios::app);

		search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

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

					search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

				}
			}
		}
	}

	AVLNode<T>* searchNode(AVLNode<T>* root, T key)
	{

		if (root == NULL)
			return NULL;


		AVLNode<T>* temp = root;

		if (temp->data == key) {
			return temp;
		}

		else if (temp->data > key) {
			return searchNode(temp->left, key);
		}

		else
			return searchNode(temp->right, key);
	}

	//void AVL_SelectYear(AVLTree<T> tree, T key) {

	//	ofstream search;
	//	search.open("AVL_Search_Query.csv", ios::trunc);
	//	search.close();
	//	search.open("AVL_Search_Query.csv", ios::app);

	//	search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

	//	for (int filenum = 0; filenum < 2; filenum++)
	//	{
	//		//string address = searchpath(tree.getroot(), key);               //path for excel
	//		ifstream file;

	//		string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
	//		path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
	//		path += ".csv";

	//		//cout << "PATH: " << address << endl;
	//		file.open(path);



	//		if (file.is_open())
	//			cout << "opened" << endl;
	//		string id;
	//		string year;
	//		string state;
	//		string cause1a;
	//		string cause1b;
	//		string cause2;
	//		string deaths;
	//		string rate;
	//		int num = 10;
	//		while (!file.eof())
	//		{

	//			num--;
	//			getline(file, id, ',');
	//			getline(file, year, ',');
	//			getline(file, cause1a, ',');
	//			getline(file, cause2, ',');
	//			getline(file, state, ',');
	//			getline(file, deaths, ',');
	//			getline(file, rate, '\n');
	//			//cout << state << " ";
	//			if (key == year)
	//			{
	//				cout << "ID: " << id << " ";
	//				cout << "year: " << year << " ";
	//				cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
	//				cout << "state: " << state << " ";
	//				cout << "deaths: " << deaths << " ";
	//				cout << "rate: " << rate << endl;

	//				search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
	//			}
	//		}
	//	}
	//}


	void AVL_SelectYear(AVLTree<T> tree, T key) {

		ofstream search;
		search.open("AVL_Search_Query.csv", ios::trunc);
		search.close();
		search.open("AVL_Search_Query.csv", ios::app);

		search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		AVLNode<T>* temp = searchNode(tree.getroot(), key);
		listNode<T>* temp2 = temp->list.head;
		string path = "";
		while (temp2->next != NULL)
		{

			string prevpath = path;
			path = temp2->path;

			if (prevpath != path)
			{
				ifstream file;
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

					if (key == year)
					{
						cout << "ID: " << id << " ";
						cout << "year: " << year << " ";
						cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
						cout << "state: " << state << " ";
						cout << "deaths: " << deaths << " ";
						cout << "rate: " << rate << endl;

						search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
					}


				}

			}

			temp2 = temp2->next;

		}

	}

	/*void AVL_SelectYear(AVLTree<T> tree, T key) {

		ofstream search;
		search.open("AVL_Search_Query.csv", ios::trunc);
		search.close();
		search.open("AVL_Search_Query.csv", ios::app);

		search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		AVLNode<T>* temp = searchNode(tree.getroot(), key);
		listNode<T>* temp2 = temp->list.head;
		string path = "";
		while (temp2->next != NULL)
		{

			string prevpath = path;
			path = temp2->path;

			if (prevpath != path)
			{
				ifstream file;
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

					if (key == year)
					{
						cout << "ID: " << id << " ";
						cout << "year: " << year << " ";
						cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
						cout << "state: " << state << " ";
						cout << "deaths: " << deaths << " ";
						cout << "rate: " << rate << endl;

						search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
					}


				}

			}

			temp2 = temp2->next;

		}

	}*/

	void AVL_SelectRate(AVLTree<T> tree, T key)
	{
		ofstream search;
		search.open("AVL_Search_Query.csv", ios::trunc);
		search.close();
		search.open("AVL_Search_Query.csv", ios::app);

		search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

		for (int filenum = 0; filenum < 2; filenum++)
		{
			ifstream file;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

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

				if (key == rate)
				{
					cout << "ID: " << id << " ";
					cout << "year: " << year << " ";
					cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << " ";
					cout << "state: " << state << " ";
					cout << "deaths: " << deaths << " ";
					cout << "rate: " << rate << endl;

					search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";
				}
			}
		}
	}

	void AVL_SelectDeath(AVLTree<T> tree, T key) {

		ofstream search;
		search.open("AVL_Search_Query.csv", ios::trunc);
		search.close();
		search.open("AVL_Search_Query.csv", ios::app);

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

	void AVL_rangeQueryID(AVLTree<T> tree, string start, string end)
	{
		ofstream range;
		range.open("AVL_Range_Query.csv", ios::trunc);
		range.close();
		range.open("AVL_Range_Query.csv", ios::app);

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

	void AVL_rangeQueryYEAR(AVLTree<T> tree, string start, string end)
	{
		ofstream range;
		range.open("AVL_Range_Query.csv", ios::trunc);
		range.close();
		range.open("AVL_Range_Query.csv", ios::app);

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

	void AVL_rangeQueryDEATHS(AVLTree<T> tree, string start, string end)
	{
		ofstream range;
		range.open("AVL_Range_Query.csv", ios::trunc);
		range.close();
		range.open("AVL_Range_Query.csv", ios::app);

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

	void AVL_rangeQueryRate(AVLTree<T> tree, string start, string end)
	{
		ofstream range;
		range.open("AVL_Range_Query.csv", ios::trunc);
		range.close();
		range.open("AVL_Range_Query.csv", ios::app);

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

	void AVL_deleteQueryID(AVLTree<T> tree, T key)
	{
		ofstream del;
		del.open("AVL_Delete_Query.csv", ios::trunc);
		del.close();
		del.open("AVL_Delete_Query.csv", ios::app);

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

	void AVL_deleteQueryYear(AVLTree<T> tree, T key)
	{
		ofstream del;
		del.open("AVL_Delete_Query.csv", ios::trunc);
		del.close();
		del.open("AVL_Delete_Query.csv", ios::app);

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

	void AVL_deleteQueryCause(AVLTree<T> tree, T key)
	{
		ofstream del;
		del.open("AVL_Delete_Query.csv", ios::trunc);
		del.close();
		del.open("AVL_Delete_Query.csv", ios::app);

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

	void AVL_deleteQueryState(AVLTree<T> tree, T key)
	{
		ofstream del;
		del.open("AVL_Delete_Query.csv", ios::trunc);
		del.close();
		del.open("AVL_Delete_Query.csv", ios::app);

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

	void AVL_deleteQueryDeath(AVLTree<T> tree, T key)
	{
		ofstream del;
		del.open("AVL_Delete_Query.csv", ios::trunc);
		del.close();
		del.open("AVL_Delete_Query.csv", ios::app);

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

	void AVL_deleteQueryRate(AVLTree<T> tree, T key)
	{
		ofstream del;
		del.open("AVL_Delete_Query.csv", ios::trunc);
		del.close();
		del.open("AVL_Delete_Query.csv", ios::app);

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

	void AVL_updateQueryID(AVLTree<T> tree, T old, T replace)
	{
		ofstream upd;
		upd.open("AVL_Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("AVL_Update_Query.csv", ios::app);

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

	void AVL_updateQueryYear(AVLTree<T> tree, T old, T replace)
	{
		ofstream upd;
		upd.open("AVL_Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("AVL_Update_Query.csv", ios::app);

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

	void AVL_updateQueryCause(AVLTree<T> tree, T old, T replace)
	{
		ofstream upd;
		upd.open("AVL_Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("AVL_Update_Query.csv", ios::app);

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

	void AVL_updateQueryState(AVLTree<T> tree, T old, T replace)
	{
		ofstream upd;
		upd.open("AVL_Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("AVL_Update_Query.csv", ios::app);

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

	void AVL_updateQueryDeath(AVLTree<T> tree, T old, T replace)
	{
		ofstream upd;
		upd.open("AVL_Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("AVL_Update_Query.csv", ios::app);

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

	void AVL_updateQueryRate(AVLTree<T> tree, T old, T replace)
	{
		//string path = searchpath(tree.getroot(), old);

		ofstream upd;
		upd.open("AVL_Update_Query.csv", ios::trunc);
		upd.close();
		upd.open("AVL_Update_Query.csv", ios::app);

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




	AVLNode<T>* UpdateNode(AVLNode<T>* node, T key, T rep)
	{
		if (node == NULL)
		{
			return NULL;
		}

		if (key < node->data)
		{
			node->left = UpdateNode(node->left, key, rep);
		}
		else if (key > node->data)
		{
			node->right = UpdateNode(node->right, key, rep);
		}
		else
		{
			node->data = rep;
		}

		return node;
	}


	~AVLTree()
	{
		removeTree(root);
	}

	void removeTree(AVLNode<T>* node)
	{
		if (node != NULL)
		{
			removeTree(node->left);   
			removeTree(node->right);  
			delete node;         
		}
	}
};



