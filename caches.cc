#include "caches.h"


void cache_comp_directa(int numBloques, int tamBloque, string fdirec_ruta)
{
    vector<CampoCache> cache(numBloques);
    int despBloque = log2(tamBloque);
    int direccion;
    int etiqueta;
    int indice;


    ofstream salida;
    ifstream fdirec;
    salida.open("salida_composicion_directa.txt");
    fdirec.open(fdirec_ruta);

    while(fdirec >> direccion)
    {
        etiqueta = direccion >> despBloque;
        indice = etiqueta % numBloques;

        salida << "| Direccion: "<< direccion << "| Etiqueta: " << etiqueta << "| Indice: " << indice;

        if(cache[indice].getEtiqueta() == etiqueta && cache[indice].getValidez()) //Si el bit de validez es verdadero y las etiquetas coinciden
        {
            salida << " -> Acierto\n";
        }
        else
        {
            salida << " -> Fallo\n";
            cache[indice].setEtiqueta(etiqueta);
            cache[indice].setValidez(true);     // Pone a verdadero el bit de validez
        }
    }

    salida.close();
    fdirec.close();
}
