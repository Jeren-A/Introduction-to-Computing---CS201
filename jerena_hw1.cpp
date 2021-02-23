//Student ID: 28517
//Full Name: Jeren Annagurbanova
//Course: CS201



#include <iostream>
#include <string>
using namespace std;

int main(){

	
	string name, course, answer, cgrade, pgrade, choice;
	cout<<"Welcome to the Fall 2020-2021 Semester grading system. What is your name? ";
	cin>>name;
    cout<<"Hello "<<name<<"! Please enter the name of the course to be processed: ";
	cin>>course;
	cout<<"Hello "<<name<<"! If you take the "<<course<<" for the first time, enter YES otherwise NO: ";
	cin>>answer;
	if (answer=="YES"){  
		cout<<"What is your grade from (A,B,C,D,F)? ";
		cin>>cgrade;
		if ((cgrade=="D") || (cgrade== "C") || (cgrade == "B") || (cgrade == "A" )) {    
			cout<<"Do you want to switch your grade from "<<cgrade<<" to S (YES or NO)? ";
			cin>>answer;
			if (answer== "YES"){
				cout<<name<<", your final grade for "<<course<<" is S. Goodbye..."<<endl;}
			else if (answer == "NO"){
				cout<<name<<", your final grade for "<<course<< " is "<<cgrade<<". Goodbye..."<<endl;}
			else{
				cout<<"Invalid grade selection. Goodbye..."<<endl;}
		}
		else if (cgrade=="F"){
			cout<<"Do you want to switch your grade from "<<cgrade<<" to U (YES or NO)? ";
			cin>>answer;
			if (answer== "YES"){
				cout<<name<<", your final grade for "<<course<<" is U. Goodbye..."<<endl;}
			else if (answer == "NO"){
				cout<<name<<", your final grade for "<<course<< " is "<<cgrade<<". Goodbye..."<<endl;}
			else{
				cout<<"Invalid grade selection. Goodbye..."<<endl;}}
		else {
			cout<<"Invalid grade selection. Goodbye..."<<endl;}
		}
	else if (answer == "NO"){
		cout<<"Please enter your previous grade from (A,B,C,D,F,S,U): ";
		cin>>pgrade;
		if ((pgrade!="D") && (pgrade!= "C") && (pgrade != "B") && (pgrade != "A" )&& (pgrade != "F" )&&(pgrade != "S" )&&(pgrade != "U" ) ){
			cout<<"Invalid grade selection. Goodbye..."<<endl;
			}
		else{
			cout<<"Please enter your current grade from (A,B,C,D,F): ";
			cin>>cgrade;
			if ((cgrade!="D") && (cgrade!= "C") && (cgrade != "B") && (cgrade != "A" )&&  (cgrade != "F" )&& (cgrade != "S" )&&(cgrade != "U" ) ){
				cout<<"Invalid grade selection. Goodbye..."<<endl; }
			else{
				cout<<"Please enter the grade you want to choose from (A,B,C,D,F,S,U): ";
				cin>>choice;
				if ((choice!="D") &&  (choice != "C") &&  (choice != "B") &&  (choice != "A" )&&  (choice != "F" )&& (choice != "S" )&& (choice != "U" ) ){
					cout<<"Invalid grade selection. Goodbye..."<<endl;}
				else{
					if ((cgrade=="F") && (pgrade == "F") && (choice!= "F")){
						cout<<"Invalid grade selection. If you received "<<pgrade<<" before, and fail this semester, you get F."<<endl;} //student has to choose F no other way
					else if ((cgrade=="F") &&  (pgrade== "S") && (choice!= "F")){
						cout<<"Invalid grade selection. If you received "<<pgrade<<" before and fail this semester, you get F."<<endl;} //again student has to choose F no other way
					else if ((cgrade=="F") && ((pgrade=="A")|| (pgrade == "B")|| (pgrade == "C")|| (pgrade == "D")|| (pgrade == "U")) && ((choice != "F") && (choice != "U"))){
						cout<<"Invalid grade selection. You cannot choose a higher or lower grade than you deserve."<<endl;}
					else if (((cgrade == "A") || (cgrade == "B") || (cgrade == "C") || (cgrade == "D")) && (pgrade == "U") && (choice!=cgrade && choice!= "S")){
						cout<<"Invalid grade selection. If you received U before, you may choose "<< "S"<<" or current letter grade."<<endl;}
					else if ((cgrade == "A") && ((choice!= "A")  && (choice!= "S"))){ //below I will be verifying the student not to choose the grade higher than they deserve
						cout<<"Invalid grade selection. You cannot choose a higher or lower grade than you deserve."<<endl;}
					else if ((cgrade == "B") && ((choice!= "B") && (choice!= "S"))){
						cout<<"Invalid grade selection. You cannot choose a higher or lower grade than you deserve."<<endl;}
					else if ((cgrade == "C") && ((choice != "C") && (choice!= "S"))){
						cout<<"Invalid grade selection. You cannot choose a higher or lower grade than you deserve."<<endl;}
					else if ((cgrade == "D") && ((choice!= "D") && (choice!= "S"))){
						cout<<"Invalid grade selection. You cannot choose a higher or lower grade than you deserve."<<endl;}
					else{
						cout<<name<<", your final grade for "<<course<<" is "<<choice<<". Goodbye..."<<endl;}}}
		}	
	}
			
	else{}
	return 0;
}
