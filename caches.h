#ifndef CACHES_H_INCLUDED
#define CACHES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <list>

using namespace std;

void cache_comp_directa(int numBloques, int tamBloque, string fdirec_ruta);
void cache_asoc_conjuntos(int numBloques, int tamBloques, int tamConjuntos, string fdirec_ruta);
void cache_asociativa_compl(int numBloques, int tamBloques, string fdirec_ruta);

class CampoCache
{
    private:
        bool validez = false;
        int etiqueta = 0;
        int tiempo = -1;
    public:


        //getters

        
        int getTiempo()
        {
            return this->tiempo;
        }
        bool getValidez()
        {
            return this->validez;
        }

        int getEtiqueta()
        {
            return this->etiqueta;
        }

        //setters
        
        void setTiempo(int t)
        {
            this->tiempo = t;
        }
        void setValidez(bool val)
        {
            this->validez = val;
        }
        void setEtiqueta(int et)
        {
            this->etiqueta = et;
        }
		
		void cambiar(bool val, int et, int tmp)
		{
			this->setValidez(val);
			this->setEtiqueta(et);
			this->setTiempo(tmp);
		}
};

#endif // CACHES_H_INCLUDED
