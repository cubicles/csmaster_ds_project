#include <iostream>
#include <iomanip>

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------LISTA PADRE ------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////
template<typename E> class lista{
    public:
    lista(){}
    ~lista(){}
    virtual void limpiar()=0;
    virtual void agregar(E e)=0;
    virtual void insertar(E e)=0;
    virtual void moverAInicio() = 0;
    virtual void moverAlFinal() = 0;
    virtual void anterior() = 0;
    virtual void siguiente() = 0;
    virtual int longitud() = 0;
    virtual int posicionActual() = 0;
    virtual void moverAPosicion(int id) = 0;
    virtual E getValor() = 0;
    virtual void setValor(E e) = 0;
    virtual E eliminar() = 0;
};
//////////////////////////////////////////////////////////////////////////////////
//-----------------------------------LISTA ARREGLO------------------------------//
//////////////////////////////////////////////////////////////////////////////////
template<typename E> class listaArreglo: public lista<E>{
    private:
        E* arreglo; 
        int tamMax;
        int tamList;
        int actual;
    public:
        listaArreglo(int tamMax =1000){
            this->tamMax = tamMax;
            this->tamList = this->actual = 0;
            this->arreglo = new E[this->tamMax];
        }
        ~listaArreglo(){
            delete[] this->arreglo;
        }
        void limpiar() {
            delete[] this->arreglo;
            this->tamList = this->actual = 0;
            this->arreglo = new E[this->tamMax];
        }   
        void agregar(E e){
            if (this->tamList<=this->tamMax)
            {
                this->arreglo[this->tamList]=e;
                this->tamList++;
            }
        }
        void insertar(E e){
            for (int i = this->tamList; i > this->actual; i--){
            this->arreglo[i] = this->arreglo[i-1];
            } 
            this->arreglo[this->actual] = e;
            this->tamList++;  
        }
        void moverAInicio(){
            this->actual = 0;
        }
        void moverAlFinal(){
            this->actual=this->tamList;
        }
        void anterior(){
            if (0<this->actual)
            {
                this->actual--;
            }
        }
        void siguiente(){
            if (this->actual<this->tamList)
            {
                this->actual++;
            }
        }
        int longitud(){
            return this->tamList;
        }
        int posicionActual(){
            return this->actual;
        }
        void moverAPosicion(int id){
            if (id>0 && id<this->tamList)
            {
                this->actual = id;
            }
        }
        E getValor(){
            return this->arreglo[this->actual];
        }
        void setValor(E e){
            this->arreglo[this->actual] = e;
        }
        E eliminar(){
            E eliminado = this->arreglo[this->actual];
            for (int i = this->actual; i < this->tamList; ++i) {
                this->arreglo[i] = this->arreglo[i+1];
            }
            this->tamList--;
            return eliminado;
        }

};
template<typename E> class Nodo{
    private:
    public:
        E elemento;
        Nodo *siguiente;
        Nodo(E elemento, Nodo* proximo=NULL){
            this->elemento = elemento;
            this->siguiente = proximo;
        }
        Nodo(Nodo* proximo = NULL){
            this->siguiente = proximo;
        }
};
//////////////////////////////////////////////////////////////////////////////////
// ----------------------LISTA NODOS -------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////

