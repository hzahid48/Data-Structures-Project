#pragma once
#include <iostream>
using namespace std;

template<class T>
class Node {
public:
	Node* next;
	T data;

	Node() {
		next = nullptr;
	}

	Node(T data) {
		this->data = data;
	}
};

//TASK 1---------------------------------------------------------------------------------------------
template<class T>
class Queue {
public:
	Node<T>* front;
	Node<T>* rear;

	Queue() {
		front = NULL;
		rear = NULL;
	}

	void enqueue(T data) {
		Node<T>* m = new Node<T>(data);
		if (isEmpty()) {
			front = rear = m;
		}

		else {
			rear->next = m;
			rear = rear->next;
		}
	}

	void dequeue() {
		if (isEmpty()) {
			cout << "queue is emplty\n";
		}

		else {
			Node<T>* temp = front;
			front = front->next;
			delete temp;
		}
	}

	T Front() {
		return front->data;
	}

	bool isEmpty() {
		if (front == NULL || rear == NULL) {
			return true;
		}

		return false;
	}
};
