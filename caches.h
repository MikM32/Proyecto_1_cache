#ifndef CACHES_H_INCLUDED
#define CACHES_H_INCLUDED

#include <fstream>
#include <vector>
#include <cmath>
#include <fstream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void cache_comp_directa(int numBloques, int tamBloque, string fdirec_ruta);
void cache_asoc_conjuntos(string fdirec_ruta);
void cache_comp_asociativa(string fdirec_ruta);

class CampoCache
{
    private:
        bool validez = false;
        int etiqueta = 0;
    public:


        //getters
        bool getValidez()
        {
            return this->validez;
        }

        int getEtiqueta()
        {
            return this->etiqueta;
        }

        //setters
        void setValidez(bool val)
        {
            this->validez = val;
        }
        void setEtiqueta(int et)
        {
            this->etiqueta = et;
        }
};

#endif // CACHES_H_INCLUDED
