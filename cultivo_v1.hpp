#ifndef _cultivo_v1_hpp_
#define _cultivo_v1_hpp_
#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 24; // numero de horas al día

template <typename VT >
struct DayHour{
  int hour;
  //HourMinute <VT> * minutes;
  DayHour < VT > * nextHour;
};

template <typename VT >
struct HourMinute{
  int minute;
  //Node <VT> * minuteData;
  HourMinute < VT > * nextMinute;
};



template <typename VT>
class BigTable{
private:
  //Puntero al buckets que clasifican por toda la info en horas del día
  DayHour <VT> ** table;

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



#include "cultivo_v1.cpp"
#endif
