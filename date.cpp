/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  Automne 2018 / TP2                                   *
 *  http://ericbeaudry.uqam.ca/INF3105/tp2/              */
#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>

Date::Date() {
    jours = 0;
    heures = 0;
    minutes = 0;
}

int Date::changerDateEnNb(int jours, int heures, int minutes) const {
    return jours*(60*24) + heures*(60) + minutes;
}

bool Date::operator <(const Date& d) const {
    return changerDateEnNb(jours, heures, minutes) < changerDateEnNb(d.jours, d.heures, d.minutes);
}

bool Date::operator <=(const Date& d) const{
    return changerDateEnNb(jours, heures, minutes) <= changerDateEnNb(d.jours, d.heures, d.minutes);;
}

std::ostream& operator << (std::ostream& os, const Date& d){

    char chaine[40];
    sprintf(chaine, "%dj_%02dh%02dm", d.jours, d.heures, d.minutes);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    char j, m, h, underscore;
    int jours, heures, minutes;
    is >> jours >> j >> underscore >> heures >> h >> minutes >> m;
    assert(j=='j');
    assert(underscore=='_');
    assert(h=='h' && m=='m');

    d.jours = jours;
    d.heures = heures;
    d.minutes = minutes;


    return is;
}

