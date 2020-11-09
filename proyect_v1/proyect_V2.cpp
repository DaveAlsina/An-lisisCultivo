#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <list>
#include <utility>
#include <string>

#include "../List/Iterator.hpp"
#include "../List/list.hpp"

using namespace std;

void readCsv(List& obj, string dir);

int main(){
	/*
	 * couts para verificar que los includes funcionan correctamente
	 *
        //testeo constructor por defecto de Node
        Node* empty1 = new Node;

        //testeo contructor de iterador 
        Iterator it(empty1);
	
        //testeo creación de lista vacía
        List lst;
        cout<<endl<<"Lista creada"<<endl;

        lst.push_back(empty1);
	*/




return 0;
}

void readCsv(List& obj, string dir){

	ifstream temporal(dir);  //input file stream en el archivo csv
	string line; 		 //guarda las lineas que se van leyendo del csv
	double cols[4];		 //variable que guarda los datos
	long long int date;	 //variable que guarda la fecha en tiempo unix

	if(temporal.good()){	 //si el input file stream está bien
	
		while(!temporal.eof()){ //mientras el stream no esté vacio...
			
			getline(temporal, line); //obtiene la linea actual y la guarda en 'line'	
			stringstream ss(line);   //crea un stream de string para moverse a través de él cómodamente	
				
			for(int i=0; i<4; i++){			  //guarda las demás columnas en sus casillas
				if(ss.peek() == ',') ss.ignore(); //ignora la coma
				ss >> cols[i];		  	  //hace la siguiente extracción
			}
				
			if(ss.peek() == ',') ss.ignore(); //ignora la coma
			ss >> date;			  //guarda la última columna (la de la fecha) *WeNeedMagicHere!!!*	
			
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

