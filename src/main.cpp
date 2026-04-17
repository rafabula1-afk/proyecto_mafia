#include <iostream>
#include "gestor_sucesion.h"

int main() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "  SISTEMA DE SUCESION - FAMILIA MAFIA   " << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    GestorSucesion gestor;
    
    std::cout << "Inicializando sistema..." << std::endl;
    gestor.inicializar("datos.csv");
    
    std::cout << "\nSistema inicializado correctamente." << std::endl;
    
    gestor.mostrarMenuPrincipal();
    
    return 0;
}
