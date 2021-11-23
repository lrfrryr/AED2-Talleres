#include "Lista.h"

Lista::Lista() {
    length = 0;
    head = nullptr;
    fin = nullptr;
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
   Nodo* temp = head;
    while (temp != nullptr) {
        temp = temp->siguiente;
        delete head;
        head = temp;
    }
    length = 0;
    head = nullptr;
    fin = nullptr;
    //delete temp;

}

Lista& Lista::operator=(const Lista& aCopiar) {

    if (this->length > 0) {
        while (this->length>0) {
            eliminar(length-1);
        }
        this->head = nullptr;
        this->fin = nullptr;
        this->length = 0;
    }
    for (int i = 0; i < aCopiar.longitud(); i++) {
        int elem = aCopiar.iesimo(i);
        agregarAtras(elem);
    }

    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevoNodo = new Nodo(); //guardo posición del nuevo nodo
    nuevoNodo->elem = elem; //le agrego el elemento que le corresponde
    nuevoNodo->siguiente = head; //pongo la cabeza como siguiente
    nuevoNodo->anterior = nullptr; //pongo el anterior como nulo

    if (head != nullptr) {
        head->anterior = nuevoNodo; //cambio el anterior a la cabeza para que sea el nuevo nodo
    } else {
        head = nuevoNodo;
        fin = nuevoNodo;
    }

    head = nuevoNodo; // hago que el nuevo nodo sea la cabeza

    length++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevoNodo = new Nodo();

    nuevoNodo->elem = elem;
    nuevoNodo->siguiente = nullptr;

    //si la lista está vacía:
    if (head == nullptr) {
        nuevoNodo->anterior = nullptr;
        head = nuevoNodo;
        fin = nuevoNodo;
    } else {
        fin->siguiente = nuevoNodo;
        nuevoNodo->anterior = fin;
        fin = nuevoNodo;
    }
    length++;
}

void Lista::eliminar(Nat i) {
    if (head == nullptr)
        return;

    Nodo* current = head;

    for (int j = 0; j < i; j++)
        current = current->siguiente;

    /* if (current == nullptr)
        return;
    */
    if (head == current) {
        head = current->siguiente;
    }

    if (current->siguiente != nullptr) {
        current->siguiente->anterior = current->anterior;
    } else {
        fin = current->anterior;
    }

    if (current->anterior != nullptr)
        current->anterior->siguiente = current->siguiente;

    length--;
    if (length == 1) {
        fin = head;
    }

    delete current;
}


int Lista::longitud() const {
    // Completar
    return length;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* tmp = head;

    for (int j = 0; j < length; j++) {
        if (j == i) {
            return tmp->elem;
        }
        tmp = tmp->siguiente;
    }
}


int& Lista::iesimo(Nat i) {
    Nodo* tmp = head;

    for (int j = 0; j < length; j++) {
        if (j == i) {
            return tmp->elem;
        }
        tmp = tmp->siguiente;
    }
}

void Lista::mostrar(ostream& o) {
    // Completar
}
