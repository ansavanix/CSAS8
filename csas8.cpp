#include <iostream>
#include <string>

using namespace std;

//Required Functions:

void makeSlash(ofstream& oFile, int size, char c);

void makeEight(ofstream& oFile, int size, char c);

void makeTriangle(ofstream& oFile, int size, char c);

bool readRecord(ifstream& iFile, string& typeString, int& lSize, char& c);

void openInputFile(ifstream& iFile, string prompt);

bool openOutputFile(ofstream& oFile, string fname);

string createOutputFilename(string typeString, int labelSize);

void outputChar(ofstream& oFile, int count, char outChar);


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
}
