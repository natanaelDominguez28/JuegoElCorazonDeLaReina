/*gestion de jugadores*/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

typedef FILE *parchivo;

const int MAXJUG=4;

typedef char tcad[50];
typedef struct tjugador{
	tcad apellido;
	tcad nombre;
	tcad nickname;
	int puntaje;
	int cantidadPartidasGanadas;
};

void cargar_jugador(tjugador &j)
{
	bool ok=false;
	do{
		cout << "Ingresa apellido: ";
		fflush(stdin);
		gets(j.apellido);
		cout << "Ingresa nombre: ";
		fflush(stdin);
		gets(j.nombre);
		cout << "Ingresa nickname: ";
		fflush(stdin);
		gets(j.nickname);
		if(strlen(j.apellido)>0 && strlen(j.nombre)>0 && strlen(j.nickname)>0)
			ok=true;
		else
		{
			cout << "Debe llenar los campos para registrar el jugador" << endl;
			ok=false;
		}
		
	} while(ok!=true);
	j.puntaje=0;
	j.cantidadPartidasGanadas=0;
}

void buscar_jugador(parchivo jug, tcad nickname, bool &existe)
{
	tjugador j;
	jug=fopen("jugadores.txt","rb");
	while(!feof(jug))
	{
		fread(&j,sizeof(j),1,jug);
		if(!feof(jug))
		{
			if(strcmp(j.nickname,nickname)==0)
				existe=true;
		}
	}
	fclose(jug);
}
//guarda jugadores en un archivo, el nickname debe ser único por cada jugador
void alta_jugador(parchivo jug)
{
	tjugador nuevoJugador;
	char rta;
	bool existe=false;
	
	do{
		cargar_jugador(nuevoJugador);
		//llamar a módulo de búsqueda
		buscar_jugador(jug,nuevoJugador.nickname,existe);
		
		if(existe==false)
		{	jug=fopen("jugadores.txt","ab+");
			fwrite(&nuevoJugador,sizeof(nuevoJugador),1,jug);
			fclose(jug);
		}
		else
		   cout << "jugador repetido" << endl;
		
		cout << "Desea registrar otro jugador? S/N: ";
		cin >> rta;
	} while(rta !='n' && rta!='N');
}

void mostrar_jugador(tjugador j)
{
	cout << "Nombre: " << j.nombre << " Apellido: " << j.apellido << " Nickname: " << j.nickname << " Puntaje: " << j.puntaje << " Partidas ganadas: " << j.cantidadPartidasGanadas << endl;
	cout << "--------------------------" << endl;
}

void listar_jugadores(parchivo jug, int &contador)
{
	contador=0;
	tjugador j;
	jug=fopen("jugadores.txt","rb");
	if(jug==NULL)
		cout << "archivo inexistente" << endl;
	else
	{
		while(!feof(jug))
		{
			fread(&j,sizeof(j),1,jug);
			if(!feof(jug))
			{
				mostrar_jugador(j);
				contador++;
			}
		}
	}
	fclose(jug);
}

void consultar_jugador(parchivo jug, tcad nickname)
{
	tjugador j;
	bool existe=false;
	jug=fopen("jugadores.txt","rb");
	if(jug==NULL)
		cout << "archivo inexistente" << endl;
	else
	{
		while(!feof(jug) && !existe)
		{
			fread(&j,sizeof(j),1,jug);
			if(!feof(jug) && strcmp(nickname,j.nickname)==0)
			{
				mostrar_jugador(j);
				existe=true;
			}
		}
		if(!existe)
			cout << "el jugador no existe" << endl;
	}
	fclose(jug);
}

void copiar_datos(parchivo jug, tcad nickname, tjugador &temp, bool &existe)
{
	tjugador j;
	jug=fopen("jugadores.txt","rb");
	if(jug==NULL)
		cout << "archivo inexistente" << endl;
	else
	{
		while(!feof(jug) && !existe)
		{
			fread(&j,sizeof(j),1,jug);
			if(!feof(jug) && strcmp(nickname,j.nickname)==0)
			{
				existe=true;
				if(existe==true)
				{
					temp=j;
				}
			}
		}
		if(!existe)
			cout << "el jugador no existe" << endl;
	}
	fclose(jug);
}

