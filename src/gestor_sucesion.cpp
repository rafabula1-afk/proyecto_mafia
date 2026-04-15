#include "gestor_sucesion.h"
#include <limits>


GestorSucesion::GestorSucesion() : jefeActual(nullptr) {}


GestorSucesion::~GestorSucesion() {}


void GestorSucesion::cargarDesdeCSV(const std::string& filename) {
    std::ifstream archivo(filename);
    
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        return;
    }
    
    std::string linea;
    

    std::getline(archivo, linea);
    
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string campo;
        std::vector<std::string> campos;
        
        while (std::getline(ss, campo, ',')) {
            campos.push_back(campo);
        }
        
        if (campos.size() >= 10) {
            MiembroMafia miembro(
                std::stoi(campos[0]),    // id
                campos[1],               // name
                campos[2],               // last_name
                campos[3][0],            // gender
                std::stoi(campos[4]),    // age
                std::stoi(campos[5]),    // id_boss
                std::stoi(campos[6]) == 1,  // is_dead
                std::stoi(campos[7]) == 1,  // in_jail
                std::stoi(campos[8]) == 1,  // was_boss
                std::stoi(campos[9]) == 1   // is_boss
            );
            
            arbol.insertar(miembro);
            
            if (miembro.getIsBoss()) {
                jefeActual = arbol.buscar(miembro.getId());
            }
        }
    }
    
    archivo.close();
    std::cout << "Datos cargados exitosamente. ";
    std::cout << "Jefe actual: ";
    if (jefeActual) {
        std::cout << jefeActual->getData().getFullName() << std::endl;
    } else {
        std::cout << "No hay jefe asignado" << std::endl;
    }
}


void GestorSucesion::inicializar(const std::string& archivoCSV) {
    cargarDesdeCSV(archivoCSV);
}


void GestorSucesion::mostrarLineaSucesion() {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "     LÍNEA DE SUCESIÓN DE LA FAMILIA     " << std::endl;
    std::cout << "=========================================" << std::endl;
    
    arbol.mostrarLineaSucesion();
    
    if (jefeActual) {
        std::cout << "\n--- JEFE ACTUAL ---" << std::endl;
        jefeActual->getData().mostrarInfo();
    } else {
        std::cout << "\n--- NO HAY JEFE ASIGNADO ---" << std::endl;
    }
}


bool GestorSucesion::verificarEstadoJefe() {
    if (!jefeActual) {
        return true;  
    }
    
    MiembroMafia jefeData = jefeActual->getData();
    
    return jefeData.getIsDead() || 
           jefeData.getInJail() || 
           jefeData.getAge() > 70;
}


Node<MiembroMafia>* GestorSucesion::buscarSucesorEnArbolJefe(Node<MiembroMafia>* jefe) {
    if (!jefe) return nullptr;
    

    return arbol.encontrarPrimerSucesor();
}


Node<MiembroMafia>* GestorSucesion::buscarSucesorEnCompaneros(Node<MiembroMafia>* jefe) {
    if (!jefe) return nullptr;
    
    int idBoss = jefe->getData().getIdBoss();
    if (idBoss == 0) return nullptr;
    
    Node<MiembroMafia>* jefeSuperior = arbol.buscar(idBoss);
    if (!jefeSuperior) return nullptr;
    

    return arbol.encontrarPrimerSucesor();
}


Node<MiembroMafia>* GestorSucesion::buscarSucesorEnJerarquiaSuperior(Node<MiembroMafia>* jefe) {
    if (!jefe) return nullptr;
    
    int idBoss = jefe->getData().getIdBoss();
    int nivel = 0;
    const int MAX_NIVEL = 5; 
    
    while (idBoss != 0 && nivel < MAX_NIVEL) {
        Node<MiembroMafia>* jefeSuperior = arbol.buscar(idBoss);
        if (!jefeSuperior) break;
        
        Node<MiembroMafia>* sucesor = arbol.encontrarPrimerSucesor();
        if (sucesor && sucesor != jefe) {
            return sucesor;
        }
        
        idBoss = jefeSuperior->getData().getIdBoss();
        nivel++;
    }
    
    return nullptr;
}


Node<MiembroMafia>* GestorSucesion::buscarPrimerSucesorVivoLibre() {
    return arbol.encontrarPrimerSucesor();
}


