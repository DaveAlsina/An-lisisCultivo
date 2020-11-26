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

		pair<double,double> hum; //par min y max de intervalos aceptables de humedades
		pair<double,double> tempDay; //par min y max de intervalos aceptables de temperaturas (día)
		pair<double,double> tempNight; //par min y max de intervalos aceptables de temperaturas (día)

		int tableSize;
		int count; //numero de elementos en la tabla

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

		/*
		*	Getters
		*/
		int size(); //Returna el número de Nodes que tiene el HashTable
		bool empty(); //true if there are no elements
		pair<double,double> getOptHumRange();
		pair<double,double> getOptTempRange(string time);

		//Retorna la temperatura promedio de todos los datos que tiene dentro de una hora específica
		float get_mean_temp_dayMin(int dmin);

		//Retorna la temperatura promedio de todos los datos que tiene dentro de una hora específica
		float get_mean_hum_dayMin(int dmin);

		float get_mean_temp_hour(int hour);
		float get_mean_hum_hour(int hour);

		//obtiene el porcentaje de veces que se ha estado en un intervalo óptido de humedades
		double optimalHum();

		//obtiene el porcentaje de veces que se ha estado en un intervalo óptido de temperaturas
		pair<double,double> optimalTemp();

		/*
		*	Displayers
		*/
		void display(); //Imprime la tabla completa
		void displayDistro(); //imprime la cantidad de elementos por lista
		void displayOptimalRanges();
};



#include "cultivo_v1.cpp"
#endif
