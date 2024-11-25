//#include "Header.h"
#include "linkedlist.h"
#include "RBTree.h"
#include "Btree.h"
#include "AVL.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

RBTree<string> idTree;

RBTree<string>yearTree;

RBTree<string> causeTree;

RBTree<string> stateTree;
RBTree<string>deathsTree;

RBTree<string> rateTree;
//RBTree<string> idTree;
fstream idfile;
//RBTree<string>yearTree;
fstream yearfile;
//RBTree<string> causeTree;
fstream causefile;
//RBTree<string> stateTree;
fstream statefile;
//RBTree<string>deathsTree;
fstream deathfile;
//RBTree<string> rateTree;
fstream ratefile;

void RB(string cb, string c1)
{
	////RBTree<string> idTree;
	//fstream idfile;
	////RBTree<string>yearTree;
	//fstream yearfile;
	////RBTree<string> causeTree;
	//fstream causefile;
	////RBTree<string> stateTree;
	//fstream statefile;
	////RBTree<string>deathsTree;
	//fstream deathfile;
	////RBTree<string> rateTree;
	//fstream ratefile;

	if (c1 == "1")
	{
		for (int filenum = 0; filenum < 2; filenum++)
		{
			string id;
			string year;
			string cause1a;
			string cause1b;
			string cause2;
			string state;
			string deaths;
			string rate;
			string blank;
			string f_cause;

			string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
			path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
			path += ".csv";

			//string path = "NCHS_-_Leading_Causes_of_Death__United_States_1.csv";
			int i;
			ifstream inFile;
			inFile.open(path);

			if (inFile.is_open())
			{
				cout << "File has been opened" << endl;
			}
			else
			{
				cout << "NO FILE HAS BEEN OPENED" << endl;
			}

			int num = 10;
			int y = 1;
			while (!inFile.eof())
			{
				if (num != 10)
				{
					getline(inFile, id, ',');
					cout << "id: " << id << endl;

					getline(inFile, year, ',');
					cout << "year: " << year << endl;

					getline(inFile, cause1a, ',');
					getline(inFile, cause2, ',');

					f_cause = cause1a + cause2;

					getline(inFile, state, ',');
					getline(inFile, deaths, ',');
					getline(inFile, rate, '\n');

					if (cb == "a")
					{
						idfile.open("ID.txt", ios::app);
						idTree.RBinsert(id, idTree.getroot(), idfile, id, path);
						idfile.close();
					}
					if (cb == "c")
					{
						causefile.open("CAUSE.txt");
						causeTree.RBinsert(f_cause, causeTree.getroot(), causefile, id, path);
						causefile.close();
					}
					if (cb == "d")
					{
						statefile.open("STATE.txt", ios::app);
						stateTree.RBinsert(state, stateTree.getroot(), statefile, id, path);
						statefile.close();
						//stateTree.levelorder(stateTree.getroot());
					}
					if (cb == "e")
					{
						//int d = stoi(deaths);
						deathfile.open("DEATHS.txt");
						deathsTree.RBinsert(deaths, deathsTree.getroot(), deathfile, id, path);
						deathfile.close();
					}
					if (cb == "f")
					{
						ratefile.open("RATES.txt");
						rateTree.RBinsert(rate, rateTree.getroot(), ratefile, id, path);
						ratefile.close();
					}
					if (cb == "b")
					{
						//int z = stoi(year);
						yearfile.open("YEARS.txt");
						yearTree.RBinsert(year, yearTree.getroot(), yearfile, id, path);
						yearfile.close();
					}
				}

				else {
					getline(inFile, id, ',');
					getline(inFile, year, ',');
					getline(inFile, cause1a, ',');
					getline(inFile, cause2, ',');
					getline(inFile, state, ',');
					getline(inFile, deaths, ',');
					getline(inFile, rate, '\n');
				}

				num--;
			}

			inFile.close();

		}
	}


	//stateTree.levelorder(stateTree.getroot());

	else {
		if (cb == "a")
		{
			idfile.open("ID.txt");
			RBTree<string> idTree;
			idTree.ReadTree(idTree, idfile);
		}

		if (cb == "c")
		{
			//cause
			causefile.open("CAUSE.txt");
			RBTree<string> causeTree;
			causeTree.ReadTree(causeTree, causefile);
		}

		if (cb == "d") {
			//state
			statefile.open("STATE.txt");
			RBTree<string> stateTree;
			stateTree.ReadTree(stateTree, statefile);
		}

		if (cb == "e") {
			//dath
			deathfile.open("DEATHS.txt");
			RBTree<string> deathsTree;
			deathsTree.ReadTree(deathsTree, deathfile);
		}

		if (cb == "f") {
			//rate
			ratefile.open("RATES.txt");
			RBTree<string> rateTree;
			rateTree.ReadTree(rateTree, ratefile);
		}

		if (cb == "b")
		{
			//year
			yearfile.open("YEARS.txt");
			RBTree<string> yearTree;
			yearTree.ReadTree(yearTree, yearfile);
		}
	}

	idfile.close();
	deathfile.close();
	yearfile.close();
	causefile.close();
	statefile.close();
	ratefile.close();
}
AVLTree<string> Avl_idTree;
AVLTree<string> Avl_yearTree;
AVLTree<string> Avl_causeTree;
AVLTree<string> Avl_stateTree;
AVLTree<string> Avl_deathsTree;
AVLTree<string> Avl_rateTree;

