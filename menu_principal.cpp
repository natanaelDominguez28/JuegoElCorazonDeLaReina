/*menu principal del tp final integrador
*Grupo 23
*Dominguez Natanael
*Rodriguez M. Ruth Mabel
*Estructura de Datos 2023
*/
#include <iostream>
#include <stdlib.h>
#include "arbol_de_jugadores.hpp"
#include "lista_doble.hpp"
#include "tda_pila_modificado.hpp"

using namespace std;

const int MAXJUGADORES=4;

typedef struct tjugadores{
	tlistadoble cartasJugador;
	tjugador jugador;
	tpila pilaCartas;
};

void menu(int &op);
void menuJugadores(int &opjugador);
void menuBaraja(int &opbaraja);
void menuJugar(int &opJuego);
void elegir_jugador(parchivo jugadores, tjugadores arrjug[], int &cantidadElegidos);
void repartirCartas(tcola &mazo, tjugadores arrjug[], int cantidadElegidos);
bool puedoSacar(tlistadoble listaJugador, tcarta cmazo);
void jugar(tjugadores arrjug[], tcola &mazo, int cantidadElegidos, pnodobinario &arboljugadores);
//void agregar_jugador(tjugador j, tjugadores arrjug[], int &ocup);
void agregar_jugador(tjugador j, tjugadores arrjug[], int ocup, bool &repetido);
void inicializar(tjugadores jugadores[], int cantidadElegidos);
void agregar_arbol_ganadores(parchivo jug, pnodobinario &nuevo, pnodobinario &arbol);//corrección a árbol de ganadores (ranking)

main()
{
	int op, opjugador, opbaraja, opjuego, totalJugadores;
	parchivo jug, baraja;
	tcad nick;
	tcola lis;
	tjugadores elegidos[MAXJUGADORES];
	pnodobinario arbol;
	char eleccion;
	
	bool mazoCreado = false;
	bool jugadoresElegidos = false;
	iniciar_arbol(arbol);
	
	do{
		system("cls");
		menu(op);
		switch(op){
		case 1:
			do{
				system("cls");
				menuJugadores(opjugador);
				switch(opjugador){
				case 1:
					jug=fopen("jugadores.txt","ab+");
					alta_jugador(jug);
					fclose(jug);
					break;
				case 2:
					cout << "Ingresa el nombre de usuario del jugador: ";
					fflush(stdin);
					gets(nick);
					consultar_jugador(jug, nick);
					system("pause");
					break;
				case 3:
					cout << "Ingresa el nombre de usuario del jugador: ";
					fflush(stdin);
					gets(nick);
					modificar_jugador(jug,nick);
					break;
				case 4:
					listar_jugadores(jug,totalJugadores);
					cout << "jugadores registrados: " << totalJugadores << endl;
					system("pause");
					break;
				case 5:
					cout << "Ingresa el nombre de usuario del jugador: ";
					fflush(stdin);
					gets(nick);
					eliminar_jugador(jug,nick);
					break;
				case 6:
					cout << "retorno..." << endl;
					break;
				default: 
					cout << "opcion incorrecta" << endl;
				}
			} while(opjugador!=6);
			break;
		case 2:
			do{
				system("cls");
				menuBaraja(opbaraja);
				switch(opbaraja){
				case 1:
					baraja=fopen("baraja.txt","ab+");
					alta(baraja);
					cout << "baraja creada exitosamente " << endl;
					fclose(baraja);
					system("pause");
					break;
				case 2:
					crear_mazo(baraja, lis);
					mazoCreado = true;
					cout << "Mazo creado exitosamente" << endl;
					system("pause");
					break;
				case 3:
					if(mazoCreado!=true)
						cout << "debe crear el mazo" << endl;
					else
						mostrar_mazo(lis);
					system("pause");
					break;
				case 4:
					cout << "retorno..." << endl;
					break;
				default: cout << "opcion incorrecta" << endl;
				}
			} while(opbaraja!=4);
			
			break;
		case 3:
			do{
				system("cls");
				menuJugar(opjuego);
				switch(opjuego){
				case 1:
						elegir_jugador(jug,elegidos,totalJugadores);
						jugadoresElegidos=true;
					break;
				case 2:
					if(mazoCreado==true && jugadoresElegidos==true)
					{
						repartirCartas(lis,elegidos,totalJugadores);
					}
					else
						cout << "debe elegir jugadores y crear el mazo para poder jugar" << endl;
					system("pause");
					break;
				case 3:
					if(mazoCreado==true && jugadoresElegidos!=true)
						cout << "debe elegir 2 jugadores para iniciar la partida" << endl;
					else
					{
						if(mazoCreado!=true && jugadoresElegidos==true)
							cout << "debe crear el mazo" << endl;
						else
						{	
							if(mazoCreado!=true && jugadoresElegidos!=true)
								cout << "debe elegir jugadores y crear el mazo para poder continuar" << endl;
							else
							{
								cout << "Iniciando partida, buena suerte" << endl;
								jugar(elegidos,lis,totalJugadores,arbol);
							}
						}
					}
					free(lis.inicio); //libera el mazo creado
					free(arbol); //libera el árbol de jugadores
					free(elegidos); //libera la estructura donde están los jugadores elegidos para la partida
					system("pause");
					break;
				case 4:
					cout << "retorno ..." << endl;
					delete(lis.inicio);
					break;
				default: cout << "opcion incorrecta" << endl;
				}
			} while(opjuego!=4);
	
			break;
		case 4:
			//agregado luego de presentar tp integrador
			cout << "Desea ver los jugadores en orden creciente? S/n: ";
			cin >> eleccion;
			cout << "Ranking: " << endl;
			if(eleccion=='s' || eleccion=='S')
				enorden_creciente(arbol);
			else
			   enorden_decreciente(arbol);
			system("pause");
			break;
		case 5: cout << "fin del programa" << endl;
			break;
		default: 
			cout << "opcion incorrecta" << endl;
		}
	} while(op!=5);
	system("pause");
}

