/*
 *    AUTHOR: Catedra de lenguajes de Taller 1
 *    DATE: 04/2021
 *    LICENCE: Creative Commons
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

struct Producto
{
    int Id;         /*Valor incremental*/
    char *Nombre;   /*Sacar de la lista de Nombres*/
    char *Sucursal; /*Sacar de la lista de Sucursales*/
    float Peso;     /*Valor entre 0.5 y 50*/
};
typedef struct Producto TProducto;

typedef struct nodo Tnodo;
struct nodo
{
    TProducto *dato;
    Tnodo *siguiente;
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
        "OjoPhone 11"};

char Sucursales[3][15] =
    {
        "Tucuman", "Salta", "Santiago"};

Tnodo *CrearListaVacia();
bool EsListaVacia(Tnodo *cabecera);
Tnodo *CrearNodo(TProducto *dato);
void InsertarNodo(Tnodo **cabecera, Tnodo *nodo);
void MostrarLista(Tnodo *lista);
void EliminaPrimerElemento(Tnodo **cabecera);
Tnodo *DesenlazarPrimerNodo(Tnodo **cabecera);
TProducto *CreaProducto(int id);
void MuestraProd(TProducto *prod);
void MueveProductos(Tnodo **lista, Tnodo **repartoPesado, Tnodo **repartoLiviano, Tnodo **deposito);
float PesoTotal(Tnodo *lista);
int cantProd(Tnodo *lista);
void MostrarNProductos(Tnodo *lista, int cant);
void LiberaMemoria(Tnodo **lista);

int main()
{
    srand(time(NULL));
    int cant = 50 + rand() % 50;
    Tnodo *lista = CrearListaVacia();
    Tnodo *nodo;
    TProducto *prod;
    for (int i = 0; i < cant; i++)
    {
        prod = CreaProducto(i);
        nodo = CrearNodo(prod);
        InsertarNodo(&lista, nodo);
    }
    // MostrarLista(lista);
    Tnodo *repartoLiviano = CrearListaVacia();
    Tnodo *repartoPesado = CrearListaVacia();
    Tnodo *deposito = CrearListaVacia();
    MueveProductos(&lista, &repartoPesado, &repartoLiviano, &deposito);
    printf("\n_______________________________________Reparto Liviano:_______________________________________\n");
    MostrarLista(repartoLiviano);
    printf("\n_______________________________________Reparto pesado:_______________________________________\n");
    MostrarLista(repartoPesado);
    printf("\n_______________________________________Deposito:_______________________________________ \n");
    MostrarLista(deposito);
    printf("\n=====================================Cantidades y pesos===========================\n");
    printf("\n_______________________________REPARTO LIVIANO_______________________________\n");
    printf("Cantidad: %d\nPeso: %.2f", cantProd(repartoLiviano), PesoTotal(repartoLiviano));
    printf("\n_______________________________REPARTO PESADO_______________________________\n");
    printf("Cantidad: %d\nPeso: %.2f", cantProd(repartoPesado), PesoTotal(repartoPesado));
    printf("\n_______________________________DEPOSITO_______________________________\n");
    printf("Cantidad: %d\nPeso: %.2f", cantProd(deposito), PesoTotal(deposito));
    printf("\n===============================MUESTRA N PROD=============================\n");
    int cantidadMostrar;
    printf("\nCantidad a productos a mostrar (-1), toda la lista:  ");
    scanf("%d", &cantidadMostrar);
    MostrarNProductos(repartoLiviano, cantidadMostrar);
    LiberaMemoria(&repartoLiviano);
    LiberaMemoria(&repartoPesado);
    LiberaMemoria(&deposito);
}

Tnodo *CrearListaVacia()
{
    return (NULL);
}