fstream a_idfile;
fstream a_yearfile;
fstream a_causefile;
fstream a_statefile("AVL_STATE.txt");
fstream a_deathfile;
fstream a_ratefile;

void AVL(string cb, string c1)
{
		if (c1 == "1")
		{
			for (int filenum = 0; filenum < 2; filenum++) {
				string id;
				string year;
				string cause1a;
				string cause1b;
				string cause2;
				string state;
				string deaths;
				string rate;
				string blank;
				string f_cause;

				string path = "NCHS_-_Leading_Causes_of_Death__United_States_";
				path += to_string(filenum + 1);  //converting the number to string to add it in the file name 
				path += ".csv";
				int i;
				ifstream inFile;
				inFile.open(path);

				if (inFile.is_open())
				{
					cout << "File has been opened" << endl;
				}
				else
				{
					cout << "NO FILE HAS BEEN OPENED" << endl;
				}

				int num = 10;
				int y = 1;
				//id = " ";
				while (!inFile.eof())
				{
					if (num != 10)
					{
						getline(inFile, id, ',');

						cout << "id: " << id << endl;
						//idfile << id<<endl;

						getline(inFile, year, ',');
						cout << "year: " << year << endl;
						//yearfile << year<<endl;

						getline(inFile, cause1a, ',');
						getline(inFile, cause2, ',');
						//cout << "cause: " << cause1a << " " << cause1b << ", " << cause2 << endl;
						f_cause = cause1a + cause2;
						//causefile << cause1a << " " << cause1b << ", " << cause2 << endl;

						getline(inFile, state, ',');
						//cout << "state: " << state << endl;
						//statefile << state << endl;

						getline(inFile, deaths, ',');
						//cout << "deaths: " << deaths << endl;
						//deathfile << deaths << endl;

						getline(inFile, rate, '\n');
						//cout << "rate: " << rate << endl << endl;
						//ratefile << rate << endl;

						//y = stoi(id);
						//float x = stoi(rate);
						//cout << "\n\nY: " << y;


						//stateTree.RBinsert(state);
						//rateTree.RBinsert(x);


						if (cb == "a")
						{
							a_idfile.open("AVL_ID.txt");
							Avl_idTree.Insert(id, Avl_idTree.getroot(), a_idfile, id, path);
							a_idfile.close();
						}
						if (cb == "c")
						{
							a_causefile.open("AVL_CAUSE.txt");
							Avl_causeTree.Insert(f_cause, Avl_causeTree.getroot(), a_causefile, id, path);
							a_causefile.close();
						}
						if (cb == "d")
						{
							a_statefile.open("AVL_STATE.txt");
							Avl_stateTree.Insert(state, Avl_stateTree.getroot(), a_statefile, id, path);
							a_statefile.close();
							//stateTree.levelorder(stateTree.getroot());
						}
						if (cb == "e")
						{
							//int d = stoi(deaths);
							a_deathfile.open("AVL_DEATHS.txt");
							Avl_deathsTree.Insert(deaths, Avl_deathsTree.getroot(), a_deathfile, id, path);
							a_deathfile.close();
						}
						if (cb == "f")
						{
							a_ratefile.open("AVL_RATES.txt");
							Avl_rateTree.Insert(rate, Avl_rateTree.getroot(), a_ratefile, id, path);
							a_ratefile.close();
						}
						if (cb == "b")
						{
							//int z = stoi(year);
							a_yearfile.open("AVL_YEARS.txt");
							Avl_yearTree.Insert(year, Avl_yearTree.getroot(), a_yearfile, id, path);
							a_yearfile.close();
						}
					}

					else {
						getline(inFile, id, ',');
						getline(inFile, year, ',');
						getline(inFile, cause1a, ',');
						getline(inFile, cause2, ',');
						getline(inFile, state, ',');
						getline(inFile, deaths, ',');
						getline(inFile, rate, '\n');
					}

					num--;
				}

				inFile.close();
			}
		}

		a_idfile.close();
		a_deathfile.close();
		a_yearfile.close();
		a_causefile.close();
		a_statefile.close();
		a_ratefile.close();
}

