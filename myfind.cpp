#include <iostream>
#include <getopt.h>

using namespace std;

void print_usage() {
	cout << "Correct usage: \"myfind [-R] [-i] searchpath filename1 [filename2]...[filename]\"" << endl;
}


int main(int argc, char* argv[]) {
	int c;
	int optc=0;
	int error=0;	
	int option_R=0;
	int option_i=0;

	while((c = getopt(argc, argv, "Ri:")) != EOF) {
		switch(c) {
			case 'R':
				if(option_R) {
					error=1;
					break;
				}
				option_R=1;
				optc++;
				cout << "myfind: parsing option R" << endl;
				break;
			case 'i':
				if (option_i) {
					error=1;
					break;
				}
				option_i=1;
				optc++;
				cout << "myfind: parsing option i" << endl;
				break;
			case '?':
				error=1;
			default:
				return 1;
			
		}
	}
	if (error || argc-optc<3) {
		print_usage();
		return 1;
		
	}
	
	for(int i=1+optc; i<argc; i++) {
		cout << "myfind: parsing argument " << argv[i] << endl;
	}
	return 0;

}





