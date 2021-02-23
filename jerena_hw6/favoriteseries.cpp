#include "favoriteseries.h"
#include <iostream>
#include <string>
#include <vector>
#include "strutils.h"
#include "date.h"

using namespace std;

FavoriteSeries::FavoriteSeries(string uName, string uSurname){
	userName = uName;
	userSurname = uSurname;
}

string FavoriteSeries::getFullName() const{

	return userName+" "+userSurname;

}			// returns the full name (name&surname) of the user 
void FavoriteSeries:: addSeries(const series & s){

	int count = favSeries.size();
    favSeries.push_back(s); 
    int loc = count;     
	while (loc > 0 && favSeries[loc-1].seriesName > s.seriesName){    
		favSeries[loc] = favSeries[loc-1];
		loc--; 
    }
    favSeries[loc] = s;  //actual insertion 
}	// add a TV series to the favorite list



bool FavoriteSeries::ifExists(int seriesCode){
	for(int i = 0; i < favSeries.size(); i++){
		if (favSeries[i].seriesCode == seriesCode){
		return true;}
	}
	return false;
}		// check if a series is in the favorite list or not

bool FavoriteSeries::isListEmpty() const{
	return favSeries.size() == 0;
}			// return trues if the favorite list is empty

void FavoriteSeries::dropSeriesSorted(int code){
	if(!isListEmpty()){
		bool posFound = false;
		int k, pos, last =favSeries.size() -1;
		for(k = 0; k < last; k++){
			if (favSeries[k].seriesCode == code){
				pos = k; posFound = true;
			}
			if (posFound){
				favSeries[k] = favSeries[k+1];
			}
		}favSeries.pop_back();

	}
}			// drops the TV series with the given TV series code 
										// from the vector (favSeries) while keeping the vector sorted

int FavoriteSeries::slotint(string slot) const{
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

void FavoriteSeries::sorting(vector<myEpisode> &list) const{
    int k,loc, numElts = favSeries.size();;
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

void FavoriteSeries::alreadyAdded(vector<actor> & act, actor a) const{
	bool found = false;
	for (int i = 0; i < act.size(); i ++){
		if (act[i].actorname == a.actorname){
			act[i].count++;
			found = true;
		}
	}
	if (found  == false){
		a.count = 1;
		act.push_back(a);
	}
	
}
void FavoriteSeries::displayFavoriteList() const{
	
	if(!isListEmpty()){
		cout << getFullName << ", here is your favorite TV series:"<< endl;
		vector<myEpisode> all_episodes;
		for(int i = 0; i < favSeries.size(); i ++){
		for(int j = 0 ; j < favSeries[i].episodes.size(); j++){
			myEpisode e;
			e.series_name = favSeries[i].seriesName;
			e.seriesCode = favSeries[i].seriesCode;
			e.date = favSeries[i].episodes[j].date;
			e.episodeName = favSeries[i].episodes[j].episodeName;
			e.slot = favSeries[i].episodes[j].slot;
			all_episodes.push_back(e);
		}
	}
	sorting(all_episodes);
	cout << "CODE,SERIES,EPISODE,DATE,SLOT"<<endl;
	for(int i = 0; i<all_episodes.size(); i ++){
		cout<< all_episodes[i].seriesCode<<","<< all_episodes[i].series_name<<","<< all_episodes[i].episodeName
			<<","<< all_episodes[i].date<<","<< all_episodes[i].slot<<endl;
	}
	}else{
		cout << getFullName()<< ", your favourite list is empty" << endl;
	}


}		// displays the favorite TV series list


void FavoriteSeries::sortActors(vector<actor> & act) const{
	int k,loc, numElts = act.size();
    for (k=1; k < numElts; k++){ 
        actor hold = act[k];// insert this element
        loc = k;              // location for insertion
        // shift elements to make room for hold (i.e. a[k])
		while (0 < loc  && hold.count < act[loc-1].count){
            act[loc] = act[loc-1];
            loc--;
        }

		if (0 < loc && (act[loc-1].count == hold.count)){
			while (0< loc && (act[loc-1].actorname < hold.actorname)){
   				act[loc] = act[loc-1];
				loc--;
				if (0 < loc && (act[loc-1].count != hold.count)){
				break;}
			}
		}
        act[loc] = hold;
	}

}
void FavoriteSeries::displayFavoriteActors() const{
	if (isListEmpty()){
		cout << getFullName() << ", you did not add any TV series yet!" << endl;
	}
	else{
	cout << userName<< ", here is your favorite actors" << endl;
	vector<actor> actors;
	for (int i = 0; i < favSeries.size(); i ++ ){
		for(int j = 0; j < favSeries[i].actorNames.size(); j++){
			actor a;
			a.actorname = favSeries[i].actorNames[j];
			alreadyAdded(actors, a);
		}
	}

	sortActors(actors);
	int size = actors.size();
	for (int i = size-1; i  = 0; i--){
		cout<<actors[i].actorname<<": "<<actors[i].count<<endl;
	}

	}
}
bool FavoriteSeries::isConflict(const series & inSeries) const{
	for (int ii = 0; ii < inSeries.episodes.size();ii++){
		for (int i = 0; i < favSeries.size(); i ++){
			for(int j= 0; j < favSeries[i].episodes.size();j++){
				if(favSeries[i].episodes[j].date == inSeries.episodes[ii].date){
					if(favSeries[i].episodes[j].slot == inSeries.episodes[ii].slot){
						return true;
					}
				}
			}
		}
	}
	return false;
}

