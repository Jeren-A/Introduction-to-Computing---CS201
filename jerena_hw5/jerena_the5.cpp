#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"

using namespace std;

//struct:
struct info{
		double score;
		double avg_score;
		int count;
		string  s_name;
		string actor;
};

//unique etmek:
bool check( const vector<info> & list, string name, int & loc){
	for (int i=0; i<list.size(); i++){
		if (list[i].s_name == name){
			loc = i;
			//cout<<"list[i].s_name is "<<list[i].s_name<<" and loc is "<<loc<<endl;
			return true;}
	}
	
	return false;
	}
//struct-a ibermek:
void fStruct(vector<info> & list, string sName, double scr, int ocr, bool n, int loc){
	info information;
	if (n == true){
		
		list[loc].score+=scr;
		list[loc].count +=1;
    	}
	else if (n==false){
	information.s_name = sName;
	information.score = scr;
	information.count = ocr;
	list.push_back(information);
	//cout<<"falsa giryan file name lar"<<information.s_name<<endl;

	}
	
}

void modifyAverage(vector<info> & v){
	for(int i = 1; i < v.size(); i++){
		v[i].avg_score = v[i].score / v[i].count;
	}
}
void sorting(vector<info> &list){
int k,loc, numElts = list.size();
    for (k=1; k < numElts; k++){ 
        info hold = list[k];// insert this element
        loc = k;              // location for insertion
        // shift elements to make room for hold (i.e. a[k])
		while (0 < loc  && hold.avg_score < list[loc-1].avg_score){
            list[loc] = list[loc-1];
            loc--;
        }

		if (list[loc-1].avg_score == hold.avg_score){
			while (list[loc-1].s_name < hold.s_name){
   				list[loc] = list[loc-1];
				loc--;
				if (list[loc-1].avg_score != hold.avg_score){
				break;}
			}
		}
        list[loc] = hold;
	}
}
void printSeries(vector <info> & list){
	cout<<"RANK,NAME,ACTOR,POINTS\n";
	int size = list.size();
	int j = 1;
	for (int i = size-1; i > 0; i--){
		cout<<j<<","<<list[i].s_name<<","<<list[i].actor<<","<<list[i].avg_score<<endl;
		j++;
	}
}
void accordingRating(const vector<info> & list){
	double input;
	cout<<"Please enter the minimum rating: ";
	cin>>input;

	if (input > 10 || input < 0){
		cout<<"This is not a valid rating!"<<endl;
		return;
	}
	cout<<"RANK,NAME,ACTOR,POINTS\n";
	int j = 1;
	for(int i = list.size()-1; i > 0; i--){
		if(list[i].avg_score < input){
			return;
		}

		cout<<j<<","<<list[i].s_name<<","<<list[i].actor<<","<<list[i].avg_score<<endl;
		j++;
		
	}
}
void addToFav(const vector<info> & list, vector<info> & favList){
	string input, error;
	cout<< "Please enter the name of series: ";
	cin.clear();
	getline(cin, error);
	getline(cin,input);
	ToUpper(input);

	for(int i = 1; i < list.size(); i++ ){
		if (list[i].s_name == input){
			for(int j = 0; j < favList.size(); j++){
				if (favList[j].s_name == input){
				    cout << "Your favorite list already have "<<input<< endl;
					return;
				}
			}
			favList.push_back(list[i]);
			return;
		}
	}
	cout<<"There is no such TV series!" << endl;
}
void printFav(vector<info> & favList){
	if(!favList.size()){
		cout<< "Your favorite list is currently empty!" << endl;
		return;
	}
	sorting(favList);
	int j = 1; 
	cout<<"RANK,NAME,ACTOR,POINTS\n";
	for (int i = favList.size() - 1; i >=0; i--){
		cout<<j<<","<<favList[i].s_name<<","<<favList[i].actor<<","<<favList[i].avg_score<<endl;
		j++;
	}
}

int main(){

     
	string filename_actors, filename_rating, lineRate, lineActors, actors_name, name;
	ifstream actors_file, rating_file;

    //File open:
	cout<<"Welcome to Netflix TV Series Ratings Calculator!\n";
	do{	
		cout<<"Please enter a filename for Series-Actor file: ";
		cin>>filename_actors;
		actors_file.open(filename_actors.c_str());
		if (actors_file.fail()){
			cout<<"Can not find the specified file.\n";}}
	while(actors_file.fail());

	do{	
		cout<<"Please enter a filename for Rating file: ";
		cin>>filename_rating;
		rating_file.open(filename_rating.c_str());
		if (rating_file.fail()){
			cout<<"Can not find the specified file.\n";}}
	while(rating_file.fail());

	bool n=false;
	vector <info> list;
	fStruct(list, "", 0.0, 0, n, 0);
	
	while (getline(rating_file, lineRate)){

		istringstream lineStream(lineRate);
		double score_from_file;
		lineStream>>score_from_file; //here I get the score

	    string series_name="";
		string name_last="";
		while(lineStream >> name){   //here I get the movie name
			ToUpper(name);
			series_name+=name+" ";
			
		}
		name_last = series_name.substr(0, series_name.length()-1);
		//cout<<score_from_file<<" "<<name_last<<endl;
		int loc=0;
		if (check(list, name_last, loc)==true){
			n= true;
			fStruct(list, name_last, score_from_file, 1, n, loc);
		}
		
		else{
			int loc=0;
			fStruct(list, name_last, score_from_file, 1, n, loc);
		}
		n = false;
	}
	while (getline(actors_file, lineActors)){
		string actor="", actorName = "", seriesName = "", sName = "";
		bool isActorName = true;
		istringstream lineStream(lineActors);
		while(lineStream >> actor){   //here I get the movie name
			ToUpper(actor);
			if ((isActorName == true) && actor.at(actor.length()-1) != ';'){
				actorName+= actor + " ";
			}
			else if((isActorName == true) && actor.at(actor.length()-1) == ';'){
				actorName+= actor.substr(0, actor.length()-1);
				isActorName = false;
			}
			else{ // series name
				ToUpper(actor);
				seriesName +=actor +" ";
			}
			sName = seriesName.substr(0, seriesName.length()-1);
		}
		
		for(int i = 0; i < list.size(); i++){
			if(sName == list[i].s_name){
				list[i].actor = actorName;
			}
		}
	}
	modifyAverage(list);
	sorting(list);
	vector<info> favList;
	string inpt;
	do{
		cout<<"---\nMENU\n1. Print the series\n2. Search the series according to the rating\n3. Add the series to the favorite list\n4. Print the favorite list\n5. Exit\n---\n";
		cout<<"Enter your choice: ";
		cin>>inpt;
		cout<<"---"<<endl;
		while(inpt!="1" && inpt!="2" && inpt!="3" && inpt!="4" && inpt!="5"){  
		    cout<<"This is not a valid option!"<<endl;
			cout<<"---\nMENU"<<endl;
			cout<<"1. Print the series\n2. Search the series according to the rating\n3. Add the series to the favorite list\n4. Print the favorite list\n5. Exit\n";
			cout<<"---\nEnter your choice: ";
			cin>>inpt;
			cout<<"---"<<endl;
		}
		if (inpt == "1"){
			printSeries(list);}
		else if (inpt == "2"){
			accordingRating(list);}
	    else if (inpt == "3"){
			addToFav(list, favList);}
		else if (inpt == "4"){
			printFav(favList);}
		
	}
	while(inpt !="5");

	
	
	actors_file.close();
	rating_file.close();
	return 0;
	
}
	