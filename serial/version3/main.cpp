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
void reverse_secuence(string &secuence);


int main(int argc, char *argv[]) {

  ifstream secuence(argv[1]);

  string dna( (istreambuf_iterator<char>(secuence) ),(istreambuf_iterator<char>()    ) );
  secuence.close();
  double ts = omp_get_wtime();
  reverse_secuence(dna);
  double tf = omp_get_wtime();
  // cout << dna;
  cout << "Time in Seconds: " << tf - ts << " for " << argv[1] << endl;
    
  ofstream outputFile;
  outputFile.open("complemento.txt");
  outputFile << dna;
  outputFile.close();

  return 0;
}



void reverse_secuence(string &secuence) {
  int len = secuence.length();
  int n = len - 1;
  for(int i = 0; i < (len/2); i++){
    if( secuence[i] == 'A'){
      secuence[i] = 'T';
    }
    else if( secuence[i] == 'T'){
      secuence[i] = 'A';
    }
    else if( secuence[i] == 'G'){
      secuence[i] = 'C';
    }
    else if( secuence[i] == 'C'){
      secuence[i] = 'G';
    }

    if( secuence[n] == 'A'){
      secuence[n] = 'T';
    }
    else if( secuence[n] == 'T'){
      secuence[n] = 'A';
    }
    else if( secuence[n] == 'G'){
      secuence[n] = 'C';
    }
    else if( secuence[n] == 'C'){
      secuence[n] = 'G';
    }

    swap(secuence[i], secuence[n]);
    n = n - 1;
  }   
}
