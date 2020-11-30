#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include "utils.h"
#include <string>
using namespace std;

int main(int argc, char **argv) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " DBName\n";
		return 1;
	}
	char command[100] = "mkdir ";
	system(strcat(command, argv[1]));
	chdir(argv[1]);

	ofstream outfile("meta.db");
	// outfile.open;

	DBConfig config;
	config.init(string(argv[1]));
	// cout << config.dbName << endl;
	outfile << config.dbName << endl;
    outfile << config.tableNum;
    outfile.close();


	return 0;
}