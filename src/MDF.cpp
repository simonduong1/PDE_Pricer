#include "../include/MDF.h"
#include<iostream>

//Trouver la volatilité 
void MDFE::long_pas() {
    dt = T / (N-1);   //dt correspond à longueurs des pas dans la grille temporelle (pour N points distincts)
    dx = S_max / (I-1);  //idem pour dx, pour la grille spatiale.
    Sval.resize(I + 1);
    for (unsigned long i = 0; i < I + 1; i++) {
        Sval[i] = i * dx;  //Puisque S_min=0 (par hypothèse) pour tout i S_i=S_min+i*dx
    }                      //En supposant S_min=0 on ne perd pas vraiment en généralité au vu des options pricées
}

void MDFE::init_cond() {
    //pass_t = T;  //on part de T (raisonnement à rebours)
    //pres_t = T - dt; 
    pass_t = 0;
    pres_t = 0;
    Old.resize(I+1);  //On redimensionne les vecteurs des valeurs de l'option au nombre de points de la grille spatiale
    New.resize(I+1);
    delta.resize(I + 1);
    theta.resize(I + 1);
    gamma.resize(I + 1);
    //On applique la relation terminale à chaque points de la grille spatiale
    for (unsigned long i = 0; i < I + 1; i++) {
        Old[i] = edp->initial_condition(Sval[i]);
    }
}

//Fonction pour calculer les condtions "au bord" i.e les conditions limites.
void MDFE::boundaries() {
    New[0] = edp->borne_inf(pres_t, Sval[0]);
    New[I] = edp->borne_sup(pres_t, Sval[I]);
}

void MDFE::dom() {
    //On implémente la relation par récurrence entre Old et New
   
    for (unsigned long i = 1; i < I; i++) {
        //calcul dynamique des poids associés à Old[i-1],Old[i] et Old[i+1] respectivement.
         a = edp->diffusion_coef(pass_t, i) * dt - edp->convection(pres_t, i) * dt / 2;
         b = 1 - 2 * edp->diffusion_coef(pass_t, i) * dt + edp->correc_coef(pass_t, Sval[i]) * dt;
         c = edp->diffusion_coef(pass_t, i) * dt + edp->convection(pass_t, i) * dt / 2;
         delta[i] = (Old[i + 1] - Old[i - 1]) / 2 * dx;
         gamma[i] = (Old[i + 1] - 2 * Old[i] + Old[i - 1]) / dx * dx;
        New[i] = ((a * Old[i - 1]) + (b * Old[i]) + (c * Old[i + 1]));
        theta[i] = (New[i] - Old[i]) / dt;
    }
    // Gestion des bords
    // Delta pour le bord gauche et bord droit 
    delta[0] =(Old[1] - Old[0]) / dx;  // Différence avant
    delta[I] = (Old[I] - Old[I - 1]) / dx;  // Différence arrière

    // Gamma pour les bords gauche et droit 
    gamma[0] = (Old[2] - 2 * Old[1] + Old[0]) / (dx * dx);  // Bord gauche
    gamma[I] = (Old[I] - 2 * Old[I - 1] + Old[I - 2]) / (dx * dx);  // Bord droit

    // Theta pour les bords gauche  et droit 
    theta[0] = (New[0] - Old[0]) / dt;  // Bord gauche
    theta[I] = (New[I] - Old[I]) / dt;  // Bord droit
}

//Ici, nous implémentons la fonction "mettant à jour" les différentes grilles et permettant de générer un fichier csv par option.
//En effet, nous avons passé en argument une chaîne de caractère qui permettra d'associer à chaque fichier un nom différent.
//Ainsi, lorsque l'on appellera deux fois cette fonctio de suite avec deux noms différents (deux strings différentes) deux fichiers
//différents seront générés, empechant alors l'écrasement du premier fichier.
//D'autre part, cette fonction, prenant en argument la valeur du spot price du sous jacent, va fournir une estimation
//du prix de l'option à la date 0, soit Pi(0,S_0). On utilse une interpolation linéaire, on repère les deux valeurs les plus
//proches de S_0, disons Sval[i] et Sval[i+1] et on applique une formule d'interpolation linéaire du type:
//   Pi(0,S_0)~New[i] +(S_O-Sval[i])(New[i+1]-New[i])/(Sval[i+1]-Sval[i]). (~ signifie "environ égale à").

void MDFE::prog_pas(const std::string f, double S_0) {
    std::ofstream file("output/" + f + ".csv");
    if (!file.is_open()) {
        std::cout << "Erreur : impossible d'ouvrir le fichier !" << std::endl;
        return;
    }
    file << "Position,Time,Value,delta, gamma, theta\n";

    double spot = 0.0; //Pour "stocker" le spot price
    bool interpolated = false;  //Afin de ne pas refaire plusieurs fois le calcul (Flag Method) 

    while (pres_t < T) {

        pres_t = pass_t + dt;
        boundaries();
        dom();

        //Remplissage de la grille dans le fichier csv
        for (unsigned long i = 0; i < I; i++) {
            file << Sval[i] << ";" << pass_t << ";" << New[i] << ";"<< delta[i] << ";" << gamma[i] << ";" << theta[i] << "\n";
        }

        //Interpolation seulement à la date t=0

        if (pass_t == 0 && !interpolated) {
            if (S_0< Sval[0] || S_0> Sval[I]) {
                std::cout << "Erreur: le spot price n'est pas dans la grille" << std::endl;
                file.close();
                return;
            }
            for (unsigned long i = 0; i < I + 1; i++) {
                if (Sval[i] <= S_0 && Sval[i + 1] > S_0) {
                    double slope = (New[i + 1] - New[i]) / (Sval[i + 1] - Sval[i]);
                    spot = New[i] + slope * (S_0 - Sval[i]);
                    interpolated = true;  // Empêche d'effectuer une autre interpolation, application du Flag.
                    break;
                }
            }
        }
                
        

        Old = New;
        pass_t = pres_t;

    }
    file.close();

    //Il nous reste plus qu'à afficher le prix interpolé associé au spot S_0
    if (interpolated) {
        std::cout << "Prix de l'option "<<f<<" au temps t = 0, associé à S_0 = " << S_0 << " : " << spot<< std::endl;
    }
    else {
        std::cout << "Erreur : l'interpolation n'a pas été réalisée pour S_0 = " << S_0 << std::endl;
    }
}



MDF::MDF(EDP* pde_, double T_, unsigned long N_, double x_max_, unsigned long I_) {
    if (!(T_ > 0 && N_ > 0 && x_max_ > 0 && I_ > 0)) {
        throw std::invalid_argument("Arguments must be strictly positive.");
    }
    edp = pde_;

    T = T_;
    N = N_;
    S_max = x_max_;
    I = I_;
    Sval.resize(I + 1);
}

MDFE::MDFE(EDP* pde_, double T_, unsigned long N_, double x_max_, unsigned long I_) :  MDF(pde_, T_, N_, x_max_, I_) {
    long_pas();
    init_cond();
}
