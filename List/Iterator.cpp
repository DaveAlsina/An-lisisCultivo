#ifdef _Iterator_hpp_
#ifndef _Iterator_cpp_
#define _Iterator_cpp_ 

#include "Iterator.hpp"
#include <iostream> 

using namespace std;
				/*Clase Iterator*/


/*
 * Contructors and Destructors
 *
 */
Iterator::Iterator(Node* pointer){
	link = pointer;  
}


Iterator::~Iterator(){
	link = nullptr;	
	delete link;
	//cout<<"destroyed iterator."<<endl;
}


/*
 *  Setters
 *
 */
void Iterator::setLink(Node* pointer){
	link = pointer;
}




/*
 * Getters
 *
 */

Node* Iterator::getLink()const{

	return link;
}


/*
 *Decrement and increment operators
 *
 */

Iterator& Iterator::operator++(){ //prefijo++

	link = link->next;  
	return *this;
}


Iterator& Iterator::operator--(){ //prefijo--

	link = link->prev;  
	return *this;
}




/*Member of pointer*/

Node* Iterator::operator->(){
	return link;
} 



#endif			/**/
#endif 
