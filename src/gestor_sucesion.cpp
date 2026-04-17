#include "gestor_sucesion.h"

GestorSucesion::GestorSucesion() : jefeActual(nullptr) {}

GestorSucesion::~GestorSucesion() {}

void GestorSucesion::crearArchivoCSV() {
    std::ofstream archivo("datos.csv");
    if (archivo.is_open()) {
        archivo << "id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss\n";
        archivo << "1,Vito,Corleone,H,65,0,0,0,1,1\n";
        archivo << "2,Sonny,Corleone,H,40,1,0,0,0,0\n";
        archivo << "3,Fredo,Corleone,H,38,2,0,0,0,0\n";
        archivo << "6,Peter,Clemenza,H,55,3,0,0,0,0\n";
        archivo << "7,Salvatore,Tessio,H,58,3,0,0,0,0\n";
        archivo << "8,Vincent,Mancini,H,25,2,0,0,0,0\n";
        archivo << "10,Luca,Brasi,H,50,8,1,0,0,0\n";
        archivo << "11,Carlo,Rizzi,H,30,8,0,1,0,0\n";
        archivo << "4,Michael,Corleone,H,35,1,0,0,0,0\n";
        archivo << "5,Tom,Hagen,H,45,4,0,0,0,0\n";
        archivo << "12,Joey,Zasa,H,48,6,0,0,0,0\n";
        archivo << "9,Connie,Corleone,M,42,4,0,0,0,0\n";
        archivo.close();
        std::cout << "Archivo datos.csv creado." << std::endl;
    }
}

void GestorSucesion::cargarDatosEnMemoria() {
    MiembroMafia vito(1, "Vito", "Corleone", 'H', 65, 0, false, false, true, true);
    MiembroMafia sonny(2, "Sonny", "Corleone", 'H', 40, 1, false, false, false, false);
    MiembroMafia fredo(3, "Fredo", "Corleone", 'H', 38, 2, false, false, false, false);
    MiembroMafia peter(6, "Peter", "Clemenza", 'H', 55, 3, false, false, false, false);
    MiembroMafia salvatore(7, "Salvatore", "Tessio", 'H', 58, 3, false, false, false, false);
    MiembroMafia vincent(8, "Vincent", "Mancini", 'H', 25, 2, false, false, false, false);
    MiembroMafia luca(10, "Luca", "Brasi", 'H', 50, 8, true, false, false, false);
    MiembroMafia carlo(11, "Carlo", "Rizzi", 'H', 30, 8, false, true, false, false);
    MiembroMafia michael(4, "Michael", "Corleone", 'H', 35, 1, false, false, false, false);
    MiembroMafia tom(5, "Tom", "Hagen", 'H', 45, 4, false, false, false, false);
    MiembroMafia joey(12, "Joey", "Zasa", 'H', 48, 6, false, false, false, false);
    MiembroMafia connie(9, "Connie", "Corleone", 'M', 42, 4, false, false, false, false);
    
    arbol.insertar(vito);
    arbol.insertar(sonny);
    arbol.insertar(fredo);
    arbol.insertar(peter);
    arbol.insertar(salvatore);
    arbol.insertar(vincent);
    arbol.insertar(luca);
    arbol.insertar(carlo);
    arbol.insertar(michael);
    arbol.insertar(tom);
    arbol.insertar(joey);
    arbol.insertar(connie);
    
    jefeActual = arbol.buscar(1);
    std::cout << "Datos cargados en memoria." << std::endl;
}

void GestorSucesion::inicializar(const std::string& archivoCSV) {
    std::ifstream archivo(archivoCSV);
    if (!archivo.is_open()) {
        std::cout << "No se encontro " << archivoCSV << std::endl;
        crearArchivoCSV();
    }
    archivo.close();
    cargarDatosEnMemoria();
    std::cout << "Inicializacion completada." << std::endl;
}

