#include <iostream>
#include "gestor_sucesion.h"

int main() {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║  SISTEMA DE SUCESIÓN - FAMILIA MAFIA   ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝\n" << std::endl;
    
    GestorSucesion gestor;
    
    std::cout << "Inicializando sistema..." << std::endl;
    gestor.inicializar("datos.csv");
    
    gestor.mostrarMenuPrincipal();
    
    return 0;
}