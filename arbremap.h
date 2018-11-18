#if !defined(__ARBREMAP_H__)
#define __ARBREMAP_H__

#include "arbreavl.h"

template <class K, class V>
class ArbreMap {
    private:
        class Entree {
            public:
                Entree(const K& c):cle(c),valeur(){ }
                K cle;
                V valeur;
                bool operator < (const Entree& e) const { return cle < e.cle; }
        };

    ArbreAVL<Entree> entrees;

    public:
        class Iterateur {
            public:
                Iterateur(const ArbreMap& a) : iter(a.entrees.debut()) {}
                Iterateur(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {}
                operator bool() const {return iter.operator bool();};
                bool operator!() const;

                Iterateur& operator++() {++iter; return *this;}
                Iterateur operator++(int);

                const K& cle() const {return (*iter).cle;}
                V& valeur() {return (V&) (*iter).valeur;}

                private:
                    typename ArbreAVL<Entree>::Iterateur iter;
        };
        class IterateurConst{
            typename ArbreAVL<Entree>::Iterateur iter;
            public:
                const V& valeur() const {return (*iter).valeur;}
        };

        bool contient(const K&) const;

        void enlever(const K&);
        void vider();
        bool vide() const;

        Iterateur debut() { return Iterateur(*this); }
        Iterateur fin() { return Iterateur(entrees.fin());}
        Iterateur rechercher(const K& cle) { return Iterateur(entrees.rechercher(cle));}
        Iterateur rechercherEgalOuSuivant(const K& cle) {return Iterateur(entrees.rechercherEgalOuSuivant(cle));}
        Iterateur rechercherEgalOuPrecedent(const K& cle) {return Iterateur(entrees.rechercherEgalOuPrecedent(cle));}

        const V& operator[] (const K&) const;
        V& operator[] (const K&);
};



template <class K, class V>
void ArbreMap<K,V>::vider(){
    entrees.vider();
}

template <class K, class V>
bool ArbreMap<K,V>::vide() const{
    return entrees.vide();
}

template <class K, class V>
void ArbreMap<K,V>::enlever(const K& c)
{
    // À compléter
}

template <class K, class V>
bool ArbreMap<K,V>::contient(const K& cle) const
{
    return entrees.contient(cle);
    return entrees.contient(Entree(cle));
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& c)  const {
    typename ArbreAVL<Entree>::Iterateur iter=entrees.rechercher(c);
    return entrees[iter].valeur;
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const K& c) {
    typename ArbreAVL<Entree>::Iterateur iter=entrees.rechercher(Entree(c));
    if(!iter){
        entrees.inserer(Entree(c));
        iter = entrees.rechercher(c);
    }
    return entrees[iter].valeur;
}


#endif

