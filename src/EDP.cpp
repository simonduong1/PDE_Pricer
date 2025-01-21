#include "../include/EDP.h"
#include <cmath>

BSEDP::~BSEDP() {};
BSEDP::BSEDP(Option* option_) {
    option = option_;
};


//Methode correspondant au coefficient de diffusion de l'équation Black Scholes (BS)
//Celui-ci est donné par 1/2 σ² S^2:
//Ce terme reflète l’incertitude sur le prix futur de l’actif sous-jacent.
double BSEDP::diffusion_coef(double t,double x) const {
    return 0.5 * pow(option->getvol(), 2) * pow(x, 2);
}

//Coefficient de convection rS
//Ce terme représente l’évolution du prix d’un produit dérivé en fonction du mouvement attendu du sous-jacent S, induit 
//par le taux sans risque r.
double BSEDP::convection(double t,double x) const {
    return option->getFreeRate() * x;
}

//Coefficient source de 0
//Signifie qu'il n'y a pas de création ou de destruction externe de valeur : système fermé et neutre au risque.
double BSEDP::source(double t, double x) const {
    return 0.0;
}

//Coefficient de correction: -r
//Il agit comme une "correction temporelle", prenant en compte 
//la perte de valeur liée à l’écoulement du temps et au coût d'opportunité.
double BSEDP::correc_coef(double t, double x) const {
    return -option->getFreeRate();
}

// Condition en S --> 0 pour un call et pour un put
//Pour l'Asset or nothing Call 1{S>=K} --> 0 lorsque S-->0 car K>0
double BSEDP::borne_inf(double t,double x) const {
    if (option->getOptionType() == C) {
        return 0.0;

    }
    else if (option->getOptionType() == P) {
        return option->getStrike() * exp(-(option->getFreeRate()) * (option->getMaturity() - t));
    }
    else if (option->getOptionType() == AC || option->getOptionType() == CBK) {
        return 0.0;
    }
    return 1;
}

// Condition en S --> S_max pour un Call et pour un put
//Pour l'option Asset or nothing Call on prendra S_max > K donc 1{S>=K} --> 1 lorsque S-->S_max
double BSEDP::borne_sup(double t, double x) const {
    if (option->getOptionType() == C) {

        return x - option->getStrike() * exp(-option->getFreeRate() * (option->getMaturity() - t));
    }

    else if (option->getOptionType() == P) { //Par relation de parité Call-Put
        return 0.0; 
    }
    else if (option-> getOptionType() == AC) {
        return x; 
    }
    else if (option->getOptionType() == CBK) {
        if (x > option->getBarrier()) { //Si la barrière est plus grande que S_max, la condition au bord se réecrit 
                                        //S-->B.
            return option->getBarrier() - option->getStrike() * exp(-option->getFreeRate()*(option->getMaturity() - t));
        }
        else {
            return x- option->getStrike() * exp(-option->getFreeRate() * (option->getMaturity() - t));
        }
    }
    return 1;
}

std::string BSEDP::getOptionType()
{
    return option->getOptionType();
}

//On utilise le polymorphisme que avons induit dans la classe Payoff, utilisant
//la surcharge de l'opérateur ().
//Nous n'avons donc pas besoin de savoir s'il s'agit de PayoffCall ou PayoffPut pour
//Appeler cet opérateur.
//(*option->getPayoff())(x)  appelle la méthode virtuelle de l'objet pointé par getPayoff()
double BSEDP::initial_condition(double x) const {
    return option->getpayoff()->operator()(x);
}

