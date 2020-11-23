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

		int tableSize;
		int count; //numero de elementos en la tabla

		//metodo que recibe una valor en unixtime, lo convierte a hora:min:seg, y lo envia a DayHour según la hora convertida
		int hash(Node* n);

	public:
		BigTable();
		~BigTable();
		
		/*
		*	Getters
		*/ 		
		int size(); //Returna el número de Nodes que tiene el HashTable
		bool empty(); //true if there are no elements
		
		
		/*
		*	Modifiers
		*/ 		
		//Agrega un 'Node' a las listas de los buckets 
		void insert(Node* n);		

		//Retorna la temperatura promedio de todos los datos que tiene dentro de una hora específica
		float get_mean_temp(int hour); 

		//Retorna la temperatura promedio de todos los datos que tiene dentro de una hora específica
		float get_mean_hum(int hour); 
	
		/*
		*	Displayers
		*/ 		
		void display(); //Imprime la tabla completa	
		void displayDistro(); //imprime la cantidad de elementos por lista
};



#include "cultivo_v1.cpp"
#endif
