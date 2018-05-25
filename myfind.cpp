#include <iostream>
#include <getopt.h>

using namespace std;

void print_usage() {
	cout << "Correct usage: \"myfind [-R] [-i] searchpath filename1 [filename2]...[filename]\"" << endl;
}


int main(int argc, char* argv[]) {
	cout << "Hello World?" << endl;
	print_usage();
	return 0;
}
