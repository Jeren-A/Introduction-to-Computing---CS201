 #include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "favoriteseries.h"
#include "strutils.h"
#include "date.h"


//no need for string utils
using namespace std;


string upper(string & s){
    for(int i=0; i<= s.length();i++) {
      if(s[i]>='a' && s[i]<='z')
      {
		s[i]=s[i]-32;
      }
    }
    return s;
}

void addEpisodeToSerie(vector<series> & myseries, episode ep){
	int code = ep.seriesCode;
	for(int i = 0; i < myseries.size(); i++){
		if(myseries[i].seriesCode == code){
			myseries[i].episodes.push_back(ep);
			break;
		}
	}
}
int slotint(string slot){
	if (slot == "MORNING"){
		return 1;
	}
	if(slot == "AFTERNOON"){
		return 2;
	}
	if (slot == "EVENING"){
		return 3;
	}
}

void sorting(vector<myEpisode> &list){
int k,loc, numElts = list.size();
bool notequal = true, notequalslot = true;
    for (k=1; k < numElts; k++){ 
        myEpisode hold = list[k] ;// insert this element
        loc = k;               // location for insertion
        // shift elements to make room for hold (i.e. a[k])
		while (0 < loc  && (hold.date < list[loc-1].date)){
            list[loc] = list[loc-1];
            loc--;
        }

		if (0 < loc && (list[loc-1].date == hold.date)){
			 
			while (0< loc && (slotint(hold.slot) < slotint(list[loc-1].slot))){
   				list[loc] = list[loc-1];
				loc--;
				if (0 < loc && (list[loc-1].date != hold.date)){
					break;
				}
			}
			if (0< loc && slotint(hold.slot) == slotint(list[loc-1].slot)){
			
				while (0< loc && hold.seriesCode < list[loc-1].seriesCode){
   					list[loc] = list[loc-1];
					loc--;
					if(0 < loc && (list[loc-1].date != hold.date)){
						break;

					}
					if (0 < loc && slotint(list[loc-1].slot) != slotint(hold.slot)){
						break;
					}
				}
			}
		}
        list[loc] = hold;
	}
}


void printAllTvSeries(const vector<series> & myseries){
	vector<myEpisode> all_episodes;
	for(int i = 0; i < myseries.size(); i ++){
		for(int j = 0 ; j < myseries[i].episodes.size(); j++){
			myEpisode e;
			e.series_name = myseries[i].seriesName;
			e.seriesCode = myseries[i].seriesCode;
			e.date = myseries[i].episodes[j].date;
			e.episodeName = myseries[i].episodes[j].episodeName;
			e.slot = myseries[i].episodes[j].slot;
			all_episodes.push_back(e);
		}
	}
	sorting(all_episodes);
	cout << "CODE,SERIES,EPISODE,DATE,SLOT"<<endl;
	for(int i = 0; i<all_episodes.size(); i ++){
		cout<< all_episodes[i].seriesCode<<","<< all_episodes[i].series_name<<","<< all_episodes[i].episodeName
			<<","<< all_episodes[i].date<<","<< all_episodes[i].slot<<endl;
	} 
}

series exists(int code, const vector<series> & myseries){
	for(int i = 0 ; i < myseries.size(); i++){
		if(myseries[i].seriesCode == code)
			return myseries[i];
	}series a;
	a.seriesName = "";
	return a;
}
void addSeriesFunc(const vector<series> & myseries, FavoriteSeries &favs){
	int usercode;
	cout<< "Enter the code for te TV series you want to add: ";
	cin>> usercode;
	series c = exists(usercode, myseries);
	if (c.seriesName != "")
	{
		if (favs.ifExists(usercode)){
			cout<< favs.getFullName() << ", you can't add this TV series because you already added it!"<< endl;
			return;
		}
		if(favs.isConflict(c)){
			cout<< favs.getFullName() << ", you can't add this TV series because of a date and slot conflict!"<< endl;
			return;
		}else{
		favs.addSeries(c);
		cout<< favs.getFullName() << ", "<< c.seriesName << " added to your schedule." << endl;}
	
	}else{
		cout << favs.getFullName() << ", there is no such TV series in the database!"<< endl; 
	}


}
void dropTVseries(const vector<series> & myseries, FavoriteSeries & favs){
	if(favs.isListEmpty()){
		cout<< favs.getFullName() << ", you did not add any TV series yet!"<<endl;
	    return;
	}
	int usercode;
	cout<< "Enter the code for te TV series you want to drop: ";
	cin>> usercode;
	series c = exists(usercode, myseries);
	if (c.seriesName != "")
	{
		if (!favs.ifExists(usercode)){
			cout<< favs.getFullName() << ", there is no such a TV series in your favorite list!" << endl;		
		}else
		{   
			favs.dropSeriesSorted(usercode);
			cout<< favs.getFullName() << ", "<<c.seriesName << " has been dropped from your favorite list!"<< endl;
		}
	}else{
		cout << favs.getFullName() << ", there is no such TV series in the database!"<< endl; 
	}
}
void printFavSchedule(FavoriteSeries & favs){
	if(favs.isListEmpty()){
		cout<< favs.getFullName()<< ", you did not add any TV series yet!"<< endl;
	}
	else{
		favs.displayFavoriteList();
	}
}
void printFavActors(FavoriteSeries & favs){
	favs.displayFavoriteActors();
}


