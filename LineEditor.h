#include"DbLinkList.h"
#include<fstream>

class LineEditor {
public:
	LineEditor(char [], char []);
	void Run();
private:
	DbLinkList textBuffer;
	int curLineNo;
	ifstream inFile;
	ofstream outFile;
	char infName[20];
	
	void Help();
	void View();
	void Goto();
	void Insert();
	void Delete();
	void Substitute();
	void Change();
	void Find();
	void Length();
	void Read();
	void Write();
};