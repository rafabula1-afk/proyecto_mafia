#ifndef GESTOR_SUCESION_H
#define GESTOR_SUCESION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "arbol_familia.h"
#include "miembro_mafia.h"

class GestorSucesion {
private:
    ArbolFamilia<MiembroMafia> arbol;
    Node<MiembroMafia>* jefeActual;


    void cargarDesdeCSV(const std::string& filename);
    Node<MiembroMafia>* buscarSucesorEnArbolJefe(Node<MiembroMafia>* jefe);
    Node<MiembroMafia>* buscarSucesorEnCompaneros(Node<MiembroMafia>* jefe);
    Node<MiembroMafia>* buscarSucesorEnJerarquiaSuperior(Node<MiembroMafia>* jefe);
    Node<MiembroMafia>* buscarPrimerSucesorVivoLibre();
    Node<MiembroMafia>* buscarPrimerSucesorEnPrison();
    void procesarSucesionAutomatica();

public:
    GestorSucesion();
    ~GestorSucesion();

    // Métodos públicos
    void inicializar(const std::string& archivoCSV);
    void mostrarLineaSucesion();
    void asignarNuevoJefe();
    void modificarMiembro(int id);
    void guardarEstado(const std::string& filename);
    void mostrarMenuPrincipal();
    bool verificarEstadoJefe();
};

#endif