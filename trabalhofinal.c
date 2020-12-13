#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define MAX 16
#define MAXFILA 4
#define MAXPILHA 7
//PROGAMADOR JOÃO LUCAS SILVA MOTA

//1ª Parte -- PARTE DAS STRUCTS DE CADA ESTRUTURA

typedef struct
{
	int indice;
	char nome[20];
	int tam;
} APP;

typedef struct
{
	int IA, FA, IL, FL;
	APP v[MAX];
} LLV;

typedef struct
{
	APP info;//informação de tam/indice/nome
	int prox;//próximo
	int ant; //anterior
} no;

typedef struct
{
	no vet[MAX];
	int disp;
} LLSE;

typedef struct
{
	no vet[MAX];
	int disp;
} LLDE;

typedef struct
{
	no vetor[MAX];
	int topo;
} Pilha;

typedef struct
{
	no vet[MAXFILA];
	int disp;
} Fila;










//2ª Parte-- INICIALIZAÇÃO

void inicializar(LLV *store, LLSE *meusapps , LLDE *run, Fila *F , Pilha *execucao)
{
	int i;

	store->IA = 1;//LLV
	store->FA = 15;
	store->IL = 0;
	store->FL = 0;



	for(i = 0; i < MAX; i++)  //LLSE
	{
		meusapps->vet[i].prox = i + 1;
	}
	meusapps->vet[0].prox = -5;// lista vazia no começo
	meusapps->vet[MAX - 1].prox = -1; // final da lista em si
	meusapps->disp = 1;

	for(i = 0; i < MAX; i++)   //LLDE
	{
		run->vet[i].prox = i + 1;
		run->vet[i].ant = i - 1;
	}
	run->vet[0].prox = -5;
	run->vet[0].ant = -5;
	run->vet[MAX - 1].prox = -1;
	run->vet[MAX - 1].ant = -1;
	run->disp = 1;

	execucao->topo = 0; //PILHA('LIFO')

	for(i = 0; i < MAXFILA; i++)   //FILA ('FIFO') É UMA LLDE COM INSERÇÃO SÓ NO INICIO E FIM
	{
		F->vet[i].prox = i + 1;
		F->vet[i].ant = i - 1;
	}
	F->vet[0].prox = -5;
	F->vet[0].ant = -5;
	F->vet[MAXFILA - 1].prox = -1;
	F->vet[MAXFILA - 1].ant = -1;
	F->disp = 1;

}










///3ª PARTE--------- FUNÇÕES QUE ACHAM A POS DE INSERÇÃO PARA O LLSE E LLDE----
//ps:a pos do LLV JÁ ESTÁ DENTRO DA FUNÇÃO DE INSERIR!

//LLSE
int posicaoLLSE(LLSE *futuro, APP passado[], int j) //esta função só é chamada quando a lista não está cheia; retorna o índice de onde eu devo inserir
{
	int pos, i;
	pos = 21; //valor aléatorio que escolhi para o primeiro valor de posição
	i = futuro->vet[0].prox; //recebe o inicio da lista
	while(1)  //vai até o final da lista
	{
		if (futuro->vet[i].info.tam >= passado[j].tam)
		{
			pos = i;
			break;	//quando achar a posição de inserção "para"
		}
		if(futuro->vet[i].prox == -5)
			break;
		i = futuro->vet[i].prox;//icrementador do loop
	}
//se posição continuar 21 entao é porque está no final da lista+1,
//fiz este ajuste, pois minha comparação é do tipo 'menor que' observa-se isso no loop

	return pos;
	//posição pode retornar de -5 a 16 ou 21 que é o valor que vou manipular no final
}


//LLDE
int posicaoLLDE(LLDE *futuro, APP passado[], int j) //esta função só é chamada quando a lista não está cheia; retorna o índice de onde eu devo inserir
{
	int pos, i;
	pos = 21; //valor aléatorio que escolhi para o primeiro valor de posição
	i = futuro->vet[0].prox; //recebe o inicio da lista
	while(1)  //vai até o final da lista
	{
		if (futuro->vet[i].info.tam >= passado[j].tam)
		{
			pos = i;
			break;	//quando achar a posição de inserção "para"
		}
		if(futuro->vet[i].prox == -5)
			break;
		i = futuro->vet[i].prox;//icrementador do loop
	}
//se posição continuar 21 entao é porque está no final da lista+1,
//fiz este ajuste, pois minha comparação é do tipo 'menor que' observa-se isso no loop

	return pos;
	//posição pode retornar de -5 a 16 ou 21 que é o valor que vou manipular no final
}










///4ª PARTE ----------- FUNÇÕES INSERIR----------------


