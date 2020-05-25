#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <omp.h>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
void reversed_compliment(string &secuence);

int main(int argc, char *argv[]) {

    ifstream secuence(argv[1]);
    string dna( (istreambuf_iterator<char>(secuence) ), (istreambuf_iterator<char>()    ) );
    secuence.close();
    double ts = omp_get_wtime();
    reversed_compliment(dna);
    double tf = omp_get_wtime();

    cout << "Time in Seconds: " << tf - ts << " for " << argv[1] << endl;
    
    ofstream outputFile;
    outputFile.open("complemento.txt");
    outputFile << dna;
    outputFile.close();
    
    return 0;
}



 void reversed_compliment(string 
&secuence) {
    reverse(secuence.begin(), secuence.end()); 
    replace(secuence.begin(), secuence.end(), 'A', 't'); 
    replace(secuence.begin(), secuence.end(), 'T', 'a'); 
    replace(secuence.begin(), secuence.end(), 'G', 'c'); 
    replace(secuence.begin(), secuence.end(), 'C', 'g'); 
    boost::to_upper(secuence);
    //cout<< secuence << endl;
   
}
