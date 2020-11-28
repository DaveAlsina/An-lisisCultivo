#ifndef _cultivo_v1_hpp_
#define _cultivo_v1_hpp_

#include <iostream>
#include <string>
#include "../List/list.hpp"

using namespace std;


//en este caso se debe cambiar el table size por 60*24
const int TABLE_SIZE = 1440; // numero de horas al día


class BigTable{
	private:
  		//Puntero al buckets que clasifican por toda la info en horas del día
		List** table;
		int errorCount;

		pair<double,double> hum; 		//par min y max de intervalos aceptables de humedades
		pair<double,double> tempDay; 		//par min y max de intervalos aceptables de temperaturas (día)
		pair<double,double> tempNight; 		//par min y max de intervalos aceptables de temperaturas (día)

		int tableSize;			//tamaño de la tabla
		int count; 			//numero de elementos en la tabla

		//metodo que recibe una valor en unixtime, lo convierte a hora:min:seg, y lo envia a DayHour según la hora convertida
		int hash(Node* n);

	public:
		BigTable();
		~BigTable();


		/*
		*	Modifiers
		*/

		//Agrega un 'Node' a las listas de los buckets
		void insert(Node* n);
		void chgHumRange(double min, double max);			//cambia el rango óptimo para humedad
		void chgTempRange(string time,double min, double max);		//cambia el rango óptimo para temperatura

		void errorDetected(); //Suma 1 a errorCount y no agrega lo que hay en esa fila del csv
		/*
		*	Getters
		*/
		int size(); 							//Returna el número de Nodes que tiene el HashTable
		bool empty();							//retorna el bool que indica presencia o ausencia de
										//elementos
		int number_errors(); // retorna el número de errores encontrados en la lectura del csv errorCount

		pair<double,double> getOptHumRange();				//devuelve una copia de los rangos óptimos para humedad
		pair<double,double> getOptTempRange(string time);		//devuelve una copia de los rangos óptimos para temperatura

		//Retorna la temperatura promedio de todos los datos que tiene dentro de una hora específica
		float get_mean_temp_dayMin(int dmin);

		//Retorna la temperatura promedio de todos los datos que tiene dentro de una hora específica
		float get_mean_hum_dayMin(int dmin);

		float get_mean_temp_hour(int hour);
		float get_mean_hum_hour(int hour);

		//obtiene el porcentaje de veces que se ha estado en un intervalo óptimo de humedades
		double optimalHum(bool print = false);	//lo imprime si print es 'true'

		//obtiene el porcentaje de veces que se ha estado en un intervalo óptimo  de temperaturas
		pair<double,double> optimalTemp(bool print = false);	//lo imprime si print es 'true'

		/*
		*	Displayers
		*/
		void display(); 		//Imprime la tabla completa
		void displayDistro(); 		//imprime la cantidad de elementos por lista
		void displayOptimalRanges();	//muestra con formato
};



#include "cultivo_v1.cpp"
#endif
