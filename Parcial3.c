/*
*    AUTHOR: Catedra de lenguajes de Taller 1 
*    DATE: 04/2021
*    LICENCE: Creative Commons 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<stdbool.h>

typedef struct Producto TProducto;
struct Producto
{
    int Id; /*Valor incremental*/
    char *Nombre; /*Sacar de la lista de Nombres*/
    char *Sucursal; /*Sacar de la lista de Sucursales*/    
    float Peso; /*Valor entre 0.5 y 50*/
}Producto;

typedef struct nodo Tnodo;
struct nodo
{
   TProducto * Producto;
   Tnodo * Siguiente;
} nodo;

char Nombre[10][35] = 
{
    "Ventilador Portatil", 
    "Lavarropas Semi Automatico", 
    "Licuadora", 
    "Heladera Chui", 
    "Exprimidor", 
    "Tv 65 pulgadas SanSan", 
    "Cocina", 
    "Estacion De Poder 5", 
    "XCaja Serie X ",
    "OjoPhone 11"
};

char Sucursales[3][15] = 
{
    "Tucuman", "Salta", "Santiago"
};

/* Crea una nueva lista vacia */
Tnodo * CrearListaVacia();
//Funcion que pregunta si la lista es vacia
bool Esvacia(Tnodo* lista);
/*Crea un nuevo puntero de Producto en memoria (estructura Producto) lo carga con valores aleatorios y lo devuelve */
TProducto * CrearProducto(int id);

/*Crea un nuevo nodo en memoria (estructura TNodo) y lo devuelve */
Tnodo * CrearNodo(TProducto * Producto);

/*Inserta un Nodo al comienzo de la lista*/
void InsertarEnLista(Tnodo ** Lista, Tnodo * Nodo);

/*Quita el primer nodo de la lista y lo devuelve*/
Tnodo * QuitarNodo(Tnodo ** Lista);

/*Cuenta la cantidad nodos de la lista */
int  CantidadDeNodos(Tnodo * Lista);

/*Devuelve el total de la suma de los Peso de los productos de la lista */
int  PesoDeLista(Tnodo * Lista);

/*Muestra Los elementos de la lista*/
void Mostrar(Tnodo * Lista);

/* Eliminar Lista de memoria */
void EliminarLista(Tnodo ** Lista);

//Cargar productos de una lista 
TProducto* CargarProducto(int i);

//Cargar productos en los camiones
void MoverProductos(Tnodo** ListadoDeProductos, Tnodo**RepartoLiviano, Tnodo** RepartoPesado, Tnodo** Deposito);
int main()
{              
    srand(time(NULL));
    int SucursalSeleccionada;
    float TotalDeCompra = 0;
    Tnodo * ListadoDeProductos = CrearListaVacia();
    Tnodo * Deposito = CrearListaVacia();
    Tnodo * RepartoLiviano = CrearListaVacia();
    Tnodo * RepartoPesado = CrearListaVacia();
    Tnodo* nodo;
    TProducto* Producto;

    int cantProductos = rand() % 91 + 10;         
    printf("Creando Productos y Nodos");    
     
     /* Cargando la lista de Productos */
    for (int i = 0; i < cantProductos; i++)
    {
        /* Aquí debes crear los Productos, los nodos y cargalos en la lista Productos */   
        Producto=CargarProducto(i);
        nodo=CrearNodo(Producto);
        InsertarEnLista(&ListadoDeProductos, nodo); 

    }
    printf("=============LISTA PRODUCTOS ==========\n");
    Mostrar(ListadoDeProductos);
    MoverProductos(&ListadoDeProductos,&RepartoLiviano,&RepartoPesado,&Deposito);
    printf("=========REPARTO PESADO===========\n");
    Mostrar(RepartoPesado);
    printf("========REPARTO LIVIANO========\n");
    Mostrar(RepartoLiviano);
    printf("================DEPOSITO============\n");
    Mostrar(Deposito);
    /* Quitar los juegos los nodos de memoria cargar a la lista Juegos y de carrito */
    printf("Mostrar la sucursal (1 - Tucumán, 2 - Salta , 3 - Deposito)"); 
    scanf(" %d",&SucursalSeleccionada);
    
    /* Eliminar de memoria free() lo que se creó */
    
    /*fin del programa*/
    printf("Fin parcial"); 
    getchar();
    return 0;
}

Tnodo * CrearListaVacia()
{
    return NULL;
}

TProducto* CargarProducto(int i){
    TProducto* aux;
    aux=(TProducto*)malloc(sizeof(TProducto));
    aux->Id=i;
    aux->Nombre=(char*)malloc(35*sizeof(char));
    aux->Nombre=Nombre[rand()%10];
    aux->Peso=rand()%50+0.5;
    aux->Sucursal=(char*)malloc(15*sizeof(char));
    aux->Sucursal=Sucursales[rand()%3];
    return(aux);
}

Tnodo * CrearNodo(TProducto * Producto){
    Tnodo* aux;
    aux=(Tnodo*)malloc(sizeof(Tnodo));
    aux->Producto=Producto;
    aux->Siguiente=NULL;
    return(aux);
}

void InsertarEnLista(Tnodo ** Lista, Tnodo * Nodo){
    Nodo->Siguiente=(*Lista);
    (*Lista)=Nodo;
}

Tnodo * QuitarNodo(Tnodo ** Lista){
    Tnodo* nodo;
    Tnodo* aux=(*Lista);
    if(!Esvacia(*Lista)){
       nodo=aux;
       nodo->Siguiente=NULL;
       aux=aux->Siguiente;
    }
    return(nodo);
}

int  PesoDeLista(Tnodo * Lista){
    int peso=0;
    while(!Esvacia(Lista)){
        peso+=Lista->Producto->Peso;
        Lista=Lista->Siguiente;
    }
    return(peso);
}

void MoverProductos(Tnodo** ListadoDeProductos, Tnodo**RepartoLiviano, Tnodo** RepartoPesado, Tnodo** Deposito){
    Tnodo* nodo;
    int elegir;
    while(!Esvacia(*ListadoDeProductos)){
        nodo=QuitarNodo(ListadoDeProductos);
        if(nodo->Producto->Peso>=10)
        {
            if(PesoDeLista(*RepartoPesado)>600)
            {
                InsertarEnLista(Deposito,nodo);
            }else
            {
                InsertarEnLista(RepartoPesado, nodo);
            }
        }
        else
        {
            if(PesoDeLista(*RepartoLiviano)>100){
                InsertarEnLista(Deposito,nodo);
            }
            else
            {
                InsertarEnLista(RepartoLiviano, nodo);
            }
        }
    }
}

void Mostrar(Tnodo * Lista){
    while(!Esvacia(Lista)){
        printf("\n    Producto %d      \n",Lista->Producto->Id);
        printf("NOMBBRE: %s\n",Lista->Producto->Nombre);
        printf(" SUCURSAL: %s\n",Lista->Producto->Sucursal);
        printf("PESO: %d",Lista->Producto->Peso);
    }
}