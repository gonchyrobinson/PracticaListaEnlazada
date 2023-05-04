#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#define TAMA 500
struct TDocumento
{
    int CantidadDePaginas; // de 1 a 500
    char *TipoDeDocumento; // se construye con los titulos
    int Volumen;           // de 1 a 10
};
typedef struct TDocumento TDocumento;
struct Tnodo
{
    TDocumento dato;         // Documento (dato del nodo)
    struct Tnodo *siguiente; // Siguiente Nodo.
};
typedef struct Tnodo Tnodo;

Tnodo *CrearListaVacia();
bool EsListaVacia(Tnodo *cabecera);
Tnodo *CrearNodo(TDocumento dato);
void InsertarNodo(Tnodo **cabecera, Tnodo *nodo);
void MostrarLista(Tnodo *lista);
Tnodo *QuitarNodoDeLaLista(Tnodo **cabecera);
void EliminaPrimerElemento(Tnodo **cabecera);
TDocumento CrearDocumento();
void MuestraDocumento(TDocumento doc);
void DistribuyeDocumentos(Tnodo **lista, Tnodo **usoInterno, Tnodo **contenidoPublico);
int ContarNodos(Tnodo *lista);
void LiberaMemoria(Tnodo **lista);

char TipoDeDocumento[2][12] = {"Uso Interno", "Uso Publico"};

int main()
{
    Tnodo *lista = CrearListaVacia();
    Tnodo *nodo;
    TDocumento doc;
    for (int i = 0; i < TAMA; i++)
    {
        doc = CrearDocumento();
        nodo = CrearNodo(doc);
        InsertarNodo(&lista, nodo);
    }
    // MostrarLista(lista);
    Tnodo *usoInterno = CrearListaVacia();
    Tnodo *ContenidoPublico = CrearListaVacia();
    DistribuyeDocumentos(&lista, &usoInterno, &ContenidoPublico);
    /*printf("\n=======================USO INTERNO==========================\n");
    MostrarLista(usoInterno);
    printf("\n======================CONTENIDO PUBLICO==========================\n");
    MostrarLista(ContenidoPublico);
    printf("\n=======================lista==========================\n");
    MostrarLista(lista);
    */
    printf("\n=====================================CONTAR NODOS==============================\n");
    printf("Lista principal: %d\nLista Uso interno: %d\nLista Uso Publico: %d", ContarNodos(lista), ContarNodos(usoInterno), ContarNodos(ContenidoPublico));
    LiberaMemoria(&usoInterno);
    LiberaMemoria(&ContenidoPublico);
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

Tnodo *CrearNodo(TDocumento dato)
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
        printf("\n--------------------MUESTRA NODO ------------\n");
        MuestraDocumento(lista->dato);
        lista = lista->siguiente;
    }
}

Tnodo *QuitarNodoDeLaLista(Tnodo **cabecera)
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

TDocumento CrearDocumento()
{
    TDocumento doc;
    doc.CantidadDePaginas = 1 + rand() % 500;
    doc.TipoDeDocumento = TipoDeDocumento[rand() % 2];
    doc.Volumen = 1 + rand() % 10;
    return (doc);
}

void MuestraDocumento(TDocumento doc)
{
    printf("\n===============================MUESTRA DOCUMENTO======================\n");
    printf("Tipo de documento: %s\nCantidad de paginas: %d\nVolumen: %d", doc.TipoDeDocumento, doc.CantidadDePaginas, doc.Volumen);
}

void DistribuyeDocumentos(Tnodo **lista, Tnodo **usoInterno, Tnodo **contenidoPublico)
{
    Tnodo *nodo;
    while (!EsListaVacia(*lista))
    {
        nodo = QuitarNodoDeLaLista(lista);
        if (nodo)
        {
            if (strcmp(nodo->dato.TipoDeDocumento, "Uso Interno") == 0)
            {
                InsertarNodo(usoInterno, nodo);
            }
            else
            {
                InsertarNodo(contenidoPublico, nodo);
            }
        }
    }
}

int ContarNodos(Tnodo *lista)
{
    int contador = 0;
    while (!EsListaVacia(lista))
    {
        contador += 1;
        lista = lista->siguiente;
    }
    return (contador);
}

void LiberaMemoria(Tnodo **lista)
{
    Tnodo *aux;
    while (!EsListaVacia(*lista))
    {
        aux = *lista;
        *lista = (*lista)->siguiente;
        free(aux);
    }
}