//INSERIR LLV
void inserirLLV(LLV *futuro, APP passado[], int i)
{
	int j, posicao;
	APP guarda;//operação quando insere no final
	if (futuro->IA == futuro->IL && futuro->FL == futuro->FA && futuro->FL == 15) //CONDIÇÃO LISTA CHEIA
	{
		printf("Lista está cheia!\n");
	}
	else//A LISTA NÃO ESTÁ CHEIA
	{

		if (futuro->FL == 0 && futuro->IL == 0) //LISTA VAZIA //INSERE LOGO NO INICIO
		{
			if (futuro->IL == futuro->FL && futuro->IL == 0) //ENTÃO É PQ A LISTA ESTÁ VAZIA
			{
				//LOGO SÓ INSERE NA PRIMEIRA POS E ATUALIZA O VALOR DE IL E FL
				futuro->v[1] = passado[i];
				futuro->IL = futuro->IA;
				futuro->FL = futuro->IA;
			}
		}
		else	//LISTA JÁ NÃO ESTÁ VAZIA
		{
			//ENTÃO...
			posicao = futuro->FL + 1; //Valor default, Se não achar um valor igual
			for (j = futuro->IL; j <= futuro->FL; j++) //CAÇA ONDE TEM QUE COLOCAR
			{
				if (passado[i].tam <= futuro->v[j].tam)//Comparando os tamanhos
				{
					posicao = j; // acha posição onde tem que substituir
					break;
				}
			}
			if (posicao == 16)
				posicao = 15;
			if (posicao == futuro->IL) //INSERE NO INÍCIO
			{
				if(futuro->IL > futuro->IA)  //1ª condição se tiver espaço no começo
				{
					futuro->IL--;
					futuro->v[futuro->IL] = passado[i]; //Joga diretamente no começo
				}
				else //2ª condição
				{
					for(j = futuro->FL; j >= futuro->IL; j--) //joga todos para frente
					{
						futuro->v[j + 1] = futuro->v[j];
					}
					futuro->FL++; //Final da lista é incrementada com +1
					futuro->v[futuro->IL] = passado[i]; //depois só Insere no começo
				}
			}

			else if (posicao == futuro->FL) //INSERE NO FIM
			{
				if (futuro->FL < futuro->FA)//1ª condição se tiver espaço no final
				{
					guarda = futuro->v[futuro->FL];
					futuro->v[futuro->FL] = passado[i];
					futuro->FL++;// incrementa +1
					futuro->v[futuro->FL] = guarda; //Joga diretamente no final
				}
				else
				{
					for(j = futuro->IL; j <= futuro->FL; j++) //2ª condição joga todos para tras
						guarda = futuro->v[futuro->FL];
					futuro->v[futuro->FL] = passado[i];
					{
						futuro->v[j - 1] = futuro->v[j];
					}

					futuro->IL--; //inicio da lista é desincrementada com -1
					futuro->v[futuro->FL] = guarda; //depois só Insere no final
				}
			}
			else //Insere no meio
			{
				if(futuro->FL != futuro->FA)
				{
					for(j = futuro->FL; j >= futuro->IL + posicao - 1; j--)
					{
						futuro->v[j + 1] = futuro->v[j];
					}
					futuro->FL++;
					futuro->v[posicao] = passado[i];
				}
				else
				{
					for(j = futuro->IL; j <= futuro->IL + posicao - 2; j++)
					{
						futuro->v[j - 1] = futuro->v[j];
					}
					futuro->IL--;
					futuro->v[posicao] = passado[i];
				}

			}
		}
	}
}


//INSERIR LLSE
int alocaNoLLSE(LLSE *lista)  //usando quando insere atualiza o valor de disp automaticamente
{
	int d;
	if(lista->disp == -1)  //lista cheia
	{
		return 0; //retorna valor 0 quando a lista esta cheia
	}
	d = lista->disp;
	lista->disp = lista->vet[lista->disp].prox;//o ponto prox vai ser meu novo disponivel
	return d;
}

void inserirLLSE(LLSE *futuro, APP passado[], int i) //o "i" é o indice de passado
{
	int j, local;
	int d = alocaNoLLSE(futuro);// recebe o valor de disp

	if(d != 0)  // se for diferente de 0 é porque a lista ainda não está cheia
	{
		futuro->vet[d].info = passado[i];//ja grava a info no vetor
		local = posicaoLLSE(futuro, passado, i); //acha a posição de inserção

		if (futuro->vet[0].prox == -5)  // se a lista estiver vazia então so insere no valor de disp
		{
			futuro->vet[0].prox =  d;
			futuro->vet[d].prox = -5; //recebe o inicio da lista,no caso,-5
			return;

		}

		else if(local == futuro->vet[0].prox)  //inserir no inicio
		{
			futuro->vet[d].prox = futuro->vet[0].prox;
			futuro->vet[0].prox = d;
			return;
		}

		else if (futuro->vet[local].prox == -5 || local == 21)  //então é no final ou no penultimo
		{
			if (local == 21) //insere no final diretamente
			{
				j = futuro->vet[0].prox;
				while(futuro->vet[j].prox != -5)
				{
					j = futuro->vet[j].prox; //ultimo elemento antes de eu inserir
				}
				futuro->vet[d].prox = futuro->vet[j].prox;
				futuro->vet[j].prox = d;
				return;
			}
			else //insere na penultima posição
			{
				int k;
				j = futuro->vet[0].prox;// aqui tento achar a pos do atual 'ultimo'
				while(futuro->vet[futuro->vet[j].prox].prox != -5)
				{
					j = futuro->vet[j].prox; //penultimo elemento antes de eu inserir
				}
				k = futuro->vet[0].prox;
				while(futuro->vet[k].prox != -5)
				{
					k = futuro->vet[k].prox; //ultimo elemento antes de eu inserir
				}

				//obs fiz esse ajuste pois minha comp para achar a pos é 'menor que'
				futuro->vet[d].prox = k; // elemento inserido aponta para o antigo ultimo
				futuro->vet[j].prox = d; // o antigo penultimo aponta para o elemento inserido

				return;
			}
		}

		else //insere no meio
		{
			j = futuro->vet[0].prox;
			while(futuro->vet[j].prox != local) //para achar o penultimo
			{
				j = futuro->vet[j].prox;
			}
			futuro->vet[d].prox = futuro->vet[j].prox;//vetor do disp recebe ponto prox antigo
			futuro->vet[j].prox = d;//ponto prox antigo aponta p disp agoraa
			return;
		}



	}



}


//INSERIR LLDE
int alocaNoLLDE(LLDE * lista)
{
	int d;
	if(lista->disp == -1)  //lista cheia
	{
		return 0;
	}
	d = lista->disp;
	lista->disp = lista->vet[lista->disp].prox;
	return d;
}


