#include "gestor_sucesion.h"

GestorSucesion::GestorSucesion() : jefeActual(nullptr), archivoDatos("") {}

GestorSucesion::~GestorSucesion() {}

void GestorSucesion::crearDatosEjemplo() {
    MiembroMafia vito(1, "Vito", "Corleone", 'H', 65, 0, false, false, true, true);
    MiembroMafia sonny(2, "Sonny", "Corleone", 'H', 40, 1, false, false, false, false);
    MiembroMafia fredo(3, "Fredo", "Corleone", 'H', 38, 1, false, false, false, false);
    MiembroMafia michael(4, "Michael", "Corleone", 'H', 35, 1, false, false, false, false);
    MiembroMafia tom(5, "Tom", "Hagen", 'H', 45, 1, false, false, false, false);
    MiembroMafia clemenza(6, "Peter", "Clemenza", 'H', 55, 1, false, false, false, false);
    MiembroMafia tessio(7, "Salvatore", "Tessio", 'H', 58, 1, false, false, false, false);
    MiembroMafia vincent(8, "Vincent", "Mancini", 'H', 25, 4, false, false, false, false);
    MiembroMafia connie(9, "Connie", "Corleone", 'M', 42, 1, false, false, false, false);
    MiembroMafia luca(10, "Luca", "Brasi", 'H', 50, 1, true, false, false, false);
    MiembroMafia carlo(11, "Carlo", "Rizzi", 'H', 30, 1, false, true, false, false);
    MiembroMafia joey(12, "Joey", "Zasa", 'H', 48, 0, false, false, false, false);
    
    arbol.insertar(vito);
    arbol.insertar(sonny);
    arbol.insertar(fredo);
    arbol.insertar(michael);
    arbol.insertar(tom);
    arbol.insertar(clemenza);
    arbol.insertar(tessio);
    arbol.insertar(vincent);
    arbol.insertar(connie);
    arbol.insertar(luca);
    arbol.insertar(carlo);
    arbol.insertar(joey);
    
    jefeActual = arbol.buscar(1);
}

void GestorSucesion::cargarDesdeCSV(const std::string& filename) {
    std::ifstream archivo(filename);
    
    if (!archivo.is_open()) {
        std::cout << "Archivo no encontrado. Creando datos de ejemplo..." << std::endl;
        crearDatosEjemplo();
        guardarEstado();
        std::cout << "Archivo creado con 12 miembros." << std::endl;
        return;
    }
    
    std::string linea;
    std::getline(archivo, linea);
    
    if (linea.empty()) {
        std::cout << "Archivo vacio. Llenando con datos de ejemplo..." << std::endl;
        archivo.close();
        crearDatosEjemplo();
        guardarEstado();
        std::cout << "Archivo llenado con 12 miembros." << std::endl;
        return;
    }
    
    bool tieneDatos = false;
    while (std::getline(archivo, linea)) {
        tieneDatos = true;
        std::stringstream ss(linea);
		std::string campos[10]; 
		int i = 0;
		std::string campo;
		
		while (std::getline(ss, campo, ',') && i < 10) {
		    campos[i] = campo;
		    i++;
		}
		
		if (i >= 10) {
		    MiembroMafia miembro(
		        std::stoi(campos[0]),
		        campos[1],
		        campos[2],
		        campos[3][0],
		        std::stoi(campos[4]),
		        std::stoi(campos[5]),
		        std::stoi(campos[6]) == 1,
		        std::stoi(campos[7]) == 1,
		        std::stoi(campos[8]) == 1,
		        std::stoi(campos[9]) == 1
		    );
            
            arbol.insertar(miembro);
            
            if (miembro.getIsBoss()) {
                jefeActual = arbol.buscar(miembro.getId());
            }
        }
    }
    
    archivo.close();
    
    if (!tieneDatos) {
        std::cout << "Archivo solo tiene cabecera. Llenando con datos de ejemplo..." << std::endl;
        crearDatosEjemplo();
        guardarEstado();
        std::cout << "Archivo llenado con 12 miembros." << std::endl;
        return;
    }
    
    std::cout << "Datos cargados exitosamente desde " << filename << std::endl;
    std::cout << "Jefe actual: ";
    if (jefeActual) {
        std::cout << jefeActual->getData().getFullName() << std::endl;
    } else {
        std::cout << "No hay jefe asignado" << std::endl;
    }
}

