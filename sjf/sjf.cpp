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

		completition[0] = TESTES[t].tempoDeIngresso[0] + TESTES[t].tempoDeDuracao[0];	//O tempo em que o processo é concluido
		turnaround[0] = completition[0] - TESTES[t].tempoDeIngresso[0];					//Turnaround do processos
		waiting[0] = turnaround[0] - TESTES[t].tempoDeDuracao[0];						//Tempo de espera do processo

		cout << "Processo: 1 - " << TESTES[t].tempoDeIngresso[0] << " " << TESTES[t].tempoDeDuracao[0] << endl;
		cout << "Waiting Time: " << waiting[0] << endl;
		cout << "Turnaround: " << turnaround[0] << endl;
		cout << "-----------------\n" << endl;

		for (int i = 1; i < TESTES[t].processos; i++){	//Observe que o loop começa a partir do segundo processo, pois o primeiro ja foi analizado anteriormente
			temp = turnaround[i-1];		//temp recebe o turnaround do processo anterior
			int menor = TESTES[t].tempoDeDuracao[i];	//menor recebe o tempo de duração do processo atual
			for (int j = i; j < TESTES[t].processos; j++){
				/*Aqui o loop irá procurar pelo processo com menor tempo de duração que ja tenha 
				entrado na fila antes do processo em execução ser concluido*/
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

			/*Será então calculado o completition time, turnaround e tempo de espera do processo mais curto encontrado
			e ele será colocado na ordem apropriada na fila*/

			cout << "Processo: " << val+2 << " - " << TESTES[t].tempoDeIngresso[i] << " " << TESTES[t].tempoDeDuracao[i] << endl;
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