void inserirLLDE(LLDE *futuro, APP passado[], int i)
{

	int d = alocaNoLLDE(futuro), r, local, j;
	if(d != 0)// se a lista não estiver cheia
	{
		futuro->vet[d].info = passado[i];
		local = posicaoLLDE(futuro, passado, i); //acha a posição, dentro do vetor, de inserção

		if (futuro->vet[0].prox == -5)  // se a lista estiver vazia então so insere no valor de disp
		{
			futuro->vet[0].prox =  d;
			futuro->vet[d].prox = -5; //recebe o inicio da lista,no caso,-5
			futuro->vet[d].ant = 0;
			return;
		}


		if(local == futuro->vet[0].prox)  //inserir no inicio da lista
		{
			r = futuro->vet[0].prox;
			if(r != -5)
			{
				futuro->vet[r].ant = d;
			}
			futuro->vet[d].prox = r;
			futuro->vet[d].ant = 0;
			futuro->vet[0].prox = d;
			return;
		}

		else if (futuro->vet[local].prox == -5 || local == 21)  //então é no final ou no penultimo
		{
			if (local == 21) //insere no final diretamente
			{
				j = futuro->vet[0].prox;
				while(futuro->vet[j].prox != -5)
				{
					j = futuro->vet[j].prox; //ultimo elemento antes de eu inserir
				}
				r = futuro->vet[j].prox;
				if(r != -5)
				{
					futuro->vet[r].ant = d;
				}

				futuro->vet[d].prox = r;
				futuro->vet[d].ant = j;
				futuro->vet[j].prox = d;
				return;
			}
			else //insere na penultima posição
			{
				int k;

				k = futuro->vet[0].prox;
				while(futuro->vet[k].prox != -5)
				{
					k = futuro->vet[k].prox; //ultimo elemento antes de eu inserir
				}

				//obs fiz esse ajuste pois minha comp para achar a pos é 'menor que'
				futuro->vet[d].prox = k; // elemento inserido aponta para o antigo ultimo
				futuro->vet[futuro->vet[k].ant].prox = d; // o antigo penultimo aponta para o elemento inserido
				futuro->vet[d].ant = futuro->vet[k].ant; //elemento atual aponta para o antigo antepenultimo
				futuro->vet[k].ant = d; //anterior do antigo ultimo aponta para o atual penultimo
				return;
			}



		}
		else //inserir no meio
		{
			futuro->vet[d].ant = futuro->vet[local].ant;
			futuro->vet[d].prox = local;
			futuro->vet[futuro->vet[local].ant].prox = d;
			futuro->vet[local].ant = d;
			return;
		}

	}

}

//INSERIR PILHA
void push(Pilha * P, APP info)
{
	P->vetor[P->topo++].info = info; //Elemento é inserido no topo e então é incrementado
}

//ALOCA FILA
int alocaNoFILA(Fila *lista)
{
	int d;
	if(lista->disp == -1)  //lista cheia
	{
		return 0;
	}
	d = lista->disp;
	lista->disp = lista->vet[lista->disp].prox;
	return d;
}


//INSERIR FILA

void inserirFILA(Fila * F, APP info[], LLSE *meusapps, int id) //insere pelo fim
{
	int  r, j, aux;
	int d = alocaNoFILA(F);
	if (d == 0) //LISTA CHEIA, tira pelo começo
	{
		inserirLLSE(meusapps, info, F->vet[F->vet[0].prox].info.indice); //instala o primeiro elemento inserido
		//QUANDO TERMINAR ENTÃO ESREVE NOS MEUS APPS ORDENADO
		FILE *arquivo;
		int cont = 1;
		int i = meusapps->vet[0].prox;
		while(1)
			//Deixar os id's ordenados caso haja alteração no tamanho dos aquivos do txt
		{
			meusapps->vet[i].info.indice = cont;
			cont++;
			if(meusapps->vet[i].prox == -5)
				break;
			i = meusapps->vet[i].prox;
		}
		arquivo = fopen("meusapps.txt", "w");
		i = meusapps->vet[0].prox;
		while(1)
		{
			fprintf(arquivo, "%d %s %d\n", meusapps->vet[i].info.indice, meusapps->vet[i].info.nome, meusapps->vet[i].info.tam);
			if (meusapps->vet[i].prox == -5)
				break;
			i = meusapps->vet[i].prox; // printar todos elementos  do apps
		}
		fclose(arquivo);
		aux = F->vet[0].prox;
		F->vet[0].prox = F->vet[F->vet[0].prox].prox; //Guarda o atual inicio da lista
		liberaNoFILA(F, aux);
		d = alocaNoFILA(F);
	}
	F->vet[d].info = info[id];
	//DEPOIS INSERE NO final do vetor
	if (F->vet[0].prox == -5)  // se a lista estiver vazia então so insere no valor de disp
	{
		F->vet[0].prox =  d; //Guarda inicio da lista
		F->vet[0].ant = d; //Guarda final da lista
		F->vet[d].prox = -5; //recebe o inicio da lista,no caso,-5

	}
	else //inserindo pelo fim
	{
		j = F->vet[0].ant;//Final da lista
		r = F->vet[j].prox;
		if(r != -5)
		{
			F->vet[r].ant = d;
		}

		F->vet[d].prox = r;
		F->vet[d].ant = j;
		F->vet[j].prox = d;
		F->vet[0].ant = d;//Final da lista agora é d
	}



}










//5ª Parte ----------Funções de REMOÇÃO---------

