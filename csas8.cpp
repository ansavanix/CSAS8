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
	topLine(oFile, size, c, "Triangle");
	xAxis(oFile, width);
	oFile << " " << 1;
	oFile << " ";
	outputChar(oFile, size - 1, ' ');
	outputChar(oFile, 4, c);
	outputChar(oFile, width - size - 6, ' ');
	oFile << endl;
	int startFirst = size - 2;
	int startSecond = startFirst + 3;
	for (int i = 2; i < size; i++) {
		if (i < 10) {
			oFile << " ";
		}
		oFile << i;
		oFile << " ";
		outputChar(oFile, startFirst, ' ');
		outputChar(oFile, 2, c);
		outputChar(oFile, startSecond - startFirst - 1, ' ');
		outputChar(oFile, 2, c);
		oFile << endl;
		startFirst--;
		startSecond++;
	}
	oFile << " ";
	oFile << size;
	oFile << "  ";
	outputChar(oFile, width, c);
	oFile << endl;
	xAxis(oFile, width);
}

//slashes
void makeSlash(ofstream& oFile, int size, char c){
  int grid =1;
  
  while (size > 0){
int Yaxis = size;
    if (grid <10){
oFile << " "<< grid;}
    else{
oFile  <<  grid;}
    
while (Yaxis>0){
  oFile<< " ";
  Yaxis --;}
    
oFile<< "  "<< c << "\n";
size--;
grid++;    
  }
  }
//end slash

void makeEight(ofstream &oFile, int size, char c) {
  topLine(oFile, size, c, "Figure Eight");
  xAxis(oFile, size);
  oFile << endl;
  int middle = 0;
  int edgeWidth = 0;
  int rowCount = 0;
  if (size < 10) {
    size = 10;
  }
  edgeWidth = size / 10;
  if (edgeWidth < 2) {
    edgeWidth = 2;
  }
  rowCount = edgeWidth / 2;
  if (size % 2 == 0) 
  {
    middle = size / 2;
  } 
  else
  {
    middle = size / 2;
  }
  int length = size - edgeWidth * 2;
  for (int currentRow = 1; currentRow <= size; currentRow++) {
    if (currentRow < 10)
    {
      oFile << ' ' << currentRow;
    }
    else
    {
      oFile << currentRow;
    }
    oFile << ' ' << ' ';
    if ((size - currentRow == size - 1) || (size - currentRow == middle) || (size - currentRow == 0)) 
    {
      for (int i = 0; i < edgeWidth; i++) 
      {
        oFile << ' ';
      }
      outputChar(oFile, length, c);
    } 
    else 
    {
      outputChar(oFile, edgeWidth, c);
      outputChar(oFile, length, ' ');
      outputChar(oFile, edgeWidth, c);
    }
    /*if (currentRow == (size - 1)) 
    {
      if (size % 2 == 0) 
      {
        outputChar(oFile, edgeWidth, c);
        outputChar(oFile, length, ' ');
        outputChar(oFile, edgeWidth, c);
      }
    }*/
    oFile << endl;
  }
  oFile << endl;
  xAxis(oFile, size);
}

void openInputFile(ifstream& iFile, string prompt){
  string fileName;
  do {
    cout << prompt;
  cin >> fileName;
  iFile.open(fileName);
  } while(!iFile.is_open() && (cout << "Try again." << endl));
}

string createOutputFilename(string typeString, int labelSize) {
  string fileName = typeString;
  fileName = fileName + "_" + to_string(labelSize) + ".txt";
  return fileName;
}

void outputChar(ofstream& oFile, int count, char outChar) {
	for (int i = 0; i < count; i++) {
		oFile << outChar;
	}
}
