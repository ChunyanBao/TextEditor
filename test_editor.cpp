#include "textEditor.h"

using namespace std;

void test_insert()
{
	//test the function: insert(size_t p,const string & str);
	
	textEditor editor1("Hello World");
	string editor2 = "c++ ";
	cout<<"before insertion: "<<editor1<<endl;

	//first, the position <= length of text
	editor1.insert(0, editor2);
	cout<<"after insertion 1: "<<editor1<<endl;

	//second, the position > length of text
	//expected result - no insertion happen
	editor1.undo();
	editor1.insert(12,editor2);
	cout<<"after insertion 2: "<<editor1<<endl<<endl;
}

void test_append()
{
	//test the function: append(const testEditor & t)
	textEditor editor1("Hello World");
	string editor2 = " c++";
	cout<<"before append: "<<editor1<<endl;

	editor1.append(editor2);
	cout<<"after append: "<<editor1<<endl<<endl;

}

void test_erase1()
{
	//test the function:erase(size_t p, size_t n)
	
	textEditor editor1("Hello World");
	cout<<"original text: "<<editor1<<endl;

	//test case 1: p <= editor1.length() && n <= editor1.length()
	editor1.erase(2,4);
	cout<<"after erase: "<<editor1<<endl;

	editor1.undo();
	//test case 2: p <= editor1.length() && n > editor1.length()
	editor1.erase(2, 15);
	cout<<"after erase: "<<editor1<<endl;	

	editor1.undo();
	//test case 3: p >= editor1.length() - expect: no erase would happen
	editor1.erase(12, 3);
	cout<<"after erase: "<<editor1<<endl<<endl;
}

void test_erase2()
{
	//test the function: erase(size_t n)
	textEditor editor1("Hello World");
	cout<<"original text: "<<editor1<<endl;

	//test case 1: n <= editor1.length();
	editor1.erase(8);
	cout<<"after erase: "<<editor1<<endl;
	
	editor1.undo();

	//test case 2: n > editor1.length(); - expect: erase fail, no erase would happen
	
	editor1.erase(20);
	cout<<"after erase: "<<editor1<<endl<<endl;
}


void test_replace()
{
	//test the function: replace(const textEditor & t)
	textEditor editor1("Hello World");
	string editor2 = "c++";
	cout<<"original text: "<<editor1<<endl;
	//test case 1: pos<editor1.length() && len <editor1.length()
	editor1.replace(0,1,editor2);
	cout<<"test case 1: after replace: "<<editor1<<endl;

	//test case 2: pos<editor1.length() && len>editor1.length()
	editor1.undo();
	editor1.replace(0, 20,editor2);
	cout<<"test case 2: after replace: "<<editor1<<endl;


	//test case 3: pos>editor1.length() && len>editor1.length()
	editor1.undo();
	editor1.replace(20, 6,editor2);
	cout<<"test case 3: after replace: "<<editor1<<endl<<endl;

}

void test_undo_redo_append()
{
	//test function: redo and undo append
	textEditor editor1("Hello World");
	string editor2 = " c++";
	cout<<"original text: "<<editor1<<endl;

	// append 
	editor1.append(editor2);
	cout<<"append: "<<editor1<<endl;

	editor1.undo();
	cout<<"undo : "<<editor1<<endl;
	editor1.redo();
	cout<<"redo : "<<editor1<<endl<<endl;
}

void test_undo_redo_insert()
{
	//test function: redo and undo insert
	textEditor editor1("Hello World");
	string editor2 = " c++";
	cout<<"original text: "<<editor1<<endl;

	// insert
	editor1.insert(11,editor2);
	cout<<"insert: "<<editor1<<endl;

	editor1.undo();
	cout<<"undo test insert: "<<editor1<<endl;

	editor1.redo();
	cout<<"redo test insert: "<<editor1<<endl<<endl;
}


