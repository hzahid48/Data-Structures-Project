#include "queue.h"
#include "linkedlist.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

bool duplicate;

template <class T>
class BNode
{

    T* keys;   // array for keys
    string path;
    int order;  //order
    BNode<T>** BNode_child;    //array of child pointers
    int num_keys;   //num of keys
    bool leaf;

    SLinkedList<string> list;

public:

    BNode(int t1)
    {
        path = "";
        order = t1;
        leaf = false;
        num_keys = 0;
        keys = new T[2 * order - 1];
        BNode_child = new BNode<T> *[2 * order];

    }

    BNode(int t1, bool leaf1, string p)
    {
        order = t1;
        leaf = leaf1;
        path = p;
        keys = new T[2 * order - 1];
        BNode_child = new BNode<T> *[2 * order];

        num_keys = 0;
    }

    void insertlist(BNode<T>* n, string id, string path)
    {
        n->list.insert(id, path);
    }

    void insert_nf(BNode<T>* node, T data, string id, string p)    // inserting a new key rooted with node, node must be non full
    {
        int x = num_keys - 1;

        if (leaf == true)
        {
            while (x >= 0 && keys[x] > data)
            {
                keys[x + 1] = keys[x];
                x--;
            }

            if (keys[x] == data)
            {
                node->insertlist(node, id, p);
                //duplicate = true;
            }

            keys[x + 1] = data;
            num_keys = num_keys + 1;
        }
        else
        {
            while (x >= 0 && keys[x] > data)
                x--;


            if (keys[x] == data)
            {
                node->insertlist(node, id, p);
            }

            if (BNode_child[x + 1]->num_keys == 2 * order - 1)
            {
                split_child(x + 1, BNode_child[x + 1], p);

                if (keys[x + 1] < data)
                {
                    x++;
                }
            }
            BNode_child[x + 1]->insert_nf(node, data, id, p);
        }
    }

    void split_child(int z, BNode<T>* x, string p)     // split_child child x 
    {
        BNode<T>* newNode = new BNode<T>(x->order, x->leaf, p);
        newNode->num_keys = order - 1;

        for (int i = 0; i < order - 1; i++)
        {
            newNode->keys[i] = x->keys[i + order];
        }

        if (x->leaf == false)
        {
            for (int j = 0; j < order; j++)
                newNode->BNode_child[j] = x->BNode_child[j + order];
        }


        x->num_keys = order - 1;
        for (int i = num_keys; i >= z + 1; i--)
        {
            BNode_child[i + 1] = BNode_child[i];
        }


        BNode_child[z + 1] = newNode;

        for (int i = num_keys - 1; i >= z; i--)
        {
            keys[i + 1] = keys[i];
        }

        keys[z] = x->keys[order - 1];
        num_keys = num_keys + 1;
    }

    void inorder()
    {
        int i;
        for (i = 0; i < num_keys; i++)
        {
            if (leaf == false)
                BNode_child[i]->inorder();
            cout << " " << keys[i];
        }

        if (leaf == false)
            BNode_child[i]->inorder();
    }

    void writeinorder(fstream& file)
    {
        int i;

        /*if (node)
        {
            for (i = 0; i < node->order - 2; i++) {
                inorder(node->BNode_child[i]);
                file << node->keys[i];
                file << endl;
            }
            inorder(node->BNode_child[node->num_keys - 1]);
            file << endl;
        }*/
        //SLinkedList<string> tem;
       
        for (i = 0; i < num_keys; i++)
        {
            //tem = BNode_child[i]->list;
            if (leaf == false)
            {
                file << "\n";
                BNode_child[i]->writeinorder(file);
               /* while (tem.head != NULL)
                {
                    file << "T: " << tem.head->data;
                    file << tem.head->path;
                    file << endl;
                    tem.head = tem.head->next;
                }*/
                file << "\n";
                file << "," << keys[i]<<" P: "<<path;
                
                file << "\n";
            }

            else
            {
                file << "," << keys[i] << " P: " << path;
            }
            cout << " " << keys[i];
        }

        if (leaf == false) {
            //tem = BNode_child[i]->list;
            BNode_child[i]->writeinorder(file);
            file << keys[i] << " ";
           /* while (tem.head != NULL)
            {
                file << "T: " << tem.head->data;
                file << tem.head->path;
                file << endl;
                tem.head = tem.head->next;
            }*/
        }
    }

