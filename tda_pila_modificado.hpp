#include <iostream>
#include <stdlib.h>
//#include "gestion_baraja.hpp"

using namespace std;

const int MAXPILA=10;
typedef tcarta tcontenedor[MAXPILA];
typedef struct tpila{
	tcontenedor datos;
	int cima;
};

void iniciar_pila(tpila &p)
{
	p.cima=-1;
}

bool pila_vacia(tpila p)
{
	return p.cima==-1;
}

bool pila_llena(tpila p)
{
	return p.cima==MAXPILA-1;
}

void agregar_pila(tpila &p, tcarta nuevo)
{
	if(pila_llena(p)==true)
		cout << "pila llena" << endl;
	else
	{
		p.cima++;
		p.datos[p.cima]=nuevo;
	}
}

tcarta quitar_pila(tpila &p)
{
	tcarta extraido;
	if(pila_vacia(p)==true)
	{
		extraido.numero=0;
		strcpy(extraido.palo,"NINGUNO");
		strcpy(extraido.tipo,"NINGUNO");
		extraido.puntaje=0;
	}
	else
	{
		extraido=p.datos[p.cima];
		p.cima--;
	}
	return extraido;
}

tcarta tope_pila(tpila p)
{
	tcarta tope;
	if(pila_vacia(p)==true)
	{
		tope.numero=0;
		strcpy(tope.palo, "NINGUNO");
		strcpy(tope.tipo, "NINGUNO");
		tope.puntaje=0;
	}
	else
		tope=p.datos[p.cima];	
	return tope;
}
