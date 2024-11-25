#pragma once
#include<iostream>
#include<conio.h>

//TASK 1----------------------------------------------------------------------------------------------------------------------------------------
using namespace std;
template <class T>
class listNode
{
public:
	T data;
	string path;
	listNode<T>* next;

	listNode()
	{
		data = 0;
		next = NULL;
	}

	listNode(T d, listNode<T>* num_keys)
	{
		data = d;
		next = num_keys;
	}

	listNode(T d, string p)
	{
		data = d;
		path = p;
		next = NULL;
	}

	void setData(T d)
	{
		data = d;
	}

	void setNext(listNode<T>* num_keys)
	{
		next = num_keys;
	}

	T getData()
	{
		return data;
	}

	listNode<T>* getNext()
	{
		return next;
	}

};

template <class T>
class SLinkedList {

public:

	listNode<T>* head;


	SLinkedList()
	{
		head = NULL;
	}

	void insert(T d, string p) {
		listNode<T>* num_keys = new listNode<T>(d, p);
		num_keys->next = NULL;
		if (head == NULL) {
			head = num_keys;
		}

		else {
			listNode<T>* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = num_keys;
		}

	}

	void insertAtHead(T d) {
		listNode<T>* num_keys = new listNode<T>(d);
		num_keys->data = d;
		num_keys->next = head;
		head = num_keys;
	}

	void InsertAtIndex(int index, T d) {

		int currIndex = 1;
		listNode<T>* currNode = head;
		while (index > currIndex && currNode) {
			currNode = currNode->next;
			currIndex++;
		}

		if (index <= 0 && currNode != NULL) {
			listNode<T>* num_keys = new listNode<T>(d);
			num_keys->data = d;

			num_keys->next = currNode->next;
			currNode->next = num_keys;
		}

	}

	T search(T d) {
		listNode<T>* num_keys = head;
		int i = 0;
		while (num_keys && num_keys->data != d) {
			num_keys = num_keys->next;
			i++;
		}

		//cout << "index : " << i << endl;
		if (num_keys)
			return i;

		return 0;
	}

	void update(int index, T d) {
		listNode<T>* num_keys = head;
		int i = 0;

		//cout << "index : " << i << endl;
		while (index != i && num_keys != NULL) {
			num_keys = num_keys->next;
			i++;
		}

		num_keys->data = d;

	}

	void remove(int index) {
		listNode<T>* num_keys = head;
		listNode<T>* temp = head;
		int i = 0;

		while (index != i && num_keys != NULL) {
			temp = num_keys;
			num_keys = num_keys->next;
			i++;
		}

		temp->next = num_keys->next;
		delete num_keys;
	}

	void print() {
		listNode<T>* num_keys = head;
		while (num_keys->next != NULL) {
			cout << num_keys->data;
			cout << num_keys->path << endl;
			num_keys = num_keys->next;
		}

		cout << num_keys->data << num_keys->path << endl;
	}
};