Node<MiembroMafia>* GestorSucesion::buscarPrimerSucesorEnPrison() {
    return arbol.encontrarSucesorEnPrison();
}


void GestorSucesion::procesarSucesionAutomatica() {
    if (!jefeActual) {
        std::cout << "No hay jefe actual. Buscando primer sucesor válido..." << std::endl;
        jefeActual = buscarPrimerSucesorVivoLibre();
        
        if (!jefeActual) {
            std::cout << "No se encontraron sucesores libres. ";
            std::cout << "Buscando en prisión..." << std::endl;
            jefeActual = buscarPrimerSucesorEnPrison();
        }
        
        if (jefeActual) {
            arbol.actualizarJefatura(jefeActual);
            std::cout << "¡NUEVO JEFE ASIGNADO!" << std::endl;
            jefeActual->getData().mostrarInfo();
        }
        return;
    }
    
    MiembroMafia jefeData = jefeActual->getData();
    
    std::cout << "\n--- INICIANDO PROCESO DE SUCESIÓN ---" << std::endl;
    std::cout << "Jefe actual: " << jefeData.getFullName() << std::endl;
    std::cout << "Motivo: ";
    
    if (jefeData.getIsDead()) {
        std::cout << "Fallecimiento" << std::endl;
    } else if (jefeData.getInJail()) {
        std::cout << "Encarcelamiento" << std::endl;
    } else if (jefeData.getAge() > 70) {
        std::cout << "Edad superior a 70 años" << std::endl;
    }
    

    std::cout << "\n1. Buscando sucesor en árbol del jefe actual..." << std::endl;
    Node<MiembroMafia>* sucesor = buscarSucesorEnArbolJefe(jefeActual);
    

    if (!sucesor) {
        std::cout << "2. Buscando sucesor en compañeros del jefe..." << std::endl;
        sucesor = buscarSucesorEnCompaneros(jefeActual);
    }
    

    if (!sucesor) {
        std::cout << "3. Buscando sucesor en jerarquía superior..." << std::endl;
        sucesor = buscarSucesorEnJerarquiaSuperior(jefeActual);
    }
    

    if (!sucesor) {
        std::cout << "4. Buscando cualquier sucesor vivo y libre..." << std::endl;
        sucesor = buscarPrimerSucesorVivoLibre();
    }
    

    if (!sucesor) {
        std::cout << "5. Buscando sucesores en prisión..." << std::endl;
        sucesor = buscarPrimerSucesorEnPrison();
    }
    

    if (sucesor) {

        jefeData.setIsBoss(false);
        if (jefeData.getIsDead() || jefeData.getInJail()) {
            jefeData.setWasBoss(true);
        }
        

        arbol.actualizarJefatura(sucesor);
        jefeActual = sucesor;
        
        std::cout << "\n=========================================" << std::endl;
        std::cout << "     ¡NUEVO JEFE DE LA FAMILIA!         " << std::endl;
        std::cout << "=========================================" << std::endl;
        jefeActual->getData().mostrarInfo();
    } else {
        std::cout << "\n¡ALERTA! No se pudo encontrar un sucesor válido." << std::endl;
        std::cout << "La familia se queda sin jefe." << std::endl;
        jefeActual = nullptr;
    }
}


void GestorSucesion::asignarNuevoJefe() {
    if (!verificarEstadoJefe()) {
        std::cout << "El jefe actual sigue en condiciones de gobernar." << std::endl;
        std::cout << "¿Desea forzar la sucesión? (S/N): ";
        char respuesta;
        std::cin >> respuesta;
        
        if (respuesta != 'S' && respuesta != 's') {
            return;
        }
    }
    
    procesarSucesionAutomatica();
}


