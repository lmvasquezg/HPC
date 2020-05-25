#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <omp.h>
#include <mpi.h>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
void reverse_secuence(string &secuence, int rank, int nRanks);


int main(int argc, char *argv[]) {

  //Inicialización MPI
  MPI_Init(&argc, &argv);
  int rank, nRanks;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nRanks);

  //Apertura de archivo
  ifstream secuence(argv[1]);
  string dna( (istreambuf_iterator<char>(secuence) ),(istreambuf_iterator<char>()    ) );
  secuence.close();

  MPI_Barrier(MPI_COMM_WORLD);

  double start,finish;
  //Ejecución y toma de tiempos
  if ( rank == 0 ) start = omp_get_wtime();
  reverse_secuence(dna, rank, nRanks);
  if ( rank == 0 ) finish = omp_get_wtime();
  
  MPI_Barrier(MPI_COMM_WORLD);

  //Resultados
  cout << "Time in Seconds: " << tf - ts << " for " << argv[1] << endl;
  
  //Escritura a archivo
  if ( rank == 0){
    ofstream outputFile;
    outputFile.open("complemento.txt");
    outputFile << dna;
    outputFile.close();
  }

  MPI_Finalize();
  return 0;
}



void reverse_secuence(string &secuence, int rank, int nRanks) {
  int len = secuence.length();
  int half = len/2;
  int steps = half / nRanks;
  int start = steps * rank;
  int end = steps * (rank + 1);
  int n = len - start - 1;
  if ( len % 2 == 0 && rank == nRanks - 1) end ++;

  for(int i = start; i < end; i++){
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
  char *complemento = NULL;

  if (rank == 0) {
    complemento = (char *) malloc(sizeof(char) * secuence.length());
  }
  cout << "Hola soy el rank " << rank << " Inicio " << start << " Fin " << end << " Salida " << secuence << endl;
  MPI_Gather(secuence.c_str() + start, end - start, MPI_CHAR, complemento_left, stepsPerProcess, MPI_CHAR, 0, MPI_COMM_WORLD);
  MPI_Gather(secuence.c_str() + ( len - end ), end - start, MPI_CHAR, complemento_rigth, stepsPerProcess, MPI_CHAR, 0, MPI_COMM_WORLD);
  
  cout << "Total" << complemento_left << complemento_rigth << endl;
  //return complemento;

}