void GestorSucesion::inicializar(const std::string& archivoCSV) {
    archivoDatos = archivoCSV;
    cargarDesdeCSV(archivoCSV);
}

void GestorSucesion::mostrarLineaSucesion() {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "     LINEA DE SUCESION DE LA FAMILIA     " << std::endl;
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
    if (!jefeActual) return true;
    MiembroMafia jefeData = jefeActual->getData();
    return jefeData.getIsDead() || jefeData.getInJail() || jefeData.getAge() > 70;
}

Node<MiembroMafia>* GestorSucesion::buscarSucesorEnArbolJefe(Node<MiembroMafia>* jefe) {
    if (!jefe) return nullptr;
    return arbol.encontrarPrimerSucesor();
}

Node<MiembroMafia>* GestorSucesion::buscarSucesorEnCompaneros(Node<MiembroMafia>* jefe) {
    if (!jefe) return nullptr;
    return arbol.encontrarPrimerSucesor();
}

Node<MiembroMafia>* GestorSucesion::buscarSucesorEnJerarquiaSuperior(Node<MiembroMafia>* jefe) {
    if (!jefe) return nullptr;
    return arbol.encontrarPrimerSucesor();
}

Node<MiembroMafia>* GestorSucesion::buscarPrimerSucesorVivoLibre() {
    return arbol.encontrarPrimerSucesor();
}

Node<MiembroMafia>* GestorSucesion::buscarPrimerSucesorEnPrison() {
    return arbol.encontrarSucesorEnPrison();
}

void GestorSucesion::procesarSucesionAutomatica() {
    if (!jefeActual) {
        std::cout << "No hay jefe actual. Buscando primer sucesor valido..." << std::endl;
        jefeActual = buscarPrimerSucesorVivoLibre();
        
        if (!jefeActual) {
            std::cout << "No se encontraron sucesores libres. Buscando en prisión..." << std::endl;
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
    
    std::cout << "\n--- INICIANDO PROCESO DE SUCESION ---" << std::endl;
    std::cout << "Jefe actual: " << jefeData.getFullName() << std::endl;
    std::cout << "Motivo: ";
    
    if (jefeData.getIsDead()) std::cout << "Fallecimiento" << std::endl;
    else if (jefeData.getInJail()) std::cout << "Encarcelamiento" << std::endl;
    else if (jefeData.getAge() > 70) std::cout << "Edad superior a 70 años" << std::endl;
    
    Node<MiembroMafia>* sucesor = buscarSucesorEnArbolJefe(jefeActual);
    if (!sucesor) sucesor = buscarSucesorEnCompaneros(jefeActual);
    if (!sucesor) sucesor = buscarSucesorEnJerarquiaSuperior(jefeActual);
    if (!sucesor) sucesor = buscarPrimerSucesorVivoLibre();
    if (!sucesor) sucesor = buscarPrimerSucesorEnPrison();
    
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
        std::cout << "\n¡ALERTA! No se pudo encontrar un sucesor valido." << std::endl;
        jefeActual = nullptr;
    }
}

void GestorSucesion::asignarNuevoJefe() {
    if (!verificarEstadoJefe()) {
        std::cout << "El jefe actual sigue en condiciones de gobernar." << std::endl;
        std::cout << "¿Desea forzar la sucesion? (S/N): ";
        char respuesta;
        std::cin >> respuesta;
        if (respuesta != 'S' && respuesta != 's') return;
    }
    
    procesarSucesionAutomatica();
    guardarEstado();
}

void GestorSucesion::guardarNodosEnArchivo(Node<MiembroMafia>* node, std::ofstream& archivo) {
    if (!node) return;
    
    guardarNodosEnArchivo(node->getChild(0), archivo);
    
    MiembroMafia m = node->getData();
    archivo << m.getId() << ","
            << m.getName() << ","
            << m.getLastName() << ","
            << m.getGender() << ","
            << m.getAge() << ","
            << m.getIdBoss() << ","
            << (m.getIsDead() ? 1 : 0) << ","
            << (m.getInJail() ? 1 : 0) << ","
            << (m.getWasBoss() ? 1 : 0) << ","
            << (m.getIsBoss() ? 1 : 0) << "\n";
    
    guardarNodosEnArchivo(node->getChild(1), archivo);
}

void GestorSucesion::guardarEstado() {
    if (archivoDatos.empty()) {
        std::cerr << "Error: No se ha especificado un archivo de datos." << std::endl;
        return;
    }
    
    std::ofstream archivo(archivoDatos);
    
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo guardar en " << archivoDatos << std::endl;
        return;
    }
    
    archivo << "id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss\n";
    guardarNodosEnArchivo(arbol.getRoot(), archivo);
    archivo.close();
    
    std::cout << "Datos guardados en " << archivoDatos << std::endl;
}

