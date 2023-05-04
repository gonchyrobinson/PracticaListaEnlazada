#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
struct Producto
{
    int id;
    char* nombre;
    int cantidad;
    float precio;
    float costo;
    float porcentajeGanancia;
};
typedef struct Producto item;
char Nombres[3][20]={"Comida","Ropa","Limpieza"};

struct Tnodo{
    item dato;
    struct Tnodo* siguiente;
};typedef struct Tnodo Tnodo;

Tnodo* CrearListaVacia();
bool EsListaVacia(Tnodo* cabecera);
Tnodo* CrearNodo(item dato);
void InsertarNodo(Tnodo** cabecera, Tnodo* nodo);
void MostrarLista(Tnodo* lista);
item CargarProducto(int id);
void MostrarProducto(item prod);
void menu(Tnodo** lista);
void EliminaPrimerElemento(Tnodo** cabecera);
void EliminarPorId(Tnodo** lista, int id);
Tnodo* DesenlazarNodoPorId(Tnodo**lista, int id);
Tnodo* BuscarNodoPorId(Tnodo* lista, int id);
float CalculaLasVentasDiarias(Tnodo* lista);
void AplicaDescuento(Tnodo* lista, float porcentaje);
float CalculaGanancias(Tnodo* lista);
void LiberaLista(Tnodo**lista);
void InsertarAlFInal(Tnodo** lista, Tnodo*nodo);
void EliminarNodoDelFinal(Tnodo**lista);

int main(){
    Tnodo* lista=CrearListaVacia();
    int cant;
    item prod;
    Tnodo* nodo;
    printf("Cantidad productos:  ");
    scanf("%d", &cant);
    for (int i = 0; i < cant; i++)
    {
        prod=CargarProducto(i);
        nodo=CrearNodo(prod);
        InsertarNodo(&lista,nodo);
    }
    MostrarLista(lista);
    menu(&lista);
    LiberaLista(&lista);
    
}

Tnodo* CrearListaVacia(){
    return(NULL);
}

bool EsListaVacia(Tnodo* cabecera){
    if(cabecera==NULL){
        return(true);
    }else
    {
        return(false);
    }
    
}

Tnodo* CrearNodo(item dato){
    Tnodo* nodo=(Tnodo*)malloc(sizeof(struct Tnodo*));
    nodo->dato=dato;
    nodo->siguiente=NULL;
    return(nodo);
}

void InsertarNodo(Tnodo** cabecera, Tnodo* nodo){
    nodo->siguiente=*cabecera;
    *cabecera=nodo;
}

void MostrarLista(Tnodo* lista){
    printf("\n==================================MUESTRA LISTA===================================\n");
    while (!EsListaVacia(lista))
    {
        printf("\n--------------------MUESTRA NODO ------------\n");
        MostrarProducto(lista->dato);
        lista=lista->siguiente;
    }
    
}

item CargarProducto(int id){
    item prod;
    prod.id=id;
    prod.nombre=Nombres[rand()%3];
    prod.cantidad=rand()%11;
    prod.costo=rand()%1000*100/100;
    prod.precio=prod.costo+rand()%1000*100/100;
    prod.porcentajeGanancia=((prod.precio-prod.costo)/prod.costo)*100;
    return(prod);
}

void MostrarProducto(item prod){
    printf("\n=========================MUESTRA PRODUCTO=================================0\n");
    printf("\nID: %d\nNombre: %s\nCantidad: %d\nCosto: %.2f\nPrecio:%.2f\nPorcentaje Ganancias: %.2f",prod.id,prod.nombre,prod.cantidad, prod.costo, prod.precio, prod.porcentajeGanancia);

}

void menu(Tnodo** lista){
    puts("\n========================MENU=================================\n");
    int opcion;
    printf("\nIngrese: \n0-Salir\n1- Mostrar\n2-Insertar\n3-Eliminar\n4-Buscar por id\n5-Calcula Ventas Diarias\n6-Aplica 10\% a los productos que tengan un porcentaje de ganancias determinado\n7-Ganancias totales\n8-Insertar producto al final\n");
    scanf("%d",&opcion);
    item prod;
    float precio;
    float porcentaje;
    Tnodo* nodo=NULL;
    int id;
    while (opcion!=0)
    {
        switch (opcion)
        {
        case 1:
            MostrarLista(*lista);
        break;
        case 2:
            printf("\nID: ");
            scanf("%d",&id);
            prod=CargarProducto(id);
            nodo=CrearNodo(prod);
            InsertarNodo(lista,nodo);  
        break;
        case 3:
            printf("Id que desea eliminar: ");
            scanf("%d", &id);
            EliminarPorId(lista,id);
        break;
        case 4:
            printf("Id que desea buscar:  ");
            scanf("%d", &id);
            nodo=BuscarNodoPorId(*lista,id);
            if (nodo)
            {
                MostrarProducto(nodo->dato);
            }else{
                printf("\nNo se encontro el id");
            }
        break;
        case 5:
            printf("\n===================TOTAL VENTAS DIARIAS=========================\n");
            precio=CalculaLasVentasDiarias(*lista);
            printf("\nTotal: %.2f", precio);
        break;
        case 6:
            printf("\n=========================APLICA DESCUENTO DEL 10========================\n");
            printf("\n Porcentaje de ganancias:  ");
            scanf("%f",&porcentaje);
            AplicaDescuento(*lista,porcentaje);
        break;
        case 7:
            printf("\n======================================GANANCIAS TOTALES ================================\n");
            printf("Ganancias: %.2f",CalculaGanancias(*lista));
        break;
        case 8:
            printf("\n=======================================INSERTAR AL FINAL=================================\n");
            printf("\nID: ");
            scanf("%d",&id);
            prod=CargarProducto(id);
            nodo=CrearNodo(prod);
            InsertarAlFInal(lista,nodo);
        break;
        case 9:
            EliminarNodoDelFinal(lista);
        break;
        default:
            break;
        }
        printf("\nIngrese: \n0-Salir\n1- Mostrar\n2-Insertar\n3-Eliminar\n4-Buscar por id\n5-Calcula Ventas Diarias\n6-Aplica 10\% a los productos que tengan un porcentaje de ganancias determinado\n7-Ganancias totales\n8-Insertar nodo al final\n9-Eliminar nodo del final");
        scanf("%d",&opcion);
    }
    
}

