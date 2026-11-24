#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "partidos.h"   // <-- cambia esto por el nombre de TU archivo donde está struct Partido
using namespace std;

// Máximo de equipos posibles (15 partidos x 2 equipos)
const int MAX_EQUIPOS = 6;

// Estructura para guardar las estadísticas de cada equipo
struct EquipoTabla {
    string nombre;
    int pj;   // partidos jugados
    int pg;   // partidos ganados
    int pe;   // partidos empatados
    int pp;   // partidos perdidos
    int gf;   // goles a favor
    int gc;   // goles en contra
    int pts;  // puntos
};
// Busca un equipo en la tabla; si no existe, lo agrega con todo en cero.
// Devuelve la posición del equipo dentro del arreglo.
inline int buscarOAgregarEquipo(
    EquipoTabla tabla[],
    int &totalEquipos,
    const string &nombre)
{
    for (int i = 0; i < totalEquipos; i++) {
        if (tabla[i].nombre == nombre) {
            return i;
        }
    }
        tabla[totalEquipos].nombre = nombre;
    tabla[totalEquipos].pj = 0;
    tabla[totalEquipos].pg = 0;
    tabla[totalEquipos].pe = 0;
    tabla[totalEquipos].pp = 0;
    tabla[totalEquipos].gf = 0;
    tabla[totalEquipos].gc = 0;
    tabla[totalEquipos].pts = 0;

    totalEquipos++;
    return totalEquipos - 1;
}

// Actualiza las estadísticas de UN equipo según los goles del partido
inline void registrarPartidoEquipo(EquipoTabla &equipo, int golesPropios, int golesRival)
{
    equipo.pj++;
    equipo.gf += golesPropios;
    equipo.gc += golesRival;

    if (golesPropios > golesRival) {        // Ganó: +3
        equipo.pg++;
        equipo.pts += 3;
    } else if (golesPropios == golesRival) { // Empató: +1
        equipo.pe++;
        equipo.pts += 1;
    } else {                                 // Perdió: +0
        equipo.pp++;
    }

}
// Devuelve true si el equipo "a" debe ir ARRIBA del equipo "b"
// Criterios: 1) puntos  2) diferencia de goles  3) goles a favor
inline bool vaPrimero(const EquipoTabla &a, const EquipoTabla &b)
{
    if (a.pts != b.pts) {
        return a.pts > b.pts;
    }

    int difA = a.gf - a.gc;
    int difB = b.gf - b.gc;
    if (difA != difB) {
        return difA > difB;
    }

    return a.gf > b.gf;
}

// Ordena la tabla (método burbuja)
inline void ordenarTabla(EquipoTabla tabla[], int totalEquipos)
{
    for (int i = 0; i < totalEquipos - 1; i++) {
        for (int j = 0; j < totalEquipos - 1 - i; j++) {
            if (vaPrimero(tabla[j + 1], tabla[j])) {
                EquipoTabla temp = tabla[j];
                tabla[j] = tabla[j + 1];
                tabla[j + 1] = temp;
            }
        }
    }
}
// Función principal: arma y muestra la tabla de posiciones
inline void mostrarTablaPosiciones(
    const Partido resultados[],
    int totalPartidos)
{
    if (totalPartidos == 0) {
        cout << "Primero debes simular el torneo.\n";
        return;
    }

    EquipoTabla tabla[MAX_EQUIPOS];
    int totalEquipos = 0;

    // Recorremos cada partido guardado y actualizamos a ambos equipos
    for (int i = 0; i < totalPartidos; i++) {
        int pos1 = buscarOAgregarEquipo(tabla, totalEquipos, resultados[i].equipo1);
        int pos2 = buscarOAgregarEquipo(tabla, totalEquipos, resultados[i].equipo2);

        registrarPartidoEquipo(tabla[pos1], resultados[i].goles1, resultados[i].goles2);
        registrarPartidoEquipo(tabla[pos2], resultados[i].goles2, resultados[i].goles1);
    }
    
    ordenarTabla(tabla, totalEquipos);

    // Imprimir la tabla
    cout << "\n--- TABLA DE POSICIONES ---\n";
    cout << left  << setw(5)  << "POS"
         << left  << setw(14) << "EQUIPO"
         << right << setw(4)  << "PJ"
         << setw(4) << "PG"
         << setw(4) << "PE"
         << setw(4) << "PP"
         << setw(5) << "GF"
         << setw(5) << "GC"
         << setw(5) << "PTS" << "\n";

    for (int i = 0; i < totalEquipos; i++) {
        cout << left  << setw(5)  << (i + 1)
             << left  << setw(14) << tabla[i].nombre
             << right << setw(4)  << tabla[i].pj
             << setw(4) << tabla[i].pg
             << setw(4) << tabla[i].pe
             << setw(4) << tabla[i].pp
             << setw(5) << tabla[i].gf
             << setw(5) << tabla[i].gc
             << setw(5) << tabla[i].pts << "\n";
    }

    cout << "\nPJ: jugados. PG: ganados. PE: empatados. PP: perdidos. "
         << "GF: goles a favor. GC: goles en contra. PTS: puntos.\n";
}