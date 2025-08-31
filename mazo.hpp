#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "lista_simple.hpp"

using namespace std;

const int MAX=48;
typedef tcarta mazo[MAX];

void mostrar_mazo(tcola &lis)
{
	tcarta m[MAX];
	pnodocola nuevo;

	for(int i=0;i<MAX;i++)
	{	
		m[i]=quitar_cola(lis)->dato;
		cout << "Carta -> " << i+1 << endl;
		mostrar_carta(m[i]);
		crear_nodo(nuevo,m[i]);
		agregar_cola(lis,nuevo);
	}
}

bool chequearNoRepetido(int n, int num[])
{
	bool rep=false;
	for(int i=0;i<MAX;i++)
	{
		if(num[i]==n)
			rep=true;
	}
	return rep;
}

void mezclar(tcola &lis){
	srand(time(NULL));
	int i,p,valorAleatorio, posicionesAleatorias[MAX];
	tcarta aux[MAX];
	pnodocola nuevo;
	//vaciar el contenido de la lista en el arreglo
	for(i=0;i<MAX;i++)
	{
		aux[i]=quitar_cola(lis)->dato;
	}
	//quitar elementos del arreglo de manera aleatoria y agregarla a la cola
	iniciar_cola(lis);//agregada luego de presentar tp final
	for(p=0;p<MAX;p++){
		do{	
			valorAleatorio = rand()%48;
		}while(chequearNoRepetido(valorAleatorio,posicionesAleatorias));
		posicionesAleatorias[p]=valorAleatorio;
		crear_nodo(nuevo,aux[posicionesAleatorias[p]]);
		agregar_cola(lis,nuevo);
	}
}
	
void crear_mazo(parchivo baraja, tcola &q)
{
	baraja=fopen("baraja.txt","rb");
	tcarta b;
	pnodocola nuevo;
	iniciar_cola(q);
	
	if(baraja==NULL)
		cout << "no existe el archivo" << endl;
	else
	{
		while(!feof(baraja))
		{
			fread(&b,sizeof(b),1,baraja);
			if(!feof(baraja))
			{
				crear_nodo(nuevo,b);
				agregar_cola(q,nuevo);
			}
		}
		fclose(baraja);
	}
	mezclar(q);
}
	
