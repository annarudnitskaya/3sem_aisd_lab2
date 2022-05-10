#pragma once
#include <iostream>
#include "queue.h"
#include <string>
#include <stdexcept>
using namespace std;
struct List_node
{
	int data;
	char symb;
	string code;
	List_node* Next;
	bool washere = false;

};

class List
{
private:
	List_node* Head;
	List_node* Tail;
	size_t sizeoflist;

public:
	List() {
		Head = nullptr;
		Tail = nullptr;
		sizeoflist = 0;
	}

	~List();

	void push_front(int data, char symb);

	void push_back(int data, char symb);

	void pop_back();

	void pop_front();

	void insert(int, size_t, char);

	int at(size_t);

	void remove(size_t);

	size_t get_size(); //

	void print_to_console();

	void clear();

	void set(size_t, int);

	bool isEmpty();

	void addfirstelement(int, char);

	void push_back_list(List&);

	List_node* get_pointer(size_t index);

	void insert_sorted(int data, char symb);

	void insert_list(List&, size_t);

	size_t separating(size_t index1, size_t index2, size_t sum) {
		List_node* current = Head;
		for (int i = 0; i < index1; i++)
			current = current->Next;

		size_t semi_sum = 0;

		size_t index3;
		for (index3 = index1; index3 <= index2; index3++) {
			semi_sum += current->data;
			if (semi_sum > sum / 2)
				break;
		}

		return index3;
	}

	size_t get_sizeofword()
	{
		size_t sizeofword = 0;
		List_node* current = Head;
		for (int i = 0; i < sizeoflist; i++) {
			sizeofword += current->data;
			current = current->Next;
		}
		return sizeofword;
	}

	List_node* get_head() {
		return Head;
	}

};

List::~List()
{
	while (Head != nullptr)
	{
		List_node* temp = Head->Next;
		delete Head;
		Head = temp;
	}

}

void List::addfirstelement(int data, char symb) {

	Head = new List_node;
	Head->data = data;
	Head->symb = symb;
	Head->Next = nullptr;
	Tail = Head;


}

void List::push_front(int data, char symb)
{
	List_node* temp = new List_node;
	temp->data = data;
	temp->symb = symb;
	if (sizeoflist == 0)
		addfirstelement(data, symb);

	temp->Next = Head;
	Head = temp;
	sizeoflist++;
}

void List::push_back(int data, char symb)  //adding a new 
{
	List_node* temp = new List_node;
	temp->data = data;
	temp->symb = symb;
	if (sizeoflist == 0)
		addfirstelement(data, symb);

	else {
		Tail->Next = temp;
		Tail = temp;
	}
	temp->Next = nullptr;
	sizeoflist++;
}

void List::pop_back() {   //deleting the last element 
	if (Head != Tail)
	{
		List_node* temp = Head;

		while (temp->Next != Tail)
			temp = temp->Next;

		List_node* temp2 = temp->Next;
		temp->Next = nullptr;
		Tail = temp;
		delete temp2;
		sizeoflist--;
	}

	else if (sizeoflist == 1)
	{
		clear();
	}

	else if (sizeoflist == 0)
		cout << endl << "The list is empty!" << endl;

}

void List::pop_front() {   //deleting the first element
	if (Head != Tail)
	{
		List_node* temp = Head;
		Head = temp->Next;
		delete temp;
		sizeoflist--;
	}

	else if (sizeoflist == 1)
	{
		clear();
	}

	else if (sizeoflist == 0)
		cout << endl << "The list is empty!" << endl;

}

void List::print_to_console()   //showing the list
{
	List_node* temp = Head;

	while (temp != nullptr)
	{
		cout << temp->code << " ";
		cout << temp->data << " ";
		if (temp->symb == ' ')
			cout << "_ ";
		else
			cout << temp->symb << " ";
		cout << " code: " << temp->code;
		cout << endl;
		temp = temp->Next;
	}
}

