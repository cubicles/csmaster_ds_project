#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <fstream>
#include <stdio.h>
// Añade paquete de idiomas
#include <locale.h>
#include <windows.h>
//#include <bits/stdc++.h>
using namespace std;

//===========================================================================
//=========================== LISTA =========================================
//===========================================================================
template<typename E> class Lista{
private:

public:
    //constructor
    Lista(){} //podemos dejarla vacia

    ~Lista(){}

    virtual void limpiar() = 0;
    //inserta elemento en la ubicacion actual del puntero
    virtual void insertar(E elemento) = 0;
    //agregar elemento al final de la lista
    virtual void agregar(E elemento) = 0;
    //Mover "actual" al inicio de la lista
    virtual void moverAInicio() = 0;
    //Mover "actual" al final de la lista
    // primer espacio disponible
    virtual void moverAlFinal() = 0;
    //Mover "actual" a la posicion anterior (izquierda)
    virtual void anterior() = 0;
    //Mover "actual" a la posicion posterior (derecha)
    virtual void siguiente() = 0;
    //Retornar le numero de elementos de la lista
    virtual int longitud() = 0;
    //Retornar la posicion del elemento "actual"
    virtual int posicionActual() = 0;
    //"Actual" se mueve a la posicion "pos"
    virtual void moverAPosicion(int pos) = 0;
    //Retorna el valor que estaba en la posicion "actual"
    virtual E getValor() = 0;
    //Modificar el valor en la posicion "actual"
    virtual void setValor(E elemento) = 0;
    //Libera de la memoria y retorna el elemento "actual"
    virtual E eliminar() = 0;
};