void menuAVL()
{
	int c1;   // number
	string c2;  // alphabets
	string c3;  //roman
	char con; // yes or no

	do
	{
		cout << "\nWhich operation do you want to perform:\n";
		cout << "1. Start\n"
			<< "a. ID\t\tb.Year\t\tc.Cause\n"
			<< "d.State\t\te.Deaths\tf.Rate\n\n";
		/*cout << "2. Read from file\n"
			<< "a. ID\t\tb.Year\t\tc.Cause\n"
			<< "d.State\t\te.Deaths\tf.Rate\n\n";*/
		cout << "2. Search Query\n"
			"a. ID\t\tb.Year\t\t"
			<< "c.State\nd.Deaths\te.Rate\n\n";
		cout << "3. Range Query\n"
			"a. ID\t\tb.Year\t\t"
			<< "c.State\nd.Deaths\te.Rate\n\n";
		cout << "4. Delete Query\n"
			<< "a. ID\t\tb.Year\t\t"
			<< "c.State\nd.Deaths\te.Rate\n\n";
		cout << "5. Update Query\n"
			<< "a. ID\t\tb.Year\t\t"
			<< "c.State\nd.Deaths\te.Rate\n\n";


		cout << "\nChoose operation: ";
		cin >> c1;
		while (c1 < 1 || c1 > 6)
		{
			cout << "Enter again\n";
			cin >> c1;
		}


		switch (c1)
		{
		case 1:
		{
			cout << "Choose the field: ";
			cin >> c3;
			AVL(c3, "1");
		}
		break;

		//case 2:
		//{
		//	cout << "Choose the field: ";
		//	cin >> c3;
		//	//AVL(c3, "2");
		//}
		//break;

		case 2:
		{
			cout << "Choose the field you want to search for: ";
			cin >> c2;
			if (c2 == "c")
			{
				string choose;
				cout << "Select a state: ";
				cin >> choose;
				//fstream search;
				Avl_stateTree.AVL_SelectState(Avl_stateTree, choose);
			}

			if (c2 == "a")
			{
				string choose;
				cout << "Select an ID: ";
				cin >> choose;
				Avl_idTree.AVL_SelectID(Avl_idTree, choose);
			}

			if (c2 == "b")
			{
				string choose;
				cout << "Select a year: ";
				cin >> choose;
				Avl_yearTree.AVL_SelectYear(Avl_yearTree, choose);
			}

			if (c2 == "e")
			{
				string choose;
				cout << "Select rate: ";
				cin >> choose;
				Avl_rateTree.AVL_SelectRate(Avl_rateTree, choose);
			}

			if (c2 == "f")
			{
				string choose;
				cout << "Select number of deaths: ";
				cin >> choose;
				Avl_deathsTree.AVL_SelectDeath(Avl_deathsTree, choose);
			}
		}
		break;

		case 3:
		{
			cout << "Choose the field you want to search for: ";
			cin >> c2;

			if (c2 == "a")
			{
				string choose1, choose2;
				cout << "(Enter two numbers) Select the range: ";
				cin >> choose1 >> choose2;
				Avl_idTree.AVL_rangeQueryID(Avl_idTree, choose1, choose2);
			}

			if (c2 == "b")
			{
				string choose1, choose2;
				cout << "(Enter two numbers) Select the range: ";
				cin >> choose1 >> choose2;
				Avl_yearTree.AVL_rangeQueryYEAR(Avl_yearTree, choose1, choose2);
			}

			if (c2 == "c")
			{
				string choose1, choose2;
				cout << "(Enter two numbers) Select the range: ";
				cin >> choose1 >> choose2;
				Avl_deathsTree.AVL_rangeQueryDEATHS(Avl_deathsTree, choose1, choose2);
			}

			if (c2 == "d")
			{
				string choose1, choose2;
				cout << "(Enter two numbers) Select the range: ";
				cin >> choose1 >> choose2;
				Avl_rateTree.AVL_rangeQueryRate(Avl_rateTree, choose1, choose2);
			}
		}

		break;

		case 4:
		{
			cout << "Choose which entry do you want to delete: ";
			cin >> c2;

			if (c2 == "a")
			{
				string choose;
				cout << "Enter the ID: ";
				cin >> choose;
				Avl_idTree.AVL_deleteQueryID(Avl_idTree, choose);
				Avl_idTree.deleteNode(choose, Avl_idTree.getroot());
				a_idfile.open("AVL_ID.txt", ios::trunc);
				a_idfile.close();
				a_idfile.open("AVL_ID.txt");
				Avl_idTree.AVLwritefile(Avl_idTree.getroot(), a_idfile);
				idfile.close();
			}
			if (c2 == "b")
			{
				string choose;
				cout << "Enter the Year: ";
				cin >> choose;
				Avl_yearTree.AVL_deleteQueryYear(Avl_yearTree, choose);
				Avl_yearTree.deleteNode(choose, Avl_yearTree.getroot());
				a_yearfile.open("AVL_YEARS.txt", ios::trunc);
				a_yearfile.close();
				a_yearfile.open("AVL_YEARS.txt");
				Avl_yearTree.AVLwritefile(Avl_yearTree.getroot(), a_yearfile);
				a_yearfile.close();
			}

			if (c2 == "c")
			{
				string choose;
				cout << "Enter the state: ";
				cin >> choose;
				Avl_stateTree.AVL_deleteQueryState(Avl_stateTree, choose);
				Avl_stateTree.deleteNode(choose, Avl_stateTree.getroot());
				a_statefile.open("AVL_STATE.txt", ios::trunc);
				a_statefile.close();
				a_statefile.open("AVL_STATE.txt");
				Avl_stateTree.AVLwritefile(Avl_stateTree.getroot(), a_statefile);
				a_statefile.close();
			}
			if (c2 == "d")
			{
				string choose;
				cout << "Enter the number of deaths: ";
				cin >> choose;
				Avl_deathsTree.AVL_deleteQueryDeath(Avl_deathsTree, choose);
				Avl_deathsTree.deleteNode(choose, Avl_deathsTree.getroot());
				a_deathfile.open("AVL_DEATH.txt", ios::trunc);
				a_deathfile.close();
				a_deathfile.open("AVL_DEATHStxt");
				Avl_deathsTree.AVLwritefile(Avl_deathsTree.getroot(), a_deathfile);
				a_deathfile.close();
			}
			if (c2 == "e")
			{
				string choose;
				cout << "Enter the rate: ";
				cin >> choose;
				Avl_rateTree.AVL_deleteQueryRate(Avl_rateTree, choose);
				Avl_rateTree.deleteNode(choose, Avl_rateTree.getroot());
				a_ratefile.open("AVL_RATES.txt", ios::trunc);
				a_ratefile.close();
				a_ratefile.open("AVL_RATES.txt");
				Avl_rateTree.AVLwritefile(Avl_rateTree.getroot(), a_ratefile);
				a_ratefile.close();
			}
		}
		break;

		case 5:
		{
			cout << "Choose which entry do you want to update: ";
			cin >> c2;

			if (c2 == "a")
			{
				string choose1, choose2;
				cout << "(Enter two values) Enter the IDs:  ";
				cin >> choose1 >> choose2;
				Avl_idTree.AVL_updateQueryID(Avl_idTree, choose1, choose2);
				Avl_idTree.UpdateNode(Avl_idTree.getroot(), choose1, choose2);
				a_idfile.open("AVL_ID.txt", ios::trunc);
				a_idfile.close();
				a_idfile.open("AVL_ID.txt");
				Avl_idTree.AVLwritefile(Avl_idTree.getroot(), a_idfile);
				idfile.close();
			}
			if (c2 == "b")
			{
				string choose1, choose2;
				cout << "(Enter two values) Enter the Years: ";
				cin >> choose1 >> choose2;
				Avl_yearTree.AVL_updateQueryYear(Avl_yearTree, choose1, choose2);
				Avl_yearTree.UpdateNode(Avl_yearTree.getroot(), choose1, choose2);
				a_yearfile.open("AVL_YEARS.txt", ios::trunc);
				a_yearfile.close();
				a_yearfile.open("AVL_YEARS.txt");
				Avl_yearTree.AVLwritefile(Avl_yearTree.getroot(), a_yearfile);
				a_yearfile.close();
			}
			if (c2 == "c")
			{
				string choose1, choose2;
				cout << "(Enter two values) Enter the states: ";
				cin >> choose1 >> choose2;
				Avl_stateTree.AVL_updateQueryState(Avl_stateTree, choose1, choose2);
				Avl_stateTree.UpdateNode(Avl_stateTree.getroot(), choose1, choose2);
				a_statefile.open("AVL_STATE.txt", ios::trunc);
				a_statefile.close();
				a_statefile.open("AVL_STATE.txt");
				Avl_stateTree.AVLwritefile(Avl_stateTree.getroot(), a_statefile);
				a_statefile.close();
			}
			if (c2 == "d")
			{
				string choose1, choose2;
				cout << "(Enter two values) Enter the number of deaths: ";
				cin >> choose1 >> choose2;
				Avl_deathsTree.AVL_updateQueryDeath(Avl_deathsTree, choose1, choose2);
				a_deathfile.open("AVL_DEATH.txt", ios::trunc);
				a_deathfile.close();
				a_deathfile.open("AVL_DEATHStxt");
				Avl_deathsTree.AVLwritefile(Avl_deathsTree.getroot(), a_deathfile);
				a_deathfile.close();

			}
			if (c2 == "e")
			{
				string choose1, choose2;
				cout << "(Enter two values) Enter the rates: ";
				cin >> choose1 >> choose2;
				Avl_rateTree.AVL_updateQueryRate(Avl_rateTree, choose1, choose2);
				Avl_rateTree.UpdateNode(Avl_rateTree.getroot(), choose1, choose2);
				a_ratefile.open("AVL_RATES.txt", ios::trunc);
				a_ratefile.close();
				a_ratefile.open("AVL_RATES.txt");
				Avl_rateTree.AVLwritefile(Avl_rateTree.getroot(), a_ratefile);
				a_ratefile.close();

			}
		}
		break;

		}

		cout << "\n\nDo you want to perform again?";
		cin >> con;


	} while (con == 'Y' || con == 'y');
}
void menuRB()
{
	int c1;   // number
	string c2;  // alphabets
	string c3;  //roman
	char con; // yes or no

	do
	{
		cout << "\nWhich operation do you want to perform:\n";
		cout << "1. Start\n"
			<< "a. ID\t\tb.Year\t\tc.Cause\n"
			<< "d.State\t\te.Deaths\tf.Rate\n\n";
		cout << "2. Read from file\n"
			<< "a. ID\t\tb.Year\t\tc.Cause\n"
			<< "d.State\t\te.Deaths\tf.Rate\n\n";
		cout << "3. Search Query\n"
			"a. ID\t\tb.Year\t\t"
			<< "c.State\nd.Deaths\te.Rate\n\n";
		cout << "4. Range Query\n"
			"a. ID\t\tb.Year\t\t"
			<< "c.State\nd.Deaths\te.Rate\n\n";
		cout << "5. Delete Query\n"
			<< "a. ID\t\tb.Year\t\t"
			<< "c.State\nd.Deaths\te.Rate\n\n";
		cout << "6. Update Query\n"
			<< "a. ID\t\tb.Year\t\t"
			<< "c.State\nd.Deaths\te.Rate\n\n";
		cout << "7.BONUS\n"
			<< "a.Search ID where STATE\t\tb.Search YEAR where STATE\n"
			<< "c.Delete ID where STATE\t\td.Delete YEAR where STATE\n\n";

		cout << "\nChoose operation: ";
		cin >> c1;
		while (c1 < 1 || c1 > 7)
		{
			cout << "Enter again\n";
			cin >> c1;
		}


		switch (c1)
		{
		case 1:
		{
			//cout << "Choose tree type: ";
			//cin >> c2;
			/*if (c2 == "a")
			{*/
			cout << "Choose the field: ";
			cin >> c3;
			RB(c3, "1");

			//}
		}
		break;

		case 2:
		{
			//cout << "Choose tree type: ";
			//cin >> c2;
			/*if (c2 == "a")
			{*/
			cout << "Choose the field: ";
			cin >> c3;
			RB(c3, "2");
			//}
		}
		break;

		case 3:
		{
			cout << "Choose the field you want to search for: ";
			cin >> c2;
			if (c2 == "c")
			{
				string choose;
				cout << "Select a state: ";
				cin >> choose;
				fstream search;


				stateTree.selectQueryState(stateTree, choose);
			}

			if (c2 == "a")
			{
				string choose;
				cout << "Select an ID: ";
				cin >> choose;
				idTree.selectQueryID(idTree, choose);
			}

			if (c2 == "b")
			{
				string choose;
				cout << "Select a year: ";
				cin >> choose;
				yearTree.selectQueryYear(yearTree, choose);
			}

			if (c2 == "e")
			{
				string choose;
				cout << "Select rate: ";
				cin >> choose;
				rateTree.selectQueryRate(rateTree, choose);
			}

			if (c2 == "f")
			{
				string choose;
				cout << "Select number of deaths: ";
				cin >> choose;
				deathsTree.selectQueryDeath(deathsTree, choose);
			}
		}
		break;

		case 4:
		{
			cout << "Choose the field you want to search for: ";
			cin >> c2;

			if (c2 == "a")
			{
				string choose1, choose2;
				cout << "(Enter two numbers) Select the range: ";
				cin >> choose1 >> choose2;
				idTree.rangeQueryID(idTree, choose1, choose2);
			}

			if (c2 == "b")
			{
				string choose1, choose2;
				cout << "(Enter two numbers) Select the range: ";
				cin >> choose1 >> choose2;
				yearTree.rangeQueryYEAR(yearTree, choose1, choose2);
			}

			if (c2 == "c")
			{
				string choose1, choose2;
				cout << "(Enter two numbers) Select the range: ";
				cin >> choose1 >> choose2;
				deathsTree.rangeQueryDEATHS(deathsTree, choose1, choose2);
			}

			if (c2 == "d")
			{
				string choose1, choose2;
				cout << "(Enter two numbers) Select the range: ";
				cin >> choose1 >> choose2;
				rateTree.rangeQueryRATE(rateTree, choose1, choose2);
			}
		}

		break;

		case 5:
		{
			cout << "Choose which entry do you want to delete: ";
			cin >> c2;

			if (c2 == "a")
			{
				string choose;
				cout << "Enter the ID: ";
				cin >> choose;
				idTree.deleteQueryID(idTree, choose);
				idTree.deleteNode(choose);
				idfile.open("ID.txt", ios::trunc);
				idfile.close();
				idfile.open("ID.txt");
				idTree.writefile(idTree.getroot(), idfile);
				idfile.close();
			}
			if (c2 == "b")
			{
				string choose;
				cout << "Enter the Year: ";
				cin >> choose;
				yearTree.deleteQueryYear(yearTree, choose);
				yearTree.deleteNode(choose);
				yearfile.open("YEARS.txt");
				yearTree.writefile(yearTree.getroot(), yearfile);
				yearfile.close();
			}

			if (c2 == "c")
			{
				string choose;
				cout << "Enter the state: ";
				cin >> choose;
				stateTree.deleteQueryState(stateTree, choose);
				stateTree.deleteNode(choose);
				statefile.open("STATE.txt");
				stateTree.writefile(stateTree.getroot(), statefile);
				statefile.close();
			}
			if (c2 == "d")
			{
				string choose;
				cout << "Enter the number of deaths: ";
				cin >> choose;
				deathsTree.deleteQueryDeath(deathsTree, choose);
				deathsTree.deleteNode(choose);
				deathfile.open("DEATHS.txt");
				deathsTree.writefile(deathsTree.getroot(), deathfile);
				deathfile.close();
			}
			if (c2 == "e")
			{
				string choose;
				cout << "Enter the rate: ";
				cin >> choose;
				rateTree.deleteQueryRate(rateTree, choose);
				rateTree.deleteNode(choose);
				ratefile.open("RATES.txt");
				rateTree.writefile(rateTree.getroot(), ratefile);
				ratefile.close();
			}
		}
		break;

		case 6:
		{
			cout << "Choose which entry do you want to update: ";
			cin >> c2;

			if (c2 == "a")
			{
				string choose1, choose2;
				cout << "(Enter two values) Enter the IDs:  ";
				cin >> choose1 >> choose2;
				idTree.updateQueryID(idTree, choose1, choose2);
				idTree.UpdateNode(idTree.getroot(), choose1, choose2);
				idfile.open("ID.txt");
				idTree.writefile(idTree.getroot(), idfile);
				idfile.close();
			}
			if (c2 == "b")
			{
				string choose1, choose2;
				cout << "(Enter two values) Enter the Years: ";
				cin >> choose1 >> choose2;
				yearTree.updateQueryYear(yearTree, choose1, choose2);
				yearTree.UpdateNode(yearTree.getroot(), choose1, choose2);
				yearfile.open("YEARS.txt");
				yearTree.writefile(yearTree.getroot(), yearfile);
				yearfile.close();
			}
			if (c2 == "c")
			{
				string choose1, choose2;
				cout << "(Enter two values) Enter the states: ";
				cin >> choose1 >> choose2;
				stateTree.updateQueryState(stateTree, choose1, choose2);
				stateTree.UpdateNode(stateTree.getroot(), choose1, choose2);
				statefile.open("STATE.txt");
				stateTree.writefile(stateTree.getroot(), statefile);
				statefile.close();
			}
			if (c2 == "d")
			{
				string choose1, choose2;
				cout << "(Enter two values) Enter the number of deaths: ";
				cin >> choose1 >> choose2;
				deathsTree.updateQueryDeath(deathsTree, choose1, choose2);
				deathsTree.UpdateNode(deathsTree.getroot(), choose1, choose2);
				deathfile.open("DEATHS.txt");
				deathsTree.writefile(deathsTree.getroot(), deathfile);
				deathfile.close();
			}
			if (c2 == "e")
			{
				string choose1, choose2;
				cout << "(Enter two values) Enter the rates: ";
				cin >> choose1 >> choose2;
				rateTree.updateQueryRate(rateTree, choose1, choose2);
				rateTree.UpdateNode(rateTree.getroot(), choose1, choose2);
				ratefile.open("RATES.txt");
				rateTree.writefile(rateTree.getroot(), ratefile);
				ratefile.close();
			}
		}
		break;

		case 7:
		{
			cout << "Which bonus operation do you want to do? ";
			cin >> c2;
			if (c2 == "a")
			{
				string choose1, choose2;
				cout << "Show id where state: ";
				cin >> choose1 >> choose2;
				stateTree.Bonus_idwherestate(stateTree, choose1, choose2);
			}

			if (c2 == "b")
			{
				string choose1, choose2;
				cout << "Show year where state: ";
				cin >> choose1 >> choose2;
				stateTree.Bonus_yearwherestate(stateTree, choose1, choose2);
			}

			if (c2 == "c")
			{
				string choose1, choose2;
				cout << "Delete id where state: ";
				cin >> choose1 >> choose2;
				stateTree.bonusdel_idwherestate(stateTree, choose1, choose2);
			}

			if (c2 == "d")
			{
				string choose1, choose2;
				cout << "Delete year where state: ";
				cin >> choose1 >> choose2;
				stateTree.bonusdel_yearwherestate(stateTree, choose1, choose2);
			}
		}
		break;

		}

		cout << "\n\nDo you want to perform again?";
		cin >> con;


	} while (con == 'Y' || con == 'y');


}
BTree<int> B_idTree(12);
//fstream idfile("B_ID.txt");

