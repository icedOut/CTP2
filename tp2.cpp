/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  Automne 2018 / TP2                                   *
 *  http://ericbeaudry.uqam.ca/INF3105/tp2/              */
 
#include <fstream>
#include <iostream>
#include <string>
#include "succ.h"
#include "pointst.h"
using namespace std;

int tp2(istream& entree){
    // À compléter...
    
    int id=1;
    while(entree){
        std::string commande;
        entree >> commande >> ws;
        if(!entree) break;
        cout << id << " : ";
       
        if(commande=="creer"){
            string nom;
            PointST p;            
            int nbVoitures=0, nbPlacesLibres=0;
            entree >> nom >> p >> nbVoitures >> nbPlacesLibres;
            // À compléter...
            
            
            cout << "Creee"  << endl;
        }else if(commande=="reserver"){
            string origine, destination;
            Date debut, fin;
            entree >> origine >> debut >> destination >> fin;
            bool ok = false;
            // À compléter...
            
            
            cout << (ok ? "Acceptee" : "NonDispo") << endl;
        }else if(commande=="suggerer"){
            PointST origine, destination;
            Date debut, fin;
            entree >> origine >> debut >> destination >> fin;
            bool ok = false;
            // À compléter...
            
            // cout << "A B" << endl;
            cout << "Impossible" << endl;
        }else{
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

