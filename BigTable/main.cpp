#include "cultivo_v1.hpp"
#include <iostream>
using namespace std;

int main(){
	BigTable mitabla;
	cout<<"creación de tabla exitosa..."<<endl;
	Node* n1 = new Node{0,0,0,1,1,1,1};
	Node* n2 = new Node{7,8,9,10,11,12,13};
	Node* n3 = new Node{1,2,3,4,5,6,7};   	
	cout<<"creación de nodo exitosa..."<<endl;

	mitabla.insert(n1);
	mitabla.insert(n2);
	mitabla.insert(n3);
	cout<<"insersión de nodo  exitosa!"<<endl;

	mitabla.display();
	mitabla.displayDistro();
	cout<<"cantidad de elementos en el hashtable:\t"<<mitabla.size()<<endl;
	
	cout<<"veces en rango de humedad óptmo: " << mitabla.optimalHum()  <<"%"<<endl;
	pair<double,double> optDay = mitabla.optimalTemp();
	cout<<"veces en rango óptimo: Dia: " <<optDay.first<<"%,   Noche: "<< optDay.second <<"%"<<endl;
	return 0;
}