    void write(BNode<T>* node, fstream& file)
    {
        Queue<BNode<T>*> q;
        if (node == NULL)
        {
            return;
        }

        q.enqueue(node);
        int i = 0;
        while (!q.isEmpty() && i < num_keys)
        {
            BNode<T>* temp = q.Front();
            SLinkedList<string> tem = temp->list;

            file << "D: " << temp->keys[i] << endl;
            file << "P: " << temp->path << endl;

            while (tem.head != NULL)
            {
                file << "T: " << tem.head->data;
                file << tem.head->path;
                file << endl;
                tem.head = tem.head->next;
            }
            i++;
        }
    }

    BNode<T>* search(int k)     //returns the node
    {
        int index = 0;
        while (index < num_keys && k > keys[index])
            ++index;
        //return index;

        if (keys[index] == k)
            return this;

        if (leaf == true)
            return NULL;

        return BNode_child[index]->search(k);
    }

    int find_index(int k)   //returns the index
    {
        int index = 0;
        while (index < num_keys && keys[index] < k)
        {
            index++;
        }
        return index;
    }

    void Deletion(T k)
    {
        int index = find_index(k);

        if (index < num_keys && keys[index] == k)
        {
            if (leaf)
                deleteLeaf(index);
            else
                deleteInternal(index);
        }
        else
        {
            if (leaf)
            {
                cout << "The key " << k << "does not exist\n";
                return;
            }

            bool flag = ((index == num_keys) ? true : false);

            if (BNode_child[index]->num_keys < order)
                fill(index);

            if (flag && index > num_keys)
                BNode_child[index - 1]->Deletion(k);
            else
                BNode_child[index]->Deletion(k);
        }
        return;
    }

    // Remove from the leaf
    void deleteLeaf(int index)
    {
        for (int i = index + 1; i < num_keys; ++i)
        {
            keys[i - 1] = keys[i];
        }
        num_keys--;
        return;
    }

    void deleteInternal(int index)
    {
        int k = keys[index];

        if (BNode_child[index]->num_keys >= order)
        {
            int predecessor = Predecessor(index);
            keys[index] = predecessor;
            BNode_child[index]->Deletion(predecessor);
        }

        else if (BNode_child[index + 1]->num_keys >= order)
        {
            int successor = Successor(index);
            keys[index] = successor;
            BNode_child[index + 1]->Deletion(successor);
        }

        else
        {
            merge_keys(index);
            BNode_child[index]->Deletion(k);
        }

    }


    int Predecessor(int index)
    {
        BNode<T>* cur = BNode_child[index];
        while (!cur->leaf)
        {
            cur = cur->BNode_child[cur->num_keys];
        }
        return cur->keys[cur->num_keys - 1];
    }

    int Successor(int index)
    {
        BNode<T>* cur = BNode_child[index + 1];
        while (!cur->leaf)
        {
            cur = cur->BNode_child[0];
        }
        return cur->keys[0];
    }

    void fill(int index)    //fill child with order - 1 keys
    {
        if (index != 0 && BNode_child[index - 1]->num_keys >= order)
        {
            borrowPrev(index);
        }

        else if (index != num_keys && BNode_child[index + 1]->num_keys >= order)
        {
            borrowNext(index);
        }

        else
        {
            if (index != num_keys)
            {
                merge_keys(index);
            }
            else
            {
                merge_keys(index - 1);
            }
        }

    }

