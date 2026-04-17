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
    NodoSimple<MiembroMafia>* jefeActual;

    void crearArchivoCSV();
    void cargarDatosEnMemoria();

public:
    GestorSucesion();
    ~GestorSucesion();

    void inicializar(const std::string& archivoCSV);
    void mostrarLineaSucesion();
    void mostrarJerarquiaFamiliar();
    void asignarNuevoJefe();
    void modificarMiembro(int id);
    void mostrarMenuPrincipal();
    bool verificarEstadoJefe();
};

#endif
