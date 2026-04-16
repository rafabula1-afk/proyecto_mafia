#ifndef GESTOR_SUCESION_H
#define GESTOR_SUCESION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "arbol_familia.h"
#include "miembro_mafia.h"

class GestorSucesion {
private:
    ArbolFamilia<MiembroMafia> arbol;
    Node<MiembroMafia>* jefeActual;
    std::string archivoDatos;

    void cargarDesdeCSV(const std::string& filename);
    void crearDatosEjemplo();
    Node<MiembroMafia>* buscarSucesorEnArbolJefe(Node<MiembroMafia>* jefe);
    Node<MiembroMafia>* buscarSucesorEnCompaneros(Node<MiembroMafia>* jefe);
    Node<MiembroMafia>* buscarSucesorEnJerarquiaSuperior(Node<MiembroMafia>* jefe);
    Node<MiembroMafia>* buscarPrimerSucesorVivoLibre();
    Node<MiembroMafia>* buscarPrimerSucesorEnPrison();
    void procesarSucesionAutomatica();
    void guardarNodosEnArchivo(Node<MiembroMafia>* node, std::ofstream& archivo);

public:
    GestorSucesion();
    ~GestorSucesion();

    void inicializar(const std::string& archivoCSV);
    void mostrarLineaSucesion();
    void asignarNuevoJefe();
    void modificarMiembro(int id);
    void guardarEstado();
    void mostrarMenuPrincipal();
    bool verificarEstadoJefe();
};

#endif
