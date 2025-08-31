#include <iostream>
#include <stdlib.h>
#include "mazo.hpp"

using namespace std;

typedef struct tnodold *pnodold;
typedef struct tnodold{
	tcarta carta;
	pnodold ant;
	pnodold sig;
};

typedef struct tlistadoble{
	pnodold primero;
	pnodold ultimo;
	int cantidad;
};

void crear_nodold(pnodold &nuevo, tcarta c)
{
	nuevo = new tnodold;
	if(nuevo != NULL)
	{
		cargar_carta(c, c.numero, c.tipo, c.puntaje, c.palo);
		nuevo->carta = c;
		nuevo->ant=NULL;
		nuevo->sig=NULL;
	}
	else
	   cout << "no hay memoria disponible" << endl;
}

void iniciar_listadoble(tlistadoble &ld)
{
	ld.primero=NULL;
	ld.ultimo=NULL;
	ld.cantidad=0;
}

void agregar_iniciold(tlistadoble &ld, pnodold nuevo)
{
	if(ld.primero==NULL)
	{
		ld.primero=nuevo;
		ld.ultimo=nuevo;
	}
	else
	{
		nuevo->sig=ld.primero;
		ld.primero->ant=nuevo;
		ld.primero=nuevo;
	}
	ld.cantidad++;
}

void agregar_finalld(tlistadoble &ld, pnodold nuevo)
{
	if(ld.primero==NULL)
	{
		ld.primero=nuevo;
		ld.ultimo=nuevo;
	}
	else
	{
		ld.ultimo->sig=nuevo;
		nuevo->ant=ld.ultimo;
		ld.ultimo=nuevo;
	}
	ld.cantidad++;
}

pnodold quitar_nodo_especifico(tlistadoble &ld, tcarta c)
{
	pnodold extraido,i;
	if(ld.primero==NULL)
	{
		extraido=NULL;
	}
	else
	{
		if(ld.primero->carta.numero == c.numero )
		{
			if(ld.primero==ld.ultimo)
			{
				extraido=ld.primero;
				ld.primero=NULL;
				ld.ultimo=NULL;
			}
			else
			{
				extraido=ld.primero;
				ld.primero=extraido->sig;
				ld.primero->ant=NULL;
				extraido->sig=NULL;
			}
		}
		else
		{
			if(ld.ultimo->carta.numero == c.numero)
			{
				extraido=ld.ultimo;
				ld.ultimo=extraido->ant;
				ld.ultimo->sig=NULL;
				extraido->ant=NULL;
			}
			else
			{
				for(i=ld.primero->sig;i!=ld.ultimo && (i->carta.numero != c.numero);i=i->sig);
				if(i!=ld.ultimo)
				{
					extraido=i;
					(i->ant)->sig=extraido->sig;
					(i->sig)->ant=extraido->ant;
					extraido->sig=NULL;
					extraido->ant=NULL;
				}
				else
				   extraido=NULL;
			}
		}
		ld.cantidad--;
	}
	return extraido;
}

void mostrar_cartas(tlistadoble ld)
{
	pnodold i;
	if(ld.cantidad>0)
		for(i=ld.primero;i!=NULL;i=i->sig)
		{
			mostrar_carta(i->carta);
		}
	else
		cout << "lista vacia" << endl;
}

//verifica si existe una carta con el valor indicado "sacada" y retorna verdadero
void buscar(tlistadoble listaJugador ,int sacada, tcarta &carta, bool &existe){
	pnodold i;
	existe=false;
	
	for(i=listaJugador.primero;i!=NULL && existe==false;i=i->sig)
	{
		if(i->carta.numero==sacada)
		{
			existe=true;
			carta=i->carta;
		}
	}
}
