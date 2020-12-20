#ifdef _list_hpp_
#ifndef _list_cpp_
#define _list_cpp_

#include "list.hpp"
#include <iostream>
using namespace std;


/*
 *Constructors And Destructors
 *
 */

List::List(){
 	start = nullptr;
 	end = nullptr;
	len = 0;
}

List::~List(){
	clear();
}


/*
 *Getters and Displayers
 *
 */

void List::display(){
	Iterator it = this->Begin();

	for( ; it != nullptr; ++it){

		cout<< it->year <<" "<< it->dayMinute <<" "<<it->day <<" "<<it->month <<endl;
		cout<< it->temp <<" "<< it->heatIndx<<" "<< it->dewPoint<<" " << it->hum <<" "<< endl;
		cout<<endl;
	}
}

unsigned List::size(){
	return len;
}


/*
 * Iterators Creation
 *
 */


Iterator List::Begin(){

	Iterator it(start);
	return it;
}


Iterator List::End(){

	Iterator it(end);
	return it;
}


/*
 *Modifiers
 *
 */

//Adders
void List::push_back(Node* newElement){

	if(len==0){

		end = newElement;  //el puntero al siguiente elemento del último nodo, lo apunta hacia el nuevo elemento
		start = newElement;
		len++;
		return;
	}

	newElement->prev = end;	 //el puntero al elemento previo del elemento nuevo apunta hacia el final (el final viejo)
	end->next = newElement;  //el puntero al siguiente elemento del último nodo, lo apunta hacia el nuevo elemento
	end = newElement; 	 //el final ahora apunta hacia el elemento añadido recién

	len++;
}


//Deleters
void List::clear(){

	Iterator it = Begin();

	while(it.getLink() != nullptr){

		Node* old = it.getLink();
		++it;
		delete old;
		len--;
	}
}

#endif
#endif
