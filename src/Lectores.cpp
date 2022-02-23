#include <fstream>
#include <stdlib.h>
#include <iostream>

class Lecturalineas{
    private:
        int num_thread;
        int linea_inicial;
        int linea_final;
        int linea_objetivo;
        std::string palabra_objetivo;
        std::string palabra_anterior = "";
        std::string palabra_posterior = "";
        
    public:

        Lecturalineas();
        Lecturalineas(int num_thread,int linea_inicial, int linea_final, int linea_objetivo,std::string palabra_objetivo){
        
            this->num_thread = num_thread;
            this->linea_inicial = linea_inicial;
            this->linea_final = linea_final;
            this->linea_objetivo = linea_objetivo;
            this->palabra_objetivo = palabra_objetivo;
        }

        int getNum_thread(){
            return this->num_thread;
        }

        int getLinea_inicial(){
            return this->linea_inicial;
        }

        int getLinea_final(){
            return this->linea_final;
        }

        int getLinea_objetivo(){
            return this->linea_objetivo;
        }
        std::string getPalabra_objetivo(){
            return this->palabra_objetivo;
        }
        std::string getPalabra_anterior(){
            return this->palabra_anterior;
        }
        std::string getPalabra_posterior(){
            return this->palabra_posterior;
        }
        void toString(){
            std::cout <<"[Hilo: "<<this->num_thread<<"] "<<"inicio: "<<this->linea_inicial<<" -- final: "<<this->linea_final<<" :: "<<"linea "<<this->linea_objetivo<<" :: ..."<<this->palabra_anterior<<" "<<this->palabra_objetivo<<" "<<this->palabra_posterior<<std::endl;
        }
        void setPalabra_anterior(std::string palabra_anterior){
            this->palabra_anterior=palabra_anterior;
        }
        void setPalabra_posterior(std::string palabra_posterior){
            this->palabra_posterior=palabra_posterior;
        }
};