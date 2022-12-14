#include "tabela_simbolos.h"

//Tabela de simbolos
TabelaSimbolos ts;


//-----------------Primitivas da tabela de simbolo-----------------//
void insere(TabelaSimbolos* ts,Item* item)
{
	if(ts->tamanho == 0)
	{
		ts->primeiro = item;
		ts->ultimo = item;
	}
	else
	{
		item->prev = ts->ultimo;
		ts->ultimo->next = item;
	}
	
	ts->ultimo->next = NULL;
	ts->ultimo = item;
	ts->tamanho++;
	return;
}

Item* busca(TabelaSimbolos* ts,char* identificador)
{
	Item* elem = ts->ultimo;
	while(elem != NULL)
	{
		if(!strcmp(identificador,elem->identificador))
			break;
		else
			elem = elem->prev;
	}

	return elem;
}

void elimina(TabelaSimbolos* ts,int n)
{
	while(n > 0)
	{
		//Possui algo para remover
		if(ts->tamanho > n)
		{
			Item* toDelete = ts->ultimo;
			Item* novoTopo = ts->ultimo->prev;
			ts->ultimo = novoTopo;
			novoTopo->next = NULL;
			destroiItem(toDelete);
		}
		else
		{
			printf("[TS]\nAlerta: Tentou remover simbolos a mais");
			break;
		}
		n--;
	}
	
	if(ts->tamanho == 0)
		ts->primeiro = NULL;
	
	return;
}

//-----------------Funcoes auxiliares-----------------//
void initTS(TabelaSimbolos* ts)
{
	ts->tamanho = 0;
	ts->primeiro = NULL;
	ts->ultimo = NULL;
}

void destroiItem(Item* item)
{
	if(item == NULL)
		return;
		
	ParametroFormal* aux;
	ParametroFormal* p;
	switch(item->categoria)
	{
		case CAT_VARIAVEL:
			free(item);
			break;
		case CAT_PARAM_FORMAL_SIMPLES :
			p = item->param.next;
			
			if(p != NULL)
			{
				aux = p;
				p = p->next;
				free(aux);
			}
			free(item);
			break;
		case CAT_PROCEDIM:
			p = item->proc.parametros;
			
			if(p != NULL)
			{
				aux = p;
				p = p->next;
				free(aux);
			}
			free(item);
			break;
		default:
			break;
	}

}

void atualizaTipos(TabelaSimbolos* ts, int qtd, VarTipo tipo) {
	Item* item = ts->ultimo;
	while (item && qtd--) {
		item->var.tipo = tipo;
		item = item->prev;
	}
}
