
#include "../include/Payoff.h"


//Utilisation de la liste d'initialisation.
//Est préférable à une assignation dans le corps du constructeur.
//En effet, lorsqu'une telle assignation est effectuée, l'objet est d'abord construit
//avec une valeur par défaut, puis, est réassigné, ce qui peut entraîné une perte de performance
//(Ici, il n'est pas forcément nécessaire de le faire, mais il s'agit de bonnes pratiques
//afin de garantir une certaine robustesse de code).

PayoffCall::PayoffCall(const double& K_) : K(K_) {}; //Utilisation de la liste d'initialisation

//Méthode associée à l'overload de () pour le calcul du Payoff.

double PayoffCall::operator()(const double& S) const {
    //Retourne S-K si S>=K 0 sinon. Correspond à (S-K)+
    return (S >=K) ? S - K : 0;
}

PayoffPut::PayoffPut(const double& K_): K(K_) {};


double PayoffPut::operator()(const double& S) const {
    //Retourne  si S<=K 0 sinon. Correspond à (K-S)+
    return (S <= K) ? K - S : 0;
}

PayoffAssetorNothingC::PayoffAssetorNothingC(const double& K_) :K(K_) {};

double PayoffAssetorNothingC::operator()(const double& S) const {
    //Comme son nom l'indique le payoff est simplement S*1{S>=K}. 
    return (S >= K) ? S : 0;
} 

PayoffBarrierCallKO::PayoffBarrierCallKO(const double& K_, const double& B_) : K(K_), B(B_) {};

double PayoffBarrierCallKO:: operator()(const double& S)const {
    return (S<B && S>K) ? S-K : 0; // l'option vaut S-K que si S est plus grand que K et plus petit que la barrière B
                                  // On parle d'option barrière Knock out 
}
