#if !defined(__SUCC_H__)
#define __SUCC_H__
#include "date.h"
#include "arbreavl.h"
#include "arbremap.h"
#include "pointst.h"
#include <iostream>


class PointST;

class Succursale{
  public:

    Succursale();
    Succursale(std::string nom, PointST p, int nbVoiture, int nbPlacesLibres);

    /********GETTERS********/
    bool verifier(Date debut, Date fin);
    bool verifierDeuxSuccursales(Date debut, Date fin, bool origine);
    void enregistrer(std::string origine, Date debut, std::string destination, Date fin);
    std::string getNom() const;
    double distanceSucc(const PointST&) const;
    void afficherSuccursaleDetails() const;
    void afficherReservations();


  private:
    std::string nom;
    PointST p;
    int nbVoiture;
    int nbPlacesLibres;
    ArbreMap<Date, int[2]> reservations;

};

#endif