int main()
{
    ifstream serie, episodes;
    string seriesLine, seriesEpisodes; 
	string filenameS = "series.txt";
	string filenameE = "episodes.txt";
    vector<series> myseries;
    serie.open(filenameS.c_str());
    episodes.open(filenameE.c_str());
    
    while (getline(serie, seriesLine)){
        series s;    ////////////////////////////////////////////////////////////////--------------------
		seriesLine= seriesLine+",";
		upper(seriesLine);
        istringstream lineStream(seriesLine);
           
        int ucode;
        string name, seriesName, actorName;
		vector <string> actors;
		actorName = "";
        
      
        lineStream>>ucode;
		s.seriesCode = ucode; //////////////////////////////////////////////////////
       
        bool isName = true;
		bool isActor = true;
		while(lineStream >> name){  
			if ((isName == true) && name.at(name.length()-1) != ';'){
				seriesName+= name + " ";	
			}
			else if((isName == true) && name.at(name.length()-1) == ';'){
				seriesName+= name.substr(0, name.length()-1);
				isName = false;
				s.seriesName = seriesName;	 /////////////////////////////////////////////////////

			}
			else{
				if (name.at(name.length()-1) != ',' && isName == false){
					actorName+= name + " ";	
				}
				else if(name.at(name.length()-1) == ',' && isName == false){
					actorName+= name.substr(0, name.length()-1);
					actors.push_back(actorName);
					actorName = "";	
				}	
			}
		}
		s.actorNames = actors; ////////////////////////////////////////////////////////////////////
		myseries.push_back(s); ///////////////////////////////////////////////////////////////////
	}

	string episodesLines;
	
	while (getline(episodes, episodesLines)){
		
		episode ep; /////////////////////////////////////////////////////////////////////////////////////////
		upper(episodesLines);
		
		istringstream lineStream(episodesLines);
		
		int code;
		
		lineStream>>code;
		ep.seriesCode = code; //////////////////////////////////////////////////////////////////////////////////
		string sdate, timeslot, strng, episodeName = "";
		
		lineStream>>sdate;

		int day, month, year, fslash, sslash;

		fslash = sdate.find('/');
		sslash = sdate.find('/', fslash+1);
		month = atoi(sdate.substr(0, fslash));
		day = atoi(sdate.substr(fslash+1, sslash-fslash-1));
		year = atoi(sdate.substr(sslash+1, sdate.length()-sslash-1));
		Date edate(month, day, year);

		ep.date = edate; ////////////////////////////////////////////////////////////////////

		string lepisodename;
		lineStream >> timeslot;
		ep.slot =timeslot;
		while (lineStream >> strng){
			episodeName+=strng+" ";
		}
		lepisodename = episodeName.substr(0, episodeName.length()-1);
		ep.episodeName = lepisodename;  /////////////////////////////////////////////////////
		addEpisodeToSerie(myseries, ep); ////////////////////////////////////////////////////
	}
   //////////////////////////////////////////////////////////////////////////////////////////////////////////
	string error, uname, usurname, inpt;
	cout<<"Welcome to my favorite TV series schedule program!"<<endl;
	cout<<"Please enter your name and surname: ";
	cin>>uname>>usurname;
	upper(uname);
	upper(usurname);
	//cout<<"name is "<<uname<<usurname<<endl;
    
	FavoriteSeries favs(uname, usurname);
	do{
		cout<<"---\nMENU\n1. Print all TV series\n2. Add TV series\n3. Drop TV series\n4. Print your favorite TV series with schedule\n5. Print all your favorite actors\n6. Exit\n---\n";
		cout<<"Enter your choice: ";
		cin>>inpt;
		cout<<"---"<<endl;
		while(inpt!="1" && inpt!="2" && inpt!="3" && inpt!="4" && inpt!="5" && inpt!="6"){  
		    cout<<"This is not a valid option!"<<endl;
			cout<<"---\nMENU\n1. Print all TV series\n2. Add TV series\n3. Drop TV series\n4. Print your favorite TV series with schedule\n5. Print all your favorite actors\n6. Exit\n---\n";
			cout<<"---\nEnter your choice: ";
			cin>>inpt;
			cout<<"---"<<endl;
		}
		if (inpt == "1"){
			printAllTvSeries(myseries);
		}
		else if (inpt == "2"){
			addSeriesFunc(myseries, favs);
		}
	    else if (inpt == "3"){
			dropTVseries(myseries, favs);
		}
		else if (inpt == "4"){
			 printFavSchedule(favs);
		}
        else if (inpt == "5"){
			 printFavActors(favs);
		}
		
	}
	while(inpt !="6");

	serie.close();
	episodes.close();
	
	return 0;
}

