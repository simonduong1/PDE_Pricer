#pragma once

#include "EDP.h"
#include <vector>
#include <fstream>
#include <string>

//Ici, protected permet d'encapsuler des variables qui seront seulement disponibles dans
//la classe de base et les classes dérivées (différence avec private).

class MDF {
protected:
    EDP* edp;
    double T;  //Maturité/Longueur de la grille temporelle
    unsigned long N;  //Nombre de points sur la grille temporelle
    double dt;  //Longueur de pas temporel
    double S_max;  //Borne sup pour la grille spatiale (grille des prix du sous jacent)
    unsigned long I;  //Nombre de points sur la grille spatiale
    double dx;  //Longueur de pas sur la grille spatiale
    std::vector<double> Sval;  //Vecteur des valeurs de S (par abus de langage)

    //Coefficients associés à l'équation dynamique discrétisée.

    double a;
    double b;
    double c;

    double pres_t;  //temps présent
    double pass_t;  //temps passé
    std::vector<double> delta; //delta 
    std::vector<double> theta; //theta
    std::vector<double> gamma; //gamma
    std::vector<double> Old;  //vecteur des valeurs d'option aux dates n
    std::vector<double> New;  //vecteur des valeurs d'option aux dates n+1
    std::string f;  //paramètre que nous donnerons à la fonction prog_pas afin que celle-ci génère plusieurs fichiers distincts.
    MDF(EDP* pde_, double T_, unsigned long N_, double S_max_, unsigned long I_);

    virtual void long_pas() = 0;
    virtual void init_cond() = 0;
    virtual void boundaries() = 0;
    virtual void dom() = 0;

public:
    virtual void prog_pas(const std::string f, double S_0) = 0; // Ajout du paramètre filename et d'une valeur de spot price
                                                                //i.e le prix du sous jacent à la date t=0
};

class MDFE : public MDF {
protected:
    virtual void long_pas() override;
    virtual void init_cond() override;
    virtual void boundaries() override;
    virtual void dom() override;

public:
    MDFE(EDP*pde_, double T_, unsigned long N_, double x_max_, unsigned long I_);
    virtual void prog_pas(const std::string f,double S_0) override;
};