BTree<int>B_yearTree(7);
//fstream yearfile("B_YEARS.txt");

BTree<string> B_causeTree(7);
//fstream causefile("B_CAUSES.txt");

BTree<string> B_stateTree(7);
//fstream statefile("B_STATES.txt");

BTree<int>B_deathsTree(7);
//fstream deathfile("B_DEATHS.txt");

BTree<float> B_rateTree(7);
//fstream ratefile("B_RATES.txt");

void B(string cb)
{
	//BTree<string> B_idTree(7);
	fstream idfile("B_ID.txt");

	//BTree<string>B_yearTree(10);
	fstream yearfile("B_YEARS.txt");

	//BTree<string> B_causeTree(10);
	fstream causefile("B_CAUSES.txt");

	//BTree<string> B_stateTree(10);
	fstream statefile("B_STATES.txt");

	//BTree<string>B_deathsTree(7);
	fstream deathfile("B_DEATHS.txt");

	//BTree<string> B_rateTree(10);
	fstream ratefile("B_RATES.txt");

	string id;
	string year;
	string cause1a;
	string cause2;
	string fcause;
	string state;
	string deaths;
	string rate;


	string path = "NCHS_-_Leading_Causes_of_Death__United_States_1.csv";
	int i;
	ifstream inFile;
	inFile.open(path);

	if (inFile.is_open())
	{
		cout << "File has been opened" << endl;
	}
	else
	{
		cout << "NO FILE HAS BEEN OPENED" << endl;
	}

	int num = 25;
	//int y = 1;;
	while (!inFile.eof() && num != 0)
	{
		if (num != 25)
		{
			getline(inFile, id, ',');
			cout << "id: " << id << endl;
			getline(inFile, year, ',');
			cout << "year: " << year << endl;
			getline(inFile, cause1a, ',');
			getline(inFile, cause2, ',');
			getline(inFile, state, ',');
			getline(inFile, deaths, ',');
			getline(inFile, rate, '\n');


			fcause = cause1a + cause2;

			string y = id;

			int x = stoi(id);
			int ye = stoi(year);
			int de = stoi(deaths);
			float ra = stof(rate);

			if (cb == "a")
			{
				idfile.open("B_ID.txt");

				B_idTree.Binsert(B_idTree.getroot(), x, idfile, y, path);
				idfile.close();

			}
			if (cb == "b")
			{
				yearfile.open("B_YEAR.txt");

				B_yearTree.Binsert(B_yearTree.getroot(), ye, yearfile, y, path);
				yearfile.close();
			}
			if (cb == "c")
			{
				causefile.open("B_CAUSE.txt");
				B_causeTree.Binsert(B_causeTree.getroot(), fcause, causefile, y, path);
				causefile.close();
			}
			if (cb == "d")
			{
				statefile.open("B_STATES.txt");
				B_stateTree.Binsert(B_stateTree.getroot(), state, statefile, y, path);
				statefile.close();
			}
			if (cb == "e")
			{

				deathfile.open("B_DEATHS.txt");
				B_deathsTree.Binsert(B_deathsTree.getroot(), de, deathfile, y, path);
				idfile.close();
			}
			if (cb == "f")
			{

				ratefile.open("B_RATES.txt");
				B_rateTree.Binsert(B_rateTree.getroot(), ra, ratefile, y, path);
				ratefile.close();
			}
		}

		else {
			getline(inFile, id, ',');
			getline(inFile, year, ',');
			getline(inFile, cause1a, ',');
			getline(inFile, cause2, ',');
			getline(inFile, state, ',');
			getline(inFile, deaths, ',');
			getline(inFile, rate, '\n');
		}

		num--;
	}

	B_idTree.inorder();
	//B_causeTree.inorder();
	//B_yearTree.inorder();
	//B_stateTree.inorder();
	B_deathsTree.inorder();
	B_rateTree.inorder();
	//idfile.open("B_ID.txt");
	//B_idTree.writeTree(B_idTree.getroot(), idfile);
	//inFile.close();
	idfile.close();
	yearfile.close();
	causefile.close();
	statefile.close();
	ratefile.close();

}