void GestorSucesion::modificarMiembro(int id) {
    Node<MiembroMafia>* nodo = arbol.buscar(id);
    
    if (!nodo) {
        std::cout << "Error: Miembro con ID " << id << " no encontrado." << std::endl;
        return;
    }
    
    MiembroMafia miembro = nodo->getData();
    int opcion;
    bool cambiosRealizados = false;
    
    do {
        std::cout << "\n=== MODIFICAR MIEMBRO ===" << std::endl;
        miembro.mostrarInfo();
        
        std::cout << "\nOpciones disponibles:" << std::endl;
        std::cout << "1. Cambiar nombre" << std::endl;
        std::cout << "2. Cambiar apellido" << std::endl;
        std::cout << "3. Cambiar edad" << std::endl;
        std::cout << "4. Cambiar genero" << std::endl;
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
                if (!input.empty()) { miembro.setName(input); cambiosRealizados = true; }
                break;
            case 2:
                std::cout << "Nuevo apellido: ";
                std::getline(std::cin, input);
                if (!input.empty()) { miembro.setLastName(input); cambiosRealizados = true; }
                break;
            case 3:
                std::cout << "Nueva edad: ";
                std::cin >> valor;
                if (valor > 0 && valor < 150) { miembro.setAge(valor); cambiosRealizados = true; }
                break;
            case 4:
                std::cout << "Nuevo genero (H/M): ";
                std::cin >> genero;
                if (genero == 'H' || genero == 'M') { miembro.setGender(genero); cambiosRealizados = true; }
                break;
            case 5:
                std::cout << "¿Esta muerto? (1=Si, 0=No): ";
                std::cin >> valor;
                miembro.setIsDead(valor == 1);
                cambiosRealizados = true;
                break;
            case 6:
                std::cout << "¿Esta en prision? (1=Si, 0=No): ";
                std::cin >> valor;
                miembro.setInJail(valor == 1);
                cambiosRealizados = true;
                break;
            case 7:
                std::cout << "¿Fue jefe anteriormente? (1=Si, 0=No): ";
                std::cin >> valor;
                miembro.setWasBoss(valor == 1);
                cambiosRealizados = true;
                break;
            case 0:
                if (cambiosRealizados) {
                    nodo->setData(miembro);
                    std::cout << "Cambios guardados exitosamente." << std::endl;
                    if (jefeActual && jefeActual->getData().getId() == id) {
                        jefeActual = nodo;
                    }
                    guardarEstado();
                }
                break;
            default:
                std::cout << "Opción invalida." << std::endl;
        }
    } while (opcion != 0);
}

void GestorSucesion::mostrarMenuPrincipal() {
    int opcion;
    
    do {
        std::cout << "\n========================================" << std::endl;
        std::cout << "    FAMILIA MAFIA ITALIANA - GESTOR     " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Mostrar linea de sucesion actual" << std::endl;
        std::cout << "2. Asignar nuevo jefe automaticamente" << std::endl;
        std::cout << "3. Modificar datos de un miembro" << std::endl;
        std::cout << "4. Verificar estado del jefe actual" << std::endl;
        std::cout << "5. Guardar estado manualmente" << std::endl;
        std::cout << "0. Salir del programa" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch(opcion) {
            case 1: mostrarLineaSucesion(); break;
            case 2: asignarNuevoJefe(); break;
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
                        guardarEstado();
                    }
                } else {
                    std::cout << "El jefe actual esta en condiciones de continuar." << std::endl;
                }
                break;
            case 5: guardarEstado(); break;
            case 0:
                std::cout << "\nGuardando datos antes de salir..." << std::endl;
                guardarEstado();
                std::cout << "\n¡Grazie per aver usato il sistema!" << std::endl;
                std::cout << "¡Arrivederci!\n" << std::endl;
                break;
            default:
                std::cout << "Opción invalida. Intente nuevamente." << std::endl;
        }
    } while (opcion != 0);
}
