#include <iostream>
#include <fstream>
using namespace std;

class File_handle{
public:
	explicit File_handle(string filename) : fs(filename.c_str()) { }
	~File_handle() { 
		cout << "File_handle::~File_handle()" << endl;
		fs.close(); 
	}

	fstream fs;
};

int main(){
	string filename, tmp;
	cin >> filename;

	File_handle file(filename);
	while(getline(file.fs, tmp))
		cout << tmp << endl;
}