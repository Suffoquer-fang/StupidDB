#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char **argv) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " DBName\n";
		return 1;
	}
	char command[100] = "rmdir /S /Q ";
	system(strcat(command, argv[1]));
	return 0;
}