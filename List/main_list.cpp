#include <iostream>
#include "Iterator.hpp"
#include "list.hpp"

int main(){


	//testeo constructor por defecto de Node
	Node* empty1 = new Node;
	Node* empty2 = new Node{7,8,9,10,11,12,13};
	Node* empty3 = new Node{1,2,3,4,5,6,7}; 	


        //testeo contructor de iterador	
	Iterator it(empty1);	

	//testeo de operador de acesso a miembro de clase en Iterador	
	cout<< it->minute <<" "<<it->day <<" "<<it->month <<endl; 
	cout<< it->temp <<" "<< it->heatIndx<<" "<< it->dewPoint<<" " << it->hum <<" "<< endl; 	

	//testeo creación de lista vacía
	List lst; 
	cout<<endl<<"Lista creada"<<endl;

	lst.push_back(empty2);	
	lst.push_back(empty3);

	cout<<endl<<"For Loop para revisar operación del iterador"<<endl<<endl;
	
	for(Iterator it = lst.Begin(); it != nullptr; it++){
		
		cout<< it->minute <<" "<<it->day <<" "<<it->month <<endl; 
		cout<< it->temp <<" "<< it->heatIndx<<" "<< it->dewPoint<<" " << it->hum <<" "<< endl; 	
	}

	cout<<endl<<endl; 
	delete empty1;
	return 0; 
}
