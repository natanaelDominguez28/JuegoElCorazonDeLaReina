#include <iostream>
#include <stdlib.h>
#include "gestion_baraja.hpp"

using namespace std;

typedef char tcad[50];
typedef struct tnodocola *pnodocola;

typedef struct tnodocola{
	tcarta dato;
	pnodocola sig;
};

typedef struct tcola{
	pnodocola inicio;//frente
	pnodocola ultimo;//final
	int cantidad;
};

void crear_nodo(pnodocola &nuevo, tcarta b)//crear nodo modificado
{
	nuevo=new tnodocola;
	cargar_carta(b, b.numero, b.tipo, b.puntaje, b.palo);
	if(nuevo!=NULL)
	{
		nuevo->dato=b;
		nuevo->sig=NULL;
	}
	else
	   cout << "no hay memoria disponible" << endl; 
}

void iniciar_cola(tcola &q)
{
	q.inicio=NULL;
	q.ultimo=NULL;
	q.cantidad=0;
}

void agregar_cola(tcola &q, pnodocola nuevo)
{
	if(q.inicio==NULL)
	{
		q.inicio=nuevo;
		q.ultimo=nuevo;
	}
	else
	{
		if(q.cantidad < 48)
		{
			q.ultimo->sig=nuevo;
			q.ultimo=nuevo;
		}
		else
		   delete(nuevo);
	}
	q.cantidad++;
}

pnodocola quitar_cola(tcola &q)
{
	pnodocola extraido;
	if(q.inicio==NULL)
		extraido=NULL;
	else
	{
		extraido=q.inicio;
		q.inicio=extraido->sig;
		extraido->sig=NULL;
		q.cantidad--;
	}
	return extraido;
}

pnodocola primero(tcola q)
{
	return q.inicio;
}

pnodocola ultimo(tcola q)
{
	return q.ultimo;
}
