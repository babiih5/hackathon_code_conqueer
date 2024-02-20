// Adição de bibliotecas
#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_PONTOS_PASSADOS 10000
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


//Estrutura
typedef struct {
	int x;
	int y;
}PONTO;



//Ler Ficheiro
PONTO ReadFile(char *nomefile, PONTO pontoatual, PONTO *pontopassado, int num_pontos_passados) {

	FILE *ficheiro;
	ficheiro = fopen(nomefile, "r");
	int x, y;
	double distancia_aux, distancia=2000;
	PONTO pontotemp;
	pontotemp.x = 0;
	pontotemp.y = 0;


	if (ficheiro == NULL) {
		printf("Erro a abrir ficheiro!");
	}
	else {
		while (fscanf(ficheiro, "%d\t%d", &x, &y) == 2) {
			bool ponto_repetido = false;
			for (int i = 0; i < num_pontos_passados; ++i) {
				if (x == pontopassado[i].x && y == pontopassado[i].y) {
					ponto_repetido = true;
					break;
				}
			}

			if (ponto_repetido) {
				continue;
			}

			if ((pontoatual.y - y) == 0) {
				distancia_aux = fabs(pontoatual.x - x);
			}
			else if ((pontoatual.x - x) == 0) {
				distancia_aux = fabs(pontoatual.y - y);
			}
			else {
				distancia_aux = sqrt(pow((fabs(pontoatual.x - x)), 2) + pow((fabs(pontoatual.y - y)), 2));
			}


			if (distancia_aux < distancia && distancia_aux !=0 ) {
				distancia = distancia_aux;
				pontotemp.x = x;
				pontotemp.y = y;
			}
		}

        fclose(ficheiro);
	}
	return pontotemp;
}

//Função para ver autonomia

double CalculaAutonomia(PONTO* pontoatual, PONTO pontotemp, double autonomia, PONTO *pontopassado) {
	PONTO pontoinicial;
	pontoinicial.x = 500;
	pontoinicial.y = 0;
	double distancia_act_temp = 0, distancia_ini_temp= 0, distancia_act_ini=0;



	if ((pontoatual->y - pontotemp.y) == 0) {
		distancia_act_temp = fabs(pontoatual->x - pontotemp.x);
	}
	else if ((pontoatual->x - pontotemp.x) == 0) {
		distancia_act_temp = fabs(pontoatual->y - pontotemp.y);
	}
	else {
		distancia_act_temp = sqrt(pow((fabs(pontoatual->x - pontotemp.x)), 2) + pow((fabs(pontoatual->y - pontotemp.y)), 2));
	}


	if ((pontoatual->y - pontoinicial.y) == 0) {
		distancia_ini_temp= fabs(pontoatual->x - pontoinicial.x);
	}
	else if ((pontoatual->x - pontoinicial.x) == 0) {
		distancia_ini_temp = fabs(pontoatual->y - pontoinicial.y);
	}
	else {
		distancia_ini_temp = sqrt(pow((fabs(pontoatual->x - pontoinicial.x)), 2) + pow((fabs(pontoatual->y - pontoinicial.y)), 2));
	}

	if ((pontoatual->y - pontoinicial.y) == 0) {
		distancia_act_ini = fabs(pontoatual->x - pontoinicial.x);
	}
	else if ((pontoatual->x - pontoinicial.x) == 0) {
		distancia_act_ini = fabs(pontoatual->y - pontoinicial.y);
	}
	else {
		distancia_act_ini = sqrt(pow((fabs(pontoatual->x - pontoinicial.x)), 2) + pow((fabs(pontoatual->y - pontoinicial.y)), 2));
	}



	if ((distancia_act_temp + distancia_ini_temp) > autonomia) {
		pontoatual->x = pontoinicial.x;
		pontoatual->y = pontoinicial.y;
		autonomia = autonomia - distancia_act_ini;
		return autonomia;
	}
	else {
		pontopassado->x = pontoatual->x;
		pontopassado->y = pontoatual->y;
		pontoatual->x = pontotemp.x;
		pontoatual->y = pontotemp.y;
		autonomia = autonomia - distancia_act_temp;
		return autonomia;
	}

}

// Guardar Ficheiro
void SaveFile(char *nomefile, PONTO pontoatual) {
	FILE* ficheiro;
	
	if ((ficheiro = fopen(nomefile, "r")) == NULL) {
		ficheiro = fopen(nomefile, "w");
		if (ficheiro == NULL) {
			printf("Erro ao abrir o arquivo. \n");
			return;
		}
		else {
			fprintf(ficheiro, "Rota: (500,0)");
		}
	}
	else {
		ficheiro = fopen(nomefile, "a");
		if (ficheiro == NULL) {
		printf("Erro ao abrir o arquivo. \n");
		return;
	}
		else {
			fprintf(ficheiro, ",(%d,%d) ", pontoatual.x, pontoatual.y);

		}
	}

	
	fclose(ficheiro);

}



// Função Principal
int main(void) {

	double autonomia = 2000;
	int opcao = 0;
	char* nomefile;

	PONTO pontoatual;
	PONTO pontotemp;
	pontoatual.x = 500;
	pontoatual.y = 0;

	PONTO pontopassado[MAX_PONTOS_PASSADOS];
	int num_pontos_passados = 0;
	
	printf("Selecione o Ficheiro a ser lido \n\t 1. Pontos100.txt \n\t 2. Pontos1k.txt \n\t 3. Pontos10k.txt\n");
	scanf_s("%d", &opcao);

	switch (opcao) {
	case 1:
		nomefile = "Pontos100.txt";
		break;

	case 2:
		nomefile = "Pontos1k.txt";
		break;

	case 3:
		nomefile = "Pontos10k.txt";
		break;

	default:
		printf("Opcao invalida!");
		return 0;
	}

	do {

		pontotemp = ReadFile(nomefile, pontoatual, pontopassado, num_pontos_passados);
		autonomia = CalculaAutonomia(&pontoatual, pontotemp, autonomia, &pontopassado);

		switch (opcao)
		{
		case 1:
			SaveFile("Resultados100.txt", pontoatual);
			break;

		case 2:
			SaveFile("Resultados1k.txt", pontoatual);
			break;

		case 3:
			SaveFile("Resultados10k.txt", pontoatual);
			break;

		default:
			break;
		}
		
		pontopassado[num_pontos_passados++] = pontoatual;

	} while (((pontoatual.x != 500) && (pontoatual.y != 0)));


	return 0;
}