// REMOVER LLV
void removerLLV(LLV *meusapps, int id)
{
	int posicao, i;
	posicao = id;
	if (meusapps->IL == -1)
	{

		printf("Lista vazia\n");
		return;
	}
	else
	{
		if (posicao == 1) //Remover no inicio
		{
			meusapps->IL++;
			if(meusapps->IL > meusapps->FL)
			{
				meusapps->IL = 0;
				meusapps->FL = 0;
			}
		}

		else if (posicao == meusapps->FL - meusapps->IL + 1) //se remover no final
		{
			meusapps->FL--;
			if(meusapps->FL < meusapps->IL)
			{
				meusapps->IL = 0;
				meusapps->FL = 0;
			}
		}
		else//remove no meio
		{
			for(i = meusapps->IL + posicao - 1; i <= meusapps->FL - 1; i++)
				meusapps->v[i] = meusapps->v[i + 1];
			meusapps->FL--;
			if(meusapps->FL == meusapps->IL - 1)
			{
				meusapps->FL = 0;
				meusapps->IL = 0;
			}

		}
	}

}


//REMOVER LLSE
void liberaNoLLSE(LLSE * lista, int ind)  //usado quando remove
{
	lista->vet[ind].prox = lista->disp;
	lista->disp = ind;
}

void removerLLSE(LLSE *meusapps, int id)
{
	int local = id; //considerando que os id's estajam ordenados em ordem crescente pode fazer essa atribuição
	int atual, i, contador = 1;
	if(local == 1) // remover no inicio
	{
		atual = meusapps->vet[0].prox;
		meusapps->vet[0].prox = meusapps->vet[atual].prox;
		liberaNoLLSE(meusapps, atual);
		return;
	}
	i = meusapps->vet[0].prox;
	while(contador != local) // pos do elemento já no array
	{
		i = meusapps->vet[i].prox;
		contador++;

	}
	local = i; // variavel local já contém a pos do numero no array

	if(meusapps->vet[local].prox == -5) //final da lista
	{
		i = meusapps->vet[0].prox;// aqui tento achar a pos do atual 'ultimo'
		while(meusapps->vet[meusapps->vet[i].prox].prox != -5)
		{
			i = meusapps->vet[i].prox; //penultimo elemento antes de eu inserir
		}
		atual = meusapps->vet[i].prox;
		meusapps->vet[i].prox = meusapps->vet[atual].prox;
		liberaNoLLSE(meusapps, atual);

	}
	else //meio
	{
		int cont;
		cont = 1;
		i = meusapps->vet[0].prox;
		while(cont < id - 1) //menos 1 para obter o anterior (id-1) é a pos no numero no array, neste caso é qual é a posição crescente do numero ex: 1º, 2º, diferente do local!
		{
			i = meusapps->vet[i].prox;
			cont++;
		}
		atual = meusapps->vet[i].prox;
		meusapps->vet[i].prox = meusapps->vet[atual].prox;
		liberaNoLLSE(meusapps, local);

	}



}


//REMOVER LLDE
void liberaNoLLDE(LLDE * lista, int ind)
{
	lista->vet[ind].prox = lista->disp;
	lista->disp = ind;
}

void removerLLDE(LLDE *meusapps, int id)
{
	int local = id; //considerando que os id's estajam ordenados em ordem crescente pode fazer essa atribuição
	int i, contador = 1, q, r;
	if(local == 1) // remover no inicio
	{
		int i = meusapps->vet[0].prox;
		q = meusapps->vet[i].ant;
		r = meusapps->vet[i].prox;
		if(r != -5)
		{
			meusapps->vet[r].ant = q;
		}
		meusapps->vet[q].prox = r;
		liberaNoLLDE(meusapps, i);
		return;
	}
	i = meusapps->vet[0].prox;
	while(contador != local) // pos do elemento já no array
	{
		i = meusapps->vet[i].prox;
		contador++;
	}

	local = i; // variavel local já contém a pos do numero no array

	if(meusapps->vet[local].prox == -5) //final da lista
	{
		int i;
		i = meusapps->vet[0].prox;
		while(meusapps->vet[i].prox != -5)
		{
			i = meusapps->vet[i].prox;
		}
		q = meusapps->vet[i].ant;
		r = meusapps->vet[i].prox;
		if(r != -5)
		{
			meusapps->vet[r].ant = q;
		}
		meusapps->vet[q].prox = r;
		liberaNoLLDE(meusapps, local);
		return;
	}

	else  //remover do meio
	{
		int i;
		int cont;
		cont = 1;
		i = local;
		q = meusapps->vet[i].ant;
		r = meusapps->vet[i].prox;
		if(r != -5)
		{
			meusapps->vet[r].ant = q;
		}
		meusapps->vet[q].prox = r;
		liberaNoLLDE(meusapps, i);
		return;
	}




}


//REMOVER PILHA
void pop(Pilha * P)
{
	P->topo--; //Para remoção basta decrementar o topo
}


//REMOVER FILA

void liberaNoFILA(Fila *lista, int ind)
{
	lista->vet[ind].prox = lista->disp;
	lista->disp = ind;
}






//6ª PARTE LEITURA DE CADA ARQUIVO CORRESPONDENTE


void ler_arquivo(LLV *store, LLSE *meusapps, LLDE *run) //LER OS ARQUIVOS PARA A STRUCT CORRESPONDENTE
{
	int i = 1;
	FILE *arquivo;
	APP vetor[MAX];
	arquivo = fopen("store.txt", "r");
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo.");
		exit(1);
	}
	else
	{
		while(fscanf(arquivo, "%d %s %d", &vetor[i].indice, &vetor[i].nome, &vetor[i].tam) != EOF)
		{
			inserirLLV(store, vetor, i);
			i++;// o i vai até 15 pois começa do 1!
		}
		i = 1;
		for (i = 1; i <= 15; i++)
			//Deixar os id's ordenados caso haja alteração no tamanho dos aquivos do txt
		{
			store->v[i].indice = i;
		}
		i = 1;
		fclose(arquivo);
		fopen("store.txt", "w");
		while(i <= 15)
		{
			fprintf(arquivo, "%d %s %d\n", store->v[i].indice, store->v[i].nome, store->v[i].tam);
			i++;// o i vai até 15 pois começa do 1!
		}
		fclose(arquivo);

		i = 1;
		arquivo = fopen("meusapps.txt", "r");
		while(fscanf(arquivo, "%d %s %d", &vetor[i].indice, &vetor[i].nome, &vetor[i].tam) != EOF)
		{
			inserirLLSE(meusapps, vetor, i);
			i++;// o i vai até 15 pois começa do 1!
		}
		fclose(arquivo);

		i = 1;
		arquivo = fopen("run.txt", "r");
		while(fscanf(arquivo, "%d %s %d", &vetor[i].indice, &vetor[i].nome, &vetor[i].tam) != EOF)
		{
			inserirLLDE(run, vetor, i);
			i++;// o i vai até 15 pois começa do 1!
		}
		fclose(arquivo);
	}

}


