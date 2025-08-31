#include <iostream>
#include <stdlib.h>
#include "gestion_jugador.hpp"

using namespace std;

typedef struct tnodobinario *pnodobinario;
typedef struct tnodobinario{
	tjugador dato;
	pnodobinario izq;
	pnodobinario der;
};

void iniciar_arbol(pnodobinario &a)
{
	a=NULL;
}

void crear_nodobinario(pnodobinario &arbol, tjugador nuevo)
{
	arbol = new tnodobinario;
	if(arbol!=NULL)
	{
		arbol->dato = nuevo;
		arbol->izq=NULL;
		arbol->der=NULL;
	}
	else
	   cout << "no hay memoria disponible" << endl;
}

void insertar(pnodobinario &a, pnodobinario nuevo)
{
	if(a==NULL)
		a=nuevo;
	else
	{
		if(nuevo->dato.puntaje < a->dato.puntaje)
			insertar(a->izq,nuevo);
		else
			insertar(a->der,nuevo);
	}
}

//métodos agregados luego de presentar el tp final

//si de mayor a menor o de menor a mayor
void enorden_creciente(pnodobinario a){//IZQUIERDA-RAIZ-DERECHA
	if(a!=NULL)
	{
		enorden_creciente(a->izq);
		mostrar_jugador(a->dato);
		enorden_creciente(a->der);
	}
}
	
void enorden_decreciente(pnodobinario a)//DER-RAIZ-IZQUIERDA
{
	if(a!=NULL)
	{
		enorden_decreciente(a->der);
		mostrar_jugador(a->dato);
		enorden_decreciente(a->izq);
	}
}

void mostrar(pnodobinario a)
{
	if(a!=NULL)
	{
		//mostrar_jugador(a->dato); //se modificó el mostrar datos del jugador individualmente por uno ya definido
		cout << a->dato.nombre << endl;
		cout << a->dato.nickname << endl;
		cout << a->dato.puntaje << endl;
		mostrar(a->izq);
		mostrar(a->der);
	}
}
