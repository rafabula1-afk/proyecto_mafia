#include "miembro_mafia.h"


MiembroMafia::MiembroMafia() 
    : id(0), gender('H'), age(0), idBoss(0), 
      isDead(false), inJail(false), wasBoss(false), isBoss(false) {}


MiembroMafia::MiembroMafia(int id, std::string name, std::string lastName, 
                           char gender, int age, int idBoss, bool isDead, 
                           bool inJail, bool wasBoss, bool isBoss)
    : id(id), name(name), lastName(lastName), gender(gender), age(age),
      idBoss(idBoss), isDead(isDead), inJail(inJail), 
      wasBoss(wasBoss), isBoss(isBoss) {}


int MiembroMafia::getId() const { 
    return id; 
}

std::string MiembroMafia::getName() const { 
    return name; 
}

std::string MiembroMafia::getLastName() const { 
    return lastName; 
}

std::string MiembroMafia::getFullName() const { 
    return name + " " + lastName; 
}

char MiembroMafia::getGender() const { 
    return gender; 
}

int MiembroMafia::getAge() const { 
    return age; 
}

int MiembroMafia::getIdBoss() const { 
    return idBoss; 
}

bool MiembroMafia::getIsDead() const { 
    return isDead; 
}

bool MiembroMafia::getInJail() const { 
    return inJail; 
}

bool MiembroMafia::getWasBoss() const { 
    return wasBoss; 
}

bool MiembroMafia::getIsBoss() const { 
    return isBoss; 
}


void MiembroMafia::setName(const std::string& name) { 
    this->name = name; 
}

void MiembroMafia::setLastName(const std::string& lastName) { 
    this->lastName = lastName; 
}

void MiembroMafia::setGender(char gender) { 
    this->gender = gender; 
}

void MiembroMafia::setAge(int age) { 
    this->age = age; 
}

void MiembroMafia::setIsDead(bool isDead) { 
    this->isDead = isDead; 
}

void MiembroMafia::setInJail(bool inJail) { 
    this->inJail = inJail; 
}

void MiembroMafia::setWasBoss(bool wasBoss) { 
    this->wasBoss = wasBoss; 
}

void MiembroMafia::setIsBoss(bool isBoss) { 
    this->isBoss = isBoss; 
}


bool MiembroMafia::estaVivoYLibre() const {
    return !isDead && !inJail;
}

bool MiembroMafia::estaVivo() const {
    return !isDead;
}

bool MiembroMafia::esSucesorValido() const {
    return estaVivoYLibre();
}


bool MiembroMafia::operator>(const MiembroMafia& otro) const {
    return this->id > otro.id;
}

bool MiembroMafia::operator<(const MiembroMafia& otro) const {
    return this->id < otro.id;
}

bool MiembroMafia::operator==(const MiembroMafia& otro) const {
    return this->id == otro.id;
}


void MiembroMafia::mostrarInfo() const {
    std::cout << "ID: " << id 
              << " | Nombre: " << getFullName() 
              << " | Edad: " << age 
              << " | Genero: " << gender
              << " | Jefe: " << (isBoss ? "Si­" : "No")
              << " | Vivo: " << (isDead ? "No" : "Si­")
              << " | En prision: " << (inJail ? "Si­" : "No") 
              << std::endl;
}