void GestorSucesion::modificarMiembro(int id) {
    Node<MiembroMafia>* nodo = arbol.buscar(id);
    
    if (!nodo) {
        std::cout << "Error: Miembro con ID " << id << " no encontrado." << std::endl;
        return;
    }
    
    MiembroMafia miembro = nodo->getData();
    int opcion;
    
    do {
        std::cout << "\n=== MODIFICAR MIEMBRO ===" << std::endl;
        miembro.mostrarInfo();
        
        std::cout << "\nOpciones disponibles:" << std::endl;
        std::cout << "1. Cambiar nombre" << std::endl;
        std::cout << "2. Cambiar apellido" << std::endl;
        std::cout << "3. Cambiar edad" << std::endl;
        std::cout << "4. Cambiar género" << std::endl;
        std::cout << "5. Cambiar estado (vivo/muerto)" << std::endl;
        std::cout << "6. Cambiar estado de prisión" << std::endl;
        std::cout << "7. Marcar como ex-jefe" << std::endl;
        std::cout << "0. Guardar y salir" << std::endl;
        std::cout << "Opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::string input;
        int valor;
        char genero;
        
        switch(opcion) {
            case 1:
                std::cout << "Nuevo nombre: ";
                std::getline(std::cin, input);
                if (!input.empty()) {
                    miembro.setName(input);
                }
                break;
                
            case 2:
                std::cout << "Nuevo apellido: ";
                std::getline(std::cin, input);
                if (!input.empty()) {
                    miembro.setLastName(input);
                }
                break;
                
            case 3:
                std::cout << "Nueva edad: ";
                std::cin >> valor;
                if (valor > 0 && valor < 150) {
                    miembro.setAge(valor);
                }
                break;
                
            case 4:
                std::cout << "Nuevo género (H/M): ";
                std::cin >> genero;
                if (genero == 'H' || genero == 'M') {
                    miembro.setGender(genero);
                }
                break;
                
            case 5:
                std::cout << "¿Está muerto? (1=Sí, 0=No): ";
                std::cin >> valor;
                miembro.setIsDead(valor == 1);
                break;
                
            case 6:
                std::cout << "¿Está en prisión? (1=Sí, 0=No): ";
                std::cin >> valor;
                miembro.setInJail(valor == 1);
                break;
                
            case 7:
                std::cout << "¿Fue jefe anteriormente? (1=Sí, 0=No): ";
                std::cin >> valor;
                miembro.setWasBoss(valor == 1);
                break;
                
            case 0:
                nodo->setData(miembro);
                std::cout << "Cambios guardados exitosamente." << std::endl;
                
                
                if (jefeActual && jefeActual->getData().getId() == id) {
                    jefeActual = nodo;
                }
                break;
                
            default:
                std::cout << "Opción inválida." << std::endl;
        }
        
    } while (opcion != 0);
}


void GestorSucesion::guardarEstado(const std::string& filename) {
    std::ofstream archivo(filename);
    
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo " << filename << std::endl;
        return;
    }
    
    archivo << "id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss\n";
    
    archivo.close();
    std::cout << "Estado guardado en " << filename << std::endl;
}


void GestorSucesion::mostrarMenuPrincipal() {
    int opcion;
    
    do {
        std::cout << "\n========================================" << std::endl;
        std::cout << "    FAMILIA MAFIA ITALIANA - GESTOR     " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Mostrar línea de sucesión actual" << std::endl;
        std::cout << "2. Asignar nuevo jefe automáticamente" << std::endl;
        std::cout << "3. Modificar datos de un miembro" << std::endl;
        std::cout << "4. Verificar estado del jefe actual" << std::endl;
        std::cout << "5. Guardar estado actual" << std::endl;
        std::cout << "0. Salir del programa" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch(opcion) {
            case 1:
                mostrarLineaSucesion();
                break;
                
            case 2:
                asignarNuevoJefe();
                break;
                
            case 3: {
                int id;
                std::cout << "Ingrese el ID del miembro a modificar: ";
                std::cin >> id;
                modificarMiembro(id);
                break;
            }
                
            case 4:
                if (verificarEstadoJefe()) {
                    std::cout << "El jefe actual NECESITA ser reemplazado." << std::endl;
                    std::cout << "¿Desea iniciar el proceso de sucesión? (S/N): ";
                    char respuesta;
                    std::cin >> respuesta;
                    if (respuesta == 'S' || respuesta == 's') {
                        procesarSucesionAutomatica();
                    }
                } else {
                    std::cout << "El jefe actual está en condiciones de continuar." << std::endl;
                }
                break;
                
            case 5:
                guardarEstado("datos_actualizados.csv");
                break;
                
            case 0:
                std::cout << "\n¡Grazie per aver usato il sistema!" << std::endl;
                std::cout << "¡Arrivederci!\n" << std::endl;
                break;
                
            default:
                std::cout << "Opción inválida. Intente nuevamente." << std::endl;
        }
        
    } while (opcion != 0);
}