//INSTALADOR tem que fazer uma fila! Quando for entrar o quarto app entao o primeiro é instalado
void instalador(LLSE *meusapps, LLV *store, Fila *leitura)
{
	APP vetor[MAX];
	int id, i = 1, verifica = 0, k;
	FILE *arquivo;
	i = 1;
	arquivo = fopen("store.txt", "r");
	while(fscanf(arquivo, "%d %s %d", &vetor[i].indice, &vetor[i].nome, &vetor[i].tam) != EOF)
	{
		i++;// o i vai até 15 pois começa do 1!
	}
	fclose(arquivo);

	while(1)
	{
		verifica = 0;
		system("CLS");
		printf("==========APP_STORE_ED===========\n");
		printf("|ID |\tAPP'S\t|TAMANHO(EM KB) |\n");
		printf("|-------------------------------|\n");
		for (i = 1; i <= 15; i++)
		{
			if (i <= 9)
				printf("|%d- | %s\t|\t%d\t|\n", store->v[i].indice, store->v[i].nome, store->v[i].tam);
			else
				printf("|%d-| %s\t|\t%d\t|\n", store->v[i].indice, store->v[i].nome, store->v[i].tam);
		}
		printf("=================================\n\n");
		printf("|ID do app|-> ");
		scanf("%d", &id);
		if (id > 15 || id < 1)
		{
			printf("ID IVÁLIDO");
			return;
		}

		i = meusapps->vet[0].prox;
		if (i != -5) // se a lista já tiver algum elemento
		{
			while(1)// verifica se app já foi instalado!
			{
				if (strcmp(vetor[id].nome, meusapps->vet[i].info.nome) == 0)
				{
					system("CLS");
					printf("Aplicativo já instalado!\n\n");
					verifica = 1; //ja foi instalado
					break;
				}
				if (meusapps->vet[i].prox == -5)
					break;
				i = meusapps->vet[i].prox;
			}
		}
		i = leitura->vet[0].prox; //tem que verificar se o app já está na fila tambem
		if (i != -5)
		{
			while(1)
			{
				if (strcmp(vetor[id].nome, leitura->vet[i].info.nome) == 0)
				{
					system("CLS");
					printf("Aplicativo já está na Fila de instalação!\n\n");
					verifica = 1; //ja foi instalado
					break;
				}
				if (leitura->vet[i].prox == -5)
					break;
				i = leitura->vet[i].prox;
			}
		}



		if (verifica == 0) // se não tiver nos apps então instala
		{
			inserirFILA(leitura, vetor, meusapps, id);
			system("CLS");
			printf("Instalando %s\n\n", vetor[id].nome);
		}
		printf("|1-Continuar Instalando| |2-SAIR|\n");
		scanf("%d", &k);
		if (k != 1)
			return;


	}
}




///LOJA
void App_StoreED(LLV *store, LLSE *meusapps, Fila *leitura) //Loja
{
	int i;
	int escolha;

	system("CLS");//limpa tela
	printf("==========APP_STORE_ED===========\n");
	printf("|ID |\tAPP'S\t|TAMANHO(EM KB) |\n");
	printf("|-------------------------------|\n");
	for (i = 1; i <= 15; i++)
	{
		if (i <= 9)
			printf("|%d- | %s\t|\t%d\t|\n", store->v[i].indice, store->v[i].nome, store->v[i].tam);
		else
			printf("|%d-| %s\t|\t%d\t|\n", store->v[i].indice, store->v[i].nome, store->v[i].tam);
	}
	printf("=================================\n\n");
	printf("|1- INSTALAR|\t\t |0-SAIR|\n-> ");
	scanf("%d", &escolha);
	if (escolha == 1)
	{
		system("CLS");
		printf("==========APP_STORE_ED===========\n");
		printf("|ID |\tAPP'S\t|TAMANHO(EM KB) |\n");
		printf("|-------------------------------|\n");
		for (i = 1; i <= 15; i++)
		{
			if (i <= 9)
				printf("|%d- | %s\t|\t%d\t|\n", store->v[i].indice, store->v[i].nome, store->v[i].tam);
			else
				printf("|%d-| %s\t|\t%d\t|\n", store->v[i].indice, store->v[i].nome, store->v[i].tam);
		}
		printf("=================================\n\n");
		instalador(meusapps, store, leitura);
	}
	else
	{
		return;
	}
}



