#ifndef ARBOL_FAMILIA_H
#define ARBOL_FAMILIA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "miembro_mafia.h"

template<class T>
class Node {
private:
    T data;
    int height;
    int fe;
    Node<T> *left;
    Node<T> *right;

public:
    enum Ramas { IZQ = 0, DER = 1 };

    Node(T data, Node<T>* right, Node<T>* left);
    Node<T>* getChild(int child);
    void setLeft(Node<T>* left);
    void setRight(Node<T>* right);
    void setData(T data);
    T getData() const;
    void setFe();
    int getFe() const;
    int getHeight() const;
    void setHeight(int h);
    bool isLeaf() const;
    
    static int calculateHeight(Node<T>* node);
};

template<class T>
class ArbolFamilia {
private:
    Node<T>* root;
    enum { IZQ = 0, DER = 1 };

    
    Node<T>* rotationSimpleIzq(Node<T>* node, Node<T>* child);
    Node<T>* rotationSimpleDer(Node<T>* node, Node<T>* child);
    Node<T>* rotationDoubleIzq(Node<T>* node, Node<T>* child);
    Node<T>* rotationDoubleDer(Node<T>* node, Node<T>* child);
    
   
    Node<T>* insert(Node<T>* node, T data, bool& heightChanged);
    Node<T>* buscarNodo(Node<T>* node, int id);
    void inOrden(Node<T>* node);
    Node<T>* buscarSucesor(Node<T>* node, bool buscarEnPrison);

public:
    ArbolFamilia();
    void insertar(T data);
    Node<T>* buscar(int id);
    void mostrarLineaSucesion();
    Node<T>* encontrarPrimerSucesor();
    Node<T>* encontrarSucesorEnPrison();
    void actualizarJefatura(Node<T>* nuevoJefe);
    Node<T>* getRoot();
};


#include "arbol_familia.cpp"

#endif
