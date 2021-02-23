//Jeren Annagurbanova 28517
#include <iostream>
#include <string>

using namespace std;

bool validity_source(string source){		//checking whether the source string is valid or nit 
	for (int i= 0; i< source.length(); i++){
		if ((source.at(i) != ' ') && ('0'>source.at(i) || '9' < source.at(i)) && (!isalpha(source.at(i)))){
			return false;}
	}
    return true;
}

//checking whether the search string is valid or not
bool validity_search(string search){
	if  (search.at(search.length()-1) == '+' || search.at(search.length()-1)== '*' || search.at(search.length()-1) == '.' || (search.at(search.length()-2)== '*' && search.at(search.length()-1)== '*' )){
		return true;}
	return false;}

//taking the source string
string getSource(){
	string source = "";
	string word;
	cout<<"Enter source string: ";
	cin>> word;
	while (word != "end" && word !="END"){
	    source+=word +" ";
	    cin>>word;
	}
	return source;
}

//taking search string
bool getSearch(string & search){
	do{
		cout<<"Enter search string: ";
		cin>>search;
		if (search == "QUIT" || search == "quit"){
			return false;
	    }
	}
	while ((validity_search(search))== false);
	return true;

}
//function that presents outputs, when search input ends with plus
void end_plus(string source, string search, int & word_index, string & word)
{
	int space_index=0;
	string srch = search.substr(0, search.length()-1); //search without plus
	for(int i = 0; i< source.length()-1; )
	{   
		if (source.find(srch, i) != string::npos){ //finding search input
			word_index = source.find(srch, i); //finding starting index
			if(word_index == 0 || source.at(word_index-1) == ' '){ //if the word index is the "starting index" or in the middle of the string
				space_index = source.find(' ', word_index);
				word = source.substr(word_index, space_index-word_index);
				cout<<"index: "<<word_index<<" word: "<<word<<endl;	
			}
		i= word_index;}
		i++;}
}
//string reversing that I will be using several times to find the search strings located in the end
string reverse(string & word){
	string temp_word = word;
	int j = 0;
	for (int i = word.length()-1; i>=0; i--){
		temp_word[j] = word[i];
		j++;
	}
	word = temp_word;
	return word;
}


//function that presents outputs, when search input ends with dot "."
void end_dot(string source, string search, int & word_index_last, string & word){
	reverse(source);
	reverse(search);
	source+= ' ';
	int word_index = 0;
	for (int i = source.length()-1; i>=0; ){
		if (source.rfind(search.substr(1, search.length()-1), i) != string::npos)
		{	
			int  length;
			string n_search = search.substr(1, search.length()-1);
			word_index = source.rfind(n_search, i); 
			if (source.at(word_index-1) ==' '){
			word = source.substr(word_index, source.find(' ', word_index)-word_index);
			reverse(word);
			word_index_last = source.length() - (word_index+search.length());
			cout<<"index: "<<word_index_last<<" word: "<< word<<endl; }
			i = word_index;
			}
		i--;	}
}

//function that presents outputs, when search input ends with one star
void end_double_star(string source, string search, int & word_index, string & word){
	string srch = search.substr(0, search.length()-2); //without stars
	int space;
	for (int i= 0; i<= source.length();){
	   if (source.find(srch, i) != string::npos){
			word_index = source.find(srch, i);
			space = source.find(' ', word_index);
			if (source.rfind(' ', word_index) == string::npos)
			{
				word = source.substr(0, space);
			    cout<<"index: "<<word_index<<" word: "<<word<<endl;
				i = word_index;}
			else{
			    word = source.substr(source.rfind(' ', word_index)+1, space-(source.rfind(' ', word_index)+1) );
			    cout<<"index: "<<word_index<<" word: "<<word<<endl;
				i = word_index;
			}		
		}i++;
	}
}

//function that presents outputs, when search input ends with one star
void end_star(string source, string search, int & word_index, string & word){
	int space_index = 0;
	string srch = search.substr(0, search.length()-1);
	for (int i = 0; i<= source.length();){
	if (source.find(srch, i) != string::npos){
		word_index = source.find(srch, i);
	    space_index = source.find(' ', word_index);

		if ( word_index!=0 && source.at(word_index-1) != ' ' && source.at(word_index+search.length()-1) != ' '){

			if (source.rfind(' ', word_index) == string::npos)
			{   
				word = source.substr(0, space_index);
				if((source.rfind(srch, space_index) != (space_index - (search.length()-1))) && (source.find(srch) != 0)){
					i = word_index;
					cout<<"index: "<<word_index<<" word: "<<word<<endl;
				}
			}
			else{
				if((source.rfind(srch, space_index) != (space_index - (search.length()-1)))
					&& (source.rfind(' ', word_index)+1 != source.find(srch,source.rfind(' ', word_index) ))){
				word = source.substr(source.rfind(' ', word_index)+1, space_index-(source.rfind(' ', word_index)+1));
				i = word_index;
			 cout<<"index: "<<word_index<<" word: "<<word<<endl;}
			}	
		}
	}i++;}
}

int main(){
	string source = ";", search = "", word;
	char lastChar;
	bool notQuit;
	int word_index=0;
	while (!validity_source(source)){
		source = getSource();
	}
	
	 notQuit= getSearch(search);  

	
	while(notQuit)
	{  
	   lastChar = search.at(search.length()-1);
	   if (lastChar == '+'){
		   end_plus(source, search, word_index, word);}
	   else if ( lastChar == '.' ){
		   end_dot(source, search, word_index, word);}
	   else if( (lastChar == '*') && search.at(search.length()-2)=='*' ){
		   end_double_star(source, search, word_index, word);}
	   else if ( lastChar == '*'){
	        end_star(source, search, word_index, word);}
	  
	   notQuit = getSearch(search);
	}
	return 0;
}