bool EsListaVacia(Tnodo *cabecera)
{
    if (cabecera == NULL)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

Tnodo *CrearNodo(TProducto *dato)
{
    Tnodo *nodo = (Tnodo *)malloc(sizeof(struct Tnodo *));
    nodo->dato = dato;
    nodo->siguiente = NULL;
    return (nodo);
}

void InsertarNodo(Tnodo **cabecera, Tnodo *nodo)
{
    nodo->siguiente = *cabecera;
    *cabecera = nodo;
}

void MostrarLista(Tnodo *lista)
{
    printf("\n==================================MUESTRA LISTA===================================\n");
    while (!EsListaVacia(lista))
    {
        printf("\n");
        MuestraProd(lista->dato);
        lista = lista->siguiente;
    }
}

void EliminaPrimerElemento(Tnodo **cabecera)
{
    Tnodo *nodoAux;
    if (!EsListaVacia(*cabecera))
    {
        nodoAux = (*cabecera);
        (*cabecera) = (*cabecera)->siguiente;
        free(nodoAux);
    }
    else
    {
        printf("\nNo se puede eliminar un nodo de una lista vacia\n");
    }
}
Tnodo *DesenlazarPrimerNodo(Tnodo **cabecera)
{
    Tnodo *nodoSacado = NULL;
    if (!EsListaVacia(*cabecera))
    {
        nodoSacado = *cabecera;
        *cabecera = (*cabecera)->siguiente;
        nodoSacado->siguiente = NULL;
    }
    return (nodoSacado);
}

TProducto *CreaProducto(int id)
{
    TProducto *prod;
    prod = (TProducto *)malloc(sizeof(TProducto));
    prod->Id = id;
    prod->Nombre = Nombre[rand() % 10];
    prod->Peso = 0.5 + rand() % 50 * 100 / 100;
    prod->Sucursal = Sucursales[rand() % 3];
    return (prod);
}

void MuestraProd(TProducto *prod)
{
    printf("\n=============================MUESTRA PROD=========================\n");
    printf("\nId: %d\nNombre: %s\nPeso: %.2f\nSucursal: %s", prod->Id, prod->Nombre, prod->Peso, prod->Sucursal);
}

void MueveProductos(Tnodo **lista, Tnodo **repartoPesado, Tnodo **repartoLiviano, Tnodo **deposito)
{
    Tnodo *nodo = NULL;
    float pesoP = 0;
    float pesoL = 0;
    while (!EsListaVacia(*lista))
    {
        nodo = DesenlazarPrimerNodo(lista);
        if (nodo)
        {
            if (nodo->dato->Peso >= 10)
            {
                if (pesoP + (nodo->dato->Peso) <= 600)
                {
                    pesoP += (nodo->dato->Peso);
                    InsertarNodo(repartoPesado, nodo);
                }
                else
                {
                    InsertarNodo(deposito, nodo);
                }
            }
            else
            {
                if ((pesoL + nodo->dato->Peso) <= 100)
                {
                    InsertarNodo(repartoLiviano, nodo);
                    pesoL += (nodo->dato->Peso);
                }
                else
                {
                    InsertarNodo(deposito, nodo);
                }
            }
        }
    }
}

float PesoTotal(Tnodo *lista)
{
    float peso = 0;
    while (!EsListaVacia(lista))
    {
        peso += lista->dato->Peso;
        lista = lista->siguiente;
    }
    return (peso);
}

int cantProd(Tnodo *lista)
{
    int cant = 0;
    while (!EsListaVacia(lista))
    {
        cant += 1;
        lista = lista->siguiente;
    }
    return (cant);
}

void MostrarNProductos(Tnodo *lista, int cant)
{
    int elementos = 0;
    if (cant == -1)
    {
        MostrarLista(lista);
    }
    else
    {
        while (!EsListaVacia(lista) && elementos < cant)
        {
            printf("\n");
            MuestraProd(lista->dato);
            lista = lista->siguiente;
            elementos += 1;
        }
    }
}

void   LiberaMemoria(Tnodo **lista)
{
    Tnodo *aux;
    while (!EsListaVacia(*lista))
    {
        aux = *lista;
        *lista = (*lista)->siguiente;
        free(aux->dato);
        free(aux);
    }
}
