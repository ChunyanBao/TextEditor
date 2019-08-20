#include"textEditor.h"

textEditor::textEditor(){
	mytext = "my text";
}

textEditor::textEditor(const string & mystring){
	mytext.clear();
	mytext = mystring;
}

textEditor::textEditor(const textEditor & t){
	mytext.clear();
	mytext = t.mytext;
}

//p can be less than or equal to the length of the original text
int textEditor::insert(size_t p, const string & str){
	if(p <= mytext.length())
	{
		mytext.insert(p,str);

		editor action("insert",p,str.length(),str);
		undo_track.push(action);
		return 1;
	}
	else
		return 0; //if p outside of the range
		
}

void textEditor::append(const string & str){
	editor action("append",mytext.length(),str.length(),str);
	mytext.append(str);

	undo_track.push(action);
}

int textEditor::erase(size_t p, size_t n){
	if(p <= mytext.length()){
		string sub = mytext.substr(p,n);//characters going to be erased
		editor action("erase_at_location", p, n, sub);
		undo_track.push(action);

		mytext.erase(p,n);
		return 1;
	}
	else
		return 0;

}


int textEditor::erase(size_t n){
	if(n <= mytext.length()){
		string sub = mytext.substr(mytext.length()-n, n);
		editor action("erase_last",0,n,sub);
		undo_track.push(action);

		mytext.erase(mytext.end()-n, mytext.end());
		return 1;
	}
	else
		return 0;
}

int textEditor::replace(size_t pos, size_t len, const string & str){
	if(pos <= mytext.length()){
		string sub = mytext.substr(pos, len);
		int length = len;
		if(len>mytext.length())
			length = mytext.length();

		mytext.replace(pos,len,str);
		string sumstr = str;
		sumstr.append(sub); 
		editor action("replace", pos, length, sumstr);//str = str+sub, len = sub.length
		undo_track.push(action);
		return 1;
	}
	else
		return 0;
}

void textEditor::undo(){
	if(undo_track.empty()){
		return;
	}
	else{
		if(undo_track.top().type.compare("insert")==0)
		{
			redo_track.push(undo_track.top());
			int pos = undo_track.top().position;
			int len = undo_track.top().num;
			undo_track.pop();
			mytext.erase(pos,len);
		}
		else if(undo_track.top().type.compare("append")==0)
		{
			redo_track.push(undo_track.top());
			int len = undo_track.top().position;
  			undo_track.pop();
			mytext.erase(len);
		}
		else if(undo_track.top().type.compare("erase_at_location")==0)
		{
			redo_track.push(undo_track.top());
			int pos = undo_track.top().position;
			string str = undo_track.top().mystring;
			undo_track.pop();
			mytext.insert(pos,str);
		}
		else if(undo_track.top().type.compare("erase_last")==0)
		{
			redo_track.push(undo_track.top());
			string str = undo_track.top().mystring;
			undo_track.pop();
			mytext.append(str);
		}
		else if(undo_track.top().type.compare("replace")==0)
		{
			redo_track.push(undo_track.top());
			string str = undo_track.top().mystring; 
			int sublen = undo_track.top().num;
			int len = str.length();
			int pos = undo_track.top().position;
			string substr= str.substr(len-sublen,sublen);
			undo_track.pop();
			mytext.replace(pos,len-sublen,substr);
		}

	}
}

void textEditor::redo(){
	if(redo_track.empty())
		return;
	if(redo_track.top().type.compare("insert")==0)
	{
		int pos = redo_track.top().position;
		string str = redo_track.top().mystring;
		mytext.insert(pos,str);
		redo_track.pop();
	}
	else if(redo_track.top().type.compare("append")==0)
	{
		string str = redo_track.top().mystring;
		mytext.append(str);
		redo_track.pop();
	}
	else if(redo_track.top().type.compare("erase_at_location")==0)
	{
		int pos = redo_track.top().position;
		int number = redo_track.top().num;
		mytext.erase(pos,number);
		redo_track.pop();
	}
	else if(redo_track.top().type.compare("erase_last")==0)
	{
		int number = redo_track.top().num;
		mytext.erase(mytext.end()-number, mytext.end());
		redo_track.pop();
	}
	else if(redo_track.top().type.compare("replace")==0)
	{
		string str = redo_track.top().mystring; 
		int pos = redo_track.top().position; 
		int sublen = redo_track.top().num; 
		int len = str.length(); 
		string substr = str.substr(0,len-sublen);
		mytext.replace(pos,sublen,substr);
		redo_track.pop();
	}
}

ostream & operator<<(ostream & o,const textEditor & s){
	o<<s.mytext;
	return o;
}

istream & operator>>(istream & in, textEditor & s){
	string temp;
	in>>temp;
	s.mytext.clear();
	s.mytext = temp;
	return in;
}

textEditor & textEditor::operator = (const textEditor & t){
	if(this == &t){
		return *this;
	}
	mytext.clear();
	mytext = t.mytext;

	return *this;
}

int textEditor::loadTXT(char file_name[]){
	fstream file_in;

	file_in.open(file_name);

	if(!file_in)
		return 0;
	mytext.clear();

	if(file_in)
	{
		char temp[100];

		while(!file_in.eof()){
			file_in.get(temp,100,'\n');
			file_in.ignore(100);
		}

		mytext = temp;		
	}

	file_in.close();
	return 1;
}

int textEditor::saveTXT(char file_name[]){
	ofstream file_out;

	file_out.open(file_name);

	if(!file_out)
		return 0;
	if(file_out){
		file_out<<mytext<<endl;
	}
	file_out.close();
	return 1;
}






