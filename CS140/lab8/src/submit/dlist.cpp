//Jacob Isber
//Lab 8
//November 3rd

#include <iostream>
#include "dlist.hpp"
using namespace std;
	
	//Constcutor
	Dlist::Dlist() {
		sentinel = new Dnode;
		size = 0;
		sentinel->s = "";
		sentinel->flink = sentinel;
		sentinel->blink= sentinel;
	}
	
	//Copy constructor
	Dlist::Dlist(const Dlist &d) {
		sentinel = new Dnode;

		sentinel->s = "";
		sentinel->flink = sentinel;
		sentinel->blink = sentinel;
		size = 0;
		*this = d;

	}

	//Assignment overload, took this from his lecture notes.
	Dlist& Dlist::operator= (const Dlist &d) {
		Dlist tmp;
		Dnode *sn;
		Clear();

		sentinel = new Dnode;

		sentinel->s = "";
		sentinel->flink = sentinel;
		sentinel->blink = sentinel;
		size = 0;
	

		for(sn = d.Begin(); sn != d.End(); sn = sn->flink) tmp.Push_Back(sn->s);
		
		while(!tmp.Empty()) Push_Back(tmp.Pop_Front());
	
			return *this;

	}

//Destructor, deletes list and sentinel node
	Dlist::~Dlist() {
		Clear();
		delete sentinel;
	
	}

//Clears the list
	void Dlist::Clear() {
		Dnode *d;
		for (d = Begin(); d != End(); d = d->flink){
			Erase(d);
		}
		sentinel->s = "";
		sentinel->flink = sentinel;
		sentinel->blink = sentinel;
		size = 0;	
	}

//Checks if size is empty or not
	bool Dlist::Empty() const {
		if(size == 0) {
			return true;
		}
		return false;
	}

//Checks size of list
	size_t Dlist::Size() const {

		return size;
	}

//Pushes node to the back of the list
	void Dlist::Push_Front(const std::string &s) {
			
			Dnode *p1 = new Dnode;
			p1->flink = sentinel->flink;
			p1->blink = sentinel;
			sentinel->flink= p1;
			sentinel->flink->flink->blink = p1;
			p1->s = s;
			size++;
	}
//Pushed node to the front of the list	
	void Dlist::Push_Back(const std::string &s) {
			Dnode *p1 = new Dnode;
			p1->blink = sentinel->blink;
			p1->flink = sentinel;
			sentinel->blink = p1;
			sentinel->blink->blink->flink = p1;	
			p1->s = s;
			size++;
	}
//Returns and remove the string, node, at the back of the list
	string Dlist::Pop_Front() {
		string tmp;
		tmp = sentinel->flink->s;
		Erase(sentinel->flink);
		return tmp;
	}

//Return and removes the string, node, at the front of the list
	string Dlist::Pop_Back() {
		string tmp;
		tmp = sentinel->blink->s;
		Erase(sentinel->blink);
		return tmp;
	}

//Pointer to the first node
	Dnode *Dlist::Begin() const {
		return sentinel->flink;

	}
//Pointer to sentinel node
	Dnode *Dlist::End() const {
		return sentinel;
	}
//Pointer to prevous node
	Dnode *Dlist::Rbegin() const {
		return sentinel->blink;
		

	}
//Pointer to sentinel node
	Dnode *Dlist::Rend() const {
		return sentinel;
	}

//Inserts node before n
	void Dlist::Insert_Before(const std::string &s, Dnode *n) {
			
			Dnode *p1 = new Dnode;
			Dnode *prev;
			prev = n->blink;
			prev->flink = p1;
			p1->flink = n;
			p1->blink = prev;
			n->blink = p1;
			p1->s= s;
			size++;
	}

//Inserts node after n
	void Dlist::Insert_After(const std::string &s, Dnode *n) {
			
			Dnode *p1 = new Dnode;
			Dnode *next; 
			next = n->flink;
			n->flink = p1;
			p1->flink = next;
			p1->blink = n;
			next->blink = p1;
			p1->s = s;
			size++;
			
	}

//Erases node at n
	void Dlist::Erase(Dnode *n) {
		
		Dnode *next;
		Dnode *prev;

		next = n->flink;
		prev = n->blink;

		next->blink = prev;
		prev->flink = next;

		delete n;
		size--;
	}