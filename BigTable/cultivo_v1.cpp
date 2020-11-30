#ifdef _cultivo_v1_hpp_
#define	_cultivo_v1_cpp_

#include <cmath>
using namespace std;

/*
*       Constructors and Destructors
*/


BigTable::BigTable(){

	tableSize = TABLE_SIZE;						//inicializa el tamaño de la tabla
	count = 0;
	errorCount = 0;
	table = new List*[tableSize];				//reserva el espacio de memoria en heap

	for (int i=0; i<tableSize; i++){			//inicializa los punteros hacia una lista en memoria dinámica
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

	for (int i=0; i<tableSize; i++){	//borra cada sublista
		delete table[i];
	}

	delete[] table;						//borra el array
}


int BigTable::hash(Node* n){
	return n->dayMinute;				//usa como hash code el minuto del día
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

	double humSum;									//variable que almacena la suma
	int c = 0;										//contador de nodos
	List *assistant = table[dmin];					//acceso al principio del sublist
	Iterator it = assistant->Begin();				//iterador al principio de la lista

	while (it!=nullptr) {							//sumatoria
		humSum += it->hum;
		c++;
		it = it->next;
	}

	float h_mean = (float) humSum/c;				//Calculo del promedio
	return h_mean;
}

float BigTable::get_mean_temp_hour(int hour){
	int ini_hour = 60 * hour;
	int fin_hour = ini_hour + 60;

	double tempSum;
	int c = 0;

	for (int i = ini_hour; i<fin_hour; i++){
		List *assistant = table[i];
		Iterator it = assistant->Begin();			//iterador al principio de la lista

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
		Iterator it = assistant->Begin();			//iterador al principio de la lista

		while (it != nullptr){
			humSum += it->hum;
			c++;
			it = it->next;
		}
	}

	float h_mean = (float) humSum/c;
	return h_mean;
}


int BigTable::size(){									//retorna el la cantidad de nodos
	return count;
}
pair<double,double> BigTable::getOptHumRange(){			//retorna los Intervalos de humedad optimos para la humedad
	return hum;
}


pair<double,double> BigTable::getOptTempRange(string time){
	//recibe el intervalo 'day'/'night' y retorna el rango  optimo de temperaturas

	if ("day" == time)
		return tempDay;										//retorna el intervalo para el día
	else if ("night" == time)
		return tempNight;									//retorna el intervalo para la noche
	else{
															//muestra mensaje de error y retorna el intervalo del día por defecto
		cout<<endl;
		cout<<"recibió una franja temporal inválida las opciones son 'day' o 'night'"<<endl;
		cout<<"se retornará la franja del día por defecto..."<<endl;
		cout<<endl;
		return tempDay;
	}
}

double BigTable::optimalHum(bool print){
	/*Retorna las veces (% porcentaje) que se ha estado en condiciones
	 * optimas de humedad, si print ==  true, hace un respectivo display
	 * del resultado
	 */

	double inOptimalRange = 0;						//variable contador de las veces dentro del rango óptimo
	List* assistant = nullptr;						//variable asistente para el acceso a bucket

	for(int i=0; i<tableSize; i++){
		assistant = table[i];
		Iterator it = assistant->Begin();			//iterador al principio de la lista

		while(it != nullptr){						//suma de las incidencias dentro del rango
			if((it->hum < hum.second) and (it->hum > hum.first))
				inOptimalRange += 1;

			it = it->next;
		}
	}

	double result = (inOptimalRange*100)/count;		//calculo del porcentajes %

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

	double inOptRangeDay = 0;					//variable contador de incidencias para el dia
	int dayCount = 0;							//variable contadora de numero de datos en el día
	List* assistant = nullptr;

	//suma de insidencias de 6 am a 6 pm

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

	//suma de insidencias de 0 am a 6 am
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

	//suma de insidencias de 6 pm a 00 am
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

	result.first = (inOptRangeDay*100)/dayCount;		//calculo de los porcentajes
	result.second = (inOptRangeNight*100)/nightCount;

	if(print){

		cout<< endl <<"----------------------------------------------------------------------------------"<<endl;
		cout<<"Veces en rango óptimo de temperatura (% sobre el total de datos para cada periodo de tiempo):" << endl;
		cout<<"\tDía:  "<< result.first <<"%,   Noche: " << result.second <<"%"<<endl;
		cout<<"-----------------------------------------------------------------------------------"<<endl<<endl;
	}

	return result;
}

int BigTable::number_errors(){
	return errorCount;
}

double BigTable::stdDeviation_Hour(int h, string varible){
	int ini_hour = 60 * h;
	int fin_hour = ini_hour + 60;
	float xmean;
	double num = 0;
	double c = 0;

	if (varible == "temp"){
		xmean = get_mean_temp_hour(h);
		for (int i = ini_hour; i<fin_hour; i++){
			List *assistant = table[i];
			Iterator it = assistant->Begin();			//iterador al principio de la lista

			while (it != nullptr){
				double diferencia = xmean - it->temp;
				num += pow(diferencia,2);
				c++;
				it = it->next;
			}
		}
	}
	else if (varible == "hum"){
		xmean = get_mean_hum_hour(h);
		for (int i = ini_hour; i<fin_hour; i++){
			List *assistant = table[i];
			Iterator it = assistant->Begin();			//iterador al principio de la lista

			while (it != nullptr){
				double diferencia = xmean - it->hum;
				num += pow(diferencia,2);
				c++;
				it = it->next;
			}
		}
	}

	double stdD = sqrt(num/c);
	return stdD;
}

vector<pair<double, double>> BigTable::stdDeviation_24H(string varible, bool print){
	vector<pair<double,double>> myvec;
	for (int h = 0; h <= 23; h++){
		pair<double,double> mypair;
		if (varible == "temp"){
			mypair.first = get_mean_temp_hour(h);
			mypair.second = stdDeviation_Hour(h,varible);
		}
		else if (varible == "hum"){
			mypair.first = get_mean_hum_hour(h);
			mypair.second = stdDeviation_Hour(h,varible);
		}
		myvec.push_back(mypair);
	}
	if (print == true){
		cout << "Desviación estandar de la ";
		if (varible == "temp"){
			cout << "temperatura en °C" << endl;
		}
		else if (varible == "hum"){
			cout << "humedad en humedad relativa (%)" << endl;
		}

		for (int h = 0; h<=23; h+=2){
			cout << "Hora: " << h << "\tMedia: " << myvec[h].first << "\tDesviación estandar: " << myvec[h].second << "\t||"
			<< "\tHora: " << h+1 << "\tMedia: " << myvec[h+1].first << "\tDesviación estandar: " << myvec[h+1].second << endl;
		}
	}
	return myvec;
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

void BigTable::chgHumRange(double min, double max){
	hum.first = min; hum.second = max;
}


void BigTable::chgTempRange(string time,double min, double max){

	if(time == "day"){
		tempDay.first = min; tempDay.second = max;
	}else if (time == "night"){
		tempNight.first = min; tempNight.second = max;
	}else{
		cout<<"entrada inválida, se esperaba 'day'(para modificar el intervalo de día)"<<endl;
		cout<<"o 'night'(para modificar el intervalo de noche)"<<endl;
	}
}

void BigTable::errorDetected(){
	errorCount++;
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
	cout << "Tamaño de la tabla: " << size() << endl;
	cout << "Número de errores encontrados en la lectura del csv: " << number_errors() << endl;
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
