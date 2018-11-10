#include "tempTrender.h"
#include <string>

void project() {
	string pathToFile = "/home/courseuser/git/eliasnyh/MNXB01-project/datasets/tempDataKarlstad.root"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
	
	t.dailyTempDiff(1); // Argument "1" to exclude bad data points, "0" to include bad data points
}