//solo puede modificar nombre y apellido. El nickname, puntaje y cantidad de partidas ganadas debe mantenerse
void modificar_jugador(parchivo jug, tcad nickname)
{
	tjugador j, temp;
	bool encontrado=false;
	jug=fopen("jugadores.txt","rb+");
	if(jug==NULL)
		cout << "el archivo no existe" << endl;
	else
	{
		while(!feof(jug) && !encontrado)
		{
			fread(&j,sizeof(j),1,jug);
			if(strcmp(j.nickname,nickname)==0)
			{
				encontrado=true;
				temp = j;
			}
		}
		if(encontrado==false)
			cout << "jugador no encontrado" << endl;
		else
		{
			cout << "Ingresa apellido: ";
			fflush(stdin);
			gets(j.apellido);
			cout << "Ingresa nombre: ";
			fflush(stdin);
			gets(j.nombre);
			strcpy(temp.nickname,j.nickname);//j.nickname=temp.nickname;
			j.puntaje=temp.puntaje;
			j.cantidadPartidasGanadas=j.cantidadPartidasGanadas;
			
			fseek(jug,-sizeof(j),SEEK_CUR);
			fwrite(&j,sizeof(j),1,jug);
		}
	}
	fclose(jug);
}

//eliminar jugador
void eliminar_jugador(parchivo jug, tcad nickname)
{
	tjugador j;
	parchivo aux;
	
	jug=fopen("jugadores.txt","rb");
	aux=fopen("temporal.txt","wb");
	if(jug==NULL)
	{
		cout << "el archivo no existe" << endl;
		fclose(jug);
		fclose(aux);
	}
	else
	{
		while(!feof(jug))
		{
			fread(&j,sizeof(j),1,jug);
			if(strcmp(nickname,j.nickname)!=0 && !feof(jug))
			{
				fwrite(&j,sizeof(j),1,aux);
			}
		}
		fclose(jug);
		fclose(aux);
		if(remove("jugadores.txt")==0)
			rename("temporal.txt","jugadores.txt");
		else
			cout << "error al eliminar jugador" << endl;
	}
}

//modificado
void actualizar_puntaje(parchivo jug, tcad nickname, int nuevoPuntaje, bool empate)
{
	tjugador j;
	bool encontrado=false;
	jug=fopen("jugadores.txt","rb+");
	if(jug==NULL)
		cout << "el archivo no existe" << endl;
	else
	{
		while(!feof(jug) && !encontrado)
		{
			fread(&j,sizeof(j),1,jug);
			if(strcmp(j.nickname,nickname)==0)
			{
				encontrado=true;
				//temp = j;
				if(j.puntaje < nuevoPuntaje)
				{
					//j.puntaje=nuevoPuntaje;//actualizo puntaje
					j.puntaje=nuevoPuntaje;
				}
				if(empate!=true)
				{	
					//j.cantidadPartidasGanadas+=1;
					j.cantidadPartidasGanadas++;//incremento la cantidad de partidas ganadas
				}
				fseek(jug,-sizeof(j),SEEK_CUR);
				fwrite(&j,sizeof(j),1,jug);
			}
		}
		if(encontrado==false)
			  cout << "jugador no encontrado" << endl;
		/*else
		{
			strcpy(temp.apellido,j.apellido);
			strcpy(temp.nombre,j.apellido);
			strcpy(temp.nickname,j.nickname);//j.nickname=temp.nickname;
			if(j.puntaje < nuevoPuntaje)
			{
				//j.puntaje=nuevoPuntaje;//actualizo puntaje
				temp.puntaje=nuevoPuntaje;
			}
			if(empate!=true)
			{	
				//j.cantidadPartidasGanadas+=1;
				temp.cantidadPartidasGanadas++;//incremento la cantidad de partidas ganadas
			}
			fseek(jug,-sizeof(j),SEEK_CUR);
			fwrite(&j,sizeof(j),1,jug);
		}*/
	}
	fclose(jug);
}
