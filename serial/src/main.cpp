#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <omp.h>

using namespace std;
int main(int argc, char *argv[]) {

    ifstream secuence(argv[1]);

    string dna;
    getline(secuence, dna);

    double ts = omp_get_wtime();
    reversed_compliment(dna);
    double tf = omp_get_wtime();

    cout << "Time in Seconds: " << tf - ts << std::endl;
    
    ofstream outputFile;
    outputFile.open("outputDna.txt");
    outputFile << dna;
    outputFile.close();

    return 0;
}



void reversed_compliment(string &secuence) {
    reversed = reverse(secuence.begin(), secuence.end()); 
    replace( secuence.begin(), secuence.end(), 'A', 'T'); 
    replace( secuence.begin(), secuence.end(), 'T', 'A'); 
    replace( secuence.begin(), secuence.end(), 'G', 'C'); 
    replace( secuence.begin(), secuence.end(), 'C', 'G'); 
}