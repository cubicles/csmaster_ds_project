#include <iostream>
using namespace std;

//clase padre: lista abstracta
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
    ListaArreglo<KVPar<Key, E>> *lista;
public:

     DiccionarioArreglo(int tamMax = 100){
    lista = new ListaArreglo<KVPar<Key, E>> (tamMax);
     }
  
    ~DiccionarioArreglo(){delete lista;}
   
    void limpiar(){
        lista->limpiar();
    }
    void insertar(Key K, E e){
      KVPar<Key, E> temp(K, e);
      lista->insertar(temp);
    }

 /* E remover(Key K){
      E temp = encontrar(K); 
      if(temp != NULL){
        this->lista->eliminar();
      }
      return temp;
    } */
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
      return NULL;
    }

    int longitud(){
        return this->lista->longitud();
    }







};

int main() {  
  /*
  //viene de apartado (A) para probar:
  //funciona la sobre carga de valor
  KVPar<int, int> f(10,20);
  KVPar<int, int> g(100,200);
  f = g; //se puede igualar y "f" toma los valores de "g" entonces existe una sobre carga de estos valores 
  cout<<"Clave: "<<f.key()<<endl;
  cout<<"Valor: "<<f.valor()<<endl; 
  */
/*
//viene de (B)
  KVPar<int, int> *f = new KVPar<int, int>(10,20);
  KVPar<int, int> *g = new KVPar<int, int>(100,200);
  f = g; //f puede tomar el valor de g
  cout<<"Clave: "<<f->key()<<endl;
  cout<<"Valor: "<<f->valor()<<endl;
  delete f; //no es necesira liberar g porque cuando lo igualo a f ya se libre su espacio de memoria
*/

  //*****Test del profesor:
    
  DiccionarioArreglo<int, string> *diccionario = new  DiccionarioArreglo<int, string>;
  diccionario->insertar(3912, "Luis");  
  diccionario->insertar(2918, "Maria");  
  diccionario->insertar(16881, "Juan");  
  cout<<"Reportando Contenido de Diccionario"<<endl;
  cout<<"Elemento: "<<diccionario->encontrar(3912)<<endl;//reporta: Maria
  cout<<"Elemento Eliminado: "<<diccionario->remover(2918)<<endl;//reporta: Maria
  cout<<"Reportando Todos los elementos del Diccionario"<<endl;
  
  /*
  Reporta:
  Juan
  Maria
  Luis
  */  
  while(diccionario->longitud()>0){
    cout<<diccionario->removerCualquiera()<<endl;
  }
  delete diccionario;
  
  //********Fin Test del profesor


  return 0;
}
