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
	for (int t = 0; t < x; t++){
		cout << "Teste: " << t+1 << "\n" << endl;

		int temp, val, completition[MAX_PROCESSOS], turnaround[MAX_PROCESSOS], waiting[MAX_PROCESSOS];

		completition[0] = TESTES[t].tempoDeIngresso[0] + TESTES[t].tempoDeDuracao[0];
		turnaround[0] = completition[0] - TESTES[t].tempoDeIngresso[0];
		waiting[0] = turnaround[0] - TESTES[t].tempoDeDuracao[0];

		cout << "Processo: 1 - " << TESTES[t].tempoDeIngresso[0] << " " << TESTES[t].tempoDeDuracao[0] << endl;
		cout << "Waiting Time: " << waiting[0] << endl;
		cout << "Turnaround: " << turnaround[0] << endl;
		cout << "-----------------\n" << endl;

		for (int i = 1; i < TESTES[t].processos; i++){
			temp = turnaround[i-1];
			int menor = TESTES[t].tempoDeDuracao[i];
			for (int j = i; j < TESTES[t].processos; j++){
				if (temp >= TESTES[t].tempoDeIngresso[j] && menor >= TESTES[t].tempoDeDuracao[j]){
					menor = TESTES[t].tempoDeDuracao[j];
					val = j;
				}
			}
			completition[val] = temp + TESTES[t].tempoDeDuracao[val];
			turnaround[val] = completition[val] - TESTES[t].tempoDeIngresso[val];
			waiting[val] = turnaround[val] - TESTES[t].tempoDeDuracao[val];

			swap(&TESTES[t].tempoDeDuracao[val], &TESTES[t].tempoDeDuracao[i]);
			swap(&TESTES[t].tempoDeIngresso[val], &TESTES[t].tempoDeIngresso[i]);
			swap(&completition[val], &completition[i]);
			swap(&turnaround[val], &turnaround[i]);
			swap(&waiting[val], &waiting[i]);

			cout << "Processo: " << i << " - " << TESTES[t].tempoDeIngresso[i] << " " << TESTES[t].tempoDeDuracao[i] << endl;
			cout << "Waiting Time: " << waiting[i] << endl;
			cout << "Turnaround: " << turnaround[i] << endl;
			cout << "-----------------\n" << endl;
		}
		int medioWaiting = 0;
		int medioTurn = 0;
		for (int m = 0; m < TESTES[t].processos; m++){
			medioWaiting += waiting[m];
			medioTurn += turnaround[m];
		}
		cout << "-----------------" << endl;
		cout << "Medio Waiting Time: " << ((float)medioWaiting)/TESTES[t].processos << endl;
		cout << "Medio Turnaround: " << ((float)medioTurn)/TESTES[t].processos << endl;
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




/*
p1:	0 2 2 2 2
p2:	0 0 1 1 1 2 2 2 2 2 2 2 2 2
p3:	0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2

Waiting Time = anterior("Tempo de Ingresso" + Tempo de Duração + "Waiting Time") - "Tempo de Ingresso"
Turnaround = "Waiting Time" + "Tempo de Duração"
*/