void menu(int &op)
{
	cout << "------menu de opciones------" << endl;
	cout << "1) GESTION DE JUGADORES" << endl;
	cout << "2) GESTION DE BARAJA" << endl;
	cout << "3) JUGAR" << endl;
	cout << "4) RANKING DE JUGADORES" << endl;
	cout << "5) SALIR" << endl;
	cout << "Ingresa una opcion:";
	cin >> op;
}

void menuJugadores(int &opjugador)
{
	cout << "----- menu de jugadores --------" << endl;
	cout << "1) AGREGAR JUGADOR" << endl;
	cout << "2) CONSULTAR JUGADOR" << endl;
	cout << "3) MODIFICAR JUGADOR" << endl;
	cout << "4) LISTAR JUGADORES" << endl;
	cout << "5) ELIMINAR JUGADOR" << endl;
	cout << "6) SALIR" << endl;
	cout << "Ingresa una opcion:";
	cin >> opjugador;
}

void menuBaraja(int &opbaraja)
{
	cout << "----- menu de baraja ------" << endl;
	cout << "1) GENERAR BARAJA" << endl;
	cout << "2) CREAR MAZO" << endl;
	cout << "3) MOSTRAR MAZO" << endl;
	cout << "4) SALIR" << endl;
	cout << "Ingresa una opcion:";
	cin >> opbaraja;
}

void menuJugar(int &opJuego)
{
	cout << "------ menu juego ------" << endl;
	cout << "1) ELEGIR JUGADORES" << endl;
	cout << "2) REPARTIR CARTAS" << endl;
	cout << "3) INICIAR PARTIDA" << endl;
	cout << "4) SALIR" << endl;
	cout << "Ingresa una opcion:";
	cin >> opJuego;
}
//método corregido luego de presentar el tp final
void elegir_jugador(parchivo jugadores, tjugadores arrjug[], int &cantidadElegidos)
{
	tcad n;
	bool existe = false, repetido = false;
	tjugador aux;
	char rta;
	int ocupado=0;
	//aquí falta modificar para que el jugador no pueda enfrentarse a sí mismo, o sea jugar contra él mismo
	do{
		cout << "Ingresa nickname del jugador: ";
		fflush(stdin);
		gets(n); 
		copiar_datos(jugadores, n, aux, existe);
		
		if(existe==true)
		{
			aux.puntaje=0;//agregado luego de enviar tp final
			agregar_jugador(aux, arrjug, ocupado, repetido);
			
			if(repetido!=true)
			{
				ocupado++;
				mostrar_jugador(aux);
				cantidadElegidos=ocupado;
			}
		}
		existe=false;
		repetido=false;
		cout << "Desea agregar otro jugador? S/n: ";
		cin >> rta;

	}while(rta!='n' && rta!='N');
}

