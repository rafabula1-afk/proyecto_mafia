#ifndef ARBOL_FAMILIA_H
#define ARBOL_FAMILIA_H

#include <iostream>
#include <string>
#include "miembro_mafia.h"

template<class T>
class NodoSimple {
public:
    T data;
    NodoSimple<T>* izquierda;
    NodoSimple<T>* derecha;
    
    NodoSimple(T data);
};

template<class T>
class ArbolFamilia {
private:
    NodoSimple<T>* root;
    
    void insertarSimple(NodoSimple<T>*& node, T data);
    NodoSimple<T>* buscarSimple(NodoSimple<T>* node, int id);
    void inOrdenSimple(NodoSimple<T>* node);

public:
    ArbolFamilia();
    void insertar(T data);
    NodoSimple<T>* buscar(int id);
    void mostrarLineaSucesion();
    void actualizarJefatura(NodoSimple<T>* nuevoJefe);
    void mostrarJerarquiaPorCapas();
};

#include "arbol_familia.cpp"

#endif