void test_undo_redo_erase1()
{
	//test function: redo redo erase1
	textEditor editor1("Hello World");
	cout<<"original text: "<<editor1<<endl;

	//erase
	editor1.erase(5,3);
	cout<<"erase(5,3): "<<editor1<<endl;

	editor1.undo();
	cout<<"undo test erase(5,3): "<<editor1<<endl;

	editor1.redo();
	cout<<"redo test erase(5,3): "<<editor1<<endl<<endl;
}


void test_undo_redo_replace()
{
	//test function: redo()
	textEditor editor1("Hello World");
	string editor2 = " c++";
	cout<<"original text: "<<editor1<<endl;

	//replace
	editor1.replace(0,6,editor2);
	cout<<"replace "<<editor1<<endl;

	editor1.undo();
	cout<<"undo test replace: "<<editor1<<endl;

	editor1.redo();
	cout<<"redo test replace: "<<editor1<<endl<<endl;
}



void test_undo_redo_erase2()
{
	//test undo redo erase2
	textEditor editor1("Hello World");
	cout<<"original text: "<<editor1<<endl;

	// erase(n)
	editor1.erase(3);
	cout<<"erase(3): "<<editor1<<endl;

	editor1.undo();
	cout<<"undo test erase(3): "<<editor1<<endl;

	editor1.redo();
	cout<<"redo test erase(3): "<<editor1<<endl<<endl;
}

void test_assignment()
{
	//test assignment operator
	textEditor editor1("Hello World");
	textEditor editor2(" c++");

	cout<<"original text: "<<editor1<<endl;

	//
	editor1 = editor2;
	cout<<"assignment test: "<<editor1<<endl<<endl;
}

void test_loadtxt()
{
	//test function loadTXT(char file_name[])
	textEditor editor1("Hello World");
	cout<<"original text: "<<editor1<<endl;

	//test case 1: the text file exist	
	editor1.loadTXT("text.txt");
	cout<<editor1<<endl;

	
	//test ase 2: the file does not exist
	textEditor editor2("Hello World");
	editor2.loadTXT("file.txt");
	cout<<editor2<<endl<<endl;	
}

void test_savetxt()
{
	//test function: saveTXT(char file_name[])
	textEditor editor1("Hello World");
	textEditor editor2("Hello Ellen");
	
	editor1.saveTXT("test.txt");
	editor2.loadTXT("test.txt");
	cout<<"test save to txt: "<<editor2<<endl<<endl;
}



int main()
{
	
	test_insert();
	
	test_append();
	
	test_erase1();
	
	test_erase2();

	test_replace();

	test_undo_redo_append();
	
	test_undo_redo_insert();

	test_undo_redo_erase1();

	test_undo_redo_replace();
	
	test_undo_redo_erase2();

	test_assignment();

	test_loadtxt();

	test_savetxt();
	
	//an example for undo and redo
	cout<<"original editor: "<<endl;
	textEditor Editor("================");
	cout<<Editor<<endl<<endl;

	cout<<"insert A:"<<endl;
	Editor.insert(3,"A");
	cout<<Editor<<endl<<endl;

	cout<<"insert B:"<<endl;
	Editor.insert(6,"B");
	cout<<Editor<<endl<<endl;

	cout<<"insert C:"<<endl;
	Editor.insert(10,"C");
	cout<<Editor<<endl<<endl;

	cout<<"insert D:"<<endl;
	Editor.insert(15,"D");
	cout<<Editor<<endl<<endl;

	cout<<"undo:"<<endl;
	Editor.undo();
	cout<<Editor<<endl<<endl;

	cout<<"undo:"<<endl;
	Editor.undo();
	cout<<Editor<<endl<<endl;

	cout<<"insert E:"<<endl;
	Editor.insert(10,"E");
	cout<<Editor<<endl<<endl;

	cout<<"undo:"<<endl;	
	Editor.undo();
	cout<<Editor<<endl<<endl;

	cout<<"redo"<<endl;
	Editor.redo();
	cout<<Editor<<endl<<endl;
	return 1;
}
