#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	FILE *arq; // Arquivo sendo lido
	int **valores; // Pega os valores do arquivo
	char str1[30]; // Procura por strings importantes do arquivo
	int dim = 0; // Dimensao da matriz
	int i, j,cont; // Variaveis auxiliares
	
	arq = fopen(argv[1],"rt"); // Le o arquivo que foi passado como argumento na main
	if(arq == NULL) { // em caso de erro
		printf("Deu ruim na leitura do arquivo\n");
		exit(0);
	}
	while(dim == 0) { // Pega a dimensao da matriz
		fscanf(arq,"%s",&str1);
		if(strcmp(str1, "DIMENSION:") == 0) {
			fscanf(arq,"%d",&dim);
		}
	}
	valores = (int**) malloc(dim * sizeof(int*)); // aloca dinamicamente e inicializa a matriz
	for(i = 0; i < dim; i++) {
		valores[i] = (int*) malloc(dim * sizeof(int));
		for(j = 0; j < dim; j++) {
			valores[i][j] = 0;
		}
	}
	i = 0;
	j = 0;
	while(strcmp(str1,"EDGE_WEIGHT_FORMAT:") != 0) // Pega o tipo de leitura
		fscanf(arq,"%s",&str1);
	fscanf(arq,"%s",&str1);
	if(strcmp(str1,"LOWER_DIAG_ROW") == 0) { // Caso seje LOWER DIAG ROW
		while(strcmp(str1,"EDGE_WEIGHT_SECTION") != 0) // Joga a leitura ate o primeiro valor
			fscanf(arq,"%s",&str1);
		cont = ((dim * dim)/2) + (dim/2);
		while(cont > 0) { // Preenche o vetor valores
			fscanf(arq,"%d",&valores[i][j]);
			if(valores[i][j] == 0) {
				i++;
				j = 0;
			}
			else
				j++;
			cont--;
		}
	}
	if(strcmp(str1,"UPPER_ROW") == 0) { // Caso seje UPPER ROW
		while(strcmp(str1,"EDGE_WEIGHT_SECTION") != 0) // Joga a leitura ate o primeiro valor
			fscanf(arq,"%s",&str1);
		cont = ((dim * dim)/2) - (dim/2);
		while(cont > 0) { // Preenche o vetor valores
			if(i >= j)
				j++;
			else if(j == dim) {
				i++;
				j = 0;
			}
			else {
				fscanf(arq,"%d",&valores[i][j]);
				
				cont--;
				j++;
			}
		}
	}
	fclose(arq);
	return 0;
	 
}

