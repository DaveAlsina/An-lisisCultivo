#include <cstddef>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <list>
#include <utility>
#include <string>

#include "../List/Iterator.hpp"
#include "../List/list.hpp"
#include "../BigTable/cultivo_v1.hpp"

using namespace std;

// void readCsv(BigTable& obj, string dir);
// int convert_unixt_day_min(time_t rawtime);
// int convert_unixt_day(time_t rawtime);
// int convert_unixt_month(time_t rawtime);
// int convert_unixt_year(time_t rawtime);

int convert_unixt_day_min(time_t rawtime){
  //Función que recibe un número en unixtime y retorna el minuto del día

  struct tm * timeinfo;
  //En caso de que queramos corregir el unixtime multiplicado por mil
  // rawtime /= 1000;

  timeinfo = localtime (&rawtime);
  // int year = 1900 + timeinfo->tm_year;
  // int month = 1 + timeinfo->tm_mon;
  // int day = timeinfo->tm_mday;
  int hour = timeinfo->tm_hour;
  int minutes = timeinfo->tm_min;

  int day_min = hour* 60 + minutes;

  // cout << "Year: " << year << endl;
  // cout << "Month: " << month << endl;
  // cout << "Day: " << day << endl;
  // cout << "Minute of day: " << day_min << endl;

  return day_min;
}

int convert_unixt_day(time_t rawtime){
  //Función que recibe un número en unixtime y retorna el día del mes

  struct tm * timeinfo;
  //En caso de que queramos corregir el unixtime multiplicado por mil
  // rawtime /= 1000;

  timeinfo = localtime (&rawtime);
  int day = timeinfo->tm_mday;

  return day;
}

int convert_unixt_month(time_t rawtime){
  //Función que recibe un número en unixtime y retorna el mes del año

  struct tm * timeinfo;
  //En caso de que queramos corregir el unixtime multiplicado por mil
  // rawtime /= 1000;

  timeinfo = localtime (&rawtime);
  int month = 1 + timeinfo->tm_mon;

  return month;
}

int convert_unixt_year(time_t rawtime){
  //Función que recibe un número en unixtime y retorna el año

  struct tm * timeinfo;
  //En caso de que queramos corregir el unixtime multiplicado por mil
  // rawtime /= 1000;

  timeinfo = localtime (&rawtime);
  int year = 1900 + timeinfo->tm_year;

  return year;
}


void readCsv(BigTable& obj, string dir){

	ifstream temporal(dir);  //input file stream en el archivo csv
	string line; 		 //guarda las lineas que se van leyendo del csv
	double  cols[4];		 //variable que guarda los datos
	long long int date = 0;	 //variable que guarda la fecha en tiempo unix

//	int error = 0; 		//cuenta el número de mediciones de temperatura o humedad erróneas

	if(temporal.good()){	 //si el input file stream está bien

		while(!temporal.eof()){ //mientras el stream no esté vacio...

			getline(temporal, line); //obtiene la linea actual y la guarda en 'line'
			stringstream ss(line);   //crea un stream de string para moverse a través de él cómodamente

			ss.ignore(7, ',');	//ignora máximo 7 caracteres hasta poder llegar a la primera coma

			for(int i=0; i<4; i++){			  //guarda las demás columnas en sus casillas
				if(ss.peek() == ',') ss.ignore(); //ignora la coma
				ss >> cols[i];		  	  //hace la siguiente extracción
			}

			if(ss.peek() == ',') ss.ignore(); //ignora la coma
			ss >> date;			  //guarda la última columna (la de la fecha) *WeNeedMagicHere!!!*
			date /= 1000;

			int yr = convert_unixt_year(date);
			int month = convert_unixt_month(date);
			int day = convert_unixt_day(date);
			int daymin = convert_unixt_day_min(date);

			//Rangos aceptables de variables del csv:
			pair<double,double> tempAceptable (0,50);
			pair<double,double> humAceptable (20,90);
			//Falta confirmar el rango del heat y dp
			pair<double,double> heatAceptable (0,40);
			pair<double,double> dpAceptable (0,30);

			if (cols[0] > tempAceptable.first && cols[0] < tempAceptable.second){
				if (cols[1] > humAceptable.first && cols[1] < humAceptable.second){
					if (cols[2] > heatAceptable.first && cols[2] < heatAceptable.second){
						if (cols[3] > dpAceptable.first && cols[3] < dpAceptable.second){
							//guardado de los datos en un nodo asistente
							Node* assistant = new Node(yr,month,day,daymin,cols[0], cols[1], cols[2], cols[3]);
							//añadido del nodo a el objeto BigTable
							obj.insert(assistant);
						}
						else{obj.errorDetected();}
					}
					else{obj.errorDetected();}
				}
				else{obj.errorDetected();}
			}
			else{obj.errorDetected();}


		}
	}

}




//---------------------------------------
/*
fuentes de ideas o know how
http://www.cplusplus.com/reference/istream/istream/ignore/
https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
https://www.geeksforgeeks.org/pair-in-cpp-stl/#:~:text=The%20array%20of%20objects%20allocated,the%20keyword%20first%20or%20second.

por revisar:
https://ducciogasparri.it/2019/12/06/best-plot-and-charting-c-packages-for-data-visualization/

*/
