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