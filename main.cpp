#include"LineEditor.h"

int main() {
	char infName[20], outfName[20];
	cout << "Please input inputfile name(eg. file_in.txt): ";
	cin >> infName;
	cout << "Please input outputfile name(eg. file_out.txt): ";
	cin >> outfName;

	LineEditor Editor(infName, outfName);
	Editor.Run();

	return 0;
}