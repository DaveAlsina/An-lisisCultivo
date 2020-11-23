#include <ctime>
#include <iostream>
using namespace std;

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

int main(){
  //Descomentar para entender mejor que hace cada función

  // cout << "Function test 1: " << endl;
  // int day_min_1 = convert_unixt_day_min(1595617740);
  // int year1 = convert_unixt_year(1595617740);
  // int month1 = convert_unixt_month(1595617740);
  // int day1 = convert_unixt_day(1595617740);
  // cout << "Year: " << year1 << endl;
  // cout << "Month: " << month1 << endl;
  // cout << "Day: " << day1 << endl;
  // cout << "Minute of day: " << day_min_1 << endl;
  //
  // cout << endl;
  //
  // cout << "Function test 2: " << endl;
  // int day_min_2 = convert_unixt_day_min(1595617800);
  // int year2 = convert_unixt_year(1595617800);
  // int month2 = convert_unixt_month(1595617800);
  // int day2 = convert_unixt_day(1595617800);
  // cout << "Year: " << year2 << endl;
  // cout << "Month: " << month2 << endl;
  // cout << "Day: " << day2 << endl;
  // cout << "Minute of day: " << day_min_2 << endl;

  return 0;
}
