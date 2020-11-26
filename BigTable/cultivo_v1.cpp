#ifdef _cultivo_v1_hpp_
#define	_cultivo_v1_cpp_
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
	tempNight.first = 15;
	tempNight.second = 18;
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

	while (it!=nullptr) {
		humSum+=it->hum;
		c++;
		it=it->next;
	}
	float h_mean = (float) humSum/c;
	return h_mean;
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
			humSum += it->hum;
			c++;
			it = it->next;
		}
	}

	float h_mean = (float) humSum/c;
	return h_mean;
}


int BigTable::size(){
	return count;
}
pair<double,double> BigTable::getOptHumRange(){
	return hum;
}


pair<double,double> BigTable::getOptTempRange(string time){
	if ("day" == time)
		return tempDay;
	else if ("night" == time)
		return tempNight;
	else{
		cout<<endl;
		cout<<"recibió una franja temporal inválida las opciones son 'day' o 'night'"<<endl;
		cout<<"se retornará la franja del día por defecto..."<<endl;
		cout<<endl;
		return tempDay;
	}
}

double BigTable::optimalHum(bool print){

	double inOptimalRange = 0;
	List* assistant = nullptr;

	for(int i=0; i<tableSize; i++){
		assistant = table[i];
		Iterator it = assistant->Begin();	//iterador al principio de la lista

		while(it != nullptr){
			if((it->hum < hum.second) and (it->hum > hum.first))
				inOptimalRange += 1;

			it = it->next;
		}
	}

	double result = (inOptimalRange*100)/count;

	if (print){
		
		cout<< endl <<"-----------------------------------------------------------------------------------"<<endl;
		cout<< "Veces que ha estado en condiciones de humedad óptimas (% humedad relativa):  " 
		<< result <<"%"<<endl;
		cout<<"-----------------------------------------------------------------------------------"<<endl<<endl;
	}

	return result;
}

pair<double,double> BigTable::optimalTemp(bool print){

	/*Funcion que retorna la pareja de doubles cuyo primer elemento representa
	el porcentaje de veces que se estuvo en condiciones óptimas de día,
	el segundo elemento es análogo al primero pero en la noche*/
	pair<double, double> result;

	double inOptRangeDay = 0;
	int dayCount = 0;
	List* assistant = nullptr;

	//de 6 am a 6 pm
	for(int i=360; i<1080; i++){
		assistant = table[i];
		Iterator it = assistant->Begin();	//iterador al principio de la lista

		while(it != nullptr){
			if((it->temp < tempDay.second) and (it->temp > tempDay.first))
				inOptRangeDay += 1;

			dayCount++;
			it = it->next;
		}
	}


	double inOptRangeNight = 0;
	int nightCount = 0;

	//de 0 am a 6 am
	for(int i=0; i<360; i++){
		assistant = table[i];
		Iterator it = assistant->Begin();	//iterador al principio de la lista

		while(it != nullptr){
			if((it->temp < tempNight.second) and (it->temp > tempNight.first))
				inOptRangeNight += 1;

			nightCount++;
			it = it->next;
		}
	}

	//de 6 pm a 00 am
	for(int i=1080; i<1440; i++){
		assistant = table[i];
		Iterator it = assistant->Begin();	//iterador al principio de la lista

		while(it != nullptr){
			if((it->temp < tempNight.second) and (it->temp > tempNight.first))
				inOptRangeNight += 1;

			nightCount++;
			it = it->next;
		}
	}

	result.first = (inOptRangeDay*100)/dayCount;
	result.second = (inOptRangeNight*100)/nightCount;

	if(print){

		cout<< endl <<"-----------------------------------------------------------------------------------"<<endl;
		cout<<"Veces en rango óptimo de temperatura (% sobre el total de datos para cada periodo de tiempo):" << endl;
		cout<<"\tDía:  "<< result.first <<"%,   Noche: " << result.second <<"%"<<endl;
		cout<<"-----------------------------------------------------------------------------------"<<endl<<endl;
	}

	return result;
}

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

void BigTable::displayOptimalRanges(){
 
	cout<<"-----------------------------------------------------------------------------------"<<endl;

        cout<<"Intervalos de condiciones óptimas:"<<endl;
        cout<<"\t En temperatura(día): \t\t\t mínimo -> "<< tempDay.first << "°C\t máximo -> "<< tempDay.second <<"°C"<<endl; 
        cout<<"\t En temperatura(noche): \t\t mínimo -> "<< tempNight.first << "°C\t máximo -> "<< tempNight.second <<"°C"<<endl;
        cout<<"\t En humedad (24h)(humedad relativa %): \t mínimo -> "<< hum.first << "%\t máximo -> "<< hum.second <<"%"<<endl;
	cout<<"-----------------------------------------------------------------------------------"<<endl<<endl;
}

#endif
