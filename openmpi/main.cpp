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
char* reverse_complement(string &secuence, int rank, int nRanks);


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
  reverse_complement(dna, rank, nRanks);
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



char* reverse_complement(string &secuence, int rank, int nRanks) {
  int len = secuence.length();
  int steps = len / nRanks;
  int start = steps * rank;
  int end = steps * (rank + 1);
  if ( len % nRanks > 0 && rank == nRanks - 1) end = end + (len%nRanks) ;
  cout << steps << endl;
  char *res= new char[len];
  int n = len -1;

  //#pragma omp parallel for shared(secuence,res,len) private(n)
  for ( int i= start; i< end ; i++) {
    n = len -i -1;
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

  char *comp = NULL;
  int receive_counts[nRanks];
  int receive_displacements[nRanks];
  if (rank == 0) {
    comp = (char *) malloc(sizeof(char) * secuence.length());
  }

  for(  int i = 0; i < sizeof(receive_counts)/sizeof(receive_counts[0]); i++ ){
    if(i == nRanks - 1){
      receive_counts[i] = steps + (len % nRanks);
    }else{
      receive_counts[i] = steps;
    }
    receive_displacements[i]=0;
  }
  MPI_Gatherv(res + start, end-start, MPI_CHAR, comp, receive_counts,receive_displacements, MPI_CHAR, 0, MPI_COMM_WORLD);
  
  return res;

}