void List::clear() {   //clear all the list
	while (Head != nullptr) {
		List_node* temp = Head;
		Head = Head->Next;
		delete temp;
	}
	Head = nullptr;
	Tail = nullptr;
	sizeoflist = 0;
}

void List::insert(int data, size_t index, char symb) {   //inserting a node before a certain node
	if (index >= sizeoflist || index < 0)
		throw out_of_range("Incorrect index");

	else {
		List_node* temp = Head;
		List_node* newnode = new List_node;
		newnode->data = data;
		newnode->symb = symb;

		for (size_t i = 0; i < index - 1; i++)
			temp = temp->Next;

		newnode->Next = temp->Next;
		temp->Next = newnode;
		sizeoflist++;
	}
}

int List::at(size_t index) {   //getting data in a certain node
	if (index >= sizeoflist || index < 0)
	{
		throw out_of_range("Incorrect index");
	}

	else {
		List_node* current = Head;
		for (int i = 0; i < index; i++)
			current = current->Next;
		return current->data;
	}
}

void List::remove(size_t index) { //removing a certain node in the list
	List_node* temp1 = Head;
	if (index >= sizeoflist || index < 0)
	{
		throw out_of_range("Incorrect index");
	}

	else if (index == 0)
	{
		pop_front();
	}
	else if (index == sizeoflist - 1)
	{
		pop_back();
	}
	else {
		for (int i = 0; i < index - 1; i++)
			temp1 = temp1->Next;

		List_node* temp2 = temp1->Next;
		temp1->Next = temp2->Next;
		delete temp2;
		sizeoflist--;
	}
}

size_t List::get_size() {   //getting size of the list
	return sizeoflist;
}

void List::set(size_t index, int data) {  //changing data in certain node
	if (index >= sizeoflist || index < 0)
	{
		throw out_of_range("Incorrect index");
	}
	else {
		List_node* temp = Head;
		for (int i = 0; i < index; i++)
			temp = temp->Next;
		temp->data = data;
	}

}

bool List::isEmpty() {    //checking if the list is empty
	if (sizeoflist == 0)
		return true;
	else
		return false;
}

void List::push_back_list(List& scndlst) {  //adding one list to the end of another
	size_t counter = 1, sizeofscndlst = scndlst.get_size();
	List_node* cur = scndlst.Head;

	if (scndlst.isEmpty() != true) {
		while (counter <= sizeofscndlst) {
			push_back(cur->data, cur->symb);
			cur = cur->Next;
			counter++;
		}
	}
}

List_node* List::get_pointer(size_t index)
{
	if (index >= sizeoflist || index < 0)
	{
		throw out_of_range("Incorrect index");
	}

	else if (index == 0)
		return Head;

	else if (index == sizeoflist - 1)
		return Tail;

	else
	{
		List_node* temp = Head;
		int counter = 0;

		while (counter != index) {
			temp = temp->Next;
			counter++;
		}
		return temp;
	}
}

void List::insert_list(List& scndlst, size_t index) {
	if (index < 0 || index >= sizeoflist)
	{
		throw out_of_range("Incorrect index");
	}

	else if (index == sizeoflist - 1)
		push_back_list(scndlst);

	else {
		List_node* temp = scndlst.Head;
		size_t counter;
		for (counter = 0; counter < scndlst.sizeoflist; counter++)
		{
			insert(temp->data, index, temp->symb);
			temp = temp->Next;
			index++;
		}

	}

}

void List::insert_sorted(int data, char symb)
{
	if (sizeoflist == 0) {
		addfirstelement(data, symb);
		sizeoflist++;
	}


	else if (data <= Head->data) {
		push_front(data, symb);
	}

	else if (data >= Tail->data) {
		push_back(data, symb);
	}
	else {
		List_node* current;
		current = Head;
		for (int i = 0; i < sizeoflist; i++) {
			if (data < current->data) {
				insert(data, i, symb);
				return;
			}
			else if (data >= current->data)
				current = current->Next;
		}
	}
}
