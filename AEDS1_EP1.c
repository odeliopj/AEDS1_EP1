/////////////////////// ALUNOS ////////////////////////
//  Odélio Porto Júnior - 12701501                   //
//  Mauricio Georges Silva Assad - 11796103          // 
//                                                  //
//////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include <time.h>

#define TAMANHO 1000
#define true 1
#define false 0
typedef int bool;


//////////////////// 1) FUNÇÕES AUXILIARES GERAIS /////////////////////////

/* 1.1) strsep() */
char *strsep(char **stringp, const char *delim) { // o compilador utilizado não reconheceu esta função, por isso ela foi implementada
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

/*---------------------------------------------------------------------*/

/* 1.2) LISTA LIGADA AUXILIAR - LINHAS DE CADA PALAVRA */
/* Para armazenar as linhas em que cada palavra aparece */

/* 1.2.1) Data Struct */
typedef struct aux{
    int linha;
    struct aux* prox;
} elementoListaLinhas;

typedef struct {
    elementoListaLinhas * inicio;
} listaLinhas;

/* 1.2.2) Inicilização */
void inicializarLista(listaLinhas * l){
    l->inicio = NULL;
}

/* 1.2.3) Inserção*/
/*Função auxiliar - evitar que seja inserido elemento repetido */
elementoListaLinhas * buscaSequencialExc(listaLinhas * l, int contador_linha, elementoListaLinhas** ant){
    *ant = NULL;
    elementoListaLinhas * atual = l->inicio;

    while ((atual != NULL) && (atual->linha < contador_linha)){
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (atual->linha == contador_linha)) return atual;
    return NULL;
}

bool inserirElemListaOrd(listaLinhas * l, int contador_linha){
    elementoListaLinhas * ant;
    elementoListaLinhas * i;

    i = buscaSequencialExc(l, contador_linha, &ant);
    if (i != NULL) {
            return false;
    }

    i = (elementoListaLinhas*) malloc(sizeof(elementoListaLinhas));
    i->linha = contador_linha;

    if (ant == NULL){
        i->prox = l->inicio;
        l->inicio = i;
    }
    else {
        i->prox = ant->prox;
        ant->prox = i;
    }
    return true;
}

/* 1.2.4) Imprimir */
void exibirLista(listaLinhas * l){
    elementoListaLinhas * end = l->inicio;
    printf("\nLista: \" ");
    while (end != NULL){
        printf("%i ", end->linha);
        end = end->prox;
    }
    printf("\"\n");
}

/*---------------------------------------------------------------------*/

/* 1.3.1) LISTA LIGADA AUXILIAR II - ARMAZENAR O TXT. EM UMA LISTA LIGADA */
/* Armazena todo o texto em uma lista ligada, durante o loop que percorre o 'FILE * in', no laço 'while(in && fgets(linha, TAMANHO, in))' */ 
/* Esta lista ligada é convertida em um array de ponteiros para char posteriormente */

/* 1.3.1) Data Struct */
typedef struct aux3{
    int linha;
    char * pontLinha;
    struct aux3* prox;
} linhaTxt;

typedef struct {
    linhaTxt * inicio;
} txtArmazenadoLista;

/* 1.3.2) Inicilização */
void inicializarTxtLista(txtArmazenadoLista * listaT){
    listaT->inicio = NULL;
}

/* 1.3.3) Inserção*/
linhaTxt * buscaSequencialExcTex(txtArmazenadoLista * l, int contador_linha, linhaTxt** ant){
    *ant = NULL;
    linhaTxt * atual = l->inicio;

    while ((atual != NULL) && (atual->linha < contador_linha)){
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (atual->linha == contador_linha)) return atual;
    return NULL;
}

bool inserirTextoListaOrd(txtArmazenadoLista * l, char * linha, int contador_linha){
    linhaTxt * ant;
    linhaTxt * i;

    i = buscaSequencialExcTex(l, contador_linha, &ant);
    if (i != NULL) {
            return false;
    }

    i = (linhaTxt*) malloc(sizeof(linhaTxt));

    i->linha = contador_linha;

    char * intermed = (char *) malloc((TAMANHO + 1) * sizeof(char));
    strcpy(intermed, linha);
    i->pontLinha = intermed;

    if (ant == NULL){
        i->prox = l->inicio;
        l->inicio = i;
    }
    else {
        i->prox = ant->prox;
        ant->prox = i;
    }
    return true;
}

/* 1.3.4) Imprimir */
void exibirTxtLista(txtArmazenadoLista * l){
    linhaTxt * end = l->inicio;
    printf("\nLista: \" ");
    while (end != NULL){
        printf("%s\n", end->pontLinha);
        end = end->prox;
    }
    printf("\"\n");
}

/////////////////// 2) INDEXADOR - LISTA SEQUENCIAL /////////////////////////

 typedef struct{

     int numPalavra;
     listaLinhas * listalinhas;
     char * palavra;

 } NO_lista;


///////////////////  3) INDEXADOR - ÁRVORE BINÁRIA /////////////////////

/* 3.2) FUNÇÕES - ÁRVORE BINÁRIA*/
/* Indexar palavras nos nós (sem repetição) */

/* 2.2.1) Data Struct - Nó da árvore */
typedef struct aux1 {
    int numPalavra; // número de vezes que a palavra aparece no texto
    listaLinhas * listaLinhas; // armazenar as linhas em que a palavra aparece (lista ligada)
    char * palavra;
    struct aux1 *esq, *dir;
} NO;

/* 3.2.2) Inicializização da Árvore */
NO * inicializaArvore() {
    return(NULL);
}

/* 3.2.3) Criação do Nó */
NO * criaNovoNo(char * palavra, int contador_linha2) {
    NO * novoNo = (NO*) malloc(sizeof(NO));
    novoNo->palavra = strdup(palavra);
    novoNo->numPalavra = 1;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    listaLinhas* inicListaLinhas = (listaLinhas*) malloc(sizeof(listaLinhas)); // lista ligada p/ armazenar as linhas em que a palavra aparece
    elementoListaLinhas * element = (elementoListaLinhas*) malloc(sizeof(elementoListaLinhas));
    element->linha = contador_linha2;
    element->prox = NULL;
    inicListaLinhas->inicio = element;

    novoNo->listaLinhas = inicListaLinhas;
}

int contador_palavras = 0;
/* 3.2.4) Insere Nó*/
NO * adiciona(NO * raiz, NO * no, int contador_linha){
    if (raiz == NULL) return(no);

    int comparacao = strcasecmp(no->palavra, raiz->palavra);
    if(comparacao == 0){
        raiz->numPalavra += 1; //atualiza o contador se a palavra é repetida
        inserirElemListaOrd(raiz->listaLinhas, contador_linha);   // armazena a linha na qual a palavra repetida está
        contador_palavras--;
    }
    else if (comparacao < 0)
        raiz->esq = adiciona(raiz->esq, no, contador_linha);
    else
        raiz->dir = adiciona(raiz->dir, no, contador_linha);
    
    return (raiz);
}

/* 3.2.5) Busca Binária */
NO * buscaBinaria(char * palavraBuscada, NO * raiz){ //<<<<<<<<<<<<<<<<<<<<<<<<<<<< BUSCA

    if (raiz == NULL) return(NULL);

    int comparacao = strcasecmp(palavraBuscada, raiz->palavra);
    if (comparacao == 0) return (raiz);
    if (comparacao < 0) return buscaBinaria (palavraBuscada, raiz->esq);
    return buscaBinaria (palavraBuscada, raiz->dir);
}

/* 3.2.6) Imprimir */
void exibirArvore(NO* raiz){
    if (raiz != NULL){
        printf("%s", raiz->palavra);
        printf("(");
        exibirArvore(raiz->esq);
        exibirArvore(raiz->dir);
        printf(")");
    }
}

////////////////////////////////////////////////////////////////////////

    int AddToArray(NO *node, NO_lista arr[], int i)
    {
     if(node == NULL)
          return i;

     if(node->esq != NULL)
          i = AddToArray(node->esq, arr, i);

     arr[i].palavra = node->palavra;
     arr[i].numPalavra = node->numPalavra;
     arr[i].listalinhas = node->listaLinhas;
     i++;

     if(node->dir != NULL)
          i = AddToArray(node->dir, arr, i);

     return i;
    }


    NO_lista * buscaBinariaLista(char * palavraBuscada, NO_lista array[],int tamanho){ //<<<<<<<<<<<<<<<<<<<<<<<<<<<< BUSCA

    if (array == NULL) return(NULL);

    int lb,mid,ub;
    lb = 0;
    ub = tamanho;

    do{
        mid = (lb + ub) / 2;
        if(strcasecmp((palavraBuscada),array[mid].palavra) < 0){
            ub = mid - 1;
        }
        else if (strcasecmp((palavraBuscada),array[mid].palavra)>0){
            lb =  mid + 1;
        }
    }while(strcasecmp((palavraBuscada),array[mid].palavra)!=0 && lb<= ub);

    if(strcasecmp((palavraBuscada),array[mid].palavra)==0){
        return &array[mid];
    }
    else{
        return NULL;
    }
}

////////////////////////////////////////////////////////////////////////


//////////////////////// 4) MAIN ////////////////////////////////////////

int main(int argc, char ** argv){

	FILE * in;
	char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;
	char * copiaPalavra;
	char * txt;
	int contador_linha;
	double tempoGastoCarreg = 0.0;
	double tempoGastoBusca = 0.0;
    	NO * raiz = inicializaArvore();
   	NO * tempNO;
	txtArmazenadoLista * txtArmazenado = (txtArmazenadoLista*) malloc(sizeof(txtArmazenadoLista)); //variavel para armazenar o txt em uma lista ligada
    	inicializarTxtLista(txtArmazenado); 


    printf("Tipo de indice: \'%s\'\n", argv[2]);
    printf("Arquivo texto: \'%s\'\n", argv[1]);


    txt = argv[1]; 
    in = fopen(txt, "r");

    //////////// CRIAÇÃO DA ÁRVORE BINÁRIA  //////////////////////////////////////////

    clock_t inicioCarrega = clock(); //<<<<<<<<<<<<<<<<<<<<< CLOCKz

		//printf(">>>>> Carregando arquivo...\n");

		contador_linha = 0;
 		linha = (char *) malloc((TAMANHO + 1) * sizeof(char)); // ARRAY de chars

		while(in && fgets(linha, TAMANHO, in)){

			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

			printf("linha %03d: '%s'\n", contador_linha + 1, linha);

            		/* Criação Lista Ligada Txt */
            		/* Insere todo o txt. numa lista ligada (cada elemento sendo uma linha) */ //<<<<<<< LISTA LIGADA TXT - Inserido
            		inserirTextoListaOrd(txtArmazenado, linha, contador_linha);

			copia_ponteiro_linha = linha;

			while( (palavra = strsep(&copia_ponteiro_linha, " ")) ){

                		copiaPalavra = strdup(palavra);

                		/* Criação da Árvore */
                		int contador_linha2 = contador_linha + 1; //indica qual a linha a palavra está, para inclusão na lista ligada das linhas
                		tempNO = criaNovoNo(copiaPalavra, contador_linha2);
                		raiz = adiciona(raiz, tempNO, contador_linha2);

           			printf("\t\t'%s'\n", palavra);
                    contador_palavras++; 

			}

			contador_linha++;
		 }

		 //printf(">>>>> Arquivo carregado na Arvore!\n");
    
     /*Copiar Lista Ligada Txt p/ Array*/
    /*Copiamos os elementos da Ligada Ligada Txt para um Array para facilitar o acesso na impressão da linha*/
    int c = 0;
    linhaTxt * txt_armazenado_array[contador_linha];

    linhaTxt * end = txtArmazenado->inicio;
    while (end != NULL){
        txt_armazenado_array[c] = end;
        end = end->prox;
        linhaTxt * temp = txt_armazenado_array[c];
        //printf("\n\t\tO valor de ' txt_armazenado_array[%d] e: %s'\n", c, temp->pontLinha);
        c++;
    }

    clock_t fimCarrega;
    if (strcasecmp(argv[2],"arvore")==0)
    {
        fimCarrega = clock();
    }
    
    //////////////////////////// CRIAÇÃO LISTA LIGADA ///////////////////////////////////////////////////

    NO_lista array[contador_palavras];

    if (strcasecmp(argv[2],"lista")==0){

        AddToArray(raiz,array,0);
        fimCarrega = clock();
    }

    tempoGastoCarreg = (double)(fimCarrega - inicioCarrega) / CLOCKS_PER_SEC; //<<<<<<<<<<<<<<<<<<<<< CLOCK
    tempoGastoCarreg = tempoGastoCarreg * 1000;
         
    //////////////////////////// 4) IF - BUSCA ARVORE / ELSE - LISTA ////////////////////////////////////////

    printf("Numero de linhas no arquivo: %d\n", contador_linha);
    printf("Tempo para carregar o arquivo e construir o indice: %.3f ms\n", tempoGastoCarreg);

    char * palavraFimLoop = "fim";
    char * comandoBusca = "busca";
    char palavraBuscada[50];
    char comando_digitado[6];
    int resultaDoEstr = 1;
    int * pResultaDoEstr = &resultaDoEstr;

    do{
        printf("> ");
        scanf("%s", comando_digitado);

        *pResultaDoEstr = strcasecmp(palavraFimLoop, comando_digitado);

        if (*pResultaDoEstr == 0)
            return 0;

        else if ( strcasecmp(comandoBusca, comando_digitado) == 0 ){
            scanf("%s", &palavraBuscada);
            
        
        if(strcasecmp(argv[2],"arvore")==0){
            clock_t inicioBusca  = clock(); //<<<<<<<<<<<<<<<<<<<<< CLOCK BUSCA
            NO * noResultadoBusca = buscaBinaria(palavraBuscada, raiz);
            clock_t fimBusca  = clock();
            
                tempoGastoBusca = (double)(fimBusca - inicioBusca) / CLOCKS_PER_SEC;
                tempoGastoBusca = tempoGastoBusca * 1000;

                if (noResultadoBusca == NULL)
                    printf("Palavra '%s' nao encontrada\n",palavraBuscada);

                else if (noResultadoBusca != NULL){
                printf ("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) linha(s):\n", noResultadoBusca->numPalavra, noResultadoBusca->palavra);

                    /*Percorre a 'listaLinhas' armazenada no NO da arvore */
                    elementoListaLinhas * endElemListaLinhas = noResultadoBusca->listaLinhas->inicio;
                    while (endElemListaLinhas != NULL){
                            int numLinha = endElemListaLinhas->linha - 1; // '- 1' serve para equipara o número da linha com o índice do array de linhas
                            linhaTxt * endLinha = txt_armazenado_array[numLinha];
                            printf("'%s'\n", endLinha->pontLinha);
                            endElemListaLinhas = endElemListaLinhas->prox;
                    }
            
            printf("Tempo de busca: %.3f ms\n", tempoGastoBusca);
            }
        }
        else{
            
            clock_t inicioBusca  = clock(); //<<<<<<<<<<<<<<<<<<<<< CLOCK BUSCA
            NO_lista * noResultadoBusca = buscaBinariaLista(palavraBuscada, array, contador_palavras);
            clock_t fimBusca  = clock();
            
                tempoGastoBusca = (double)(fimBusca - inicioBusca) / CLOCKS_PER_SEC;
                tempoGastoBusca = tempoGastoBusca * 1000;

                if (noResultadoBusca == NULL)
                    printf("Palavra '%s' nao encontrada\n",palavraBuscada);

                else if (noResultadoBusca != NULL){
                printf ("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) linha(s):\n", noResultadoBusca->numPalavra, noResultadoBusca->palavra);

                    /*Percorre a 'listaLinhas' armazenada no NO da lista */
                    elementoListaLinhas * endElemListaLinhas = noResultadoBusca->listalinhas->inicio;
                    while (endElemListaLinhas != NULL){
                            int numLinha = endElemListaLinhas->linha - 1; // '- 1' serve para equipara o número da linha com o índice do array de linhas
                            linhaTxt * endLinha = txt_armazenado_array[numLinha];
                            printf("'%s'\n", endLinha->pontLinha);
                            endElemListaLinhas = endElemListaLinhas->prox;
                    }
            
            printf("Tempo de busca: %.3f ms\n", tempoGastoBusca);
            }

        }
        }
        else
            printf("Opcao invalida!\n");

    } while (*pResultaDoEstr != 0);


	//}
	return 1;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
