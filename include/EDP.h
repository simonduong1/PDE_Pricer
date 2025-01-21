#pragma once

#include "Option.h"

class EDP {
public:
    //Methodes virtuelles pures associées aux coefficients/Conditions de
    //l'equation 1d de type convection diffusion

    virtual double diffusion_coef(double t, double x) const = 0;
    virtual double convection(double t, double x) const = 0;
    virtual double source(double t, double x) const = 0;
    virtual double correc_coef(double t, double x) const = 0;

    virtual double borne_inf(double t, double x) const = 0;
    virtual double borne_sup(double t, double x) const = 0;
    virtual double initial_condition(double x) const = 0;
};

//Ces Méthodes nous seront d'une grande utilité lorsqu'il faudra calculer les grecques,
//ainsi que les différentes valeurs des options à travers les grilles temporelles et spatiales

class BSEDP : public EDP {
public:
    ~BSEDP();
    Option* option;
    BSEDP(Option* option_);
    virtual double diffusion_coef(double t, double x) const override;
    virtual double convection(double t, double x) const override;
    virtual double source(double t, double x) const override;
    virtual double correc_coef(double t, double x) const override;

    virtual double borne_inf(double t, double x) const override;
    virtual double borne_sup(double t, double x) const override;
    virtual double initial_condition(double x) const override;
    std::string getOptionType();
};

//Nous ajoutons un pointeur de la classe Option, à BSEDP afin d'avoir accès aux méthodes de cette classe.
//De part l'utilisation des getters, il nous suffira de pointer sur les getters définis dans Option.h et Option.cpp
//Afin de récupérer les paramètres d'options encapsulés.;
