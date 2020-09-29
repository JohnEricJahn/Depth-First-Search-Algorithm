#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "arvore_n_aria.h"
#include "Matriz.h"
#include "Fila.h"

// Alunos: John Eric Jahn && Luiz Guilherme

int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL, "Portuguese");
	
	Arvore arvore;
	Matriz matrizAdjacencia;
	Fila fila;
	FILE *file;
	int *vetorStatus;
	int tam, verticeInicial, i, j, temp, achou;

	
	printf("           *BREADTH FIRST SEARCH*            \n");
	
	file = fopen("grafos.txt", "r");
	
	if(file == NULL) {
		printf("Arquivo nao pode ser aberto\n");
		return 0;
	}
		
	fscanf(file, "%d", &tam);
	
	if(tam < 1) {		
		printf("O TAMANHO DA MATRIZ (1ª LINHA DO ARQUIVO) DEVE SER MAIOR QUE 0");
		exit(0);
	}
	
	inicializa_matriz(&matrizAdjacencia, tam, tam);
	
	for(i=0; i<tam; i++) {
		for(j=0; j<tam; j++) {
			int valorCelula;
			fscanf(file, "%d", &valorCelula);
			if(valorCelula == 1) {
				modifica_valor_matriz(&matrizAdjacencia, i, j, valorCelula);
			}
		}
	}
	
	printf("___________________________________________\n\n");
	
	mostra_matriz(matrizAdjacencia);
	
	fscanf(file, "%d", &verticeInicial);
	verticeInicial = verticeInicial - 1;
	
	vetorStatus = malloc(sizeof(int) * tam);
	memset(vetorStatus, 0, sizeof(int) * tam);
	
	inicializa_fila(&fila, tam);
	inicializa_Arvore(&arvore, verticeInicial);
	
	vetorStatus[verticeInicial] = 1;
	inserir(&fila, verticeInicial);
			
	while(remover(&fila, &temp) != ERRO_FILA_VAZIA) {		
		for(i=0; i<tam; i++) {
			int value;
			le_valor_matriz(matrizAdjacencia, temp, i, &value);
			
			if(value == 1) {
				if(vetorStatus[i] == 0) {
					vetorStatus[i] = 1;
					insere_filho(arvore, temp, i);
					inserir(&fila, i);
				}
			}
		}
	}
	
	gera_xml(arvore);
	
	desaloca_matriz(&matrizAdjacencia);
	desaloca_arvore(&arvore);
	desaloca_fila(&fila);
	
	return 0;
}
