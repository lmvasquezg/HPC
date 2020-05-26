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
char* reverse_secuence(string &secuence);


int main(int argc, char *argv[]) {

  ifstream secuence(argv[1]);

  string dna( (istreambuf_iterator<char>(secuence) ),(istreambuf_iterator<char>()    ) );
  secuence.close();
  double ts = omp_get_wtime();
  char *res = reverse_secuence(dna);
  double tf = omp_get_wtime();
  cout << "Time in Seconds: " << tf - ts << " for " << argv[1] << endl;
  
  ofstream outputFile;
  outputFile.open("complemento.txt");
  outputFile << res << endl;
  outputFile.close();
  //free(res);
  return 0;
}


char* reverse_secuence(string &secuence) {
  int len = secuence.length();
  char *res= new char[len];
  int n = len - 1;
  for ( int i= 0; i< len ; i++) {
    if( secuence[i] == 'A'){
      res[n] = 'T';
    }
    else if( secuence[i] == 'T'){
      res[n] = 'A';
    }
    else if( secuence[i] == 'G'){
      res[n] = 'C';
    }
    else if( secuence[i] == 'C'){
      res[n] = 'G';
    }
    n = n - 1;
  }
  
  res[len] = '\0';
  res = res +1;
  return res;
}
