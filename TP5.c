#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

char Descripcion[2][20] = {"Nuevo", "Usado"};
struct Tarea
{
    int id; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
};
typedef struct Tarea Tarea;

struct Tnodo
{
    Tarea *dato;
    struct Tnodo *siguiente;
};
typedef struct Tnodo Tnodo;

Tnodo *CrearListaVacia();
bool EsListaVacia(Tnodo *cabecera);
Tnodo *CrearNodo(Tarea *dato);
void InsertarNodo(Tnodo **cabecera, Tnodo *nodo);
void MostrarLista(Tnodo *lista);
void EliminaPrimerElemento(Tnodo **cabecera);
Tnodo *DesenlazarPrimerNodo(Tnodo **cabecera);
Tarea *CargarTarea(int i);
void MostrarTarea(Tarea *tarea);
void ModificaNodo(Tnodo **lista, Tnodo **pendientes, Tnodo **realizadas, Tnodo **enProceso);
Tnodo *DesenlazarNodoPorId(Tnodo **lista, int id);
void LiberaMemoriaConDatoPuntero(Tnodo **lista);
int main()
{
    srand(time(NULL));
    int cant = rand() % 10 + 1;
    Tarea *tarea;
    Tnodo *nodo = NULL;
    Tnodo *lista = CrearListaVacia();

    for (int i = 0; i < cant; i++)
    {
        tarea = CargarTarea(i);
        nodo = CrearNodo(tarea);
        InsertarNodo(&lista, nodo);
    }
    MostrarLista(lista);
    Tnodo* pendientes=CrearListaVacia();
    Tnodo* realizadas=CrearListaVacia();
    Tnodo* enProceso=CrearListaVacia();
    int opcion=1;
    while (opcion!=0)
    {
        ModificaNodo(&lista,&pendientes,&realizadas,&enProceso);
        printf("\nINGRESE 1 PARA SEGUIR MODIFICANDO, 0 PARA PARAR:  ");
        scanf("%d", &opcion);
    }
    MostrarLista(lista);
    printf("\n\nRealizadas:\n");
    MostrarLista(realizadas);
    printf("\n\nPendientes:\n");
    MostrarLista(pendientes);
    printf("\n\nEn Proceso:\n");
    MostrarLista(enProceso);
    LiberaMemoriaConDatoPuntero(&lista);
    LiberaMemoriaConDatoPuntero(&realizadas);
    LiberaMemoriaConDatoPuntero(&pendientes);
    LiberaMemoriaConDatoPuntero(&enProceso);
}

Tnodo* CrearListaVacia(){
    return(NULL);
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

Tnodo *CrearNodo(Tarea *dato)
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
        MostrarTarea(lista->dato);
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

Tarea *CargarTarea(int i)
{
    Tarea *aux;
    aux = (Tarea *)malloc(sizeof(Tarea));
    aux->Descripcion = Descripcion[rand() % 2];
    aux->Duracion = rand() % 90 + 10;
    aux->id = i;
    return (aux);
}

void MostrarTarea(Tarea *tarea)
{
    printf("\n");
    printf("\n ID: %d\nDESCRIPCION: %s\nDURACION: %d", tarea->id, tarea->Descripcion, tarea->Duracion);
}

void ModificaNodo(Tnodo **lista, Tnodo **pendientes, Tnodo **realizadas, Tnodo **enProceso)
{
    int opcion;
    int id;
    int listaMover;
    printf("\n==========================MODIFICA POR ID===================\n");
    printf("id:  ");
    scanf("%d", &id);
    Tnodo *buscado = NULL;
    buscado = DesenlazarNodoPorId(lista, id);
    int listaId;
    int bandera = 0;
    if (buscado)
    {
        bandera = 1;

        listaId = 1;
    }
    else
    {
        buscado = DesenlazarNodoPorId(pendientes, id);
        if (buscado)
        {
            bandera = 1;

            listaId = 2;
        }
        else
        {
            buscado = DesenlazarNodoPorId(realizadas, id);
            if (buscado)
            {
                bandera = 1;

                listaId = 3;
            }
            else
            {
                buscado = DesenlazarNodoPorId(enProceso, id);
                if (buscado)
                {
                    bandera = 1;

                    listaId = 4;
                }
                else
                {
                    printf("\nNO SE ENCONTRO EL NODO\n");
                }
            }
        }
    }
    if (bandera==1 && buscado)
    {
        printf("\nIngrese que desea hacer con el nodo:  1-Mover\n2-Eliminar\nNo hcer nada\n");
        int opcion;
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            printf("\nLista a la que desea mover:  \n1-pendientes\n2-realizadas\n3-en proceso");
            scanf("%d", &listaMover);
            switch (listaMover)
            {
            case 1:
                InsertarNodo(pendientes,buscado);
            break;
            case 2:
                InsertarNodo(realizadas,buscado);
            break;
            case 3:
                InsertarNodo(enProceso,buscado);
            break;
            
            default:
                break;
            }
            break;
        case 2:
            free(buscado);
        break;
        case 3: 
            switch (listaId)
            {
            case 1:
                InsertarNodo(pendientes,buscado);
            break;
            case 2:
                InsertarNodo(realizadas,buscado);
            break;
            case 3:
                InsertarNodo(enProceso,buscado);
            break;
            
            default:
                break;
            }
        default:
            break;
        }
    }
}
Tnodo * DesenlazarNodoPorId(Tnodo **lista, int id)
{
    Tnodo *seleccionado = NULL;
    Tnodo *aux;
    Tnodo *anterior;
    if (!EsListaVacia(*lista))
    {
        if ((*lista)->dato->id == id)
        {
            seleccionado = *lista;
            *lista = (*lista)->siguiente;
            seleccionado->siguiente = NULL;
        }
        else
        {
            aux = *lista;
            while (!EsListaVacia(aux) && aux->dato->id != id)
            {
                anterior = aux;
                aux = aux->siguiente;
            }
            if (!EsListaVacia(aux))
            {
                seleccionado = aux;
                anterior->siguiente = aux->siguiente;
                seleccionado->siguiente = NULL;
            }
        }
        return (seleccionado);
    }
}

void LiberaMemoriaConDatoPuntero(Tnodo **lista)
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