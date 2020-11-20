#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
using namespace std;

int main(int argc, char **argv) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " DBName\n";
		return 1;
	}
	char command[100] = "mkdir ";
	system(strcat(command, argv[1]));
	chdir(argv[1]);

	ofstream outfile;
	outfile.open("meta.db");
	outfile << '0' << endl;
    outfile.close();
	return 0;
}