//MEUSAPPS
void apps(LLDE *run, LLSE *meusapps, LLV *store)
{
	APP vetor[MAX];
	int i = 1, resposta, k, verifica, id2;
	FILE *arquivo;
	system("CLS");
	arquivo = fopen("meusapps.txt", "r");
	printf("===========Meus_Apps_ED==========\n");
	printf("|ID |\tAPP'S\t|TAMANHO(EM KB) |\n");
	printf("|-------------------------------|\n");
	while(fscanf(arquivo, "%d%s%d", &vetor[i].indice, &vetor[i].nome, &vetor[i].tam) != EOF)
	{
		if (i <= 9)
			printf("|%d- | %s\t|\t%d\t|\n", vetor[i].indice, vetor[i].nome, vetor[i].tam);
		else
			printf("|%d-| %s\t|\t%d\t|\n", vetor[i].indice, vetor[i].nome, vetor[i].tam);
		i++;
	}
	printf("=================================\n");
	fclose(arquivo);
	printf("\n\n1-|EXECUTAR|\t  2-|DESINSTALAR|\n\n\t   3-|SAIR|\n\n->");
	scanf("%d", &resposta);

	if (resposta == 1)
	{
		while(1)

		{
			verifica = 0;
			system("CLS");
			arquivo = fopen("meusapps.txt", "r");
			printf("============MODO_RUN=============\n\n");
			printf("============MEUS_APPS============\n");
			printf("|ID |\tAPP'S\t|TAMANHO(EM KB) |\n");
			printf("---------------------------------\n");
			i = 1;
			while(fscanf(arquivo, "%d%s%d", &vetor[i].indice, &vetor[i].nome, &vetor[i].tam) != EOF)
			{
				if (i <= 9)
					printf("|%d- | %s\t|\t%d\t|\n", vetor[i].indice, vetor[i].nome, vetor[i].tam);
				else
					printf("|%d-| %s\t|\t%d\t|\n", vetor[i].indice, vetor[i].nome, vetor[i].tam);
				i++;
			}
			printf("=================================\n\n");
			fclose(arquivo);
			printf("|ID do app|-> ");
			scanf("%d", &resposta);
			if (resposta > (i - 1) || resposta <= 0 || (meusapps->vet[0].prox == -5)) //o 'i' tem o tamanho do array
				break;// maior que tamanho da lista ou menor do que 1
			else
			{
				i = run->vet[0].prox;

				if (i != -5) // se a lista já tiver algum elemento
				{
					while(1)//verifica se já está em execução
					{
						if (strcmp(vetor[resposta].nome, run->vet[i].info.nome) == 0)
						{
							system("CLS");
							printf("O aplicativo %s já está em execução! \n\n", run->vet[i].info.nome);
							verifica = 1;
							break;
						}
						if (run->vet[i].prox == -5)
							break;
						i = run->vet[i].prox; // o i vai até no max 15 pois começa do 1!

					}
				}
				if (verifica == 0) //se não estiver instalado então instala
				{
					system("CLS");
					printf("%s foi executado com sucesso!\n\n", vetor[resposta].nome);
					inserirLLDE(run, vetor, resposta);
				}
				printf("|1-Continuar Executando| |2-SAIR|\n\n->");
				scanf("%d", &k);

				i = run->vet[0].prox;
				int cont = 1;
				while (1)
					//Deixar os id's ordenados caso haja alteração no tamanho dos aquivos do txt
				{
					run->vet[i].info.indice = cont;
					cont++;
					if(run->vet[i].prox == -5)
						break;
					i = run->vet[i].prox;
				}


				arquivo = fopen("run.txt", "w");
				i = run->vet[0].prox;
				while(1)//SALVAR NO ARQUIVO RUN
				{
					fprintf(arquivo, "%d %s %d\n", run->vet[i].info.indice, run->vet[i].info.nome, run->vet[i].info.tam);
					if(run->vet[i].prox == -5)
						break;
					i = run->vet[i].prox;	//incrementador
				}
				fclose(arquivo);



				if (k != 1) //Quando terminar..
					break;

			}
		}
	}

	else if (resposta == 2)
	{
		int cont, verifica;
		while(1)
		{
			system("CLS");
			arquivo = fopen("meusapps.txt", "r");
			printf("=========MODO_DESINSTALAR========\n\n");
			printf("============MEUS_APPS============\n");
			printf("|ID |\tAPP'S\t|TAMANHO(EM KB) |\n");
			printf("---------------------------------\n");
			i = 1;
			while(fscanf(arquivo, "%d%s%d", &vetor[i].indice, &vetor[i].nome, &vetor[i].tam) != EOF)
			{
				if (i <= 9)
					printf("|%d- | %s\t|\t%d\t|\n", vetor[i].indice, vetor[i].nome, vetor[i].tam);
				else
					printf("|%d-| %s\t|\t%d\t|\n", vetor[i].indice, vetor[i].nome, vetor[i].tam);
				i++;
			}
			printf("=================================\n");
			fclose(arquivo);
			printf("|ID do app|-> ");
			scanf("%d", &resposta);
			if (resposta > (i - 1) || resposta <= 0 || (meusapps->vet[0].prox == -5))
				break;// maior que tamanho da lista ou menor do que 1
			system("CLS");
			printf("%s foi desinstalado com sucesso!\n\n", vetor[resposta].nome);
			removerLLSE(meusapps, resposta); //AGORA REMOVE DOS MEUS APPS E DO RUN E SALVA NOS APPS
			int i;
			cont = 1;
			if(meusapps->vet[0].prox != -5)
			{
				i = meusapps->vet[0].prox;
				while(1)
					//Deixar os id's ordenados caso haja alteração no tamanho dos aquivos do txt
				{
					meusapps->vet[i].info.indice = cont;
					cont++;
					if(meusapps->vet[i].prox == -5)
						break;
					i = meusapps->vet[i].prox;
				}
			}
			if (meusapps->vet[0].prox == -5) //QUANDO NAO TEM MAIS APPS ENTAO NAO ESCREVE NADA
			{
				arquivo = fopen("meusapps.txt", "w"); //TODO ARQUIVO FICA VAZIO
				fclose(arquivo);
			}
			else
			{
				arquivo = fopen("meusapps.txt", "w");
				i = meusapps->vet[0].prox;
				while(1)
				{
					fprintf(arquivo, "%d %s %d\n", meusapps->vet[i].info.indice, meusapps->vet[i].info.nome, meusapps->vet[i].info.tam);
					if(meusapps->vet[i].prox == -5)
						break;
					i = meusapps->vet[i].prox;
				}
				fclose(arquivo);
			}
			printf("|1-Continuar Desinstalando| |2-SAIR|\n\n->");
			scanf("%d", &k);
			verifica = 0;
			i = run->vet[0].prox;
			if (i != -5) // se a lista já tiver algum elemento
			{
				while(1)//verifica se o app desinstalado está no run tambem
				{
					if (strcmp(vetor[resposta].nome, run->vet[i].info.nome) == 0)
					{
						verifica = 1;
						break;
					}
					if (run->vet[i].prox == -5)
						break;
					i = run->vet[i].prox; // o i vai até no max 15 pois começa do 1!

				}
			}
			if (verifica == 1)
			{
				removerLLDE(run, run->vet[i].info.indice);
				if (run->vet[0].prox == -5) //LISTA VAZIA
				{
					arquivo = fopen("run.txt", "w");
					fclose(arquivo);
				}
				else
				{
					cont = 1;
					i = run->vet[0].prox;
					while (1)
						//Deixar os id's ordenados caso haja alteração no tamanho dos aquivos do txt
					{
						run->vet[i].info.indice = cont;
						cont++;
						if(run->vet[i].prox == -5)
							break;
						i = run->vet[i].prox;
					}

					arquivo = fopen("run.txt", "w");
					i = run->vet[0].prox;
					while(1)//SALVAR NO ARQUIVO RUN
					{
						fprintf(arquivo, "%d %s %d\n", run->vet[i].info.indice, run->vet[i].info.nome, run->vet[i].info.tam);
						if(run->vet[i].prox == -5)
							break;
						i = run->vet[i].prox;
					}
					fclose(arquivo);

				}
			}
			if (k != 1) // na hora que terminar a desinstalação então...
			{
				break;
			}
		}



	}




}




