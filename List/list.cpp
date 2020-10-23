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
	
		newElement->prev = end;	 //el puntero al elemento previo del elemento nuevo apunta hacia el final (el final viejo)
		end = newElement;  //el puntero al siguiente elemento del último nodo, lo apunta hacia el nuevo elemento
		start = newElement;
		len++;

		return; 
	}

	end->next = newElement;  //el puntero al siguiente elemento del último nodo, lo apunta hacia el nuevo elemento
	newElement->prev = end;	 //el puntero al elemento previo del elemento nuevo apunta hacia el final (el final viejo)
	end = newElement; 	 //el final ahora apunta hacia el elemento añadido recién	

	len++;	
}

void List::push_front(Node* newElement){

	newElement->next = start;   //el puntero al siguiente elemento del nuevo nodo apunta hacia el start
	start->prev = newElement; //el puntero al elemento previo del nodo en el principio (el viejo) apunta hacia el nuevo nodo 
	start = newElement; 	   //el principio apunta hacia el elemento añadido recién 	

	len++;
}

//Deleters
void List::clear(){

	Iterator it = Begin();

	while(it.getLink() != nullptr){
		
		Node* old = it.getLink();
		it++; 
		delete old;
		len--;	
	}
	cout<<"cleaned"<<endl;
}

#endif
#endif
