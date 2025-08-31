#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

typedef FILE *parchivo;

typedef struct tcarta{
	//int indice;
	int numero;
	tcad palo;
	int puntaje;
	tcad tipo;
};

void cargar_carta(tcarta &b, int valor, tcad tipo, int puntos, tcad palo)
{
	b.numero=valor;
	strcpy(b.palo,palo);
	b.puntaje=puntos;
	strcpy(b.tipo,tipo);
}

void mostrar_carta(tcarta b)
{
	cout << "Numero: " << b.numero << " Palo: " << b.palo << endl;
	cout << "------------------"<<endl;
	//cout << "Tipo: " << b.tipo << endl;
	//cout << "Palo: " << b.palo << endl;
	//cout << "Puntaje: " << b.puntaje << endl;
}

void alta(parchivo carta)
{
	tcarta b;
	tcad tipo, palo;
	
	carta=fopen("baraja.txt","ab+");

		for(int i=1;i<=4;i++)
		{
			for(int j=1;j<=12;j++)
			{
				switch(i){
				case 1: 
					strcpy(palo,"oro");
					break;
				case 2:
					strcpy(palo,"espada");
					break;
				case 3:
					strcpy(palo,"copa");
					break;
				case 4:
					strcpy(palo,"bastos");
					break;
				default:
					cout << "datos incorrectos" << endl;
				}
				
				if(j==1 || j==2 || j==3)
				{
					if(j==1)
					{
						strcpy(tipo,"comodin");
						cargar_carta(b,j,tipo,50,palo);
					}
					else if(j==2 || j==3)
					{
						strcpy(tipo,"comodin");
						cargar_carta(b,j,tipo,25,palo);
					}
				}
				else
				{
					strcpy(tipo,"comun");
					if(j >= 4 && j <= 9)
					{
						if((j==7 && i==1) || (j==7 && i==2))
						{
							cargar_carta(b,j,tipo,15,palo);
						}
						else
							cargar_carta(b,j,tipo,5,palo);
					}
					else
					{	
						if(j >= 10 && j <= 12)
							cargar_carta(b,j,tipo,10,palo);
					}
				}
				if(!feof(carta))
				   fwrite(&b,sizeof(b),1,carta);
			}
		}
	fclose(carta);
}

void listar_cartas(parchivo baraja)
{
	tcarta b;
	baraja=fopen("baraja.txt","rb");
	if(baraja==NULL)
		cout << "archivo inexistente" << endl;
	else
	{
		while(!feof(baraja))
		{
			fread(&b,sizeof(b),1,baraja);
			if(!feof(baraja))
				mostrar_carta(b);
		}
	}
	fclose(baraja);
}