void menuB() {

	int c1;   // number
	string c2;  // alphabets
	string c3;  //roman
	char con; // yes or no

	do {

		cout << "\nWhich operation do you want to perform:\n";
		cout << "1. Start\n"
			<< "a. ID\t\tb.Year\t\tc.Cause\n"
			<< "d.State\t\te.Deaths\tf.Rate\n\n";
		cout << "2. Read from file\n"
			<< "a. ID\t\tb.Year\t\tc.Cause\n"
			<< "d.State\t\te.Deaths\tf.Rate\n\n";
		cout << "3. Search Query\n"
			<< "a.ID\t\tb.Year\t\tc.State\n"
			<< "d.Deaths\te.Rate\n\n";
		cout << "4. Range Query\n"
			<< "a.ID\t\tb.Years\t\tc.Deaths\n"
			<< "d.Rate\n\n";
		cout << "5. Delete Query\n"
			<< "a.ID\t\tb.Year\t\tc.State\n"
			<< "d.Deaths\te.Rate\n\n";
		cout << "6. Update Query\n"
			<< "a.ID\t\tb.Year\t\tc.State\n"
			<< "d.Deaths\te.Rate\n\n";
		cout << "7.BONUS\n"
			<< "a.Search ID where STATE\t\tb.Search YEAR where STATE\n"
			<< "c.Delete ID where STATE\t\td.Delete YEAR where STATE\n\n";

		cout << "\nChoose operation: ";
		cin >> c1;
		while (c1 < 1 || c1 > 6)
		{
			cout << "Enter again\n";
			cin >> c1;
		}

		switch (c1) {

		case 1:
		{
			//cout << "Choose tree type: ";
			//cin >> c2;
			/*if (c2 == "a")
			{*/
			cout << "Choose the field: ";
			cin >> c3;
			B(c3);
		}
		break;

		case 3:
		{
			cout << "Choose which entry do you want to update: ";
			cin >> c2;

			if (c2 == "a")
			{
				int choose1;
				cout << "Enter an ID:  ";
				cin >> choose1;
				B_idTree.B_searchQueryID(B_idTree, choose1);
			}

			if (c2 == "b")
			{
				int choose1;
				cout << "Enter an Year:  ";
				cin >> choose1;
				B_yearTree.B_searchQueryYear(B_yearTree, choose1);
			}

			if (c2 == "c")
			{
				string choose1;
				cout << "Enter an State:  ";
				cin >> choose1;
				B_stateTree.B_searchQueryState(B_stateTree, choose1);
			}

			if (c2 == "d")
			{
				int choose1;
				cout << "Enter an Deaths:  ";
				cin >> choose1;
				B_deathsTree.B_searchQueryDeath(B_deathsTree, choose1);
			}

			if (c2 == "e")
			{
				float choose1;
				cout << "Enter an Float:  ";
				cin >> choose1;
				B_rateTree.B_searchQueryRate(B_rateTree, choose1);
			}
		}
		break;

		}
		cout << "\nDo you want to perform again? ";
		cin >> con;
	} while (con == 'y' || con == 'Y');
}
int main()
{

	string order;
	char c;

	cout << "\n\t\t\t\t\tDATABASE MANAGEMENT SYSTEM\n\n";
	do
	{
		cout << "CHOOSE A TREE TYPE\n I. RB\t\tII. B-Tree\t\tIII. AVL\n ";
		cin >> order;
		if (order == "I")
		{
			menuRB();
		}
		else if (order == "II")
		{
			menuB();
		}
		else
		{
			menuAVL();
		}

		cout << "\nDo you want to choose a new tree type? ";
		cin >> c;
	} while (c == 'y' || c == 'Y');

	cout << "THANK YOU! ";
	return 0;
}