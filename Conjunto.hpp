#include "Conjunto.h"

template<class T>
Conjunto<T>::Conjunto() {
    _raiz = nullptr;
    longitud = 0;

}

template<class T>
Conjunto<T>::Nodo::Nodo(const T& v){
    valor = v;
    der = nullptr;
    izq = nullptr;
    padre = nullptr;
}

template<class T>
Conjunto<T>::~Conjunto() {
    destruir(_raiz);
}


template<class T>
void Conjunto<T>::destruir(Nodo *elem) {
    if(elem != NULL){
        destruir(elem->izq);
        destruir(elem->der);
        delete elem;
    }
}



template<class T>

bool Conjunto<T>::pertenece(const T &clave) const {
    bool res = false;
    Nodo* elem = _raiz;
    while (elem != NULL && !res) {
        if (elem->valor == clave) {
            res = true;
        } else if (elem->valor < clave) {
            elem = elem->der;
        } else if (elem->valor > clave) {
            elem = elem->izq;
        }
    }
    return res;
}


template<class T>
void Conjunto<T>::insertar(const T &clave) {
    if (!pertenece(clave)) {
        insertarAux(_raiz, clave);
    }
}

template<class T>
void Conjunto<T>::insertarAux(Nodo *elem, const T &clave) {
    if (_raiz == nullptr) {
        Nodo *n = new Nodo(clave);
        _raiz = n;
        _raiz->izq = nullptr;
        _raiz->der = nullptr;
        _raiz->padre = nullptr;
        longitud++;
    } else {
        if (clave > elem->valor) {
            if (elem->der == nullptr) {
                Nodo *n = new Nodo(clave);
                elem->der = n;
                n->padre = elem;
                n->izq = nullptr;
                n->der = nullptr;
                longitud++;
            } else {
                insertarAux(elem->der, clave);
            }
        } else {
            if (elem->izq == nullptr) {
                Nodo *n = new Nodo(clave);
                elem->izq = n;
                n->padre = elem;
                n->izq = nullptr;
                n->der = nullptr;
                longitud++;
            } else {
                insertarAux(elem->izq, clave);
            }
        }
    }


}


template<class T>
void Conjunto<T>::remover(const T &clave) {
    if(pertenece(clave)) {
        if (_raiz->valor == clave && _raiz->der == nullptr && _raiz->izq == nullptr) {
            delete (_raiz);
            _raiz = nullptr;
            longitud--;
        } else {
            removerAux(_raiz, clave);

        }
    }
}

template<class T>
void Conjunto<T>::removerAux(Nodo *elem, const T &clave) {
    if (elem != NULL) {
        if (clave < elem->valor) {
            removerAux(elem->izq, clave);
        } else if (clave > elem->valor) {
            removerAux(elem->der, clave);
        } else if (elem->izq == nullptr && elem->der == nullptr) {
            if ((elem->padre)->izq == elem) {
                (elem->padre)->izq = nullptr;
            }
            if ((elem->padre)->der == elem) {
                (elem->padre)->der = nullptr;
            }
            delete (elem);
            elem = NULL;
            longitud--;

        } else if (elem->izq == nullptr) {
            Nodo *temp2 = elem->der;
            if (elem->padre != nullptr){
                if ((elem->padre)-> der == elem) {
                    (elem->padre)->der = temp2;
                    temp2->padre = elem->padre;
                } else {
                    (elem->padre)->izq = temp2;
                    temp2->padre = elem->padre;
                }
            } else if (_raiz == elem){
                _raiz = temp2;
                _raiz->padre = nullptr;
            }
            delete (elem);
            elem = NULL;
            longitud--;

        } else if (elem->der == nullptr) {
            Nodo *temp2 = elem->izq;
            if (elem->padre != nullptr){
                if ((elem->padre)-> der == elem) {
                    (elem->padre)->der = temp2;
                    temp2->padre = elem->padre;
                } else {
                    (elem->padre)->izq = temp2;
                    temp2->padre = elem->padre;
                }
            } else if (_raiz == elem){
                _raiz = temp2;
                _raiz->padre = nullptr;
            }
            delete (elem);
            elem = NULL;
            longitud--;

        } else {
            T min = minimoDe(elem->der);
            elem->valor = min;
            removerAux(elem->der, min);
        }
    }
}



template<class T>
T Conjunto<T>::minimoDe(Nodo *elem) const {
    T min = elem->valor;
    Nodo *temp = elem;
    while (temp->izq != nullptr) {
        temp = temp->izq;
        min = temp->valor;
    }
    T res = min;
    return res;
}


template<class T>
const T &Conjunto<T>::siguiente(const T &clave) {
    Nodo *raiz = _raiz;
    Nodo *padre = _raiz;
    while (true) {
        if (raiz->valor == clave) {
            if (raiz->der != nullptr) {
                Nodo *suc = raiz->der;
                while (suc->izq != nullptr) {
                    suc = suc->izq;
                }
                return suc->valor;
            } else {
                return padre->valor;
            }
        } else {
            padre = raiz;
            if (clave < raiz->valor) {
                raiz = raiz->izq;
            } else {
                raiz = raiz->der;
            }
        }
    }
}


template<class T>
const T &Conjunto<T>::minimo() const {
    T &min = _raiz->valor;
    Nodo *raiz = _raiz;
    while (raiz->izq != nullptr) {
        raiz = raiz->izq;
        min = raiz->valor;
    }
    const T &res = min;
    return res;

}

template<class T>
const T &Conjunto<T>::maximo() const {
    T &max = _raiz->valor;
    Nodo *raiz = _raiz;
    while (raiz->der != nullptr) {
        raiz = raiz->der;
        max = raiz->valor;
    }
    const T &res = max;
    return res;

}

template<class T>
unsigned int Conjunto<T>::cardinal() const {
    return contarNodos(_raiz);
}

template<class T>
unsigned int Conjunto<T>::contarNodos(Nodo *elem) const {
    unsigned int res;
    if (elem == NULL) {
        res = 0;
    }
    if (elem != NULL) {
        res = 1 + contarNodos(elem->izq) + contarNodos(elem->der);
    }
    return res;
}

template<class T>
void Conjunto<T>::mostrar(std::ostream &) const {
    assert(false);
}