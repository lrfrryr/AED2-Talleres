template <typename T>
string_map<T>::string_map(){

    _raiz = nullptr;
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar;
}


template <typename T>
void string_map<T>::del(Nodo* root){

    if (root != nullptr) {

        for (int siguiente = 0; siguiente < CHARS_TRIE; siguiente++) {

            del(root->siguientes[siguiente]);
        }
        if (root->definicion != nullptr) {

            delete root->definicion;
        }
        delete root;
        _size--;
    }
}

template <typename T>
typename string_map<T>::Nodo* string_map<T>::copy(Nodo* root, int* size){

    if (root != nullptr) {

        Nodo* nuevo_nodo;
        if (root->definicion != nullptr) {

            nuevo_nodo = new Nodo(new T(*root->definicion));
            *size++;

        } else {

            nuevo_nodo = new Nodo();
        }

        for (int siguiente = 0; siguiente < CHARS_TRIE; siguiente++) {

            if (root->siguientes[siguiente] != nullptr) {

                nuevo_nodo->siguientes[siguiente] = copy(root->siguientes[siguiente], size);
            }
        }
        return nuevo_nodo;

    } else {

        return nullptr;
    }
}


template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    del(_raiz);
    int* s = new int;
    *s = 0;
    _raiz = copy(d._raiz, s);
    _size = *s;
    delete s;
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    del(_raiz);
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    int res = 0;
    int index = 0;
    Nodo* actual = _raiz;
    while ( actual != nullptr && index < clave.size() ) {
        actual = actual->siguientes[ int(clave[index]) ];
        index++;
    }
    if (actual != nullptr && actual->definicion != nullptr) {
        res = 1;
    }
    return res;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    assert(count(clave) == 1);
    int index = 0;
    Nodo** actual = &_raiz;
    while ( index < clave.size() ) {
        actual = &((*actual)->siguientes[ int(clave[index]) ]);
        index++;
    }
    return *(*actual)->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    assert(count(clave) == 1);
    int index = 0;
    Nodo** actual = &_raiz;
    while ( index < clave.size() ) {
        actual = &((*actual)->siguientes[ int(clave[index]) ]);
        index++;
    }
    return *(*actual)->definicion;
}


template <typename T>
int string_map<T>::cantHijos(string_map<T>::Nodo* n){
    int res = 0;
    for (int index = 0; index < CHARS_TRIE; index++) {
        if (n->siguientes[index] != nullptr) {
            res++;
        }
    }
    return res;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    assert(count(clave) == 1);
    Nodo* nodoActual = _raiz;
    Nodo* ultimoNodo = _raiz;
    int index = 0;
    int indexUltimo = 0;
    while ( index < clave.size() ) {
        if ((cantHijos(nodoActual)>1 || nodoActual->definicion != nullptr) && indexUltimo < clave.size() - 1 ) {
            ultimoNodo = nodoActual;
            indexUltimo = index;
        }
        nodoActual = nodoActual->siguientes[ int(clave[index]) ];
        index++;
    }
    Nodo* Borrar = ultimoNodo->siguientes[ int(clave[indexUltimo]) ];
    if (cantHijos(nodoActual) == 0) {
        ultimoNodo->siguientes[ int(clave[indexUltimo]) ] = nullptr;
        ultimoNodo = Borrar;
        del(ultimoNodo);
    } else {
        delete(nodoActual->definicion);
        nodoActual->definicion = nullptr;
    }
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& p){

    string clave = p.first;
    //T*     def   = new T;
    //*def = p.second;

    int index = 0;
    Nodo** actual = &_raiz;
    while ( index < clave.size() ) {
        if (*actual == nullptr) {

            *actual = new Nodo;
        }
        actual = &((*actual)->siguientes[ int(clave[index]) ]);
        index++;
    }
    if (*actual == nullptr) {

        *actual = new Nodo;
    }
    //(*actual)->definicion = def;
    if((*actual)->definicion != nullptr){

        delete (*actual)->definicion;
    }

    (*actual)->definicion = new T(p.second);
    _size++;
}

