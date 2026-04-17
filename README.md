# 🕴️ Sistema de Sucesión - Familia Mafia Italiana

![Versión](https://img.shields.io/badge/version-1.0.0-blue.svg)
![C++](https://img.shields.io/badge/C++-11%2B-green.svg)
![Licencia](https://img.shields.io/badge/licencia-Educativa-orange.svg)

## 📋 Tabla de Contenidos
- [Descripción del Proyecto](#-descripción-del-proyecto)
- [Características Principales](#-características-principales)
- [Requisitos del Sistema](#-requisitos-del-sistema)
- [Estructura del Proyecto](#-estructura-del-proyecto)
- [Instalación y Compilación](#-instalación-y-compilación)
- [Guía de Uso](#-guía-de-uso)
- [Formato de Datos](#-formato-de-datos)
- [Reglas de Sucesión](#-reglas-de-sucesión)
- [Ejemplos de Uso](#-ejemplos-de-uso)
- [Solución de Problemas](#-solución-de-problemas)
- [Autores y Créditos](#-autores-y-créditos)

---

## 📖 Descripción del Proyecto

Este proyecto implementa un sistema completo de gestión de sucesión para una familia de la mafia italiana. El programa utiliza estructuras de datos dinámicas (árboles binarios) para organizar jerárquicamente a los miembros de la familia y determinar automáticamente la línea de sucesión cuando ocurren eventos como fallecimientos, encarcelamientos o jubilaciones por edad.

### 🎯 Objetivos del Proyecto
- Cargar datos desde un archivo CSV con información de los miembros
- Construir un árbol binario balanceado para búsquedas eficientes
- Mostrar la jerarquía familiar completa por niveles
- Implementar reglas automáticas de sucesión
- Permitir modificaciones en tiempo real de los miembros
- Mantener persistencia de datos entre ejecuciones

### 🏗️ Estructuras de Datos Utilizadas
- **Árbol Binario de Búsqueda**: Para almacenar y buscar miembros por ID
- **Recorridos en Profundidad**: Para mostrar la jerarquía familiar
- **Plantillas (Templates)**: Para código reutilizable y genérico

---

## ✨ Características Principales

### 📂 Carga de Datos
- Lectura automática desde archivo CSV
- Creación automática de datos por defecto si no existe el archivo
- Validación de integridad de datos durante la carga
- Soporte para campos con valores booleanos (0/1)

### 🌳 Visualización Jerárquica
- Muestra la estructura familiar completa por niveles
- Indentación visual para identificar relaciones padre-hijo
- Información detallada de cada miembro:
  - ID único
  - Nombre completo
  - Edad
  - Género
  - Estado (Vivo/Muerto)
  - Situación legal (Libre/Preso)
  - Rol (Jefe/Subordinado)

### 👑 Sistema de Sucesión Automática
El programa implementa un complejo sistema de reglas para determinar automáticamente quién debe ser el próximo jefe cuando ocurre una vacante:

1. **Prioridad por cercanía sanguínea/lealtad**
2. **Verificación de estado** (vivo y libre)
3. **Búsqueda recursiva** en diferentes niveles jerárquicos
4. **Manejo de casos especiales** (todos muertos/presos)

### ✏️ Modificación de Miembros
- Cambio de nombre y apellido
- Actualización de edad
- Cambio de estado vital (vivo/muerto)
- Cambio de situación legal (libre/preso)
- Marcado como ex-jefe

### 💾 Persistencia de Datos
- Guardado automático del estado actual
- Creación de archivo CSV si no existe
- Recuperación de datos entre sesiones

---

## 🔧 Requisitos del Sistema

### Software Necesario
| Requisito | Versión Mínima | Recomendada |
|-----------|---------------|-------------|
| Sistema Operativo | Windows 7+ / Linux / macOS | Windows 10 / Ubuntu 20.04+ |
| Compilador C++ | g++ 4.8+ | g++ 9.0+ |
| Make | 3.81+ | 4.0+ |
| Estándar C++ | C++11 | C++11 o superior |

### Hardware Recomendado
- **Procesador**: 1 GHz o superior
- **Memoria RAM**: 512 MB mínimo
- **Espacio en disco**: 50 MB para el proyecto compilado

### Dependencias
- Bibliotecas estándar de C++ (iostream, fstream, sstream, string)
- No requiere bibliotecas externas adicionales

---

## 📁 Estructura del Proyecto

proyecto_mafia/
│
├── 📂 bin/ # Directorio de ejecutables y datos
│ ├── 🗄️ datos.csv # Archivo de datos de la familia
│ └── ⚙️ mafia.exe # Ejecutable del programa (Windows)
│ └── mafia # Ejecutable del programa (Linux/Mac)
│
├── 📂 obj/ # Archivos objeto generados
│ ├── miembro_mafia.o
│ ├── gestor_sucesion.o
│ └── main.o
│
├── 📂 src/ # Código fuente del proyecto
│ ├── 🎯 main.cpp # Punto de entrada del programa
│ │
│ ├── 👤 Miembro de la Familia
│ │ ├── miembro_mafia.h # Declaración de la clase MiembroMafia
│ │ └── miembro_mafia.cpp # Implementación de MiembroMafia
│ │
│ ├── 🌳 Árbol de la Familia
│ │ ├── arbol_familia.h # Declaración de estructuras de árbol
│ │ └── arbol_familia.cpp # Implementación del árbol binario
│ │
│ └── 👑 Gestor de Sucesión
│ ├── gestor_sucesion.h # Declaración del gestor principal
│ └── gestor_sucesion.cpp # Lógica de negocio y sucesión
│
├── 📄 Makefile # Script de compilación automática
└── 📖 README.md # Este archivo de documentación

### 📝 Descripción de Archivos

| Archivo | Propósito | Líneas de Código |
|---------|-----------|------------------|
| `miembro_mafia.h/cpp` | Define los atributos y métodos de cada miembro | ~150 |
| `arbol_familia.h/cpp` | Implementa el árbol binario de búsqueda | ~200 |
| `gestor_sucesion.h/cpp` | Gestiona la lógica de sucesión y el menú | ~300 |
| `main.cpp` | Punto de entrada y orquestación | ~30 |

---

📘 Guía de Uso
🎮 Navegación por el Menú Principal
text
========================================
    FAMILIA MAFIA ITALIANA - GESTOR
========================================

1. Mostrar linea de sucesion
2. Mostrar arbol jerarquico
3. Asignar nuevo jefe
4. Modificar datos de un miembro
5. Verificar estado del jefe
0. Salir
----------------------------------------
Opcion: _
📌 Opción 1: Mostrar Línea de Sucesión
Muestra todos los miembros vivos de la familia en orden de ID, indicando quién es el jefe actual.

Ejemplo de salida:


=== LINEA DE SUCESION ACTUAL ===
ID: 1 | Nombre: Vito Corleone | Edad: 65 | Genero: H | Jefe: Sí | Vivo: Sí | En prision: No
ID: 2 | Nombre: Sonny Corleone | Edad: 40 | Genero: H | Jefe: No | Vivo: Sí | En prision: No
ID: 3 | Nombre: Fredo Corleone | Edad: 38 | Genero: H | Jefe: No | Vivo: Sí | En prision: No
ID: 4 | Nombre: Michael Corleone | Edad: 35 | Genero: H | Jefe: No | Vivo: Sí | En prision: No
ID: 5 | Nombre: Tom Hagen | Edad: 45 | Genero: H | Jefe: No | Vivo: Sí | En prision: No

--- JEFE ACTUAL ---
ID: 1 | Nombre: Vito Corleone | Edad: 65 | Genero: H | Jefe: Sí | Vivo: Sí | En prision: No


🌲 Opción 2: Mostrar Árbol Jerárquico
Visualiza la estructura familiar completa por niveles de jerarquía, basada en el campo id_boss.

Ejemplo de salida:

=== ARBOL JERARQUICO FAMILIAR ===
JEFE SUPREMO:
ID: 1 | Nombre: Vito Corleone | Edad: 65 | Jefe: Sí | Vivo: Sí | En prision: No
|
  +-- ID: 2 | Nombre: Sonny Corleone | Edad: 40 | Jefe: No | Vivo: Sí | En prision: No
  |   +-- ID: 3 | Nombre: Fredo Corleone | Edad: 38 | Jefe: No | Vivo: Sí | En prision: No
  |   |   +-- ID: 6 | Nombre: Peter Clemenza | Edad: 55 | Jefe: No | Vivo: Sí | En prision: No
  |   |   +-- ID: 7 | Nombre: Salvatore Tessio | Edad: 58 | Jefe: No | Vivo: Sí | En prision: No
  |   +-- ID: 8 | Nombre: Vincent Mancini | Edad: 25 | Jefe: No | Vivo: Sí | En prision: No
  +-- ID: 4 | Nombre: Michael Corleone | Edad: 35 | Jefe: No | Vivo: Sí | En prision: No


👑 Opción 3: Asignar Nuevo Jefe
Inicia el proceso automático de sucesión basado en las reglas establecidas. El sistema:

Verifica si el jefe actual debe ser reemplazado

Busca el sucesor más adecuado según la jerarquía

Actualiza los estados correspondientes


✏️ Opción 4: Modificar Datos de un Miembro
Permite editar la información de cualquier miembro por su ID.

Submenú de modificación:

=== MODIFICAR MIEMBRO ===
ID: 2 | Nombre: Sonny Corleone | Edad: 40 | Genero: H | Jefe: No | Vivo: Sí | En prision: No

1. Cambiar nombre
2. Cambiar apellido
3. Cambiar edad
5. Cambiar estado vivo/muerto
6. Cambiar estado prision
0. Guardar y salir
Opcion: _


🔍 Opción 5: Verificar Estado del Jefe
Analiza al jefe actual y determina si necesita ser reemplazado por:

Fallecimiento

Encarcelamiento

Edad superior a 70 años

📊 Formato de Datos
📄 Estructura del Archivo CSV
El archivo datos.csv debe tener el siguiente formato:

csv
id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss
1,Vito,Corleone,H,65,0,0,0,1,1
2,Sonny,Corleone,H,40,1,0,0,0,0
3,Fredo,Corleone,H,38,2,0,0,0,0
4,Michael,Corleone,H,35,1,0,0,0,0

⚠️ Reglas de Integridad de Datos
El id debe ser único para cada miembro

El id_boss debe referenciar un id existente (excepto 0 para el jefe supremo)

No puede haber más de un miembro con is_boss = 1 simultáneamente

Un miembro con is_dead = 1 o in_jail = 1 no puede ser jefe


👑 Reglas de Sucesión
El sistema implementa un sofisticado algoritmo de sucesión basado en las siguientes reglas jerárquicas:

📜 Regla 1: Sucesión Directa

Si el jefe actual MUERE y tiene sucesores asignados:
→ El NUEVO JEFE es el primer sucesor VIVO y FUERA DE PRISIÓN encontrado en su árbol directo.

📜 Regla 2: Sucesión entre Compañeros

Si el jefe actual MUERE y NO tiene sucesores:
→ El NUEVO JEFE es el primer sucesor VIVO y FUERA DE PRISIÓN encontrado en el árbol 
  de OTRO SUCESOR de su jefe (sus "hermanos" en la organización).

📜 Regla 3: Compañero como Sucesor

Si el compañero sucesor está VIVO, FUERA DE PRISIÓN y NO TIENE SUCESORES:
→ El COMPAÑERO MISMO se convierte en el NUEVO JEFE.

📜 Regla 4: Sucesión en Jerarquía Superior

Si el jefe MUERE, NO tiene sucesores, y su jefe anterior NO asignó otro sucesor:
→ El NUEVO JEFE es el primer sucesor VIVO y LIBRE encontrado en el árbol del 
  COMPAÑERO SUCESOR de su anterior jefe (sus "tíos").
→ Si ese compañero NO tiene sucesores pero está VIVO y LIBRE:
  → ESE COMPAÑERO se convierte en el NUEVO JEFE.

📜 Regla 5: Búsqueda Ampliada

Si NO se puede hallar un sucesor en el árbol del jefe de su jefe:
→ Buscar el jefe MÁS CERCANO con DOS SUCESORES fuera de prisión.
→ Elegir como NUEVO JEFE al primer sucesor VIVO y FUERA DE PRISIÓN de ese jefe.

📜 Regla 6: Recurso de Prisión

Si TODOS los jefes y sucesores LIBRES han MUERTO:
→ Aplicar las MISMAS REGLAS anteriores pero considerando a los sucesores y jefes 
  que estén en PRISIÓN pero Sigan VIVOS.
→ La búsqueda comienza desde el MÁS CERCANO al jefe actual.
→ El primero encontrado se convierte en el NUEVO JEFE (incluso estando en prisión).

📜 Regla 7: Jubilación o Prisión del Jefe

Si un jefe:
  - Supera los 70 AÑOS de edad
  - O va a PRISIÓN
→ El puesto se pasa AUTOMÁTICAMENTE al primer sucesor LIBRE y VIVO de su árbol directo.


👥 Autores y Créditos
Desarrolladores
Rafael Bula (32.035.817)
Nelson Inciarte (33.318.220)

Asignatura
Estructuras de Datos Dinámicas
