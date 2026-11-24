#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "partidos.h"   // <-- cambia esto por el nombre de TU archivo donde está struct Partido
using namespace std;

// Máximo de equipos posibles (15 partidos x 2 equipos)
const int MAX_EQUIPOS = 30;

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
