#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#define MAX_TESTE 10
#define MAX_PROCESSOS 10

using namespace std;

struct TESTES{
	int processos;
	int tempoDeIngresso[MAX_PROCESSOS];
	int tempoDeDuracao[MAX_PROCESSOS];
};

struct TESTES TESTES[MAX_TESTE];

void swap(int *x, int *y){
	int aux = *x;
	*x = *y;
	*y = aux;
}

void selectionSort(int x){
	for (int k = 0; k < x; k++){	
		int i, j, min_idx;
 
   		for (i = 0; i < TESTES[k].processos-1; i++){
	        min_idx = i;
    	    for (j = i+1; j < TESTES[k].processos; j++) if (TESTES[k].tempoDeIngresso[j] < TESTES[k].tempoDeIngresso[min_idx]) min_idx = j;

        	swap(&TESTES[k].tempoDeIngresso[min_idx], &TESTES[k].tempoDeIngresso[i]);
       		swap(&TESTES[k].tempoDeDuracao[min_idx], &TESTES[k].tempoDeDuracao[i]);
   		}
   	}
}


void printLista(int x){
    cout << "\n-----------------\n";
	for (int i = 0; i < x; i++){
		cout << "Teste " << i+1 << endl;
		cout << "Processos Totais: " << TESTES[i].processos << endl;
		for(int j = 0; j < TESTES[i].processos; j++){
			cout << "Processo " << j+1 << ": " << TESTES[i].tempoDeIngresso[j] << " " << TESTES[i].tempoDeDuracao[j] << endl;
		}
		cout << "-----------------\n";
	}
}

void medio(int x){
	cout << "\nDetalhes sobre os processos: \n" << endl;

	for (int i = 0; i < x; i++){
		cout << "Teste: " << i+1 << endl;
		int mwt = 0, mtar = 0;
		int awt = 0, ati = TESTES[i].tempoDeIngresso[0], atd = 0;
		for (int j = 0; j < TESTES[i].processos; j++){
			int actualWt = (awt + ati + atd) - TESTES[i].tempoDeIngresso[j];
			int actualTar = actualWt + TESTES[i].tempoDeDuracao[j];
			mwt += actualWt;
			mtar += actualTar;
			
			awt = actualWt;
			ati = TESTES[i].tempoDeIngresso[j];
			atd = TESTES[i].tempoDeDuracao[j];
			
			cout << "Processo: " << j+1 << endl;
			cout << "----Waiting Time: " << actualWt << endl;
			cout << "----Turnaround: " << actualTar << endl;
		}
		cout << "-----------------" << endl;
		cout << "Medio Waiting Time: " << ((float)mwt/(float)TESTES[i].processos) << endl;
		cout << "Medio Turnaround: " << ((float)mtar/(float)TESTES[i].processos) << endl;
		cout << "-----------------\n" << endl;
	}
}

int main(int argc, char const *argv[]){
	ifstream file;
	file.open("input.txt");
	int quant = 0, processo = 0, teste = -1;
	string s;

	while(getline(file, s)){	
		cout << s << endl;
		istringstream ss(s);
		if (quant < 1){
			ss >> quant;
			processo = 0;
			teste++;
			TESTES[teste].processos = quant;
		}else{
			ss >> TESTES[teste].tempoDeIngresso[processo] >> TESTES[teste].tempoDeDuracao[processo];
			quant--;
			processo++;
		}
	}

	selectionSort(teste);
	printLista(teste);
	medio(teste);

	return 0;
}