    void borrowPrev(int index)    // borrow from prev
    {
        BNode<T>* BNode_child = BNode_child[index];
        BNode<T>* sibling = BNode_child[index - 1];

        for (int i = BNode_child->num_keys - 1; i >= 0; --i)
        {
            BNode_child->keys[i + 1] = BNode_child->keys[i];
        }

        if (!BNode_child->leaf)
        {
            for (int i = BNode_child->num_keys; i >= 0; --i)
                BNode_child->BNode_child[i + 1] = BNode_child->BNode_child[i];
        }

        BNode_child->keys[0] = keys[index - 1];

        if (!BNode_child->leaf)
        {
            BNode_child->BNode_child[0] = sibling->BNode_child[sibling->num_keys];
        }

        keys[index - 1] = sibling->keys[sibling->num_keys - 1];

        BNode_child->num_keys += 1;
        sibling->num_keys -= 1;
    }

    void borrowNext(int index)           //borrow from next
    {
        BNode<T>* BNode_child = BNode_child[index];
        BNode<T>* sibling = BNode_child[index + 1];

        BNode_child->keys[(BNode_child->num_keys)] = keys[index];

        if (!(BNode_child->leaf))
        {
            BNode_child->BNode_child[(BNode_child->num_keys) + 1] = sibling->BNode_child[0];
        }

        keys[index] = sibling->keys[0];

        for (int i = 1; i < sibling->num_keys; ++i)
        {
            sibling->keys[i - 1] = sibling->keys[i];
        }

        if (!sibling->leaf)
        {
            for (int i = 1; i <= sibling->num_keys; ++i)
                sibling->BNode_child[i - 1] = sibling->BNode_child[i];
        }

        BNode_child->num_keys += 1;
        sibling->num_keys -= 1;

    }

    void merge_keys(int index)
    {
        BNode<T>* BNode_child = BNode_child[index];
        BNode<T>* sibling = BNode_child[index + 1];

        BNode_child->keys[order - 1] = keys[index];

        for (int i = 0; i < sibling->num_keys; ++i)
        {
            BNode_child->keys[i + order] = sibling->keys[i];
        }

        if (!BNode_child->leaf)
        {
            for (int i = 0; i <= sibling->num_keys; ++i)
                BNode_child->BNode_child[i + order] = sibling->BNode_child[i];
        }

        for (int i = index + 1; i < num_keys; ++i)
        {
            keys[i - 1] = keys[i];
        }

        for (int i = index + 2; i <= num_keys; ++i)
        {
            BNode_child[i - 1] = BNode_child[i];
        }

        BNode_child->num_keys += sibling->num_keys + 1;
        num_keys--;

        delete (sibling);
    }

    void LevelOrder()
    {
        Queue<BNode<T>*> q;

        q.enqueue(this);
        BNode<T>* order = q.Front();
        int count = order->num_keys + 2;

        while (count != 0)
        {
            //cout << "count:" << count << endl;
            BNode<T>* temp = q.Front();
            q.dequeue();

            int i;
            int j = temp->num_keys;
            for (i = 0; i < j; i++)
            {
                if (leaf == false)
                    q.enqueue(temp->BNode_child[i]);
                cout << " " << temp->keys[i];
            }

            if (leaf == false)
                q.enqueue(temp->BNode_child[i]);
            count--;
        }

    }

    template <class T> friend class BTree;
};

template <class T>
class BTree
{
    BNode<T>* root;
    int order;

public:
    BTree(int temp)
    {
        root = NULL;
        order = temp;
    }

    void inorder()
    {
        if (root != NULL)
            root->inorder();
    }

    BNode<T>* search(T k)
    {
        if (root == NULL)
        {
            return NULL;
        }
        else
            root->search(k);
    }

    //void writefile(BNode<T>* p, fstream& file)
    //{
    //    //file.open(filename);
    //    Queue<BNode<T>*> q;
    //    if (p == NULL) {
    //        return;
    //    }

    //    q.enqueue(p);

    //    while (!q.isEmpty()) {
    //        BNode<T>* temp = q.Front();
    //        SLinkedList<string> tem = temp->list;

