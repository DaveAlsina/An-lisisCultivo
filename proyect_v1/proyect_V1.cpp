#include <iostream>
#include <fstream>
#include <sstream>

#include <utility>

#include <vector>
#include <list>
#include <string>
using namespace std;

//traer los datos usando IMAPS y búsqueda
//void bringFromMail()*

//vizualizar datos
bool readData(const vector<pair<double, long int>> &vec, const unsigned n=5);
bool readData(const vector<pair<short, long int>> &vec, const unsigned n=5);

//crear representaciones de los datos (Lectura + insertion sort)
void buildDataFrame(const string dir, vector< pair<double, long int> > &dataFrame);
void buildDataFrame(const string dir, vector< pair<short, long int> > &dataFrame);

//limpiar datos y guardar indicadores (cuántos puntos de datos están mal o son desechados)
//void cleanData()* -> búsqueda linear

//analizar datos
//histograma de temperatura/humedad por horas* -> sorting por grupos de horas
//variación entre las horas de los días en cuanto a temperatura/humedad*
//parametros dentro de las condiciones óptimas para el cultivo* -> búsqueda linear*
//dentro de qué horas se estuvo con más frecuencia dentro de los puntos óptimos -> búsqueda linear*


int main(){

//storting the data from the csv files into the vector of pairs
  vector< pair<double, long int> > tableTemp;
  vector< pair<double, long int> > tableHeatIndx;
  vector< pair<double, long int> > tableDewPoint;
  vector< pair<short, long int> > tableHum;


  buildDataFrame("camb_v7.csv", tableTemp);
  buildDataFrame("heatIndx_v9.csv", tableHeatIndx);
  buildDataFrame("dewpoint_v10.csv", tableDewPoint);
  buildDataFrame("humedad_v8.csv", tableHum);


//Readings to show if everything is working as expected

  cout<<"Cantidad de parejas de datos(de Temperatura): "<<tableTemp.size()<<endl;
  readData(tableTemp);

  cout<<endl;

  cout<<"Cantidad de parejas de datos(de Humedad): "<<tableHum.size()<<endl;
  readData(tableHum);

  cout<<endl;

  cout<<"Cantidad de parejas de datos(de indice de calor): "<<tableHeatIndx.size()<<endl;
  readData(tableHeatIndx);

  cout<<endl;

  cout<<"Cantidad de parejas de datos(de Punto de Rocio): "<<tableDewPoint.size()<<endl;
  readData(tableDewPoint);

}


//---------------------------------------
bool readData(const vector<pair<double, long int>> &vec, const unsigned n){

      if (n >= vec.size()){
        cout<<"Error, cantidad límite de lectura excede el tamaño del contendendor";
        return false;
      }

      for(unsigned i =0; i < n; i++){
          cout<<"data: "<<vec[i].first<<"  date:  "<<vec[i].second<<endl;
      }

      return true;
}

bool readData(const vector<pair<short, long int>> &vec, const unsigned n){

      if (n >= vec.size()){
        cout<<"Error, cantidad límite de lectura excede el tamaño del contendendor";
        return false;
      }

      for(unsigned i =0; i < n; i++){
          cout<<"data: "<<vec[i].first<<"  date:  "<<vec[i].second<<endl;
      }

      return true;
}


//---------------------------------------
void buildDataFrame(const string dir, vector< pair<double, long int> > &dataFrame){

    ifstream temporal(dir);
    string line;          //stores the lines that are being read
    double data;          //stores the data point
    long long int date;        //stores the date in unix Time

    // int centinel = 0;   //used for printing and debugging

    if(temporal.good()){

        while(!temporal.eof()){

          getline(temporal,line); //saves the current line in "line"
          stringstream ss(line);  //ss iterates through the line

          // if (centinel<5){
          //     cout << line << "  ";
          //     centinel++;
          // }

              while(ss>>data){    //stores the first part of the line into data

                if(ss.peek() == ',') ss.ignore();   //skips the comma
                ss>>date;                           //stores the unix timestamp in date
                dataFrame.push_back({data, date/1000}); //adds the pair to the dataframe

                // if (centinel<5){
                //     cout << data << "  " << date <<endl;
                //     centinel += 2;
                // }

              }
        }

    }

    temporal.close();
}

void buildDataFrame(const string dir, vector< pair<short, long int> > &dataFrame){

      ifstream temporal(dir);
      string line;          //stores the lines that are being read
      double data;          //stores the data point
      long long int date;        //stores the date in unix Time

      // int centinel = 0; //used for printing and debugging

      if(temporal.good()){

          while(!temporal.eof()){

            getline(temporal,line); //saves the current line in "line"
            stringstream ss(line);  //ss iterates through the line

            // if (centinel<5){
            //     cout << line << "  ";
            //     centinel++;
            // }

                while(ss>>data){    //stores the first part of the line into data


                  if(ss.peek() == ',') ss.ignore();   //skips the comma
                  ss>>date;                           //stores the unix timestamp in date
                  dataFrame.push_back({data, date/1000}); //adds the pair to the dataframe

                  // if (centinel<5){
                  //     cout << data << "  " << date <<endl;
                  //     centinel += 2;
                  // }

                }
          }

      }

      temporal.close();
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
