# ❤️ El Corazón de la Reina

> Juego de cartas por consola desarrollado en **C++** como Trabajo Práctico Final Integrador de la materia **Estructura de Datos** (2023).

---

## 📖 Descripción

*El Corazón de la Reina* es un juego de cartas para 2 a 4 jugadores, jugado completamente desde la terminal. En cada turno, los jugadores intentan colocar cartas de su mano que sean iguales o superiores a la carta del mazo. Al final de la partida, se suman los puntajes acumulados en la pila de cada jugador y se determina el ganador. Los resultados quedan registrados en un ranking persistente.

El proyecto aplica de forma práctica las siguientes **estructuras de datos**:

| Estructura | Uso en el juego |
|---|---|
| 🌳 Árbol Binario de Búsqueda | Ranking de jugadores (ordenado por puntaje) |
| 📋 Lista Doble Enlazada | Mano de cartas de cada jugador |
| 📋 Lista Simple Enlazada | Gestión interna de nodos |
| 🥞 Pila (modificada) | Cartas ganadas por cada jugador en la partida |
| 🔄 Cola | Mazo de juego (FIFO) |
| 📁 Archivos binarios | Persistencia de jugadores y baraja |

---

## 🎮 Mecánica del Juego

1. Se registran los jugadores participantes (2–4).
2. Se genera la baraja y se crea el mazo aleatorio.
3. Se reparten **5 cartas** a cada jugador.
4. En cada turno, el jugador activo debe colocar una carta de su mano cuyo número sea **mayor o igual** al de la carta en el tope del mazo, o usar un **comodín**.
5. Si ningún jugador puede jugar, la carta del mazo es descartada al final.
6. Al terminar las cartas, se cuentan los puntajes acumulados en la pila de cada jugador.
7. El jugador con más puntos gana. En caso de empate, ambos suman puntos.
8. Los resultados se guardan y pueden consultarse en el **ranking**.

---

## 📂 Estructura del Proyecto

```
JuegoElCorazonDeLaReina/
│
├── menu_principal.cpp          # Punto de entrada y lógica principal del juego
│
├── arbol_de_jugadores.hpp      # Árbol binario de búsqueda para el ranking
├── lista_doble.hpp             # Lista doblemente enlazada (mano del jugador)
├── lista_simple.hpp            # Lista simplemente enlazada
├── mazo.hpp                    # Cola para el mazo de cartas
├── tda_pila_modificado.hpp     # Pila modificada (cartas ganadas)
├── gestion_baraja.hpp          # Alta y carga de cartas desde archivo
├── gestion_jugador.hpp         # ABM de jugadores y manejo de puntajes
│
├── baraja.txt                  # Datos de las cartas (generado al iniciar)
├── jugadores.txt               # Registro persistente de jugadores
│
└── ED23 - Trabajo Final Integrador.pdf  # Enunciado oficial del TP
```

---

## ⚙️ Requisitos

- Compilador **C++11** o superior (`g++`, `clang++` o similar)
- Sistema operativo: **Windows**, **Linux** o **macOS**
- Solo usa la librería estándar de C++ (`iostream`, `stdlib.h`, `cstring`)

---

## ▶️ Compilación y Ejecución

### 1. Clonar el repositorio

```bash
git clone https://github.com/natanaelDominguez28/JuegoElCorazonDeLaReina.git
cd JuegoElCorazonDeLaReina
```

### 2. Compilar

```bash
g++ menu_principal.cpp -o corazon_de_la_reina
```

### 3. Ejecutar

```bash
# Linux / macOS
./corazon_de_la_reina

# Windows
corazon_de_la_reina.exe
```

---

## 🕹️ Menú Principal

```
------menu de opciones------
1) GESTION DE JUGADORES
2) GESTION DE BARAJA
3) JUGAR
4) RANKING DE JUGADORES
5) SALIR
```

**Flujo recomendado para una partida:**
1. `Gestión de Jugadores` → Registrar los jugadores
2. `Gestión de Baraja` → Generar baraja → Crear mazo
3. `Jugar` → Elegir jugadores → Repartir cartas → Iniciar partida
4. `Ranking` → Ver resultados en orden creciente o decreciente

---

## 🎥 Demo

[![Ver demo en YouTube](https://img.shields.io/badge/YouTube-Ver%20Demo-red?logo=youtube)](https://youtu.be/AT8Zk0sq-hU)

---

## 👨‍💻 Autores

| Nombre | Rol |
|---|---|
| **Natanael Dominguez** | Desarrollo |
| **Rodriguez M. Ruth Mabel** | Desarrollo |

📌 *Analista Programador Universitario — Estructura de Datos 2023*

---

## 📄 Licencia

Proyecto académico de uso educativo. Sin licencia comercial.