void inicializar(tjugadores jugadores[], int cantidadElegidos)
{
	for(int j=0;j<cantidadElegidos;j++){
		iniciar_listadoble(jugadores[j].cartasJugador);
		iniciar_pila(jugadores[j].pilaCartas);
	}
}

/*void agregar_jugador(tjugador j, tjugadores arrjug[], int &ocup)
{
	//cada vez que se agrega un jugador el ocupado incrementa aquí
	ocup++;
	if(ocup<MAXJUGADORES)
		arrjug[ocup].jugador=j;
	else
		cout << "error" << endl;
}*/

//método corregido luego de presentar el tp final
void agregar_jugador(tjugador j, tjugadores arrjug[], int ocup, bool &repetido)
{
	//cada vez que se agrega un jugador el ocupado incrementa aquí
	cout << "valor de ocupado: " << ocup << endl;
	for(int i=0;i<ocup;i++)
	{
		if(strcmp(j.nickname,arrjug[i].jugador.nickname)==0)
		{
			cout << "jugador repetido" << endl;
			repetido=true;
		}
	}
	if(repetido!=true)
		arrjug[ocup].jugador=j;
}

void repartirCartas(tcola &mazo, tjugadores arrjug[], int cantidadElegidos){
	
	pnodold cartaAsignada;
	tcarta cartaDelMazo;
	
	int i,j;
	
	inicializar(arrjug,cantidadElegidos);
	
	for(i=0;i<cantidadElegidos;i++)
	{
		cout << "Repartiendo cartas a " << arrjug[i].jugador.nickname << endl;
		for(j=0;j<5;j++)
		{
			cartaDelMazo=quitar_cola(mazo)->dato;
			crear_nodold(cartaAsignada,cartaDelMazo);
			agregar_iniciold(arrjug[i].cartasJugador,cartaAsignada);
		}
		mostrar_cartas(arrjug[i].cartasJugador);
	}
}

