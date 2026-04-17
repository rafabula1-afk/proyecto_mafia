#ifndef ARBOL_FAMILIA_CPP
#define ARBOL_FAMILIA_CPP

#include "arbol_familia.h"

template<class T>
NodoSimple<T>::NodoSimple(T data) : data(data), izquierda(nullptr), derecha(nullptr) {}

template<class T>
ArbolFamilia<T>::ArbolFamilia() : root(nullptr) {}

template<class T>
void ArbolFamilia<T>::insertarSimple(NodoSimple<T>*& node, T data) {
    if (!node) {
        node = new NodoSimple<T>(data);
        return;
    }
    if (data.getId() < node->data.getId()) {
        insertarSimple(node->izquierda, data);
    } else {
        insertarSimple(node->derecha, data);
    }
}

template<class T>
void ArbolFamilia<T>::insertar(T data) {
    insertarSimple(root, data);
}

template<class T>
NodoSimple<T>* ArbolFamilia<T>::buscarSimple(NodoSimple<T>* node, int id) {
    if (!node) return nullptr;
    if (node->data.getId() == id) return node;
    if (id < node->data.getId()) return buscarSimple(node->izquierda, id);
    return buscarSimple(node->derecha, id);
}

template<class T>
NodoSimple<T>* ArbolFamilia<T>::buscar(int id) {
    return buscarSimple(root, id);
}

template<class T>
void ArbolFamilia<T>::inOrdenSimple(NodoSimple<T>* node) {
    if (!node) return;
    inOrdenSimple(node->izquierda);
    if (node->data.estaVivo()) {
        node->data.mostrarInfo();
    }
    inOrdenSimple(node->derecha);
}

template<class T>
void ArbolFamilia<T>::mostrarLineaSucesion() {
    std::cout << "\n=== LINEA DE SUCESION ACTUAL ===" << std::endl;
    inOrdenSimple(root);
}

template<class T>
void ArbolFamilia<T>::actualizarJefatura(NodoSimple<T>* nuevoJefe) {
    if (nuevoJefe) {
        nuevoJefe->data.setIsBoss(true);
    }
}

template<class T>
void ArbolFamilia<T>::mostrarJerarquiaReal(NodoSimple<T>* node, int idBoss, int nivel) {
    if (!node) return;
    
    mostrarJerarquiaReal(node->izquierda, idBoss, nivel);
    
    if (node->data.getIdBoss() == idBoss) {
        for (int i = 0; i < nivel; i++) {
            std::cout << "  ";
        }
        std::cout << "+-- ";
        node->data.mostrarInfo();
        
        mostrarJerarquiaReal(root, node->data.getId(), nivel + 1);
    }
    
    mostrarJerarquiaReal(node->derecha, idBoss, nivel);
}

template<class T>
void ArbolFamilia<T>::mostrarJerarquiaPorCapas() {
    if (!root) {
        std::cout << "Arbol vacio" << std::endl;
        return;
    }
    
    NodoSimple<T>* jefe = buscarSimple(root, 1);
    
    if (!jefe) {
        std::cout << "No se encontro el jefe supremo (ID=1)" << std::endl;
        return;
    }
    
    std::cout << "\n=== ARBOL JERARQUICO FAMILIAR ===" << std::endl;
    std::cout << "JEFE SUPREMO:" << std::endl;
    jefe->data.mostrarInfo();
    std::cout << "|" << std::endl;
    
    mostrarJerarquiaReal(root, 1, 1);
}

template<class T>
NodoSimple<T>* ArbolFamilia<T>::getRoot() {
    return root;
}

#endif
