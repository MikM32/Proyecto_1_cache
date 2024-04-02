#include "caches.h"

                                            //tamaño de bloque en palabras
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
    int numConjuntos = numBloques / tamConjuntos;
    vector<vector<CampoCache>> cache(numConjuntos, vector<CampoCache>(tamConjuntos));
    vector<int> tiempos(tamConjuntos);

    int despBloque = log2(tamBloques);
    int direccion;
    int etiqueta;

    int indiceConjunto;

    ofstream salida;
    ifstream fdirec;
    salida.open("salida_asociativa_cojuntos.txt");
    fdirec.open(fdirec_ruta);


    CampoCache last;
    int last_i;
    while(fdirec >> direccion)
    {
        etiqueta = direccion >> despBloque;
        indiceConjunto = etiqueta % numConjuntos;
        bool flag_acierto=false;

        salida << "| Direccion: "<< direccion << "| Etiqueta: " << etiqueta << "| Indice Conj: " << indiceConjunto;
        for(int i=0; i<tamConjuntos; i++)
        {
            CampoCache campAct = cache[indiceConjunto][i];

            if(campAct.getEtiqueta() == etiqueta && campAct.getValidez())
            {
                flag_acierto = true;
                //last = campAct;
                //last_i = i;
                break;
            }
        }

        if(flag_acierto)
        {
            salida << " -> Acierto\n";
        }
        else
        {
            salida << " -> Fallo\n";
            if(cache[indiceConjunto][tamConjuntos-1].getValidez()) //esta lleno el conjunto
            {                                                       // Se usa la tecnica LRU para sustituir las etiquetas
                //CampoCache aux = last;
                last.setEtiqueta(etiqueta);
                cache[indiceConjunto][last_i] = last;
            }
            else
            {
                int j=0;
                for(j=0; j<tamConjuntos; j++)                     //Buca el indice del elemento del conjunto que esta vacio
                {
                    if(!cache[indiceConjunto][j].getValidez())
                    {
                        break;
                    }
                }

                cache[indiceConjunto][j].setEtiqueta(etiqueta);
                cache[indiceConjunto][j].setValidez(true);
                last = cache[indiceConjunto][j];
                last_i = j;
            }
        }

    }

    salida.close();
    fdirec.close();
}

//no terminado
void cache_asociativa_compl(int numBloques, int tamBloques, string fdirec_ruta)
{
    vector<CampoCache> cache(numBloques);

    int direccion;
    int etiqueta;
    int indice; //A pesar de llamarse indice las cache totalmente asociativas no tienen uno, esta variable servira para obtener la posicion de cada elemento
    int despBloque = log2(tamBloques);

    ofstream salida;
    ifstream fdirec;
    salida.open("salida_asociativa_cojuntos.txt");
    fdirec.open(fdirec_ruta);

    while(fdirec >> direccion)
    {
        etiqueta = direccion >> despBloque;
    }

    fdirec.close();
    salida.close();

}
