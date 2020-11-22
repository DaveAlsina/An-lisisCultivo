#include <ctime>
#include <iostream>
using namespace std;

int convert_unixtime(time_t rawtime){
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

int main(){
  // cout << "Function test 1: " << endl;
  // int test1 = convert_unixtime(1595617740);
  // cout << "Minute of day: " << test1 << endl;
  //
  // cout << "Function test 2: " << endl;
  // int test2 = convert_unixtime(1595617800);
  // cout << "Minute of day: " << test2 << endl;

  return 0;
}
