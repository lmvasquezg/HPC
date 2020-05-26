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
void complement(string &secuence);

int main(int argc, char *argv[]) {

   //Lectura de archivos
  ifstream secuence(argv[1]);
  string dna( (istreambuf_iterator<char>(secuence) ),(istreambuf_iterator<char>()    ) );
  secuence.close();

  //Toma de tiempos
  double ts = omp_get_wtime();
  reverse_secuence(dna);
  complement(dna);
  double tf = omp_get_wtime();

  cout << "Time in Seconds: " << tf - ts << " for " << argv[1] << endl;
  
  //Escribir salida
  ofstream outputFile;
  outputFile.open("complemento.txt");
  outputFile << dna;
  outputFile.close();

  return 0;
}


//Reversar secuencia por intercambios de parejas
void reverse_secuence(string &secuence) {
  int len = secuence.length();
  int n = len - 1;
  for(int i = 0; i < (len/2); i++){
    swap(secuence[i], secuence[n]);
    n = n - 1;
  }   
}

//Cambiar cada base por su complemento
void complement(string &secuence){
  
  for(int i = 0 ; i < secuence.length(); i++){
    
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

  }
}
