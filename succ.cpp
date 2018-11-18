/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  Automne 2018 / TP2                                   *
 *  Auteur(s):
 *  BALE02059505 - Éric Balthazard                       *
 *              - Philippe Chartrand                     *
 *                                                       */
#include "succ.h"



Succursale::Succursale() {

}

Succursale::Succursale(std::string nom, PointST p, int nbVoiture, int nbPlacesLibres)
: nom(nom), p(p), nbVoiture(nbVoiture), nbPlacesLibres(nbPlacesLibres) {

}

// ++++++++++++++++++++++++++++++++++++++++ VERIFIER ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool Succursale::verifier(Date debut, Date fin) {
    assert(debut < fin);

    if(reservations.vide()) {
        reservations[Date()][0] = nbVoiture;
        reservations[Date()][1] = nbVoiture + nbPlacesLibres;
    }

    for(ArbreMap<Date, int[2]>::Iterateur iter=reservations.rechercherEgalOuPrecedent(debut);iter;++iter) {

        if(fin <= iter.cle())
            break;

        if(iter.valeur()[0] < 1)
            return false;

    }
    return true; //changer pour false éventuellement
}

bool Succursale::verifierDeuxSuccursales(Date debut, Date fin, bool origine) {
    assert(debut < fin);

    if(reservations.vide()) {
        reservations[Date()][0] = nbVoiture;
        reservations[Date()][1] = nbVoiture + nbPlacesLibres;
    }

    if(origine == true) {

        for(ArbreMap<Date, int[2]>::Iterateur iter=reservations.rechercherEgalOuPrecedent(debut);iter;++iter) {

            if(iter.valeur()[0] > iter.valeur()[1] || iter.valeur()[0] <= 0) {
                return false;
            }

        }

    } else {

        for(ArbreMap<Date, int[2]>::Iterateur iter=reservations.rechercherEgalOuPrecedent(fin);iter;++iter) {

            if(iter.valeur()[0]+1 > iter.valeur()[1]) {
                return false;
            }

        }

    }

    return true; //changer pour false éventuellement
}

std::string Succursale::getNom() const{
    return nom;
}

double Succursale::distanceSucc(const PointST& a) const{
    return distance(p,a);
}

// Peut-être faire une fonction public de type générique qui renvoie

// ++++++++++++++++++++++++++++++++++++++++ ENREGISTRER ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Succursale::enregistrer(std::string origine, Date debut, std::string destination, Date fin) {
    ArbreMap<Date, int[2]>::Iterateur iterDebut = reservations.rechercherEgalOuPrecedent(debut);

    if(origine == nom) {
        reservations[debut][0] = iterDebut.valeur()[0];
        reservations[debut][1] = iterDebut.valeur()[1];
    }

    ArbreMap<Date, int[2]>::Iterateur iterFin = reservations.rechercherEgalOuPrecedent(fin);

    if(destination == nom) {
        reservations[fin][0] = iterFin.valeur()[0];
        reservations[fin][1] = iterFin.valeur()[1];
    }

    if(origine == nom) {

        for(ArbreMap<Date, int[2]>::Iterateur iter=reservations.rechercherEgalOuPrecedent(debut);iter;++iter) {

            if(fin <= iter.cle() && destination == nom) {
                return;
            }

            iter.valeur()[0]--;
        }
    }


    if(destination == nom && origine != nom) {

        for(ArbreMap<Date, int[2]>::Iterateur iter=reservations.rechercherEgalOuPrecedent(fin);iter;++iter) {
            iter.valeur()[0]++;
        }

    }
}
