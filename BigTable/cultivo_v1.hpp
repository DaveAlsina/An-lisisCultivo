//#ifndef _list_hpp_
//#define _list_hpp_
#ifndef _cultivo_v1_hpp_
#define _cultivo_v1_hpp_
#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 1440; // número de minutos en un día

template <typename VT >
struct HourMinute{
  int minute;
  //List <VT> * minuteData;
};


template <typename VT>
class BigTable{
private:
  //Puntero al buckets que clasifican por toda la info en horas del día
  HourMinute <VT> ** table;

  int tableSize;
  int count; //numero de elementos en la tabla

  int hash(long long int unixtime); //metodo que recibe una valor en unixtime, lo convierte a hora:min:seg, y lo envia a DayHour según la hora convertida


public:
  BigTable();
  ~BigTable();

  int size(); //Returna el número de Nodes que tiene el DS
  bool empty(); //true if there are no elements

  void insert();//Agrega un Node a un HourMinute que está dentro de un DayHour

  float get_mean_temp(int hour); //Retorna la temperatura promedio de todos los datos que tiene dentro de una hora específica
  float get_mean_hum(int hour); //Retorna la temperatura promedio de todos los datos que tiene dentro de una hora específica

  void display(); //Imprime la tabla completa
};



//#include "list.cpp"
#include "cultivo_v1.cpp"
#endif
//#endif
