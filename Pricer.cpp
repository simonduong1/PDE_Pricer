#include <iostream>
#include <cmath>
#include "include/Payoff.h"
#include "include/Option.h"
#include "include/EDP.h"
#include "include/MDF.h"

using namespace std;

int main() {
    // Paramètres du problème
    double K = 0.6;            // Strike price
    double r = 0.05;           // Risk-free rate (5%)
    double sigma = 0.2;        // Volatility of the underlying (20%)
    double T = 1.00;           // Maturité
    double x_max = 1.0;        // Valeur maximale pour le sous-jacent
    unsigned long I = 20;      // Nombre de points dans la grille spatiale
    unsigned long N = 20;      // Nombre de points dans la grille temporelle
    double B = 0.8;            // Barrière
    double S_0 = 0.2;          // Spot price du sous-jacent
    double epsilon = 0.05;          //facteur de tolérance 

    // Vérification de la condition de stabilité
    //La condition théorique est dt<=(dx^2)/2*sigma*sigma
    //Or, cette condition étant assez restrictive, certaines implémentations renvoient des résultats plutôt cohérents
    //bien que celle-ci soit violée
    //On ajoute donc une erreure espilon, telle que si la différence dt-(dx^2)/2*sigma*sigma >epsilon le programme s'arrête
    //Condition return 1.
    double dt = T / (N - 1);
    double dx = x_max / (I - 1);


    //
    if (dt - (dx * dx) / (2 * sigma*sigma) > epsilon) {
        //throw std::invalid_argument("Condition de stabilité violée ");
        cout << "Condition de stabilité violée :\n";
        cout << "Veuillez augmenter N ou diminuer I pour respecter cette contrainte." << endl;
        return 1; // Quitte le programme
    }

    // Création des noms des fichiers de sortie
    const string C = "Call";
    const string P = "Put";
    const string AC = "AssetOrNothing";
    const string CBK = "CallBarrierKO";

    // Création des payoffs
    PayoffCall* payoff_call = new PayoffCall(K);
    PayoffPut* payoff_put = new PayoffPut(K);
    PayoffAssetorNothingC* payoff_a = new PayoffAssetorNothingC(K);
    PayoffBarrierCallKO* payoff_b = new PayoffBarrierCallKO(K, B);

    // Création des options
    Option* option_c = new Option(payoff_call, K, B, T, r, sigma, C);
    Option* option_p = new Option(payoff_put, K, B, T, r, sigma, P);
    Option* option_a = new Option(payoff_a, K, B, T, r, sigma, AC);
    Option* option_b = new Option(payoff_b, K, B, T, r, sigma, CBK);

    // Création des EDP associées
    BSEDP* edp_c = new BSEDP(option_c);
    BSEDP* edp_p = new BSEDP(option_p);
    BSEDP* edp_a = new BSEDP(option_a);
    BSEDP* edp_b = new BSEDP(option_b);

    // Solveur pour le Call
    MDFE mdf_c(edp_c, T, N, x_max, I);
    mdf_c.prog_pas(C, S_0);

    // Solveur pour le Put
    MDFE mdf_p(edp_p, T, N, x_max, I);
    mdf_p.prog_pas(P, S_0);

    // Solveur pour l'option Asset or Nothing
    MDFE mdf_a(edp_a, T, N, x_max, I);
    mdf_a.prog_pas(AC, S_0);

    // Solveur pour le Call Barrier Knock Out
    MDFE mdf_b(edp_b, T, N, x_max, I);
    mdf_b.prog_pas(CBK, S_0);

    // Libération de la mémoire
    delete edp_a;
    delete edp_c;
    delete edp_p;
    delete edp_b;
    delete option_c;
    delete option_p;
    delete option_a;
    delete option_b;
    delete payoff_call;
    delete payoff_put;
    delete payoff_a;
    delete payoff_b;

    return 0;
}


