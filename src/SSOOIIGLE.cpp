/*********************************************
 * 
 * Proyecto: Practica 2 de SSOO2
 * 
 * Programa: SSOOIIGLE.cpp
 * 
 * Descripcion: Lectura y almacenamiento del libro, creación de hilos y finalización de estos.
 * 
 * Fecha de Creacion: 30-03-2020
 * 
 * Nombre: Paulino de la Fuente Lizcano
 * 
 * Seguimiento: En github se puede ver el cronograma del proyecto, aunque tuve problemas y no
 * esta todo reflejado
**********************************************/
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstring>
#include <filesystem>
#include <bits/stdc++.h>
#include "Lectores.cpp"


#define PATH_LIBROS "./libros"
#define MAX_BUFF_SIZE 1024

/***Variables globales***/
char *LIBRO;
std::string PALABRAOBJ;
int NUM_HILOS;
int nlineas=0;

std::vector<Lecturalineas> vLectores;
std::atomic<long>ocurrencias (0);
std::map<int,std::vector<Lecturalineas>> resultados;



void minusculas(std::string &cadena){
    int i;

    for(i=0;i<cadena.length();i++){
        cadena[i]=std::tolower(cadena[i]);
    }
    /*Función que convierte la palabra a minúscula*/
}
/*Cola de prioridades*/
void controlArgumentos(int argc, char *argv[]){

    if(argc!=4){
        std::cerr<<"Numero de argumentos erroneo"<<std::endl;
        exit(EXIT_FAILURE);
    }
    LIBRO = argv[1];
    PALABRAOBJ = argv[2];
    minusculas(PALABRAOBJ);
    NUM_HILOS = atoi(argv[3]);
    if(NUM_HILOS<0){
        std::cerr<<"Error en el numero de hilos"<<std::endl;
        exit(EXIT_FAILURE);
    }
}

/*Funcion que devuelve un vector, en cada posicion se almacena una palabra de la linea.*/
std::vector<std::string> procesarLinea(std::string cadena){
    std::vector<std::string>tokens;
    std::stringstream line(cadena);
    std::string aux;

    while(std::getline(line,aux,' ')){
        tokens.push_back(aux);
    }
    return tokens;
}

std::vector<std::string> eliminarCaracteres(std::vector<std::string> &palabras){
    int i;
    int x=0;
    std::vector<std::string> simbolos = {"[^,]+","[^?]+","[^¿]+","[^.]+","[^;]+","[^:]+"};
    std::regex simbol_regex(simbolos[x]);
    std::string match_str;
    std::vector<std::string> buenas;
    
        for(i=0;i<palabras.size();i++){
            auto word_begin = std::sregex_iterator(palabras[i].begin(),palabras[i].end(),simbol_regex);
            auto word_end = std::sregex_iterator();
            for(std::sregex_iterator x = word_begin; x !=word_end; x++){
                std::smatch match = *x;
                match_str = match.str();
            
            }
            buenas.push_back(match_str);
        }   
    return buenas;
}

void grep(int begin, int end,std::vector<std::string> lineaLibros,int id){

    std::vector<std::string> palabras;
    Lecturalineas *Lector;
    std::string cadena;
    int nlinea = begin;
    int j;

    for(j=begin;j<=end;j++){
        cadena = lineaLibros[j];
        nlinea++;
        minusculas(cadena);
        palabras=procesarLinea(cadena);
        palabras=eliminarCaracteres(palabras);

        for(int x=0;x<palabras.size();x++){

            if(nlinea>=j && nlinea<=end){

                if(palabras[x]==PALABRAOBJ){

                        ocurrencias++;

                        if((x+1)<palabras.size()){
                            Lector = new Lecturalineas(id,begin,end,nlinea,palabras[x]);
                            if((x-1)>=0){
                                Lector->setPalabra_anterior(palabras[x-1]);
                                Lector->setPalabra_posterior(palabras[x+1]);
                            }
                            
                        }else{
                            Lector = new Lecturalineas(id,begin,end,nlinea,palabras[x]);
                            if((x-1)>=0){
                                Lector->setPalabra_anterior(palabras[x-1]);
                            }
                        }
                        resultados[id].push_back(*Lector);
                        
                    }
                }
            }
    }
        
}

std::vector<std::string> leerLibro(char fullpath[MAX_BUFF_SIZE]){
    std::ifstream archivo(fullpath);
    std::vector<std::string> lineas;
    std::string cadena;

    if(archivo){
        while(std::getline(archivo,cadena)){
            nlineas++;
            lineas.push_back(cadena);
        }
    }else{
        std::cout<<"Error leyendo el archivo"<<std::endl;
        std::abort();
    }
    return lineas;
}

int main(int argc, char *argv[]){
    
    char fullpath[MAX_BUFF_SIZE];
    int paqueteLineas,i;
    std::vector<std::thread> vhilos;

    auto start = std::chrono::high_resolution_clock::now();
    controlArgumentos(argc, argv);
    
    sprintf(fullpath,"%s/%s.txt",PATH_LIBROS,LIBRO);
    /*Almacenamos en el vector todas las lineas del texto*/
    std::vector<std::string> lineasLibro=leerLibro(fullpath);

    paqueteLineas=nlineas/NUM_HILOS;

    if(paqueteLineas<1){
        paqueteLineas=1;
    }

    for(int i=0;i<NUM_HILOS;i++){
        int begin = i*paqueteLineas;
        int end = (begin+paqueteLineas)-1;
        if(i== NUM_HILOS-1){
            if(end!=nlineas){
                end = nlineas;
            }
        }
        vhilos.push_back(std::thread(grep,begin,end,lineasLibro,i));
    }

    std::for_each(vhilos.begin(), vhilos.end(), std::mem_fn(&std::thread::join));
    
    for(int x=0;x<resultados.size();x++){
        for(int y=0;y<resultados[x].size();y++){
            resultados[x][y].toString();
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapse = end-start;
    std::cout<<"Numero de ocurrencias: "<<ocurrencias<<std::endl;
    std::cout<<"[MANAGER] Programa acabado, con un tiempo de busqueda de: "<<elapse.count()<<std::endl;
    
}