//APP'S em execução
void app_run(LLDE *run)
{
	int i, resposta, id, k;
	APP vetor[MAX];
	FILE *arquivo;
	system("CLS");
	arquivo = fopen("run.txt", "r");
	printf("============APP_RUN_ED=========\n");
	printf("|ID |\tAPP'S\t|TAMANHO(EM KB) |\n");
	printf("|-------------------------------|\n");
	i = 1;
	while(fscanf(arquivo, "%d%s%d", &vetor[i].indice, &vetor[i].nome, &vetor[i].tam) != EOF)
	{
		if (i <= 9)
			printf("|%d- | %s\t|\t%d\t|\n", vetor[i].indice, vetor[i].nome, vetor[i].tam);
		else
			printf("|%d-| %s\t|\t%d\t|\n", vetor[i].indice, vetor[i].nome, vetor[i].tam);
		i++;
	}
	printf("=================================\n");
	fclose(arquivo);
	printf("\n\n|1-FECHAR APP|\t\t |2-SAIR|\n\n->");
	scanf("%d", &resposta);
	if (resposta == 1)
	{
		while(1)
		{
			system("CLS");
			arquivo = fopen("run.txt", "r");
			printf("============APP_RUN_ED=========\n");
			printf("|ID |\tAPP'S\t|TAMANHO(EM KB) |\n");
			printf("|-------------------------------|\n");
			i = 1;
			while(fscanf(arquivo, "%d%s%d", &vetor[i].indice, &vetor[i].nome, &vetor[i].tam) != EOF)
			{
				if (i <= 9)
					printf("|%d- | %s\t|\t%d\t|\n", vetor[i].indice, vetor[i].nome, vetor[i].tam);
				else
					printf("|%d-| %s\t|\t%d\t|\n", vetor[i].indice, vetor[i].nome, vetor[i].tam);
				i++;
			}
			printf("=================================\n");
			fclose(arquivo);
			printf("|ID do app|-> ");
			scanf("%d", &id);
			if (id > (i - 1) || id <= 0 || run->vet[0].prox == -5)
				break;// maior que tamanho da lista ou menor do que 1
			system("CLS");
			printf("%s foi fechado com sucesso!\n\n", vetor[id].nome);
			removerLLDE(run, id);
			i = run->vet[0].prox;
			int cont = 1;
			if (i != -5)
			{
				while (1)
					//Deixar os id's ordenados caso haja alteração no tamanho dos aquivos do txt
				{
					run->vet[i].info.indice = cont;
					cont++;
					if(run->vet[i].prox == -5)
						break;
					i = run->vet[i].prox;
				}
			}
			if (run->vet[0].prox == -5) //LISTA VAZIA
			{
				arquivo = fopen("run.txt", "w");
				fclose(arquivo);
			}
			else
			{

				arquivo = fopen("run.txt", "w");
				i = run->vet[0].prox;;
				while(1)
				{
					fprintf(arquivo, "%d %s %d\n", run->vet[i].info.indice, run->vet[i].info.nome, run->vet[i].info.tam);
					if(run->vet[i].prox == -5)
						break;
					i = run->vet[i].prox;	//incrementador
				}
				fclose(arquivo);



			}
			printf("|1-Continuar Fechando APP| |2-SAIR|\n\n->");
			scanf("%d", &k);
			if (k != 1) //Quando terminar..
				break;
		}

	}
}

