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


auto menor_tiempo = [](CampoCache  e, CampoCache d) //Funcion comparadora para la funcion min_element
{
	return e.getTiempo() < d.getTiempo();
};

int indice_LRU(vector<CampoCache> conjunto)
{
	int indice;
	auto min_elem = min_element(conjunto.begin(), conjunto.end(), menor_tiempo);
	
	indice = distance(conjunto.begin(), min_elem);
	
	return indice;
}

void cache_asoc_conjuntos(int numBloques, int tamBloques, int tamConjuntos, string fdirec_ruta)
{
    int numConjuntos = numBloques / tamConjuntos;
    vector<vector<CampoCache>> cache(numConjuntos, vector<CampoCache>(tamConjuntos));
	
    int despBloque = log2(tamBloques);
    int direccion;
    int etiqueta;

    int indiceConjunto;

    ofstream salida;
    ifstream fdirec;
    salida.open("salida_asociativa_cojuntos.txt");
    fdirec.open(fdirec_ruta);

	int tmp_cont = 0;
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
				cache[indiceConjunto][i].setTiempo(tmp_cont);
				
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
			int reemplazo_i = indice_LRU(cache[indiceConjunto]);
			cache[indiceConjunto][reemplazo_i].cambiar(true, etiqueta, tmp_cont);
			
        }
		
	tmp_cont++;

    }

    salida.close();
    fdirec.close();
}


void cache_asociativa_compl(int numBloques, int tamBloques, string fdirec_ruta)
{
    vector<CampoCache> cache(numBloques);

    int direccion;
    int etiqueta;
    int despBloque = log2(tamBloques);

    ofstream salida;
    ifstream fdirec;
    salida.open("salida_completamente_asociativa.txt");
    fdirec.open(fdirec_ruta);
	
	int tmp_cont = 0;
    while(fdirec >> direccion)
    {
        etiqueta = direccion >> despBloque;
		bool acierto_flag = false;
		
		salida << "Direccion: "<< direccion << " Etiqueta: " << etiqueta << " "; 
		for(int i=0; i<numBloques; i++)
		{
			if(cache[i].getEtiqueta() == etiqueta && cache[i].getValidez())
			{
				acierto_flag = true;
				cache[i].setTiempo(tmp_cont);
				
				break;
			}
		}
		
		if(acierto_flag)
		{
			salida << " -> Acierto\n";
		}
		else
		{
			salida << " -> Fallo\n";
			int reemplazo_i = indice_LRU(cache);
			cache[reemplazo_i].cambiar(true, etiqueta, tmp_cont);
		}
		
		tmp_cont++;
    }

    fdirec.close();
    salida.close();

}
