#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#define MAX_TESTE 10
#define MAX_PROCESSOS 10

using namespace std;

struct TESTES{
	int processos;						//Quantidade de processos do teste
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
		
		/*mwt, mtar são respectivamente a Média de Tempo de Espera e Média de Turnaround. Eles irão acumular o tempo de espera e
		turnaround de todos os processos antes de ser calculado a média depois
		awt é o tempo de espera do processo anterior
		actualWT e actualTar são respectivamente o tempo de espera e o turnaround do processo que está sendo analizado*/

		int mwt = 0, mtar = 0, awt = 0;

		int actualWt = 0;
		int actualTar = actualWt + TESTES[i].tempoDeDuracao[0];
		mwt += actualWt;
		mtar += actualTar;
		
		awt = actualWt;
		
		cout << "Processo: " << 1 << endl;
		cout << "----Waiting Time: " << actualWt << endl;
		cout << "----Turnaround: " << actualTar << endl;

		for (int j = 1; j < TESTES[i].processos; j++){
			actualWt = (awt + TESTES[i].tempoDeIngresso[j-1] + TESTES[i].tempoDeDuracao[j]) - TESTES[i].tempoDeIngresso[j];
			actualTar = actualWt + TESTES[i].tempoDeDuracao[j];
			mwt += actualWt;
			mtar += actualTar;
			
			awt = actualWt;
						
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

	/*quant é um contador que irá registar a quantidade de processos de cada teste///
	processo é um contador que irá contar quantos processos foram registrados///
	teste é um contador que irá contar quantos testes foram registrados. Começa com -1 pois irá incrementar para 0 no primeiro teste
	e incrementará mais uma vez após o ultimo teste*/

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