    //        file << temp->d << temp->data << endl;
    //        file << temp->p << temp->path << endl;
    //        while (tem.head != NULL) {
    //            file << temp->L;
    //            file << tem.head->data << ",";
    //            file << tem.head->path;
    //            file << temp->space << endl;
    //            tem.head = tem.head->next;
    //        }

    //        cout << endl;
    //        file << temp->c << temp->color << endl;
    //        q.dequeue();
    //        if (temp->RBNode_left != NULL) {
    //            file << temp->l << temp->RBNode_left->data << endl;
    //            q.enqueue(temp->RBNode_left);
    //        }

    //        if (temp->BNode_right != NULL) {
    //            file << temp->r << temp->RBNode_right->data << endl;
    //            q.enqueue(temp->RBNode_right);
    //        }

    //        file << temp->end << endl;

    //    }
    //}

    void Binsert(BNode<T>* node, T k, fstream& file, string id, string p)
    {
        if (root == NULL)
        {
            root = new BNode<T>(order, true, p);
            root->keys[0] = k;
            root->num_keys = 1;
        }
        else
        {
            if (root->num_keys == 2 * order - 1)
            {
                BNode<T>* s = new BNode<T>(order, false, p);

                s->BNode_child[0] = root;
                s->split_child(0, root, p);

                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->BNode_child[i]->insert_nf(node, k, id, p);
                root = s;
            }
            else
                root->insert_nf(node, k, id, p);
        }

        file.open("B_ID.txt", ios::trunc);
        file.close();

        file.open("B_ID.txt");
        write(root, file);
        file.close();
    }



    void LevelOrder()
    {
        if (root != NULL)
            root->LevelOrder();
    }

    void Deletion(T k)
    {
        if (!root)
        {
            cout << "The tree is empty\n";
            return;
        }

        root->Deletion(k);

        if (root->num_keys == 0)
        {
            BNode<T>* tmp = root;
            if (root->leaf)
            {
                root = NULL;
            }
            else
            {
                root = root->BNode_child[0];
            }

            delete tmp;
        }
    }

    BNode<T>* getroot()
    {
        return root;
    }

    void writeTree(BNode<T>* root, fstream& file) {

        if (root != NULL) {
            file << "K:";
            root->writeinorder(file);
        }

    }

    void write(BNode<T>* root, fstream& file)
    {
        if (root != NULL) {
            root->write(root, file);
        }
    }

    

    string searchPath(BNode<T>* node, T data)
    {
        if (node == NULL)
        {
            return "";
        }
        else
        {
            BNode<T>* temp = search(data);
            return temp->path;
        }
    }

