#ifdef _cultivo_v1_hpp_



/*
*       Constructors and Destructors
*/


BigTable::BigTable(){

	tableSize = TABLE_SIZE; //inicializa el tamaño de la tabla
	count = 0;
	table = new List*[tableSize]; //reserva el espacio de memoria en heap

	for (int i=0; i<tableSize; i++){ //inicializa los punteros hacia una lista en memoria dinámica
		table[i] = new List;
	}
}

BigTable::~BigTable(){

	for (int i=0; i<tableSize; i++){ //inicializa los punteros hacia nullptr
		delete table[i];
	}

	delete[] table;
}

/*
*       Getters
*/

int BigTable::size(){

	List* sublist = nullptr; 
	int quantity = 0;
	
	for (int i =0; i<tableSize; i++){
		sublist = table[i];
		quantity += sublist->size();
	}	
	
	return quantity;
}


/*
*       Modifiers
*/

void BigTable::insert(Node* n){
	
	List* sublist = table[n->minute]; 	
	cout<<"acceso al bucket"<<endl;
	sublist->push_back(n);	
}

/*
*       Displayers
*/

void BigTable::display(){

	List* sublist = nullptr; 

	for (int i =0; i<tableSize; i++){
		sublist = table[i];
		if(sublist->size() == 0) continue; 

		cout << "\t************************"<<endl;
		cout << "\t Bucket: " << i <<endl;
		cout << "\t************************"<<endl;
		sublist->display();		
	}	
}


void BigTable::displayDistro(){
	
	List* sublist = nullptr; 

	for (int i =0; i<tableSize; i++){
		sublist = table[i];
		cout<<"Elements in Bucket "<<i<< " :\t" << sublist->size()<<endl;
	}	
}



#endif
