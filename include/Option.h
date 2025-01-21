#pragma once
#include "Payoff.h"
class Option{
//Encapsulation des paramètres d'options
private:
    Payoff* payoff; //Payoff associé, overload de l'opérateur ().
    double K;       //Prix d'ecercice de l'option (Strike).
    double T;       //Maturité.
    double r;       //Taux d'intérêt (ou taux sans risque).
    double v;       //Volatilité
    double B;       //Barrière
    std::string O;  //Type de l'option
public:
    ~Option();
    Option(Payoff*payoff ,double K_,double B_, double T_, double r_, double sigma_ ,const std::string Option_type);
    //getters pour accèder aux variables privées
    double getStrike() const;
    double getMaturity() const;
    double getFreeRate() const;
    double getBarrier() const;
    double getvol() const;
    Payoff* getpayoff() const;
    std::string getOptionType() const;
};

//Notons ici, que nous utilisons des Getters afin d'accèder aux données encapsulées. 
//Il s'agit de méthode permettant d'effectuer des opérations sur les données encapsulées
//tout en préservant leur protection et leur intégrité.
