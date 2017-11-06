#include "LineEditor.h"

LineEditor::LineEditor(char infName[], char outfName[]) {
	inFile.open(infName, ios::in);
	while (inFile.fail()) {
		cout << "*Fail to open the inputfile*" << endl;
		cout << "Please input inputfile name(eg. file_in.txt): ";
		cin >> infName;
		inFile.open(infName, ios::in);
	}
	strcpy_s(this->infName, infName);
	outFile.open(outfName, ios::out);
}

void LineEditor::Run() {
	char userCommand;

	Help();

	do {
		String curLine;

		if (curLineNo != 0) {
			curLine = textBuffer.getElem(curLineNo);
			cout << curLineNo << " : " << curLine.s << endl << "??";
		}
		else
			cout << "File buffer is empty(please use command r to read file to buffer)" << endl << "??";

		cin >> userCommand;
		userCommand = tolower(userCommand);

		switch (userCommand) {
		case 'b':
			if (!textBuffer.Empty())
				curLineNo = 1;
			else
				cout << "Warning: empty buffer" << endl;
			break;
		case 'c':
			if (!textBuffer.Empty())
				Change();
			else
				cout << "Warning: empty buffer" << endl;
			break;
		case 'd':
			if (!textBuffer.Empty())
				Delete();
			else
				cout << "Warning: empty buffer" << endl;
			break;
		case 'e':
			if (!textBuffer.Empty())
				curLineNo = textBuffer.getCount();
			else
				cout << "Warning: empty buffer" << endl;
			break;
		case 'f':
			if (!textBuffer.Empty())
				Find();
			else
				cout << "Warning: empty buffer" << endl;
			break;
		case 'g':
			if (!textBuffer.Empty())
				Goto();
			else
				cout << "Warning: empty buffer" << endl;
			break;
		case 'h':
			Help();
			break;
		case 'i':
			Insert();
			break;
		case 'l':
			Length();
			break;
		case 'n':
			if (curLineNo < textBuffer.getCount())
				curLineNo++;
			else
				cout << "Warning: at end of buffer" << endl;
			break;
		case 'p':
			if (curLineNo > 1)
				curLineNo--;
			else
				cout << "Warning: at start of buffer" << endl;
			break;
		case 'q':
			break;
		case 'r':
			Read();
			break;
		case 's':
			Substitute();
			break;
		case 'v':
			if (!textBuffer.Empty())
				View();
			else
				cout << "Warning: Empty file" << endl;
			break;
		case 'w':
			if (!textBuffer.Empty())
				Write();
			else
				cout << "Warning: Empty file" << endl;
			break;
		default:
			cout << "*You may use command h to seek help*" << endl;
		}
	} while (userCommand != 'q');
}

void LineEditor::Help() {
	cout << "Valid commands are: \nb(egin)\t\tc(hange)\td(el)\te(nd)\nf(ind)\t\tg(oto)\t\th(elp)\ti(nsert)\nl(ength)\tn(ext)\t\tp(rior)\tq(uit)\nr(ead)\t\ts(ubstitute)\tv(iew)\tw(rite)" << endl;
}

void LineEditor::Change() {
	char tmp[100];
	String temp = textBuffer.getElem(curLineNo);
	cout << "What text segment do you want to replace? ";
	cin >> tmp;
	String segment = tmp;
	cout << "What new text segment do you want to add in? ";
	cin >> tmp;
	String newSeg = tmp;
	int c = temp.find(segment);
	if (c != -1) {
		temp.replace(c, segment.length(), newSeg);
		textBuffer.setElem(curLineNo, temp);
	}
	else
		cout << "Error: Substitution failed" << endl;
}

void LineEditor::Delete() {
	if (curLineNo == 0)
		cout << "Deletion failed" << endl;
	else
		textBuffer.Delete(curLineNo);
	curLineNo = textBuffer.getCount();
}

void LineEditor::Find() {
	char tmp[100];
	String temp = textBuffer.getElem(curLineNo);
	cout << "Enter String to search for: ";
	cin >> tmp;
	String target = tmp;
	int c = temp.find(target);
	if (c != -1) {
		cout << temp.s << endl;
		for (int i = 0; i < c; i++)
			cout << ' ';
		for (unsigned i = 0; i < target.length(); i++)
			cout << "^";
		cout << endl;
	}
	else
		cout << "String was not found" << endl;
}

void LineEditor::Goto() {
	cout << "Goto what line number? ";
	int lineNum;
	cin >> lineNum;
	if (lineNum<1 || lineNum>textBuffer.getCount())
		cout << "Warning: No such line" << endl;
	else
		curLineNo = lineNum;
}

void LineEditor::Insert() {
	cout << "Insert what line number? ";
	int lineNum;
	cin >> lineNum;
	if (lineNum<1 || lineNum>textBuffer.getCount() + 1)
		cout << "Warning: No such line" << endl;
	else {
		cout << "What is the new line to insert? ";
		char temp[100];
		cin.getline(temp, 100);
		cin.getline(temp, 100);
		textBuffer.Insert(lineNum - 1, temp);
		curLineNo = lineNum;
	}
}

void LineEditor::Length() {
	cout << "There are "<<textBuffer.getCount()<<" lines in the file" << endl;
	cout << "Current line's length is " << textBuffer.getElem(curLineNo).length() << endl;
}

void LineEditor::Read() {
	inFile.close();
	inFile.open(infName);
	char temp[100];
	while (!inFile.eof()) {
		inFile.getline(temp, 100);
		String source = temp;
		textBuffer.Insert(textBuffer.getCount(), source);
	}
	inFile.close();
	curLineNo = textBuffer.getCount();
}

void LineEditor::Substitute() {
	cout << "Substitute what line number? ";
	int lineNum;
	cin >> lineNum;
	if (lineNum<1 || lineNum>textBuffer.getCount())
		cout << "Warning: No such line" << endl;
	else {
		cout << "What is the new line to substitute? ";
		char temp[100];
		cin.getline(temp, 100);
		cin.getline(temp, 100);
		textBuffer.Delete(lineNum);
		textBuffer.Insert(lineNum - 1, temp);
		curLineNo = lineNum;
	}
}

void LineEditor::View() {
	int curLine = 1;
	while (curLine <= textBuffer.getCount()){
		cout << textBuffer.getElem(curLine).s << endl;
		curLine++;
	}
}

void LineEditor::Write() {
	int curLine = 1;
	while (curLine <= textBuffer.getCount())
		outFile << textBuffer.getElem(curLine++).s << endl;
}