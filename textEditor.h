#include<iostream>
#include<string>
#include<fstream>
#include<stack>

using namespace std;

struct editor
{
	string type;
	size_t position;
	size_t num;
	string mystring;
	editor(const string &t, size_t pos, size_t n, const string & s)
	{
		type = t;
		position = pos;
		num = n;
		mystring = s;
	}

};

class textEditor
{
	private:
		string mytext;
		stack <editor> undo_track;
		stack <editor> redo_track;
	
	public:
		textEditor();
		textEditor(const string & mystring);
		textEditor(const textEditor & t);

		//the insert functions return 1 if success and 0 if failed
		int insert(size_t p, const string & str);

		//append a text
		void append(const string & str);


		//erase n charaters at position p
		int erase(size_t p, size_t n);


		//erase the last n characters
		int erase(size_t n); //erase the last n charasters

		//replace the text with new text
		int replace(size_t pos, size_t len, const string & str);


		void undo();
		void redo();

		//operator overloading
		friend istream & operator >> (istream &, textEditor &);
		friend ostream & operator << (ostream &, const textEditor &);
		textEditor & operator = (const textEditor & t);

		//the load and save to txt file function 
		//return 1 if success, and 0 if failed
		int loadTXT(char file_name[]);
		int saveTXT(char file_name[]);
};
