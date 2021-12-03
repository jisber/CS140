#include <iostream>
#include "dlist.hpp"
using namespace std;
	
	/* Constructors, Destructor, Assignment Overload */
	Dlist::Dlist() {
		sentinel = new Dnode;
		size = 0;
		sentinel->s = "";
		sentinel->flink = sentinel;
		sentinel->blink= sentinel;
	}
	
	Dlist::Dlist(const Dlist &d) {
		(void) d;
	}

	Dlist& Dlist::operator= (const Dlist &d) {
		(void) d;
		return *this;
	}

	Dlist::~Dlist() {

	}

	void Dlist::Clear() {
	
	}

	// This should not delete the sentinel node.
	bool Dlist::Empty() const {
		
		return false;
	}
	size_t Dlist::Size() const {

		return 1;
	}

	/* Put new strings on the front or back of the list */
	void Dlist::Push_Front(const std::string &s) {
			
			Dnode *p1 = new Dnode;
			p1->flink = sentinel->flink;
			p1->blink = sentinel;
			sentinel->flink= p1;
			sentinel->flink->flink->blink = p1;
			p1->s = s;
	}
	
	void Dlist::Push_Back(const std::string &s) {
			Dnode *p1 = new Dnode;
			p1->blink = sentinel->blink;
			p1->flink = sentinel;
			sentinel->blink = p1;
			sentinel->blink->blink->flink = p1;	
			p1->s = s;
	}

	/* Remove and return the first or last element of the list */
	string Dlist::Pop_Front() {
		
		return "";
	}
	string Dlist::Pop_Back() {
	
		return "";
	}
	
	Dnode *Dlist::Begin() const {
		return sentinel->flink;

	}
	// Pointer to the first node on the list 
	Dnode *Dlist::End() const {
		return sentinel;
	}
	// Pointer to the last node on the list
	Dnode *Dlist::Rbegin() const {
		return sentinel->blink;
		

	}
	Dnode *Dlist::Rend() const {
		return sentinel;
	}

	// Pointer to "one before" the first node on the list.
	void Dlist::Insert_Before(const std::string &s, Dnode *n) {
		
	}

	void Dlist::Insert_After(const std::string &s, Dnode *n) {
	
		/*
			Dnode *p1 = new Dnode;
			p1->blink = sentinel->blink;
			p1->flink = sentinel;
			sentinel->blink = p1;
			sentinel->blink->blink->flink = p1;	
			p1->s = s;
			*/
}

	void Dlist::Erase(Dnode *n) {
		(void) n;
	}