void jugar(tjugadores arrjug[], tcola &mazo, int cantidadElegidos, pnodobinario &arboljugadores)
{
	pnodocola nuevo;
	pnodobinario nbinario;
	int sacada, posicionJugador, totalCartasRepartidas, puntajeGanador, puntajeRepetido;
	puntajeRepetido=0;
	tcarta extraido, elegida, carta, cartasDeLaPila;
	bool sacar=false;
	bool ok=false;
	bool existe=false;
	bool empate=false;
	
	totalCartasRepartidas=0;
	posicionJugador=0;
	puntajeGanador=0;
	//tjugador ganador;
	parchivo jug;
	
	
	for(int i=0;i<cantidadElegidos;i++)
	{
		totalCartasRepartidas+=arrjug[i].cartasJugador.cantidad;
		
	}
	cout << "Total de cartas repartidas: " << totalCartasRepartidas << endl;
	
	for(int j=0;j<totalCartasRepartidas;j++)
	{
		do{
			cout << "Turno de " << arrjug[posicionJugador].jugador.nickname << endl;
			mostrar_cartas(arrjug[posicionJugador].cartasJugador);
			cout << "carta del mazo: "<< endl;
			mostrar_carta(primero(mazo)->dato);
			sacar=puedoSacar(arrjug[posicionJugador].cartasJugador, primero(mazo)->dato);
			
			if(sacar!=true)
			{
				cout << "no puedes sacar..." << endl;
				sacar=false;
			}
			else
			{
				ok=false;//indica que se puede jugar
				do{
					cout << "Ingrese el nro de carta a sacar: ";
					cin >> sacada;// es la carta del jugador que eligió para agregar a la pila 
					buscar(arrjug[posicionJugador].cartasJugador,sacada, carta, existe);//la busca
					if(existe==true && (carta.numero>=primero(mazo)->dato.numero || strcmp(carta.tipo,"comodin")==0)){
						ok=true;
					}
				} while(ok!=true);
				//se agrega a la pila la carta extraida del mazo y una carta del jugador
				extraido=quitar_nodo_especifico(arrjug[posicionJugador].cartasJugador,carta)->carta;
				elegida=quitar_cola(mazo)->dato;//es la carta del mazo que el jugador pudo sacar
				agregar_pila(arrjug[posicionJugador].pilaCartas,extraido);
				agregar_pila(arrjug[posicionJugador].pilaCartas,elegida);
				mostrar_cartas(arrjug[posicionJugador].cartasJugador);//muestro las cartas que le quedan al jugador luego de agregarlas a la pila
			}
			posicionJugador++;
			//verifico si ningun jugador pudo extraer una carta del mazo
			if(posicionJugador==cantidadElegidos && sacar==false)
			{
				//cuando ningun jugador pueda sacar quito la carta del mazo y la guardo al final
				extraido=quitar_cola(mazo)->dato;
				crear_nodo(nuevo,extraido);
				agregar_cola(mazo,nuevo);
			}
			
		} while(posicionJugador!=cantidadElegidos);
		//reinicio la variable para que el juego continúe desde el primer jugador
		posicionJugador=0;
	}

	
	for(int p=0;p<cantidadElegidos;p++)
	{
		cout << "Cartas de " << arrjug[p].jugador.nickname << endl;
		while(pila_vacia(arrjug[p].pilaCartas)!=true)
		{
			cartasDeLaPila=quitar_pila(arrjug[p].pilaCartas);
			mostrar_carta(cartasDeLaPila);
			//puntos+=cartasDeLaPila.puntaje;
			arrjug[p].jugador.puntaje+=cartasDeLaPila.puntaje;//agregado luego de enviar el tp integrador
		}
		cout << "Puntaje total jugador " << arrjug[p].jugador.nickname << ": " << arrjug[p].jugador.puntaje << endl; 
	}
	
	for(int t=0;t<cantidadElegidos;t++)
	{
		if(puntajeGanador<arrjug[t].jugador.puntaje)
			puntajeGanador=arrjug[t].jugador.puntaje;//guardo el mayor puntaje de entre todos los jugadores elegidos
	}
	
	for(int j=0;j<cantidadElegidos;j++)
	{
		if(arrjug[j].jugador.puntaje==puntajeGanador)//busco quien es el jugador que ganó
		{	
			puntajeRepetido++;
			if(puntajeRepetido>=2)//verifico si hay jugadores empatados en puntaje
			{
				cout << "empate" << endl;
				empate=true;
				jug=fopen("jugadores.txt","rb");
				actualizar_puntaje(jug,arrjug[j].jugador.nickname,puntajeGanador, empate);
				fclose(jug);
			}
			else
			{
				empate=false;
				cout << "el ganador es " << arrjug[j].jugador.nickname << " con un total de " << puntajeGanador << " puntos" << endl;
				actualizar_puntaje(jug,arrjug[j].jugador.nickname,puntajeGanador, empate);//actualizo el puntaje en el archivo 
				/*ganador=arrjug[j].jugador;
				crear_nodobinario(nbinario,ganador);
				insertar(arboljugadores,nbinario);*/
			}
		}
	}
	agregar_arbol_ganadores(jug,nbinario,arboljugadores);//corregido luego de entregar tp final
}
//verifico si en las cartas del jugador exista al menos una que se pueda sacar  
bool puedoSacar(tlistadoble listaJugador, tcarta cmazo)
{
	bool puedoSacar=false;
	pnodold n;
	for(n=listaJugador.primero;n!=NULL;n=n->sig)
	{
		//si existe al menos una carta que sea mayor o igual a la carta del mazo o que sea comodín, devuelvo verdadero
		if((n->carta.numero >= (cmazo.numero)) || strcmp(n->carta.tipo,"comodin")==0)
			puedoSacar=true;
	}
	return puedoSacar;
}

void agregar_arbol_ganadores(parchivo jug, pnodobinario &nuevo, pnodobinario &arbol)
{
	tjugador j;
	jug=fopen("jugadores.txt","rb");

	if(jug==NULL)
		cout << "no existe el archivo" << endl;
	else
	{
		while(!feof(jug))
		{
			fread(&j,sizeof(j),1,jug);
			
			if(!feof(jug) && j.cantidadPartidasGanadas > 0)
			{
				crear_nodobinario(nuevo,j);//corregido
				if(nuevo!=NULL)
					insertar(arbol,nuevo);
			}
		}
	}
	fclose(jug);
}
