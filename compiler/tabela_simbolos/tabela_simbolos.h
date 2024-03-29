#ifndef __TABELA_SIMBOLOS__
#define __TABELA_SIMBOLOS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-----------------Categoria do simbolo-----------------//
typedef enum CategoriaSimbolo
{
    CAT_VARIAVEL,
    CAT_PARAM_FORMAL_SIMPLES,
    CAT_PROCEDIM,
	CAT_FUNCAO,
} CategoriaSimbolo;

//-----------------Tipos das variaveis-----------------//
typedef enum VarTipo{
  TYPE_UNDEFINED, TYPE_INT, TYPE_BOOL
} VarTipo;


typedef enum PassagemTipo{
  REFERENCIA,PARAMETRO
} PassagemTipo;



//-----------------Estruturas da tabela de simbolos-----------------//

typedef struct VariavelSimples
{
	VarTipo tipo;
	int deslocamento;
} VariavelSimples;

typedef struct ParametroFormal
{
	VarTipo tipo;
	int deslocamento;
	PassagemTipo passagem;
} ParametroFormal;


struct Item;

typedef struct Procedimento
{
	char rotulo[10];
	int n;							// qtd de parametros
	ParametroFormal* parametros;
	VarTipo tipo;
	int implemented;
} Procedimento;


typedef struct Item
{
	struct Item* prev,*next;
	char* identificador;
	CategoriaSimbolo categoria;
	int nivel;
	union {
		VariavelSimples var;
		ParametroFormal param;
		Procedimento proc;
	};

} Item;


//-----------------Tabela de simbolos-----------------//
typedef struct TabelaSimbolos { 

    int tamanho;
    Item* primeiro, *ultimo;
} TabelaSimbolos;


//-----------------Primitivas da tabela de simbolo-----------------//
void insere(TabelaSimbolos* ts,Item* registro);

Item* busca(TabelaSimbolos* ts,char* identificador);

void elimina(TabelaSimbolos* ts,int n);

//-----------------Funcoes auxiliares-----------------//
void initTS(TabelaSimbolos* ts);

void destroiItem(Item* item);

void atualizaTipos(TabelaSimbolos* ts, int qtd, VarTipo tipo);

#endif
