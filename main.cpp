#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void processFile(char* fileName);
char* getOutFile(char* fileName);
bool openFile(char* fileName, ifstream& stream);
bool openFile(char* fileName, ofstream& stream);
void parse(ifstream&,ofstream&);

int main(int argc, char *argv[])
{
    for(int i = 1; i < argc; ++i)
        processFile(argv[i]);
    return 0;
}

void processFile(char* fileName) {
    char* outFile = getOutFile(fileName);
    ifstream in;
    ofstream out;
    if(openFile(fileName,in)) {
        if(openFile(outFile,out)) {
            parse(in,out);
            out.close();
        }
        in.close();
    }
    delete[] outFile;
}

char* getOutFile(char* fileName) {
    char* result = new char[strlen(fileName)+15];
    strcpy(result,fileName);
    strcat(result,".translate.txt");
    return result;
}

bool openFile(char* fileName, ifstream &stream) {
    if(stream.is_open())
        stream.close();
    stream.open(fileName);
    if(stream.fail()) {
        stream.close();
        return false;
    }
    return true;
}

bool openFile(char* fileName, ofstream &stream) {
    if(stream.is_open())
        stream.close();
    stream.open(fileName);
    if(stream.fail()) {
        stream.close();
        return false;
    }
    return true;
}

void parse(ifstream& in,ofstream& out) {
    string line;
    bool read = false;
    while(!in.eof()) {
        getline(in,line);
        if(read)
            if(line.length())
                out << line << " ";
            else
                read = false;
        else
            read = true;
    }
}
