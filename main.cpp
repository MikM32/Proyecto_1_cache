#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "caches.h"

#define PALABRA 4   //Una palabra tiene 4 bytes
#define KB 1024     //Un KB tiene 1204 bytes

#define BLOQUE_SIZE 1 // 1 PALABRA
#define NUM_BLOQUES 4

#define NUM_VIAS 2

using namespace std;

/*
    --> Proyecto 1 de Arquitectura del Computador. Parte 1. <--

    Integrantes:    Miguel Matute.
                    Diego Arias.

    Descripcion:    Simular los tres tipos de cache en c++. recibe como entrada un archivo con una cantidad determinada de direcciones
                    y como salida crea un archivo donde sea vea cada acierto y fallo para cada direccion.
*/

int main(int argc, const char* argv[])
{
    if(argc < 2)
    {
        cout << "Metodo de uso:\n";
        cout << "\n\tsimulador_cache.exe [RUTA_DE_ARCHIVO_DE_DIRECCIONES]\n";
        return 1;
    }
    else{

        string fdirec_ruta = argv[1];

        //cache_comp_directa(NUM_BLOQUES, BLOQUE_SIZE, fdirec_ruta);
        cache_asoc_conjuntos(NUM_BLOQUES, BLOQUE_SIZE, NUM_VIAS, fdirec_ruta);


    }

    return 0;
}
