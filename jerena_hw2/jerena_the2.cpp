//Jeren Annagurbanova - THE2
#include <iostream>
#include <iomanip>
#include <string>
#include "strutils.h"

using namespace std;

//function prototypes
bool check_input(string, string, string, string );
void CheckCubeandDisplay(string, double, double, double); 
void calculate(string, double, double, double,double & ,double &); 
void display(string, double, double); 
string compare(string, string, string, double, double);
bool letter(string, string);

int main(){
	cout.setf(ios::fixed);
	cout.precision(2);

	//variables to be used
	string h1, h2, w1, w2, l1, l2;
	double area1=0, volume1=0, area2=0, volume2=0;
	string c1,c2;
	cout<<"Hello! This program compares two cuboids..."<<endl;
	cout<<"Please enter colors for the two cuboids: ";
	cin >> c1 >> c2;
	if (LowerString(c1) == LowerString(c2)){  //color control
		cout<< "Color names cannot be the same, good bye..."<<endl;}
	else{
		cout<<"Please enter length, width and height of the "<< c1 << " cuboid: "; 
		cin>>l1>>w1>>h1;
		if (check_input(c1, l1, w1, h1)){ //if c1 inputs are valid
			cout<<"Please enter length, width and height of the "<< c2 << " cuboid: ";
			cin>> l2 >> w2>> h2;
			if (check_input(c2, l2, w2, h2)){//if c2 inputs are valid
				calculate(c1, atof(l1), atof(w1),atof(h1), area1, volume1); //calculate area and volume for c1 and display
				cout<<endl;
				calculate(c2, atof(l2), atof(w2), atof(h2), area2, volume2); //calculate area and volume for c2 and display
				cout<<endl;
				cout<<"Comparison of the two cuboids:"<<endl;
				cout<<compare(c1, c2, "volume", volume1, volume2)<<endl; //comparing c1, c2
				cout<<compare(c1, c2, "area", area1, area2)<<endl;	
			}
		}
	}
	return 0;
}

bool check_input(string color, string length, string width, string height){
	if (atof(length) <= 0 || atof (width) <=0 || atof(height)<=0 ){
		cout<<"Invalid entry for "<<color<<" cuboid. Dimensions should be positive real numbers!"<<endl;
	return false;
	}
	else{
		return true;
	}
}

void calculate(string color, double len, double width, double height, double & area, double & volume){
	area = 2* (height *width + width * len + height*len );
	volume = len*width*height;
	display(color, area, volume);
	CheckCubeandDisplay(color, len, width, height);
}

void CheckCubeandDisplay(string color, double length, double width, double height){
	if (length == width && width == height){
		cout<<color<<" cuboid is a cube."<<endl;
	}
	else{
		cout<<color<<" cuboid is not a cube."<<endl;
	}
} 

void display(string color, double area, double volume){
	cout<<"Results for the "<<color<<" cuboid:"<<endl;
	cout<<"Area: "<<area<<endl;
	cout<<"Volume: "<<volume<<endl;
}
string compare(string color1,string color2,  string scale, double q1, double q2){
	if (q1>q2){
		return color1+" has the largest " + scale+".";
	}
	else if (q2>q1){
		return color2 +" has the largest " + scale+".";
	}
	else{
		return "Two cuboids have the same "+scale+".";
	}

}