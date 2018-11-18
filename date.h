/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  Automne 2018 / TP2                                   *
 *  http://ericbeaudry.uqam.ca/INF3105/tp2/              */
#if !defined(__DATE__H__)
#define __DATE__H__
#include <iostream>

// À compléter. Inspirez-vous de votre classe Heure du TP1.
class Date{
  public:
    Date();

    int getJours() const;
    bool operator <(const Date& date) const;
    bool operator <=(const Date& date) const;

  private:
    int dateNb;
    int jours;
    int heures;
    int minutes;

    int changerDateEnNb(int jours, int heures, int minutes) const;

  friend std::ostream& operator << (std::ostream&, const Date& date);
  friend std::istream& operator >> (std::istream&, Date& date);
};

#endif

