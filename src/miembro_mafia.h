#ifndef MIEMBRO_MAFIA_H
#define MIEMBRO_MAFIA_H

#include <string>
#include <iostream>

class MiembroMafia {
private:
    int id;
    std::string name;
    std::string lastName;
    char gender;
    int age;
    int idBoss;
    bool isDead;
    bool inJail;
    bool wasBoss;
    bool isBoss;

public:
    
    MiembroMafia();
    MiembroMafia(int id, std::string name, std::string lastName, char gender, 
                 int age, int idBoss, bool isDead, bool inJail, 
                 bool wasBoss, bool isBoss);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getLastName() const;
    std::string getFullName() const;
    char getGender() const;
    int getAge() const;
    int getIdBoss() const;
    bool getIsDead() const;
    bool getInJail() const;
    bool getWasBoss() const;
    bool getIsBoss() const;

  
    void setName(const std::string& name);
    void setLastName(const std::string& lastName);
    void setGender(char gender);
    void setAge(int age);
    void setIsDead(bool isDead);
    void setInJail(bool inJail);
    void setWasBoss(bool wasBoss);
    void setIsBoss(bool isBoss);

   
    bool estaVivoYLibre() const;
    bool estaVivo() const;
    bool esSucesorValido() const;


    bool operator>(const MiembroMafia& otro) const;
    bool operator<(const MiembroMafia& otro) const;
    bool operator==(const MiembroMafia& otro) const;

  
    void mostrarInfo() const;
};

#endif