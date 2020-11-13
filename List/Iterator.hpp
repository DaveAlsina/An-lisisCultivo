#ifndef _Iterator_hpp_
#define _Iterator_hpp_

struct Node{

        //estructura que almacena todos los datos que se
        //requieren para representar el data set

        Node(short int d = 0, short int m = 0, short int min = 0, double t=0,
        double hi = 0, double dp = 0, short int h = 0): day(d), month(m), minute(min), temp(t), heatIndx(hi), dewPoint(dp), hum(h){}

        short int day;
        short int month;
        short int minute;

        double temp;
        double heatIndx;
        double dewPoint;

        short int hum;
        Node* next = nullptr;
        Node* prev = nullptr;
};

class Iterator{

        private:
                Node* link;


        public:
                Iterator(Node* pointer);
                ~Iterator();

                /*Setters*/
                void setLink(Node* pointer);


                /*Getters*/
                Node* getLink()const;


                /*Overloads prefix operators*/
                Iterator& operator++();
                Iterator& operator--();

		/*member of pointer*/
		Node* operator->();

};


/*'==' and '!=' operator*/

bool operator!=(Iterator it, Node* ptr){
	return it.getLink() != ptr; 
}


bool operator==(Iterator it, Node* ptr){
	return it.getLink() == ptr; 
}


#include "Iterator.cpp"
#endif