void GestorSucesion::mostrarLineaSucesion() {
    arbol.mostrarLineaSucesion();
    if (jefeActual) {
        std::cout << "\n--- JEFE ACTUAL ---" << std::endl;
        jefeActual->data.mostrarInfo();
    }
}

void GestorSucesion::mostrarJerarquiaFamiliar() {
    arbol.mostrarJerarquiaPorCapas();
}

bool GestorSucesion::verificarEstadoJefe() {
    if (!jefeActual) return true;
    return jefeActual->data.getIsDead() || jefeActual->data.getInJail() || jefeActual->data.getAge() > 70;
}

void GestorSucesion::asignarNuevoJefe() {
    std::cout << "\nFuncion en desarrollo." << std::endl;
}

void GestorSucesion::modificarMiembro(int id) {
    NodoSimple<MiembroMafia>* nodo = arbol.buscar(id);
    if (!nodo) {
        std::cout << "Miembro no encontrado." << std::endl;
        return;
    }
    
    MiembroMafia miembro = nodo->data;
    int opcion;
    
    do {
        std::cout << "\n=== MODIFICAR MIEMBRO ===" << std::endl;
        miembro.mostrarInfo();
        std::cout << "\n1. Cambiar nombre" << std::endl;
        std::cout << "2. Cambiar apellido" << std::endl;
        std::cout << "3. Cambiar edad" << std::endl;
        std::cout << "5. Cambiar estado vivo/muerto" << std::endl;
        std::cout << "6. Cambiar estado prision" << std::endl;
        std::cout << "0. Guardar y salir" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;
        std::cin.ignore(10000, '\n');
        
        std::string input;
        int valor;
        
        switch(opcion) {
            case 1:
                std::cout << "Nuevo nombre: ";
                std::getline(std::cin, input);
                if (!input.empty()) miembro.setName(input);
                break;
            case 2:
                std::cout << "Nuevo apellido: ";
                std::getline(std::cin, input);
                if (!input.empty()) miembro.setLastName(input);
                break;
            case 3:
                std::cout << "Nueva edad: ";
                std::cin >> valor;
                if (valor > 0) miembro.setAge(valor);
                break;
            case 5:
                std::cout << "¿Esta muerto? (1=Si, 0=No): ";
                std::cin >> valor;
                miembro.setIsDead(valor == 1);
                break;
            case 6:
                std::cout << "¿Esta en prision? (1=Si, 0=No): ";
                std::cin >> valor;
                miembro.setInJail(valor == 1);
                break;
            case 0:
                nodo->data = miembro;
                std::cout << "Cambios guardados." << std::endl;
                if (jefeActual && jefeActual->data.getId() == id) {
                    jefeActual = nodo;
                }
                break;
        }
    } while (opcion != 0);
}

void GestorSucesion::mostrarMenuPrincipal() {
    int opcion;
    
    do {
        std::cout << "\n========================================" << std::endl;
        std::cout << "    FAMILIA MAFIA ITALIANA - GESTOR     " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Mostrar linea de sucesion" << std::endl;
        std::cout << "2. Mostrar arbol jerarquico" << std::endl;
        std::cout << "3. Asignar nuevo jefe" << std::endl;
        std::cout << "4. Modificar datos de un miembro" << std::endl;
        std::cout << "5. Verificar estado del jefe" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;
        std::cin.ignore(10000, '\n');
        
        switch(opcion) {
            case 1: mostrarLineaSucesion(); break;
            case 2: mostrarJerarquiaFamiliar(); break;
            case 3: asignarNuevoJefe(); break;
            case 4: {
                int id;
                std::cout << "ID del miembro: ";
                std::cin >> id;
                modificarMiembro(id);
                break;
            }
            case 5:
                if (verificarEstadoJefe()) {
                    std::cout << "El jefe NECESITA ser reemplazado." << std::endl;
                } else {
                    std::cout << "El jefe puede continuar." << std::endl;
                }
                break;
            case 0: std::cout << "\n¡Arrivederci!" << std::endl; break;
            default: std::cout << "Opcion invalida." << std::endl;
        }
    } while (opcion != 0);
}
