#include <iostream>
#include <getopt.h>
#include <string>
#include <dirent.h>


using namespace std;

void print_usage() {
	cerr << "Correct usage: \"myfind [-R] [-i] searchpath filename1 [filename2]...[filename]\"" << endl;
}


int main(int argc, char* argv[]) {
	int c;
	int optc=0;
	int error=0;	
	int option_R=0;
	int option_i=0;
	char* searchPath;
	
	

	while((c = getopt(argc, argv, "Ri")) != EOF) {
		switch(c) {
			case 'R':
				if(option_R) {
					cerr << "Error! Can't have option R multiple times" << endl;
					error=1;
					break;
				}
				option_R=1;
				cout << "myfind: parsing option R" << endl;
				break;
			case 'i':
				if (option_i) {
					cerr << "Error! Can't have option i multiple times" << endl;
					error=1;
					break;
				}
				option_i=1;
				cout << "myfind: parsing option i" << endl;
				break;
			case '?':
				cerr << "Error! Invalid option" << endl;
				error=1;
			default:
				return 1;
		}
	}
	for(int i=1; i<argc; i++) {
		if(**(argv+i) == '-') {
			//cout << "test" << endl;
			optc++;
		}
	}

	if (error || argc-optc<3) {
		print_usage();
		return 1;
	}
	
	searchPath = argv[1+optc];
	cout << "myfind: searchpath is " << searchPath <<endl;	
	

	for(int i=2+optc; i<argc; i++) {
                cout << "myfind: searching for " << argv[i] << endl;
        }


	//experimental
	
	struct dirent *direntp;
	DIR *dirp;
	if((dirp = opendir(argv[1+optc])) == NULL) {
		cerr << "Error! Failed to open directory" << endl;
		print_usage();
		return 1;	
	}
	while((direntp = readdir(dirp)) != NULL) {
		if(direntp->d_name[0] != '.') {
			cout << direntp->d_name << endl;
			for(int i=2+optc; i<argc; i++) {
		                if(*direntp->d_name == *argv[i]) {
					cout << "myfind: found " << argv[i] << " at " << searchPath  << endl;
				}
       			 }
		}
	}
	while ((closedir(dirp) == -1) && (errno == EINTR));
		
	//end experimental

}





