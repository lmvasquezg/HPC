#include <stdio.h>
#include <stdlib.h>
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
  char *res = reverse_complement(dna, rank, nRanks);
  if ( rank == 0 ) finish = omp_get_wtime();
  
  MPI_Barrier(MPI_COMM_WORLD);

  //Resultados
  if (rank == 0) cout << "Time in Seconds: " << finish - start << " for " << argv[1] << endl;
  
  //Escritura a archivo
  if ( rank == 0){
    ofstream outputFile;
    outputFile.open("complemento.txt");
    outputFile << res << endl;
    outputFile.close();
    free(res);
  }

  MPI_Finalize();
  return 0;
}



char* reverse_complement(string &secuence, int rank, int nRanks) {
  int len = secuence.length();
  int steps = len / nRanks;
  int start = steps * (nRanks -1 - rank);
  int end = steps * (nRanks - rank);
  if ( len % nRanks > 0 && rank == 0) end = end + (len%nRanks) ;
  char* res = new char[end-start];
  int n = end -start -1;
  omp_set_num_threads(4);
#pragma omp parallel for shared(secuence,res,start,end) firstprivate(n)
  for ( int i= start; i< end ; i++) {
    n = (end - start -1 ) -(i -start) ;
    // cout << "Proceso " << rank << "Hilo" << omp_get_thread_num() << "N " << n <<"I " << i <<endl;
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
    }else{
      res[n] = secuence[i];
    }
    n = n - 1;
  }
  res[end -start] = '\0';
  //res = res +1;
  //string str(res);
  //cout << res << "La parte de " << rank<< endl;
  char *comp = NULL;
  int *dis = NULL;
  int *count = NULL;
  //char *parte = (char *)res;
  int parte_len = strlen(res);
  
  // printf("Rank %d: \n", rank);
  if (rank == 0) {
    dis = (int *)malloc( nRanks * sizeof(int) );
    count = (int *)malloc( nRanks * sizeof(int)) ;
    dis[0] = 0;
    for(int i = 0; i < nRanks ; i++){
      if( i > 0 ){
	count[i]=steps;
      }else{
	count[i]= steps + (len % nRanks);
      }
    }

    for (int i = 1; i < nRanks; i++) {
      dis[i] = dis[i-1] + count[i-1];
    }

    /* allocate string, pre-fill with spaces and null terminator */
    comp = (char *)malloc(len * sizeof(char));            
    for (int i=0; i<len; i++) comp[i] = ' ';
    comp[len] = '\0';   
  } 

  MPI_Gatherv(res, end - start, MPI_CHAR, comp, count,dis, MPI_CHAR, 0, MPI_COMM_WORLD);
  //MPI_Gather(res + start, end -start, MPI_CHAR, rna, steps, MPI_CHAR, 0, MPI_COMM_WORLD);
  if( rank == 0){
    //printf("%d: <%s>\n", rank, comp);
    //free(comp);
    free(dis);
    free(count);
  }
  return comp;

}