void mostrar_pilha(Pilha *empilhamento)
{
	int operacao;
	int escolha;
	while(1)
	{
		system("CLS");//limpa tela
		printf("******************\n");
		printf("**PILHA_BÔNUS_ED**\n");
		printf("******************\n");
		printf("* 1-Zerar Pilha  *\n");
		printf("* 2-Exibir Pilha *\n");
		printf("* 3-Empilhar     *\n");
		printf("* 4-Desempilhar  *\n");
		printf("* 0-Sair         *\n");
		printf("******************\n");
		printf("Opção: ");
		scanf("%d", &escolha);
		if (!(escolha >= 0 && escolha <= 4))
			return;
		if (escolha == 1)
		{
			while(empilhamento->topo != 0)
			{
				empilhamento->topo--;
			}
			printf("Pilha Vazia!\n");
			system("Pause");
		}
		else if (escolha == 2)
		{
			int cont = empilhamento->topo;
			if (cont == 0)
			{
				printf("Pilha Vazia!\n");
			}
			else
			{
				system("CLS");//limpa tela
				printf("   *******\n");
				printf("   *PILHA*\n");
				printf("   *******\n\n\n");
				cont = empilhamento->topo - 1;
				int loop = 0;
				while(cont >= 0)
				{
					cont--;
					loop++;
				}
				for(cont = 1; cont <= MAXPILHA - loop; cont++)
				{
					printf("************\n");
					printf("*   %-7s*\n", "");
					printf("************\n");
				}
				cont = empilhamento->topo - 1;
				while(cont >= 0)
				{
					printf("************\n");
					printf("*   %-7s*\n", empilhamento->vetor[cont].info.nome);
					printf("************\n");
					cont--;
				}
			}
			system("Pause");
		}
		else if (escolha == 3)
		{
			APP vet[8];
			strcpy(vet[1].nome, "BLUE");
			strcpy(vet[2].nome, "YELLOW");
			strcpy(vet[3].nome, "ORANGE");
			strcpy(vet[4].nome, "PINK");
			strcpy(vet[5].nome, "BLACK");
			strcpy(vet[6].nome, "WHITE");
			strcpy(vet[7].nome, "PURPLE");
			while(1)
			{
				system("CLS");//limpa tela

				if (empilhamento->topo == MAXPILHA)
				{
					printf("Pilha Cheia!\n");
					system("pause");
					break;
				}
				printf("---------------\n");
				printf("->>>CORES<<<-\n");
				printf("---------------\n\n");
				printf("Escolha um cor a ser empilhada!\n\n");
				printf("********************************\n");
				printf("*|1-BLUE| |2-YELLOW| |3-ORANGE|*\n");
				printf("*|4-PINK| |5-BLACK | |6-WHITE |*\n");
				printf("*         |7-PURPLE|           *\n");
				printf("********************************\n\n");
				printf("Nº da cor: ");
				scanf("%d", &operacao);
				if (!(operacao >= 1 && operacao <= 7))
					break;
				system("CLS");//limpa tela
				printf("A cor %s foi empilhada!\n", vet[operacao].nome);
				push(empilhamento, vet[operacao]);
				printf("\n|1-Continuar Empilhando|   |2-Sair|\n\n");
				scanf("%d", &operacao);
				if (operacao != 1)
					break;
			}
		}
		else if (escolha == 4)
		{
			int cont = empilhamento->topo;
			if (cont == 0)
			{
				printf("Pilha Vazia!\n");
			}
			else
			{
				printf("A cor %s foi removida!\n", empilhamento->vetor[empilhamento->topo - 1].info.nome);
				pop(empilhamento);
			}
			system("Pause");
		}
		else
			return;

	}
}




void matriz_area_de_trabalho(LLSE *meusapps)
{
	int i, j, k = 0, base;
	APP matrix[5][3];//15 APP'S NO MAX
	k = meusapps->vet[0].prox;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (k != -5)
			{
				{
					strcpy(matrix[i][j].nome, meusapps->vet[k].info.nome);
					k = meusapps->vet[k].prox;
				}
			}
			else
				strcpy(matrix[i][j].nome, ""); //Copia string para uma certa "variavel"
		}
	}
	printf("| -------------- --------------\t--------------  |\n");
	k = 1;
	base = meusapps->vet[0].prox; //inicio da lista
	for (i = 0; i < 5; i++) //EXIBIR MATRIZ
	{
		for (j = 0; j < 3; j++)
		{
			if (j == 0)
				printf("|");
			if (meusapps->vet[0].prox != -5 && base != -5)
			{
				if (k + 4 < 10)
					printf(" [%d- %-9s]", k + 4, matrix[i][j].nome);
				else
					printf(" [%d- %-8s]", k + 4, matrix[i][j].nome);

			}
			else
			{
				printf(" [%-12s]", "");
			}
			k++;
		}

		printf("  |\n");
		printf("| -------------- --------------\t--------------  |\n");
	}

	printf("|\t\t\t\t\t\t|\n");
}







int main()
{
	setlocale(LC_ALL, "Portuguese");
	LLV store;
	LLSE meusapps;
	LLDE run;
	Fila leitura;
	Pilha empilhamento;
	inicializar(&store, &meusapps, &run, &leitura, &empilhamento);
	ler_arquivo(&store, &meusapps, &run); //PARA LOJA/MEUS APPS/RUN
	int choice;
	while(1)
	{
		system("CLS");//limpa tela
		printf("-------------------------------------------------\n|");
		printf("MOBILEED\t\t       ");
		printf("Horário: %s|\n", __TIME__);
		printf("|-----------------------------------------------|\n|\t\t\t\t\t\t|\n");
		matriz_area_de_trabalho(&meusapps);
		printf("-------------------------------------------------\n");
		printf("|>1-Store_ED<");
		printf("  >2-Meus_Apps_ED<");
		printf("  >3-App_Run_ED< |\n");
		printf("|\t\t\t\t\t\t|\n|      >4-Bônus-Pilha< \t >0-Desligar <\t\t");
		printf("|\n-------------------------------------------------\n->");
		scanf("%d", &choice);
		if (choice == 1)
			App_StoreED(&store, &meusapps, &leitura);
		else if (choice == 2)
			apps(&run, &meusapps, &store);
		else if (choice == 3)
			app_run(&run);
		else if (choice == 4)
			mostrar_pilha(&empilhamento);
		else if (choice == 0)
			break;
	}
	return 0;
}
