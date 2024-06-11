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


void cache_comp_directa(int numBloques, int tamBloque, string fdirec_ruta)
{
    CacheDirecta cache(numBloques, tamBloque);


    ofstream salida;
    ifstream fdirec;
    uint32 direccion;

    salida.open("salida_composicion_directa.txt");
    fdirec.open(fdirec_ruta);

    while(fdirec >> direccion)
    {
        if(cache.acceso(direccion))
        {
            salida << "Direccion: "<< direccion << "| Acierto"<<endl;
        }
        else
        {
            salida << "Direccion: "<< direccion << "| Fallo"<<endl;
        }
    }

    salida.close();
    fdirec.close();
}

int ultimo_usado(vector<int> tiempos)
{
    int indice;
    int minimo = 1000;
    for(size_t i=0; i<tiempos.size(); i++)
    {
        if(tiempos[i] < minimo)
        {
            indice = i;
            minimo = tiempos[i];
        }
    }

    return indice;
}

void cache_asoc_conjuntos(int numBloques, int tamBloques, int tamConjuntos, string fdirec_ruta)
{

    CacheConjuntos cache(numBloques, tamBloques, tamConjuntos);
    uint32 direccion;

    ofstream salida;
    ifstream fdirec;
    salida.open("salida_asociativa_cojuntos.txt");
    fdirec.open(fdirec_ruta);

    while(fdirec >> direccion)
    {
        if(cache.acceso(direccion))
        {
            salida << "Direccion: "<< direccion << "| Acierto"<<endl;
        }
        else
        {
            salida << "Direccion: "<< direccion << "| Fallo"<<endl;
        }
    }

    salida.close();
    fdirec.close();
}

//no terminado
void cache_asociativa_compl(int numBloques, int tamBloques, string fdirec_ruta)
{

    CacheCompAsoc cache(numBloques, tamBloques);
    uint32 direccion;

    ofstream salida;
    ifstream fdirec;
    salida.open("salida_compl_asociativa.txt");
    fdirec.open(fdirec_ruta);

    while(fdirec >> direccion)
    {
        if(cache.acceso(direccion))
        {
            salida << "Direccion: "<< direccion << "| Acierto"<<endl;
        }
        else
        {
            salida << "Direccion: "<< direccion << "| Fallo"<<endl;
        }
    }
    fdirec.close();
    salida.close();

}

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

        cache_comp_directa(NUM_BLOQUES, BLOQUE_SIZE, fdirec_ruta);
        cache_asoc_conjuntos(NUM_BLOQUES, BLOQUE_SIZE, NUM_VIAS, fdirec_ruta);
        cache_asociativa_compl(NUM_BLOQUES, BLOQUE_SIZE, fdirec_ruta);


    }

    return 0;
}
