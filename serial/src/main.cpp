#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main ()
{
	int a = 0;
    int c = 0;
    int g = 0;
    int t = 0; 
	
    char[1000] dna;

	int length;
	ifstream myfile;
	ofstream newfile;
	
	myfile.open("entrada.txt");
	newfile.open("salida.txt");
	
	myfile >> dna;

	length = strlen(dna);

	for(int i = 0; i < length; i++){
		if (dna[i] == 'A'){
			a++;
		} else if (dna[i] == 'T'){
			t++;
		} else if (dna[i] == 'C'){
			c++;
		}else if (dna[i] == 'G'){
			g++;
		}	
	}
	myfile.close();
	newfile.close();	
	cout << a <<" " << c << " " << g << " " << t;
	return 0;
}