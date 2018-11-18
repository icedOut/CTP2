/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  Automne 2018 / TP2                                   *
 *  http://ericbeaudry.uqam.ca/INF3105/tp2/              *                                  *
 *  Auteur(s):
 *  BALE02059505 - Éric Balthazard                       *
 *               - Philippe Chartrand                    *
 *                                                       */

#include <fstream>
#include <iostream>
#include <string>
#include "succ.h"
#include "pointst.h"
#include "arbremap.h"
#include "arbreavl.h"


using namespace std;

// ++++++++++++++++++++++++++++++++++++++++ RÉSERVATION ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool reservation(string origine, Date debut, string destination, Date fin, ArbreMap<string, Succursale>& succursales) {

    if(origine == destination) {

        if(succursales[origine].verifier(debut, fin)) {
            succursales[origine].enregistrer(origine, debut, destination, fin);
            return true;
        }

    } else {

        if(succursales[origine].verifierDeuxSuccursales(debut, fin, true) && succursales[destination].verifierDeuxSuccursales(debut, fin, false)) {
            succursales[origine].enregistrer(origine, debut, destination, fin);
            succursales[destination].enregistrer(origine, debut, destination, fin);
            return true;
        }

    }

    return false;
}

string suggerer(PointST origine, Date debut, PointST destination, Date fin, ArbreMap<string, Succursale>& succursales) {
    ArbreMap<double , Succursale> mapDistanceOrigine;
    ArbreMap<double , Succursale> mapDistanceDestination;
    // on itère sur l'arbreMap de succursales pour remplir un deuxième map contenant
    //les distance entre les succursales et les points d'origine/destination

    for(ArbreMap<string, Succursale>::Iterateur iter = succursales.debut();iter;++iter){
        Succursale s = iter.valeur();
        mapDistanceOrigine[iter.valeur().distanceSucc(origine)] = iter.valeur();
        mapDistanceDestination[iter.valeur().distanceSucc(destination)] = iter.valeur();
    }

    for(ArbreMap<double , Succursale>::Iterateur i = mapDistanceOrigine.debut();i;++i){

        if(i.valeur().verifierDeuxSuccursales(debut,fin,true)){

            for(ArbreMap<double, Succursale>::Iterateur iter = mapDistanceDestination.debut();iter;++iter){

                if(iter.valeur().verifierDeuxSuccursales(debut,fin,false)){
                    return i.valeur().getNom() + " " + iter.valeur().getNom();
                }

            }

        }

    }
    return "Impossible";
}

int tp2(istream& entree) {
    // À compléter...
    ArbreMap<string, Succursale> succursales;
    //ArbreMap<PointST, string> localisationSucc;
    int id=1;
    while(entree){
        std::string commande;
        entree >> commande >> ws;

        if(!entree) break;
        cout << id << " : ";

        if(commande=="creer") {
            string nom;
            PointST p;
            int nbVoitures=0, nbPlacesLibres=0;
            entree >> nom >> p >> nbVoitures >> nbPlacesLibres;
            succursales[nom] = Succursale(nom, p, nbVoitures, nbPlacesLibres);
            cout << ((true) ? "Creee" : "Non creee") << endl;
        } else if(commande=="reserver"){
            string origine, destination;
            Date debut, fin;
            entree >> origine >> debut >> destination >> fin;
            cout << (reservation(origine, debut, destination, fin, succursales) ? "Acceptee" : "NonDispo") << endl;
        } else if(commande=="suggerer") {
            PointST origine, destination;
            Date debut, fin;
            entree >> origine >> debut >> destination >> fin;
            cout << suggerer(origine, debut, destination, fin , succursales) << endl;

        } else {
            cout << "Commande '" << commande << "' invalide!" << endl;
            return 2;
        }
        char pointvigule=0;
        entree >> pointvigule >> ws;
        if(pointvigule!=';'){
            cout << "Fichier d'entrée invalide!" << endl;
            return 3;
        }
        id++;
    }

    return 0;
}

// syntaxe d'appel : ./tp2 [nomfichier.txt]
//   ==> argc=2 argv[0]="./tp2", argv[1]="nomfichier.txt"
int main(int argc, const char** argv){
    // Gestion de l'entrée :
    //  - lecture depuis un fichier si un argument est spécifié;
    //  - sinon, lecture depuis std::cin.
    if(argc>1){
         std::ifstream entree_fichier(argv[1]);
         if(entree_fichier.fail()){
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
             return 1;
         }
         return tp2(entree_fichier);
    }else
         return tp2(std::cin);

    return 0;
}

