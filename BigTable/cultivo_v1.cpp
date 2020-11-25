#ifdef _cultivo_v1_hpp_

using namespace std;

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

	//intervalos por defecto de porcentajes correctos de humedad (60-80)%
	hum.first = 60;
	hum.second = 80;

	//intervalos por defecto de porcentajes correctos de temperatura (20-23)°C día
	tempDay.first = 20;
	tempDay.second = 23;

	//intervalos por defecto de porcentajes correctos de temperatura (15-18)°C noche
	tempDay.first = 15;
	tempDay.second = 18;
}

BigTable::~BigTable(){

	for (int i=0; i<tableSize; i++){ //inicializa los punteros hacia nullptr
		delete table[i];
	}

	delete[] table;
}


int BigTable::hash(Node* n){
	return n->dayMinute;
}


/*
*       Getters
*/

float BigTable::get_mean_temp_dayMin(int dmin){
	double tempSum;
	int c = 0;
	List *assistant = table[dmin];
	Iterator it = assistant->Begin();	//iterador al principio de la lista
	while (it!=nullptr) {
		tempSum+=it->temp;
		c++;
		it=it->next;
	}
	float t_mean = (float) tempSum/c;
	return t_mean;
}

float BigTable::get_mean_hum_dayMin(int dmin){
	//Toca corregir el heatIndx por el hum
	double humSum;
	int c = 0;
	List *assistant = table[dmin];
	Iterator it = assistant->Begin();	//iterador al principio de la lista

	cout << endl;
	while (it!=nullptr) {
		cout << "humedad = " << it->heatIndx << endl;
		humSum+=it->heatIndx;
		c++;
		it=it->next;
	}
	float h_mean = (float) humSum/c;
	return h_mean;
}

int BigTable::size(){
	return count;
}

float BigTable::get_mean_temp_hour(int hour){
	int ini_hour = 60 * hour;
	int fin_hour = ini_hour + 60;

	double tempSum;
	int c = 0;

	for (int i = ini_hour; i<fin_hour; i++){
		List *assistant = table[i];
		Iterator it = assistant->Begin();	//iterador al principio de la lista

		while (it != nullptr){
			tempSum += it->temp;
			c++;
			it = it->next;
		}
	}

	float t_mean = (float) tempSum/c;
	return t_mean;
}

float BigTable::get_mean_hum_hour(int hour){
	int ini_hour = 60 * hour;
	int fin_hour = ini_hour + 60;

	double humSum;
	int c = 0;

	for (int i = ini_hour; i<fin_hour; i++){
		List *assistant = table[i];
		Iterator it = assistant->Begin();	//iterador al principio de la lista

		while (it != nullptr){
			humSum += it->heatIndx;
			c++;
			it = it->next;
		}
	}

	float h_mean = (float) humSum/c;
	return h_mean;
}

// pair<double,double> BigTable::getOptHumRange(){
// 	return hum;
// }
//
//
// pair<double,double> getOptTempRange(string time){
// 	if ("day" == time)
// 		return tempDay;
// 	else if ("night" == time)
// 		return tempNight;
// 	else{
// 		cout<<endl;
// 		cout<<"recibió una franja temporal inválida las opciones son 'day' o 'night'"<<endl;
// 		cout<<"se retornará la franja del día por defecto..."<<endl
// 		cout<<endl;
// 		return tempDay;
// 	}
// }
//
// double BigTable::optimalHum(){
//
// 	double inOptimalRange = 0;
// 	List* assistant = nullptr;
//
// 	for(int i=0; i<tableSize; i++){
// 		assistant = table[i];
// 		Iterator it = assistant->Begin();	//iterador al principio de la lista
//
// 		while(it != nullptr){
// 			if((it->hum < hum.second) and (it->hum > hum.first))
// 				inOptimalRange += 1;
//
// 			it = it->next;
// 		}
// 	}
//
// 	double result = (inOptimalRange*100)/count;
// 	return result;
// }
//
// pair<double,double> BigTable::optimalTemp(){
//
// 	/*Funcion que retorna la pareja de doubles cuyo primer elemento representa
// 	el porcentaje de veces que se estuvo en condiciones óptimas de día,
// 	el segundo elemento es análogo al primero pero en la noche*/
// 	pair<double, double> result;
//
// 	double inOptRangeDay = 0;
// 	int dayCount = 0;
// 	List* assistant = nullptr;
//
// 	//de 6 am a 6 pm
// 	for(int i=360; i<1080; i++){
// 		assistant = table[i];
// 		Iterator it = assistant->Begin();	//iterador al principio de la lista
//
// 		while(it != nullptr){
// 			if((it->temp < tempDay.second) and (it->temp > tempDay.first))
// 				inOptRangeDay += 1;
//
// 			dayCount++;
// 			it = it->next;
// 		}
// 	}
//
//
// 	double inOptRangeNight = 0;
// 	int nightCount = 0;
//
// 	//de 0 am a 6 am
// 	for(int i=0; i<360; i++){
// 		assistant = table[i];
// 		Iterator it = assistant->Begin();	//iterador al principio de la lista
//
// 		while(it != nullptr){
// 			if((it->temp < tempNight.second) and (it->temp > tempNight.first))
// 				inOptRangeNight += 1;
//
// 			nightCount++;
// 			it = it->next;
// 		}
// 	}
//
// 	//de 6 pm a 00 am
// 	for(int i=1080; i<1440; i++){
// 		assistant = table[i];
// 		Iterator it = assistant->Begin();	//iterador al principio de la lista
//
// 		while(it != nullptr){
// 			if((it->temp < tempNight.second) and (it->temp > tempNight.first))
// 				inOptRangeNight += 1;
//
// 			nightCount++;
// 			it = it->next;
// 		}
// 	}
//
// 	result.first = (inOptRangeDay*100)/dayCount;
// 	result.second = (inOptRangeNight*100)/nightCount;
//
// 	return result;
// }

/*
*       Modifiers
*/

void BigTable::insert(Node* n){

	int bucket = hash(n);
	List* sublist = table[bucket];
//	cout<<"acceso al bucket"<<endl;
	sublist->push_back(n);
	count++;
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