//clase hija: ListaArreglo
//para que pueda heredar los metodos usamos
//los dos puntos
template<typename E> class ListaArreglo : public Lista<E>{
private:
    //atributos(variables) que tendra esta lista hija
    //estos atributos no los pongo en el padre porque
    //cada TDA que trabajaremos tendra diferentes
    //Arreglo de elementos
    E* arreglo;
    //Tamanho fijo
    int tamMax;
    //Tamanho de la lista
    int tamLista;
    //Indice "actual"
    int actual;

public:
    //constructor:
    ListaArreglo(int tamMax = 100){
        this->tamMax = tamMax;
        //deseamos que inicien con 0
        this->tamLista = this->actual = 0;
        this->arreglo =  new E[this->tamMax];;
    }
    //destructor
    ~ListaArreglo(){
        delete[] this->arreglo;
    }

    //Mover "actual" al inicio de la lista
    void moverAInicio() {
        this->actual = 0;
    }

    //Mover "actual" al final de la lista:
    // primer espacio disponible
    //si quisiera poder moverme al final de todo el
    //arreglo (incluye espaciones vacios)
    //seria tamMax
    void moverAlFinal() {
        this->actual = this->tamLista;
    }

    //Mover "actual" a la posicion posterior (derecha)
    //en la logica del for nos va a servir
    void siguiente() {
        //Sentinela
        if( this->actual < this->tamLista  )
            this->actual++;
    }

    //Mover "actual" a la posicion anterior (izquierda)
    void anterior() {
        //Sentinela
        if( this->actual > 0 )
            this->actual--;
    }

    //Agregar un elemento a la lista (al final)
    void agregar(E elemento) {
        this->arreglo[this->tamLista] = elemento;
        this->tamLista++;
        //lo mismo abreviado:
        //this->arreglo[this->tamLista++] = elemento;
    }

    //Retornar le numero de elementos de la lista
    int longitud() {
        return this->tamLista;
    }

    //Retornar la posicion del elemento "actual"
    int posicionActual() {
        return this->actual;
    }

    //"Actual" se mueve a la posicion "pos"
    void moverAPosicion(int pos) {
        //Sentinela
        if(pos>=0 && pos<this->tamLista)
            this->actual = pos;
    }

    //Retorna el valor que estaba en la posicion "actual"
    E getValor() {
        return this->arreglo[this->actual];
    }

    //Modificar el valor en la posicion "actual"
    void setValor(E elemento) {
        this->arreglo[this->actual] = elemento;
    }

    //Limpiar la lista: dejarla vacia la lista
    void limpiar() {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    //inserta elemento en la ubicacion actual del puntero   9 5 6 7 4 -
    void insertar (E elemento){
        for (int i = this->tamLista; i > this->actual; i--){
            this->arreglo[i] = this->arreglo[i-1];
        }
        this->arreglo[this->actual] = elemento;
        this->tamLista++;

    }
    //Eliminar y retornar el elemento "actual" eliminado
    E eliminar() {
        E eliminado = this->arreglo[this->actual];
        for (int i = this->actual; i < this->tamLista; ++i) {
            this->arreglo[i] = this->arreglo[i+1];
        }
        this->tamLista--;
        return eliminado;
    }


};
//================================================================================
//=========================== DICCIONARIO =========================================
//================================================================================



/***********/
//Diccionario padre
template<typename Key, typename E> class Diccionario{
private:
public:
    Diccionario(){} //Constructor
    ~Diccionario(){} //Destructor

    //Reinicializacion de un diccionario
    virtual void limpiar() = 0;

    //Insertar un registro
    //k: la clave para el reigstro
    //e: el registro
    virtual void insertar(Key K, E e) = 0;

    //Remover y retornar un registro
    //k: la clave del registro que debe ser removido
    //Retornar: un registro. Si hay mas de un registro con la misma clave,
    //  se debe remover uno de manera arbitraria
    //Retornar NULL si la clave "K" no se encuentra en el diccionario

    //virtual E remover(Key K) = 0;


    //Remover y retornar un registro arbitrario del diccionario
    //Retornar: el registro que ha sido removido o NULL si no existe
    virtual E removerCualquiera() = 0;

    //Return: un registro o NULL si no existe
    //Si hay multiples registros, se debe retornar uno de manera aleatoria
    //K: la clave del registro a encontrar
    virtual E encontrar(Key K) = 0;

    //Retornar el numero de registros dentro del diccionario
    virtual int longitud() = 0;
};

//Estructura atomica de un diccionario
// este es lo equivalente a un Nodo usado en listas enlazadas, pilas, etc. disenado para diccionarios
//tedra dos atributos: clave y valor
template<typename Key, typename E> class KVPar{
private:
    Key k;
    E e;
public:
    //Constructores
    KVPar(){}
    //primer constructor: me ingresa el valor de la clave y el registro
    KVPar(Key kval, E eval){this->k = kval; this->e = eval;}
    //segundo constructor: debe tener distinto tipo al constructor anterior o diferente cantidad de parametros
    //esto es llamado sobre carga de constructores para este caso  (tbn se podria hacer con sobre cargar de operador de asignacion)
    //si es que el usuario no ingresa una clave u valor sino otro objeto clavePar
    //lo que tendriamos que hacer es instanciar la clave de este objeto y tbn el valor de este objeto
    //seria una copia de otro objeto ClaveValor (probado en (B))
    KVPar(const KVPar& o){ this->k = o.k; this->e = o.e;} //agregue const porque replit me marc ERROR

    //Ahora con la forma de sobre carga de operador de asignacion
    //si pido la clase entonces debe devolverme k
    //probado en (A)
    Key key(){
        return this->k;
    }
    //si pido mofificar  la clave deberia tbn poder modificarlo
    void setKey(Key ink){
        this->k = ink;
    }
    //si pido el valor deberia retornar el valor
    E valor(){
        return this->e;
    }


};

//(recordando: DiccionarioArreglo hereda de Diccionario)
template<typename Key, typename E> class DiccionarioArreglo : public Diccionario<Key, E>{
private:
    //Usaremos nuestra lista arreglo (con su clavePar)
    ListaArreglo<KVPar<Key, E> > *lista;
public:

    DiccionarioArreglo(int tamMax = 100){
        lista = new ListaArreglo<KVPar<Key, E> > (tamMax);
    }

    ~DiccionarioArreglo(){delete lista;}

    void limpiar(){
        lista->limpiar();
    }
    void insertar(Key K, E e){
        KVPar<Key, E> temp(K, e);
        lista->insertar(temp);
    }
    E remover(Key K){
        for(this->lista->moverAInicio();
            this->lista->posicionActual() < this->lista->longitud();
            this->lista->siguiente()) {
            KVPar<Key, E> temp = this->lista->getValor();
            if(K==temp.key()){
                E valor=temp.valor();
                this->lista->eliminar();
                return valor;
            }
        }
        return NULL;
    }
    //elimina el ultimo registrado
    E removerCualquiera(){
        this->lista->moverAlFinal();
        this->lista->anterior();
        KVPar<Key, E> e = this->lista->eliminar();
        return e.valor();
    }

    E encontrar(Key K){
        for(this->lista->moverAInicio();
            this->lista->posicionActual() < this->lista->longitud();
            this->lista->siguiente()) {
            KVPar<Key, E> temp = this->lista->getValor();
            if(K==temp.key())
                return temp.valor();
        }
        return 0; // Inicialmente estaba como NULL

    }

    int longitud(){
        return this->lista->longitud();
    }

};

void tokenizacion(ListaArreglo<string> &listatokens, string texto){
    string palabra;
    stringstream check1(texto);
    while(getline(check1, palabra, ' '))
    {
        listatokens.agregar(palabra);
    }
};

void tokenizacion2(ListaArreglo<string> &listatokens) {
    // Bloque de lectura
    int n; // Numero de oraciones a leer
    cout << "Ingresar numero de inputs" << endl;
    cin >> n; // Numero de inputs
    cin.ignore();

    while(n > 0) {
        string sentence;        // Linea de texto
        string delim = " ";     // Delimitador
        getline(cin,sentence);  // Leer la linea de texto
        cout << "La linea ingresada es " << sentence << endl;

        size_t pos = 0;
        while((pos = sentence.find(delim)) != string::npos) {
            listatokens.agregar(sentence.substr(0,pos));
            sentence.erase(0, pos + delim.length());
        }
        if (!sentence.empty())
            listatokens.agregar(sentence.substr(0,pos));
        n--;
    }
}

void ImprimirListaString(ListaArreglo<string> &lista) {
    for (int i = 0; i < lista.longitud(); i++) {
        lista.moverAPosicion(i);
        cout << "Elemento " << i << " de la lista: " << lista.getValor() << endl;
    }
}

bool buscarEnLista(ListaArreglo<string> &listaPalabras, string elemento){
    bool checklista = 0;
    for (listaPalabras.moverAInicio();
         listaPalabras.posicionActual() < listaPalabras.longitud();
         listaPalabras.siguiente())
    {
        checklista = listaPalabras.getValor() == elemento;
        if(checklista){
            break;
        }
    }
    return checklista;
}

void listaPalabras(ListaArreglo<string> &listaPalabras, ListaArreglo<string> &listatokens){
    bool enlista, stopW;
    string palabra;
    ListaArreglo<string> listaStopwords;
    //clean stopwords
    string lineread;
    ifstream sw("stopwords.txt");
    while (sw.good()) {
        getline(sw, lineread);
        listaStopwords.agregar(lineread);
    }
    for (listatokens.moverAInicio();
         listatokens.posicionActual() < listatokens.longitud();
         listatokens.siguiente())
    {
        palabra=listatokens.getValor();
        enlista=buscarEnLista(listaPalabras, palabra);
        stopW=buscarEnLista(listaStopwords, palabra);
        if(!enlista && palabra !=" \n" && !stopW){
            listaPalabras.agregar(palabra);
        }
    }
};
void vectorizacion(ListaArreglo<int> &FrecuenciaPalabras, string LineaTexto, ListaArreglo<string> &listaPalabras){
    ListaArreglo<string> tokensTexto;
    string palabra;
    string token;
    int cont;
    bool aux;
    stringstream check1(LineaTexto);
    tokenizacion(tokensTexto, LineaTexto);
    for (listaPalabras.moverAInicio();
         listaPalabras.posicionActual() < listaPalabras.longitud();
         listaPalabras.siguiente())
    {
        cont=0;
        palabra=listaPalabras.getValor();
        for(tokensTexto.moverAInicio();
            tokensTexto.posicionActual()<tokensTexto.longitud();
            tokensTexto.siguiente()){
            token=tokensTexto.getValor();

            aux = palabra==token;
            if (aux)cont++;
        }
        FrecuenciaPalabras.agregar(cont);
    }
};
//============================================LECTORES==============================================

void lectorIDVectorizado(DiccionarioArreglo<int,ListaArreglo<int>> DicVectorizado, DiccionarioArreglo<int,string> DicLineaTexto){
    ListaArreglo<int> listaNumeroArreglo; // variable auxiliar
    string lineatexto; // input
    string texto; // variables auxiliares
    for (int i = 1; i <= DicVectorizado.longitud(); i++)
    {
        texto=DicLineaTexto.encontrar(i);
        cout<<"ID: "<<i<<" | Texto: "<< texto<<" | Vectorizado: ";
        listaNumeroArreglo = DicVectorizado.encontrar(i);
        for (listaNumeroArreglo.moverAInicio();
             listaNumeroArreglo.posicionActual() < listaNumeroArreglo.longitud();
             listaNumeroArreglo.siguiente())
        {
            cout<<listaNumeroArreglo.getValor();
        }
        cout<<endl;
    }
};

void lectorNum(ListaArreglo<int> listaLectura){
    for (listaLectura.moverAInicio();
         listaLectura.posicionActual() < listaLectura.longitud();
         listaLectura.siguiente())
    {
        cout<<listaLectura.getValor()<<endl;
    }
};
void lectorStr(ListaArreglo<string> listaLectura){
    for (listaLectura.moverAInicio();
         listaLectura.posicionActual() < listaLectura.longitud();
         listaLectura.siguiente())
    {
        cout<<listaLectura.getValor()<<endl;
    }
};
void lectorGeneral(ListaArreglo<string> palabra, ListaArreglo<int> frecuencia){
    frecuencia.moverAInicio();
    for (palabra.moverAInicio();
         palabra.posicionActual() < palabra.longitud();
         palabra.siguiente())
    {
        cout<<"----------------------"<<endl;
        cout<<"Palabra: "<<palabra.getValor()<<" | Frecuencia: "<<frecuencia.getValor()<<endl;
        cout<<"----------------------"<<endl;
        frecuencia.siguiente();
    }
};

int Distancia(ListaArreglo<int> textoVector, ListaArreglo<int> queryVector){
    int calc, sum = 0;
    for (textoVector.moverAInicio(), queryVector.moverAInicio();
         textoVector.posicionActual() < textoVector.longitud();
         textoVector.siguiente(), queryVector.siguiente())
    {
        calc = textoVector.getValor() - queryVector.getValor();
        calc = abs(calc);
        sum = sum + calc;
    }
    return sum;
}

//========================================================DICTIONARY ARRAY=======================
void DicIDVectorizado(DiccionarioArreglo<int,ListaArreglo<int>> &DicVectorizado, DiccionarioArreglo<int,string> &DicLineaTexto){
// Contenedores de los datos
    ListaArreglo<string> listatokens;// Hola, brasil, peru, peru
    ListaArreglo<string> listaPalab; //Hola, brasil, peru

    ListaArreglo<int> listaAux; // variable auxiliar
    string texto; // variables auxiliares

    /*_______________________________ Lectura de archivo_____________________________________ */
    ifstream myfile;
    ifstream ip("Libro1.csv");
    string lineatext;
    string valor;
    int i = 0;
    // Establecer el idioma a español
    setlocale(LC_ALL, "spanish"); // Cambiar locale - Suficiente para máquinas Linux
    //SetConsoleCP(1252); // Cambiar STDIN -  Para máquinas Windows
    //SetConsoleOutputCP(1252); // Cambiar STDOUT - Para máquinas Windows

    // seteado las N entradas de lineas de texto y el id
    int id=1;
    // Generar inputs: Leer lineas de texto -> ListaPalbras sin repetir
    ListaArreglo<string> listaPrueba;
    while (ip.good()) {
        getline(ip, lineatext, ',');
        getline(ip,valor, '\n');
        if(id > 1){
            listaPrueba.agregar(lineatext);
        }
        id++;
    }
    int id_=1;
    cout<<"_________________________________________"<<endl;
    cout<<"Corpus:__________________________________"<<endl;
    cout<<"ID_____:_______Lineas de texto___________"<<endl;
    for (listaPrueba.moverAInicio();
         listaPrueba.posicionActual() < listaPrueba.longitud()-1;
         listaPrueba.siguiente())
    {
        cout<<id_<<"     |"<<listaPrueba.getValor()<<endl;
        DicLineaTexto.insertar(id_,listaPrueba.getValor()); // Guardamos en diccionario id, linea de texto
        tokenizacion(listatokens,listaPrueba.getValor()); // Tokenizar cada uno en listaArreglo<string>  listatokens
        listaPalabras(listaPalab,listatokens); // Refinamiento: eliminacion de palabras repetidas y stopwords
        listatokens.limpiar();
        id_++;
    }

    /*_______________________________ Imprimir Bag-of-words_____________________________________ */
    cout<<"_________________________________________"<<endl;
    cout<<"Bag of words:____________________________"<<endl;
    for (listaPalab.moverAInicio();
         listaPalab.posicionActual() < listaPalab.longitud();
         listaPalab.siguiente())
    {
        cout<<listaPalab.posicionActual()+1<<" : "<<listaPalab.getValor()<<endl;
    }


    /*_______________________________ Consulta_____________________________________ */
    ListaArreglo<int> listaVectoresQuery;
    string textoQuery;
    int radio;
    cout<<"_________________________________________"<<endl;
    cout<<"Consulta:________________________________"<<endl;
    cout<<"Ingrese un query: ";
    getline(cin,textoQuery);
    cout<<endl<<"Ingrese el radio: ";
    cin>>radio;
    vectorizacion(listaVectoresQuery , textoQuery, listaPalab);//obtenemos vector del query
    cout<<"Imprimir vector del query: "<<endl;
    for(listaVectoresQuery.moverAInicio(); //Inicializacion
        listaVectoresQuery.posicionActual()<listaVectoresQuery.longitud(); //Condicion de parada
        listaVectoresQuery.siguiente()){ //Incremento
        cout<<listaVectoresQuery.getValor()<<" ";
    }
    cout<<endl;

    /*_______________________________ Calculo de distancia_____________________________________ */
    cout<<"______________________________________________________"<<endl;
    cout<<"Calculo de distancias:________________________________"<<endl;
    //Vectoriza las N lineas de Texto de un diccionario y añade su id desde 1 hasta N
    for (int i = 1; i <= DicLineaTexto.longitud(); i++)
    {
        ListaArreglo<int> listaVectores;
        texto=DicLineaTexto.encontrar(i);
        //cout<<texto<<endl;
        vectorizacion(listaVectores,texto,listaPalab);
        //Guardar en el diccionario
        DicVectorizado.insertar(i,listaVectores); //agregar ajuste de clave: vector, valor: texto

        listaAux = DicVectorizado.encontrar(i);


        /*lectorIDVectorizado*/
        ListaArreglo<int> listaNumeroArreglo; // variable auxiliar
        string lineatexto_2; // input
        string texto_2; // variables auxiliares


        texto_2=DicLineaTexto.encontrar(i);
        cout<<"ID: "<<i<<" | Texto: "<< texto_2<<" | Vectorizado: ";
        listaNumeroArreglo = listaAux;
        for (listaNumeroArreglo.moverAInicio();
             listaNumeroArreglo.posicionActual() < listaNumeroArreglo.longitud();
             listaNumeroArreglo.siguiente())
        {
            cout<<listaNumeroArreglo.getValor();
        }

        int distancia = Distancia(listaAux, listaVectoresQuery);
        cout<<" Distancia: "<<distancia;
        (distancia <= radio)? cout<<" Texto similar": cout<<" " ;
        cout<<endl;

        listaNumeroArreglo.limpiar();
        cout<<endl;
        DicVectorizado.limpiar();
        listaVectores.limpiar();
    }
};

int main() {
    DiccionarioArreglo<int,ListaArreglo<int>> DicVectorizado; // Dic<int,LisArray<int>>
    DiccionarioArreglo<int,string> DicLineaTexto; // Dic<int, strin>
    DicIDVectorizado(DicVectorizado,DicLineaTexto);
    return 0;
}