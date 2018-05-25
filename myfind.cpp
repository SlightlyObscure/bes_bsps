#include <iostream>
#include <getopt.h>
#include <string>
#include <dirent.h>
#include <string.h>

using namespace std;

void print_usage() {
	cerr << "Correct usage: \"myfind [-R] [-i] searchpath filename1 [filename2]...[filename]\"" << endl;
}

int file_searcher(int argc, char* argv[], int optc, int option_i, int option_R, const char* searchPath) {
	//experimental

	
	struct dirent *direntp;
	DIR *dirp;
	if((dirp = opendir(searchPath)) == NULL) {
		cerr << "Error! Failed to open directory or file is not a directory" << endl;
		return 1;
			
	}
	while((direntp = readdir(dirp)) != NULL) {
		if(direntp->d_name[0] != '.') {
			cout << direntp->d_name << endl;
			for(int i=2+optc; i<argc; i++) {
		                if(option_i) {
					if(strcasecmp(direntp->d_name, argv[i]) == 0) {
						cout << "myfind: found " << argv[i] << " at " << searchPath  << endl;
					}
				}
				else {
					if(strcmp(direntp->d_name, argv[i]) == 0) {
                                                cout << "myfind: found " << argv[i] << " at " << searchPath  << endl;
                                        }
				}
       			}
			if(option_R) {
				string PathPart1(searchPath);
				string PathPart2(direntp->d_name);
				string almost_next = PathPart1 + PathPart2 + "/";
				const char* searchPath_next = almost_next.c_str();
				cout << "recursive search at: " << searchPath_next << endl;
				file_searcher(argc, argv, optc, option_i, option_R, searchPath_next);
			}
		}
	}
	while ((closedir(dirp) == -1) && (errno == EINTR));
	

	return 0;

	
	//end experimental
	
}


int main(int argc, char* argv[]) {
	int c;
	int optc=0;
	int error=0;	
	int option_R=0;
	int option_i=0;
	const char* searchPath;
	
	

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
	
	DIR *dirp;
	if((dirp = opendir(argv[1+optc])) == NULL) {
                cerr << "Error! Failed to open directory" << endl;
                print_usage();
                return 1;
        }
	while ((closedir(dirp) == -1) && (errno == EINTR));	

	for(int i=2+optc; i<argc; i++) {
        	cout << "myfind: searching for " << argv[i] << endl;
        }


	file_searcher(argc, argv, optc, option_i, option_R, searchPath);	

	return 0;	

}





