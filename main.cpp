#include <cstddef>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <list>
#include <utility>
#include <string>

#include "List/Iterator.hpp"
#include "List/list.hpp"
#include "BigTable/cultivo_v1.hpp"
#include "DataHandling/proyect_V2.cpp"

int main(){
	BigTable mitabla;
	readCsv(mitabla , "DataHandling/generalData.csv");

	// mitabla.displayDistro();
	cout<<endl;

	//muestra los rangos de condiciones óptimas por defecto y analiza la
	//cantidad de datos dentro de estos óptimos
	mitabla.displayOptimalRanges();
	mitabla.optimalHum(true);
	mitabla.optimalTemp(true);

	//cambios de rangos optimos de temperaturas y humedades
	mitabla.chgHumRange(50,80);
	mitabla.chgTempRange("day",15,20);
	mitabla.chgTempRange("night",15,20);

	mitabla.displayOptimalRanges();
	mitabla.optimalHum(true);
	mitabla.optimalTemp(true);

	cout << "Promedio de temperatura en el minuto 1000 = "<< mitabla.get_mean_temp_dayMin(1000) <<" °C"<< endl <<endl;

	cout << "Promedio de la temperatura en el minuto 4 del día = " << mitabla.get_mean_temp_dayMin(4) <<" °C"<< endl;
	cout << "Promedio de la humedad en el minuto 4 del día = " << mitabla.get_mean_hum_dayMin(4) <<" %"<< endl << endl;

	cout << "Promedio de la temperatura en la hora 7 del día = " << mitabla.get_mean_temp_hour(7) <<" °C"<< endl;
	cout << "Promedio de la humedad en la hora 7 del día = " << mitabla.get_mean_hum_hour(7) <<" %"<< endl;

  cout << endl;
	mitabla.stdDeviation_24H("temp", true);
  cout << endl;
  mitabla.stdDeviation_24H("hum", true);

	return 0;
}
