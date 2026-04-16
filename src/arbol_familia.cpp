#ifndef ARBOL_FAMILIA_CPP
#define ARBOL_FAMILIA_CPP

#include "arbol_familia.h"


template<class T>
int Node<T>::calculateHeight(Node<T>* node) {
    if (node == nullptr) return 0;
    int heightLeft = calculateHeight(node->left);
    int heightRight = calculateHeight(node->right);
    return (heightLeft > heightRight) ? heightLeft + 1 : heightRight + 1;
}

template<class T>
Node<T>::Node(T data, Node<T>* right, Node<T>* left) 
    : data(data), height(1), fe(0), right(right), left(left) {}

template<class T>
Node<T>* Node<T>::getChild(int child) {
    return (child == IZQ) ? left : right;
}

template<class T>
void Node<T>::setLeft(Node<T>* left) { 
    this->left = left; 
    height = calculateHeight(this);
    setFe();
}

template<class T>
void Node<T>::setRight(Node<T>* right) { 
    this->right = right; 
    height = calculateHeight(this);
    setFe();
}

template<class T>
void Node<T>::setData(T data) { 
    this->data = data; 
}

template<class T>
T Node<T>::getData() const { 
    return data; 
}

template<class T>
void Node<T>::setFe() {
    int hLeft = (left) ? left->height : 0;
    int hRight = (right) ? right->height : 0;
    fe = hRight - hLeft;
}

template<class T>
int Node<T>::getFe() const { 
    return fe; 
}

template<class T>
int Node<T>::getHeight() const { 
    return height; 
}

template<class T>
void Node<T>::setHeight(int h) { 
    height = h; 
    setFe(); 
}

template<class T>
bool Node<T>::isLeaf() const { 
    return !left && !right; 
}


template<class T>
ArbolFamilia<T>::ArbolFamilia() : root(nullptr) {}

template<class T>
Node<T>* ArbolFamilia<T>::rotationSimpleIzq(Node<T>* node, Node<T>* child) {
    node->setLeft(child->getChild(DER));
    child->setRight(node);
    
  
    node->setHeight(node->calculateHeight(node));
    child->setHeight(child->calculateHeight(child));
    
  
    return child;
}

template<class T>
Node<T>* ArbolFamilia<T>::rotationSimpleDer(Node<T>* node, Node<T>* child) {
    node->setRight(child->getChild(IZQ));
    child->setLeft(node);
    

    node->setHeight(node->calculateHeight(node));
    child->setHeight(child->calculateHeight(child));
    
    return child;
}

template<class T>
Node<T>* ArbolFamilia<T>::rotationDoubleIzq(Node<T>* node, Node<T>* child) {
    Node<T>* grandChild = child->getChild(IZQ);
    
    node->setRight(grandChild->getChild(IZQ));
    grandChild->setLeft(node);
    child->setLeft(grandChild->getChild(DER));
    grandChild->setRight(child);
    
  
    node->setHeight(node->calculateHeight(node));
    child->setHeight(child->calculateHeight(child));
    grandChild->setHeight(grandChild->calculateHeight(grandChild));
    
    return grandChild;
}

template<class T>
Node<T>* ArbolFamilia<T>::rotationDoubleDer(Node<T>* node, Node<T>* child) {
    Node<T>* grandChild = child->getChild(DER);
    
    node->setLeft(grandChild->getChild(DER));
    grandChild->setRight(node);
    child->setRight(grandChild->getChild(IZQ));
    grandChild->setLeft(child);
    
  
    node->setHeight(node->calculateHeight(node));
    child->setHeight(child->calculateHeight(child));
    grandChild->setHeight(grandChild->calculateHeight(grandChild));
    
    return grandChild;
}

template<class T>
Node<T>* ArbolFamilia<T>::insert(Node<T>* node, T data, bool& heightChanged) {
    if (!node) {
        heightChanged = true;
        return new Node<T>(data, nullptr, nullptr);
    }

    if (node->getData() > data) {
        node->setLeft(insert(node->getChild(IZQ), data, heightChanged));
        
        if (heightChanged) {
            node->setHeight(node->calculateHeight(node));
            
            Node<T>* child = nullptr;
            int fe = node->getFe();
            
            if (fe == 1) {
                heightChanged = false;
            } else if (fe == 0) {
               
            } else if (fe == -1) {
                child = node->getChild(IZQ);
                if (child->getFe() == -1) {
                    node = rotationSimpleIzq(node, child);
                } else {
                    node = rotationDoubleDer(node, child);
                }
                heightChanged = false;
            }
        }
    } else if (node->getData() < data) {
        node->setRight(insert(node->getChild(DER), data, heightChanged));
        
        if (heightChanged) {
            node->setHeight(node->calculateHeight(node));
            
            Node<T>* child = nullptr;
            int fe = node->getFe();
            
            if (fe == 1) {
                child = node->getChild(DER);
                if (child->getFe() == 1) {
                    node = rotationSimpleDer(node, child);
                } else {
                    node = rotationDoubleIzq(node, child);
                }
                heightChanged = false;
            } else if (fe == 0) {
               
            } else if (fe == -1) {
                heightChanged = false;
            }
        }
    }
    
    return node;
}

template<class T>
void ArbolFamilia<T>::insertar(T data) {
    bool heightChanged = false;
    root = insert(root, data, heightChanged);
}

template<class T>
Node<T>* ArbolFamilia<T>::buscarNodo(Node<T>* node, int id) {
    if (!node) return nullptr;
    
    if (node->getData().getId() == id) return node;
    
   
    T tempData = T(id, "", "", 'H', 0, 0, false, false, false, false);
    
    if (node->getData() > tempData)
        return buscarNodo(node->getChild(IZQ), id);
    else
        return buscarNodo(node->getChild(DER), id);
}

template<class T>
Node<T>* ArbolFamilia<T>::buscar(int id) {
    return buscarNodo(root, id);
}

template<class T>
void ArbolFamilia<T>::inOrden(Node<T>* node) {
    if (!node) return;
    inOrden(node->getChild(IZQ));
    if (node->getData().estaVivo()) {
        node->getData().mostrarInfo();
    }
    inOrden(node->getChild(DER));
}

template<class T>
void ArbolFamilia<T>::mostrarLineaSucesion() {
    std::cout << "\n=== LÍNEA DE SUCESIÓN ACTUAL ===\n";
    std::cout << "Miembros vivos:\n";
    inOrden(root);
}

template<class T>
Node<T>* ArbolFamilia<T>::buscarSucesor(Node<T>* node, bool buscarEnPrison) {
    if (!node) return nullptr;

    Node<T>* sucesor = buscarSucesor(node->getChild(IZQ), buscarEnPrison);
    if (sucesor) return sucesor;

    const T& data = node->getData();
    bool esValido = buscarEnPrison ? 
                   (data.estaVivo() && data.getInJail()) : 
                   data.estaVivoYLibre();
    
    if (esValido) return node;

    return buscarSucesor(node->getChild(DER), buscarEnPrison);
}

template<class T>
Node<T>* ArbolFamilia<T>::encontrarPrimerSucesor() {
    return buscarSucesor(root, false);
}

template<class T>
Node<T>* ArbolFamilia<T>::encontrarSucesorEnPrison() {
    return buscarSucesor(root, true);
}

template<class T>
void ArbolFamilia<T>::actualizarJefatura(Node<T>* nuevoJefe) {
    if (nuevoJefe) {
        T data = nuevoJefe->getData();
        data.setIsBoss(true);
        nuevoJefe->setData(data);
    }
}

template<class T>
Node<T>* ArbolFamilia<T>::getRoot() { 
    return root; 
}

#endif