void EliminaPrimerElemento(Tnodo** cabecera){
    Tnodo* nodoAux;
    if(!EsListaVacia(*cabecera)){
        nodoAux=(*cabecera);
        (*cabecera)=(*cabecera)->siguiente;
        free(nodoAux);
    }else
    {
        printf("\nNo se puede eliminar un nodo de una lista vacia\n");
    }
    
}
Tnodo* DesenlazarNodoPorId(Tnodo**lista, int id){
    Tnodo* seleccionado=NULL;
    Tnodo* aux;
    Tnodo* anterior;
    if (!EsListaVacia(*lista))
    {
        if ((*lista)->dato.id==id)
        {
            seleccionado=*lista;
            *lista=(*lista)->siguiente;
            seleccionado->siguiente=NULL;
        }else
        {
            aux=*lista;
            while (!EsListaVacia(aux) && (aux)->dato.id!=id)
            {
                anterior=aux;
                aux=(aux)->siguiente;
            }
            if (!EsListaVacia(aux))
            {
                seleccionado=aux;
                anterior->siguiente=aux->siguiente;
                seleccionado->siguiente=NULL;
            }
            
        }
        
        
    }
    return(seleccionado);
    
    
}

void EliminarPorId(Tnodo** lista, int id){
    Tnodo* seleccionado=NULL;
    seleccionado=DesenlazarNodoPorId(lista,id);
    if (seleccionado)
    {
        free(seleccionado);
    }else
    {
        printf("\n ID inexistente");
    }
    
    
}

Tnodo* BuscarNodoPorId(Tnodo* lista, int id){
    Tnodo* buscado=NULL;
    while (!EsListaVacia(lista) && lista->dato.id!=id)
    {
        lista=lista->siguiente;
    }
    if (!EsListaVacia(lista))
    {
        buscado=lista;
    }
    return(buscado);
    
}

float CalculaLasVentasDiarias(Tnodo* lista){
    float ventas=0;
    while (!EsListaVacia(lista))
    {
        ventas+=(lista->dato.precio*lista->dato.cantidad);
        lista=lista->siguiente;
    }
    return(ventas);
}

void AplicaDescuento(Tnodo* lista, float porcentaje){
    while (!EsListaVacia(lista))
    {
        if (lista->dato.porcentajeGanancia>=porcentaje)
        {
            lista->dato.precio*=0.90;
        }
        lista=lista->siguiente;
        
    }
    
}

float CalculaGanancias(Tnodo* lista){
    float ganancias=0;
    while (!EsListaVacia(lista))
    {
        ganancias+=(lista->dato.precio-lista->dato.costo)*lista->dato.cantidad;
        lista=lista->siguiente;
    }
    return(ganancias);
    
}

void LiberaLista(Tnodo**lista){
    Tnodo* aux;
    while (!EsListaVacia(*lista))
    {
        aux=*lista;
        *lista=(*lista)->siguiente;
        free(aux);
    }
    
}
void InsertarAlFInal(Tnodo** lista, Tnodo*nodo){
    Tnodo* anterior=NULL;
    Tnodo* aux;
    if (EsListaVacia(*lista))
    {
        nodo->siguiente=*lista;
        *lista=nodo;
    }else
    {
        aux=*lista;
        while (!EsListaVacia(aux))
        {
            anterior=aux;
            aux=aux->siguiente;
        }
        anterior->siguiente=nodo;
    }
    
    
}

void EliminarNodoDelFinal(Tnodo**lista){
    Tnodo* anterior;
    Tnodo* aux;
    if (!EsListaVacia(*lista))
    {
        if (EsListaVacia((*lista)->siguiente))
        {
            aux=*lista;
            *lista=NULL;
            free(aux);   
        }else{
            aux=*lista;
            while (!EsListaVacia(aux) && !EsListaVacia(aux->siguiente))
            {
                anterior=aux;
                aux=aux->siguiente;
            }
            anterior->siguiente=aux->siguiente;
            free(aux);
            
        }
        
    }
    
    
}