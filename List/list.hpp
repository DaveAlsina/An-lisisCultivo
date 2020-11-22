#ifndef _list_hpp_ 
#define _list_hpp_

#include "Iterator.hpp"

class List{

	friend class Iterator;
	
	private:

		Node* start; //linkea al comienzo de la lista
		Node* end; 	
		unsigned len; 	

	public: 

		
		/*
		 * Constructor y Destructor
		 *
		 */

		List(); 
		~List(); 
	
		Iterator Begin();
		Iterator End();

		/*
		 * Modificadores
		 *
		 */
		
		void push_back(Node* newElement);
		void push_front(Node* newElement);

		void clear();

		/*
		 * Getters and Displayers
		 *
		 */
		
		void display();
		unsigned size();

};

#include "list.cpp"
#endif
