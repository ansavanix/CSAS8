#include <iostream>
#include <string>
#include <fstream>

using namespace std;


//Helper Functions:

void topLine(ofstream& oFile, int size, char c, string symbolName); //Anthony

void xAxis(ofstream& oFile, int size); //Anthony

//Required Functions:

void makeSlash(ofstream& oFile, int size, char c); //Sebastian

void makeEight(ofstream& oFile, int size, char c); //Charles

void makeTriangle(ofstream& oFile, int size, char c); //Anthony

bool readRecord(ifstream& iFile, string& typeString, int& lSize, char& c); //Yu Peng

void openInputFile(ifstream& iFile, string prompt); //Miracle

bool openOutputFile(ofstream& oFile, string fname); //Yu Peng

string createOutputFilename(string typeString, int labelSize); //Miracle

void outputChar(ofstream& oFile, int count, char outChar); //Anthony


int main() {
	cout << "Welcome to Rebel Alliance Computational Support" << endl;
	
	ifstream fileSpec;
	openInputFile(fileSpec, "Input Specification File: ");
	
	string symbolType;
	int size;
	char c;
	
	int shapeCount = 0;
	
	while (readRecord(fileSpec, symbolType, size, c)) {
		string outputFileName = createOutputFilename(symbolType, size);
		ofstream outputFile;
		
		cout << "File \"" << outputFileName << "\" ";
		if (!openOutputFile(outputFile, outputFileName)) {
			cout << "failed to open" << endl;
			continue;
		}
		cout << "successfully opened" << endl;
		shapeCount++;
		
		if (symbolType == "slash") makeSlash(outputFile, size, c);
		else if (symbolType == "figureEight") makeEight(outputFile, size, c);
		else makeTriangle(outputFile, size, c);
		
		outputFile.close();
	}
	
	cout << "Finished processing input file" << endl;
	cout << shapeCount << "Shapes Created" << endl;
	return 0;
}

bool readRecord(ifstream& iFile, string& typeString, int& lSize, char& c)
{
	if(iFile.eof()){
		return false;
	} else {
	iFile >> typeString >> lSize >> c;
	return true;
	}
}

bool openOutputFile(ofstream& oFile, string fname)
{
	oFile.open(fname);
	if(oFile.is_open()){
		return true;
	}
	return false;
}

void makeEight(ofstream& oFile, int size, char c)
{
    int middle = 0;
    int edgeWidth = 0;
    int rowCount = 0;
    if (size < 10)
    {
        size = 10;
    }
    edgeWidth = size / 10;
    if (edgeWidth < 2)
    {
        edgeWidth = 2;
    }
    rowCount = edgeWidth / 2;
    if (size % 2 == 0)
    {
        int middle = size / 2;
    }
    else
    {
        middle = (size / 2) + 1;
    }
    for (int currentRow = 1; currentRow <= size; currentRow++)
    {
        cout << (currentRow + 1) + "  ";
        if ((size - currentRow == size - 1) || (size - currentRow == middle) || (size - currentRow == 0))
        {
             for (int i = 0; i < edgeWidth; i++)
             {
                   cout << " ";
             }
        }

    }
}

void topLine(ofstream& oFile, int size, char c, string symbolName) {
	oFile << "Symbol: " << symbolName << " Size: " << size << " Character: '" << c << "'" << endl;
}

void xAxis(ofstream& oFile, int size) {
	oFile << "    ";
	int current = 1;
	for (int i = 0; i < size; i++) {
		oFile << current;
		current++;
		if (current == 10) current = 0;
	}
	oFile << endl;
}

void makeTriangle(ofstream& oFile, int size, char c) {
	int width = size * 2;
	topLine(oFile, width, c, "Triangle");
	xAxis(oFile, width);
	outputChar(oFile, size - 2, ' ');
	outputChar(oFile, 4, c);
	outputChar(oFile, width - size - 6, ' ');
	oFile << endl;
	int startFirst = size - 2;
	int startSecond = startFirst + 4;
	for (int i = 1; i < size; i++) {
		if (i < 10) {
			oFile << " ";
		}
		oFile << i;
		outputChar(oFile, startFirst, ' ');
		outputChar(oFile, 2, c);
		outputChar(oFile, startSecond - startFirst - 1, ' ');
		outputChar(oFile, 2, c);
		oFile << endl;
		startFirst--;
		startSecond++;
	}
	xAxis(oFile, width);
}