template<typename E> class listaEnlazada: public lista<E>{
    private:
        Nodo<E*>* cabeza;
        Nodo<E*>* cola;
        Nodo<E*>* actual;
        int tamList;

        void inicializar(){
            this->tamList = 0;
            this->cabeza=this->cola=this->actual=new Nodo<E*>;
        }
        void eliminarLista(){
            while (this->cabeza!=NULL)
            {
                this->actual = this->cabeza;
                this->cabeza = this->cabeza->siguiente;
                delete actual;
            }  
        }
    public:
        listaEnlazada(){
            inicializar();
        }
        ~listaEnlazada(){
            eliminarLista();
        }
        void limpiar() {
            eliminarLista();
            inicializar();
        }
        void inicializarNulos(){
            this->tamList = 0;
            this->
        }
        void agregar(E e){
            this->cola = this->cola->siguiente = new Nodo<E*>(new E(e), NULL);
            this->tamList++;
        }
        void insertar(E e){
            this->actual->siguiente = new Nodo<E*>(new E(e), this->actual->siguiente);
            if(this->cola==this->actual) this->cola = this->actual->siguiente;
            this->tamList++;
        }
        void moverAInicio(){
            this->actual = this->cabeza;
        }
        void moverAlFinal(){
            this->actual=this->cola;
        }
        void anterior(){
            if (vacio())
            {
                Nodo<E*> *aux;
                aux = this->cabeza;
                while (aux->siguiente != this->actual)
                {
                    aux = aux->siguiente;
                }
                this->actual = aux;
            }
        }
        void siguiente(){
            if (this->actual!=this->cola)
            {
               this->actual=this->actual->siguiente;
            }
        }
        int longitud(){
            return this->tamList;
        }
        int posicionActual(){
            Nodo<E*> *temp = cabeza;
            int i;
            for(i=0; actual!=temp;i++) temp = temp->siguiente;
            return i;
        }
// --------- Funcion auxiliar Vacio-----------------------
        bool vacio(){
            bool vacio = false;
            if (this->cabeza == this->cola) vacio=true;
            return vacio; 
        }
//--------------------------------------------------------
        void moverAPosicion(int id){
            if (!vacio())
            {
                if (id>0 && id<= this->tamList)
                {
                   Nodo<E*> *temp;
                   temp = this->cabeza;
                   for (int i = 0; i < id; i++)
                   {
                       temp = temp->siguiente;
                   }
                   this->actual = temp;
                } else{
                    cout<<"FUERA DE RANGO"<<endl;
                }
            } else{
                cout<<"LISTA VACIA"<<endl;
            }
        }

        E getValor(){
            E valor;
            if (this->actual->siguiente==NULL)
            {
                cout<<"NO EXISTE";
            } else{
                valor = *this->actual->siguiente->elemento;
            }
            return valor;
        }
        void setValor(E e){
            if (this->actual->siguiente==NULL)
            {
                cout<<"NO EXISTE";
            } else{
                *this->actual->siguiente->elemento=e;
            }
        }
        E eliminar(){
            E eliminado = *this->actual->elemento;
            Nodo<E*> *temp;
            temp =  this->cabeza;
            while (temp->siguiente != this->actual) temp = temp->siguiente;
            temp->siguiente = this->actual->siguiente;
            delete this->actual;
            this->actual = temp->siguiente;
            this->tamList--;
            return eliminado;
        }
};
////////////////////////////////////////////////////////////////////////////////////
//---------------------------------ARBOL PADRE------------------------------------//
////////////////////////////////////////////////////////////////////////////////////
template<typename E> class arbol
{
private:
public:
    arbol(){}
    ~arbol(){}
    virtual void insertar(E e)=0;
    virtual E buscar(E id)=0;
    virtual int longitud(E e)=0;
};
////////////////////////////////////////////////////////////////////////////////////
//---------------------------------ARBOL LISTA------------------------------------//
////////////////////////////////////////////////////////////////////////////////////
template<typename E> class arbolLista:public arbol<E>{
    private:
        listaEnlazada<E> *arreglo;
        int tamMax;
        int tamList;
    public:
//--------------------------------NODOS HIJOS--------------------------------------
        int hijoIzquierda(int id){
            return 2*id+1;
        }
        int hijoDerecha(int id){
            return 2*id+2;
        }
//-------------------------INICIALIZAR CON NULOS-----------------------------------
        void inicioNulos(){
            for (this->arreglo->moverAInicio();
            this->arreglo->posicionActual()<this->tamMax;
            this->arreglo->siguiente())
            {
                this->arreglo->setValor(-1);
            }
            
        }
//---------------------------------------------------------------------------------
    arbolLista(int tamMax=1000){
        this->tamMax = tamMax;
        this->arreglo = new listaEnlazada<E>(tamMax);
        this->tamList = 0;
        this->arreglo->moverAInicio();
        this->arreglo->inicio
        

    }

};


//---------------------------------ARBOL NODOS-------------------------------------



//-------------------------------DICCIONARIO PADRE---------------------------------



//-------------------------------DICCIONARIO ARBOL---------------------------------

//-------------------------------FUNCIONES ADICIONALES -----------------------------

void imprimirALista(){
    listaArreglo<int> *prueba = new listaArreglo<int>;
    prueba->agregar(19);
    prueba->agregar(20);
    prueba->agregar(30);
    for (prueba->moverAInicio(); 
    prueba->posicionActual() < prueba->longitud();
    prueba->siguiente())
    {
        cout<<prueba->getValor()<<endl;
    }
    prueba->eliminar();
    for (prueba->moverAInicio(); 
    prueba->posicionActual() < prueba->longitud();
    prueba->siguiente())
    {
        cout<<prueba->getValor()<<endl;
    }
    delete prueba;
};

void imprimirLLista(){
    listaEnlazada<int> * prueba = new listaEnlazada<int>;
    prueba->agregar(19);
    prueba->agregar(20);
    prueba->agregar(30);
    for (prueba->moverAInicio(); 
    prueba->posicionActual() < prueba->longitud();
    prueba->siguiente())
    {
        cout<<prueba->getValor()<<endl;
    }
    prueba->eliminar();
    for (prueba->moverAInicio(); 
    prueba->posicionActual() < prueba->longitud();
    prueba->siguiente())
    {
        cout<<prueba->getValor()<<endl;
    }
    delete prueba;
}

int main(){
    imprimirALista();
    imprimirLLista();
}