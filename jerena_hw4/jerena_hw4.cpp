#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"

using namespace std;

bool check(string & output, string pool_w, string m_w, int count, bool & ch1, bool & ch2);
int main(){
	string filename_pool, filename_m, lineM, m_w, pool_w;
	ifstream pool, m;

	do{	
		cout<<"Please enter a filename for the word pool: ";
		cin>>filename_pool;
		pool.open(filename_pool.c_str());
		if (pool.fail()){
			cout<<"Cannot open the word pool file.\n";}}
	while(pool.fail());

	do{	
		cout<<"Please enter a filename for the main text: ";
		cin>>filename_m;
		m.open(filename_m.c_str());
		if (m.fail()){
			cout<<"Cannot open the main text file.\n";}}
	while(m.fail());
	
	cout<<"You may find the results below:"<<endl;
	cout<<endl;
	char space = ' ';
	while (getline(m, lineM)){
		istringstream lineStream(lineM);
		string line="";
		while(lineStream >> m_w){
			ToLower(m_w);
			string output ="";
			bool ch1 = false, ch2 = false;
			while(pool>>pool_w){
				ToLower(pool_w);
				if (m_w.length() == pool_w.length()){
					if (m_w == pool_w){ 
						line+= pool_w+ space;
						ch1 = true;
						ch2 = false;
						break;
					}
					else{
						int count=0;
						for (int i = 0; i<m_w.length(); i++){
							if(m_w.at(i) == pool_w.at(i)){
							count++;
							}
						}
						int len = m_w.length();
						if ((len%2 == 0 && count>=(len/2)) || (len%2==1 && count>=(len/2)+1)){
							if (check(output, pool_w, m_w, count, ch1, ch2) == true){
								output+=pool_w+',';
								ch1 = true;
								ch2 = true;
								}
						}
					}

				}
			}
			// end of comparing a main word with all pool words
			
			if (ch1 == false){
				line+= "{"+m_w+"}"+space;	//works only if main could not find any possible match
			}
			if (ch2 == true){
				if (output.length()==m_w.length()+1)
					line+=output.substr(0, output.length()-1)+space;
				else
					line+="("+output.substr(0, output.length()-1)+")"+space;//displaying output that was collected in the loop
			}
			//as I need to reread the pool file again, I will clear the data I collected before
			pool.clear();
			pool.seekg(0);
		}
		cout<<line.substr(0, line.length()-1);
		cout<<endl; //will start reading another line
	}

	
	pool.close();
	m.close();



return 0;
}
bool check(string & output, string pool_w, string m_w, int count, bool & ch1, bool & ch2){
	int oldCount = 0;
	if (output == ""){
		output = pool_w+',';
		ch1 = true;
		ch2 = true;
		return false;
	}
	for (int i = 0; i<pool_w.length(); i++){
		if(output.at(i) == m_w.at(i)){
			oldCount++;
		}
	}
	if (oldCount < count){
		output.replace(0, output.length()-1, pool_w);
		output = pool_w + ',';
		return false;
		}
	else if (oldCount == count) {
		return true;
		}
	else
		return false;
		
	}


