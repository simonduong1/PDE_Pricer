#pragma once
#include<string>

//On commence ce projet par définir des "raccourcis" pour le nom 
//de chaque option que nous allons utiliser.

const std::string C = "Call";
const std::string P = "Put";
const std::string AC = "Asset Or Nothing Call";
const std::string CBK = "Call Barrier K.O ";

//La première classe du projet se nomme "Payoff".
//Remarquons ici que l'on utilise un destructeur Virtuel.
//Celui-ci sera donc hérité par les classes dérivées
//Il ne sera alors pas nécessaire, de redéfinir de destructeurs dans ces classes


class Payoff {
public:
    Payoff() {};
    virtual ~Payoff() {};
    //Overload de l'opérateur (). Définition d'une méthode virtuelle pure
    virtual double operator()(const double& S) const = 0;
};

//Overload de l'opérateur () et définition d'une méthode virtuelle pure grace à const=0;.
//Const signifie ici que la méthode ne modifiera pas l'état interne des objets.
//Autrement dit, celle-si s'applique également aux objets de type const.


//Classe dérivée ayant pour objectif de calculer le payoff d'un call 

class PayoffCall : public Payoff {
//Encapsulation du Strike, celui est accessible
//seulement dans la classe PayoffCall
private:
    double K;
public:
    PayoffCall(const double& K_);

    virtual double operator()(const double& S) const override;
};

//Nous utilisons ici la fonction "override" afin d'indiquer clairement au compilateur
//qu'il s'agit d'une redéfinition de la méthode virtuelle pure associée à la classe de base.


//On applique ces mêmes idées aux  classes dérivées suivantes
class PayoffPut : public Payoff {
private:
    double K;
public:
    PayoffPut(const double& K_);

    virtual double operator()(const double& S) const override;
};

class PayoffAssetorNothingC : public Payoff {
private:
    double K;
public:
    PayoffAssetorNothingC(const double& K_);
    virtual double operator()(const double& S) const override;
};

class PayoffBarrierCallKO : public Payoff {
private:
    double K;
    double B; //Barrière du knock out 
public:
    PayoffBarrierCallKO(const double& K, const double& B);
    virtual double operator()(const double& S) const override;
    
};