    void B_searchQueryYear(BTree<T> tree, T data)
    {
        string address = searchPath(tree.getroot(), data);               //path for excel
        ifstream file;
        if (address == "0") {
            return;
        }

        cout << "PATH: " << address << endl;
        file.open(address);

        ofstream search;
        search.open("BSearch_Query.csv", ios::trunc);
        search.close();

        search.open("BSearch_Query.csv", ios::app);
        search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";
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
        while (!file.eof() )
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

                int y = stoi(year);
                if (data == y)
                {

                    search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

                    cout << "ID: " << id << " ";
                    cout << "year: " << year << " ";
                    cout << "cause: " << cause1a << ", " << cause2 << " ";
                    cout << "state: " << state << " ";
                    cout << "deaths: " << deaths << " ";
                    cout << "rate: " << rate << endl;

                    //string cause1 = cause1a + "," + cause1b;

                    
                }
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

    void B_searchQueryRate(BTree<T> tree, T data)
    {
        //cout << "DATA: " << data;
        string address = "NCHS_-_Leading_Causes_of_Death__United_States_1.csv";              //path for excel
        ifstream file;
        if (address == "0") {
            return;
        }

        

        cout << "PATH: " << address << endl;
        file.open(address);

        ofstream search;
        search.open("BSearch_Query.csv", ios::trunc);
        search.close();

        search.open("BSearch_Query.csv", ios::app);
        search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";
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
                
                float y = stof(rate);
                if (data == y)
                {

                    search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

                    cout << "ID: " << id << " ";
                    cout << "year: " << year << " ";
                    cout << "cause: " << cause1a << ", " << cause2 << " ";
                    cout << "state: " << state << " ";
                    cout << "deaths: " << deaths << " ";
                    cout << "rate: " << rate << endl;

                    //string cause1 = cause1a + "," + cause1b;


                }
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

    void B_searchQueryID(BTree<T> tree, T data)
    {
        string address = searchPath(tree.getroot(), data);               //path for excel
        ifstream file;
        if (address == "0") {
            return;
        }

        cout << "PATH: " << address << endl;
        file.open(address);

        ofstream search;
        search.open("BSearch_Query.csv", ios::trunc);
        search.close();

        search.open("BSearch_Query.csv", ios::app);
        search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";
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

                int y = stoi(id);
                if (data == y)
                {

                    search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

                    cout << "ID: " << id << " ";
                    cout << "year: " << year << " ";
                    cout << "cause: " << cause1a << ", " << cause2 << " ";
                    cout << "state: " << state << " ";
                    cout << "deaths: " << deaths << " ";
                    cout << "rate: " << rate << endl;

                    //string cause1 = cause1a + "," + cause1b;


                }
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

    void B_searchQueryDeath(BTree<T> tree, T data)
    {
        string address = searchPath(tree.getroot(), data);               //path for excel
        ifstream file;
        if (address == "0") {
            return;
        }

        cout << "PATH: " << address << endl;
        file.open(address);

        ofstream search;
        search.open("BSearch_Query.csv", ios::trunc);
        search.close();

        search.open("BSearch_Query.csv", ios::app);
        search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";
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

                int y  = stoi(deaths);
                if (data == y)
                {

                    search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

                    cout << "ID: " << id << " ";
                    cout << "year: " << year << " ";
                    cout << "cause: " << cause1a << ", " << cause2 << " ";
                    cout << "state: " << state << " ";
                    cout << "deaths: " << deaths << " ";
                    cout << "rate: " << rate << endl;

                    //string cause1 = cause1a + "," + cause1b;


                }
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

    void B_searchQueryState(BTree<T> tree, T data)
    {
        string address = "NCHS_-_Leading_Causes_of_Death__United_States_1.csv";       //path for excel
        ifstream file;
        if (address == "0") {
            return;
        }

        cout << "PATH: " << address << endl;
        file.open(address);

        ofstream search;
        search.open("BSearch_Query.csv", ios::trunc);
        search.close();

        search.open("BSearch_Query.csv", ios::app);
        search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";
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

                //int y = stoi(deaths);
                if (data == state)
                {

                    search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

                    cout << "ID: " << id << " ";
                    cout << "year: " << year << " ";
                    cout << "cause: " << cause1a << ", " << cause2 << " ";
                    cout << "state: " << state << " ";
                    cout << "deaths: " << deaths << " ";
                    cout << "rate: " << rate << endl;

                    //string cause1 = cause1a + "," + cause1b;


                }
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


    void B_updateQueryState(BTree<T> tree, T old, T replace)
    {
        string address = "NCHS_-_Leading_Causes_of_Death__United_States_1.csv";       //path for excel
        ifstream file;
        if (address == "0") {
            return;
        }

        cout << "PATH: " << address << endl;
        file.open(address);

        ofstream search;
        search.open("BUpdate_Query.csv", ios::trunc);
        search.close();

        search.open("BUpdate_Query.csv", ios::app);
        search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";
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

                //int y = stoi(deaths);
                if (old == state)
                {

                    state = replace;
                }

                cout << "ID: " << id << " ";
                cout << "year: " << year << " ";
                cout << "cause: " << cause1a << ", " << cause2 << " ";
                cout << "state: " << state << " ";
                cout << "deaths: " << deaths << " ";
                cout << "rate: " << rate << endl;


                search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

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


    void B_updateQueryID(BTree<T> tree, T old, T replace)
    {
        string address = "NCHS_-_Leading_Causes_of_Death__United_States_1.csv";       //path for excel
        ifstream file;
        if (address == "0") {
            return;
        }

        cout << "PATH: " << address << endl;
        file.open(address);

        ofstream search;
        search.open("BUpdate_Query.csv", ios::trunc);
        search.close();

        search.open("BUpdate_Query.csv", ios::app);
        search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";
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

                int y = stoi(id);

                if (old == y)
                {
                    string c = to_string(replace);
                    id = c;
                }
                
                cout << "ID: " << id << " ";
                cout << "year: " << year << " ";
                cout << "cause: " << cause1a << ", " << cause2 << " ";
                cout << "state: " << state << " ";
                cout << "deaths: " << deaths << " ";
                cout << "rate: " << rate << endl;


                search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

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

    void B_updateQueryYear(BTree<T> tree, T old, T replace)
    {
        string address = "NCHS_-_Leading_Causes_of_Death__United_States_1.csv";       //path for excel
        ifstream file;
        if (address == "0") {
            return;
        }

        cout << "PATH: " << address << endl;
        file.open(address);

        ofstream search;
        search.open("BUpdate_Query.csv", ios::trunc);
        search.close();

        search.open("BUpdate_Query.csv", ios::app);
        search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";
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

                int y = stoi(year);
                if (old == y)
                {
                    string c = to_string(replace);
                    year = c;
                }

                
                cout << "ID: " << id << " ";
                cout << "year: " << year << " ";
                cout << "cause: " << cause1a << ", " << cause2 << " ";
                cout << "state: " << state << " ";
                cout << "deaths: " << deaths << " ";
                cout << "rate: " << rate << endl;


                search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

                //string cause1 = cause1a + "," + cause1b;


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

    void B_updateQueryDeath(BTree<T> tree, T old, T replace)
    {
        string address = "NCHS_-_Leading_Causes_of_Death__United_States_1.csv";       //path for excel
        ifstream file;
        if (address == "0") {
            return;
        }

        cout << "PATH: " << address << endl;
        file.open(address);

        ofstream search;
        search.open("BUpdate_Query.csv", ios::trunc);
        search.close();

        search.open("BUpdate_Query.csv", ios::app);
        search << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";
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

                int y = stoi(deaths);

                if (old == y)
                {
                    string c = to_string(replace);
                    deaths = c;
                    
                }

                cout << "ID: " << id << " ";
                cout << "year: " << year << " ";
                cout << "cause: " << cause1a << ", " << cause2 << " ";
                cout << "state: " << state << " ";
                cout << "deaths: " << deaths << " ";
                cout << "rate: " << rate << endl;


                search << id << "," << year << "," << cause1a << "," << cause2 << "," << state << "," << deaths << "," << rate << "\n";

                //string cause1 = cause1a + "," + cause1b;


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

    void B_deleteQueryState(BTree<T> tree, T key)
    {
        string address = "NCHS_-_Leading_Causes_of_Death__United_States_1.csv";
            //searchPath(tree.getroot(), key);               //path for excel
        ifstream file;
        if (address == "0")
        {
            return;
        }

        cout << "PATH: " << address << endl;
        file.open(address);

        ofstream del;
        del.open("BDelete_Query.csv", ios::trunc);
        del.close();

        del.open("BDelete_Query.csv", ios::app);
        del << "ID,Year,113 Cause Name,Cause Name,State,Deaths,Age-adjusted Death Rate,\n";

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

                //int y = stoi(year);

                while (key == state)
                {
                    getline(file, id, ',');
                    getline(file, year, ',');
                    getline(file, cause1a, ',');
                    getline(file, cause2, ',');
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


   /*~BTree()
    {
        removeTree(root);
    }

    void removeTree(BNode<T>* node)
    {
        
            if (node != NULL) 
            {
                removeTree(node->left);
                node->left == NULL;;
                removeTree(node->right);
                node->right == NULL;
                delete node;
            }
        
    }*/

    
};





