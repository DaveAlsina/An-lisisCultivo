#ifdef _cultivo_v1_hpp_

template <typename VT>
BigTable<VT>::BigTable(){

	tableSize = TABLE_SIZE; //inicializa el tamaño de la tabla
	count = 0;
	table = new DayHour<VT>*[tableSize]; //reserva el espacio de memoria en heap

	for (int i=0; i<tableSize; i++){ //inicializa los punteros hacia nullptr
		table[i] = nullptr;
	}
}

template <typename VT>
BigTable<VT>::~BigTable(){
}














#endif
