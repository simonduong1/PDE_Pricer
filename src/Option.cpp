#include "../include/Option.h"
#include<string>
#include<stdexcept>

Option::Option(Payoff* payoff_, double K_, double B_,double T_, double r_, double sigma_, const std::string Option_type ) : payoff(payoff_), K(K_),B(B_), T(T_), r(r_), v(sigma_), O(Option_type) {};

//Méthodes associées à chaque getters 

Option::~Option() {};

Payoff* Option::getpayoff() const {
	return payoff;
};

double Option::getStrike() const {
	return K;
}

double Option::getMaturity() const {
	return T;
}

double Option::getFreeRate() const {
	return r;
}

double Option::getvol() const {
	return v;
}

double Option::getBarrier() const {
	return B;
}

std::string Option::getOptionType() const {
	return O;
}

