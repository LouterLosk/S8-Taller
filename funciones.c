#include ".\funciones.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void IngresoProducto(int valor,int Maxproducts,char producto[][LONGITUD],int recursos[MAXPRODUCTS],int tiempo[][3]){
        char mensaje[LONGITUD];
        int cont = 0;
        for (int i = valor; i < Maxproducts; i++) {
        printf("---------------------------------------------\n");
        printf("Producto %d\n", i + 1);
        guardarPalabra("Ingrese el nombre: ", producto[i], LONGITUD);
        recursos[i] = leerNumeroEnteroEntre("Ingrese la cantidad necesaria de recursos: ",1000,1);
        do
        {
            printf("Tiempo de fabricacion\n");
            tiempo[i][0] = leerNumeroEnteroEntre("Ingrese las horas: ",23,0);
            tiempo[i][1] = leerNumeroEnteroEntre("Ingrese los minutos: ",59,0);
            tiempo[i][2] = leerNumeroEnteroEntre("Ingrese los segundos: ",59,0);
            if((tiempo[i][0]||tiempo[i][1]||tiempo[i][2]) == 0 ){
                printf("Debe ingresar un valor\n");
                cont = 1;
            }else{
                cont = 0;
            }
        } while (cont == 1);
        printf("---------------------------------------------\n");
    }
}

void Menu(char productos[][LONGITUD],int recursos[],int tiempo[][3],int *maxRecursos,int *maxTiempo){
    int eleccion = 0;
    int valor = 0;
    int seleccion = 0;
    int recursosIni = *maxRecursos;
    int cantidad;
    do
    {
        printf("\n");
        printf("\n----- Menu -----\n");
        printf("1. Ingresar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Calcular tiempo y recursos\n");
        printf("5. Verificar productos\n");
        printf("6. Salir\n");
        eleccion = leerNumeroEnteroEntre("Seleccione una opcion: ",6,1);
        printf("\n");
        switch (eleccion){
        case 1 :
            seleccion = leerNumeroEnteroEntre("1.Agregar recursos 2.Agregar producto:\n",2,1);
            if (seleccion == 1)
            {
                *maxRecursos += leerNumeroEnteroEntre("Ingrese la cantidad de recursos: ",10000,0);
            }else{
                valor = buscarEspacioLibre(productos);
                if (valor != -1)
                {
                    IngresoProducto(valor,MAXPRODUCTS,productos,recursos,tiempo);
                }else{
                    printf("No se puede agregar mas productos");
                }
            }
            break;
        case 2 :
            valor = 0;
            valor = BuscarProdutcoEncontrado(productos,recursos,tiempo);
            mostrarProducto(valor,productos,recursos,tiempo);
            printf("Editar el prodcto:\n");
            IngresoProducto(valor,valor + 1,productos,recursos,tiempo);
            break;
        case 3 :
            valor = 0;
            printf("Eliminar el prodcto:\n");
            valor = BuscarProdutcoEncontrado(productos,recursos,tiempo);
            mostrarProducto(valor,productos,recursos,tiempo);
            eliminarProducto(valor,productos,recursos,tiempo);
            break;
        case 4 :
            printf("Crear prodcto: \n");
            valor = BuscarProdutcoEncontrado(productos,recursos,tiempo);
            mostrarProducto(valor,productos,recursos,tiempo);
            cantidad = leerNumeroEnteroEntre("Ingrese la cantidad de productos que desea crear: ",1000,0);
            crearProducto(cantidad,productos[valor],recursos[valor],tiempo[valor],maxRecursos,maxTiempo);
            break;
        case 5 :
            printf("---------------------------------------------\n");
            printf("En el inventario existe %d de recursos\n",recursosIni);
            printf("El maximo de timpo es %d\n",*maxTiempo);
            printf("---------------------------------------------\n");
            for (int i = 0; i < MAXPRODUCTS; i++)
            {
                mostrarProducto(i,productos,recursos,tiempo);
            }
            break;
        case 6 :
            printf("Saliendo.....");
            break;
        default:
            break;
        }
    } while (eleccion != 6); 
}





int BuscarProdutcoEncontrado(char nombre[][LONGITUD],int recursos[],int tiempo[][3]){
    char nombreBuscado[LONGITUD];
    int repetir = 0;
    while (repetir == 0){
        guardarPalabra("Ingrese el nombre del producto: ", nombreBuscado, LONGITUD);
        for (int i = 0; i < MAXPRODUCTS; i++) 
        {
            if (findProducto(nombre[i], nombreBuscado) == 0) 
            {
                repetir = 1;
                return i;
            }
        }
        printf("Producto no encontrado.\n");
    }
}

int findProducto(char destino[],char nombreBuscado[]){
        if (strcmp(destino, nombreBuscado) == 0) {
            return 0;
        }else{
            return 1;
        }
    }

void eliminarProducto(int NrProducto, char nombre[][LONGITUD], int recursos[], int tiempo[][3]) {
    if (NrProducto < 0 || NrProducto >= MAXPRODUCTS) {
        printf("Índice de producto inválido.\n");
        return;
    }
    // Mover los productos siguientes una posición hacia arriba
    for (int i = NrProducto; i < MAXPRODUCTS - 1; i++) {
        strcpy(nombre[i], nombre[i + 1]);
        recursos[i] = recursos[i + 1];
        tiempo[i][0] = tiempo[i + 1][0];
        tiempo[i][1] = tiempo[i + 1][1];
        tiempo[i][2] = tiempo[i + 1][2];
    }
    // Limpiar el último producto
    nombre[MAXPRODUCTS - 1][0] = '\0';
    recursos[MAXPRODUCTS - 1] = 0;
    tiempo[MAXPRODUCTS - 1][0] = 0;
    tiempo[MAXPRODUCTS - 1][1] = 0;
    tiempo[MAXPRODUCTS - 1][2] = 0;
    printf("Producto eliminado correctamente.\n");
}

int buscarEspacioLibre(char producto[][LONGITUD]) {
    for (int i = 0; i < MAXPRODUCTS; i++) {
        if (producto[i][0] == '\0') {
            return i; // Espacio libre encontrado
        }
    }
    return -1; // No hay espacio libre
}

void crearProducto(int Cantidad,char nombre[],int recursos,int tiempo[3],int *maxRecursos,int *maxTiempo){
    int TotalSegundos = (tiempo[2]+tiempo[1]*60+tiempo[0]*3600);
    TotalSegundos *= Cantidad; 
    int horas = TotalSegundos / 3600;
    int minutos = (TotalSegundos % 3600)/60;
    int segundos = TotalSegundos % 60;
         if ((Cantidad * recursos) > *maxRecursos || (*maxTiempo <(TotalSegundos / 3600)))
        {
            printf("Se ha exedido la cantidad maxima de recursos\n");
        }else{
            printf("Se necesita %d de recursos\n",Cantidad * recursos);
            if ((segundos) > 59)
            {
                minutos += (segundos)/60;
                segundos = 0;
                if (minutos > 59)
                {
                    horas += (minutos)/60;
                    minutos = 0;
                }
            }
            printf("%s%d horas %d minutos %d segundos\n","Se necesita ",horas,minutos,segundos);
            int seguir = leerNumeroEnteroEntre("Desea crearlos? 1.Si 2.No\n",2,1);
            printf("Elementos creados con exito!!!");
            if(seguir == 1){
                *maxRecursos -= Cantidad * recursos;
            }
        }
    }

void guardarPalabra(char *mensaje, char destino[], int longitud) {
    int esValido = 0;
    while (esValido == 0){
        printf("%s", mensaje);
        if (fgets(destino, longitud, stdin) != NULL) {
            size_t len = strlen(destino);
            if (len > 0 && destino[len - 1] == '\n') {
                destino[len - 1] = '\0'; // Elimina el salto de línea
            }
            // Verificar que no contenga números
            for (size_t i = 0; i < strlen(destino); i++) {
                if (isdigit(destino[i])) { // Si hay un número
                    printf("Error: No se permiten numeros. Intente de nuevo.\n");
                    i = strlen(destino);
                    esValido = 0;
                }else{
                    esValido = 1;
                }
            }
        }else 
            {
            printf("Error al leer la entrada.\n");
            }
    }
    for (int i = 0; destino[i] != '\0'; i++) {
        destino[i] = tolower(destino[i]);
    }
}


int leerNumeroEnteroEntre(char *mensaje,int max,int min){
    int valor = 0;
    printf("%s",mensaje);
    while(scanf("%d",&valor) != 1 || valor > max ||valor < min)
    {
        printf("Dato mal ingresado\n");
        printf("%s",mensaje);
        while ((getchar()) != '\n'); 
    }
    while ((getchar()) != '\n');
    return valor;
}

void mostrarProducto(int i,char nombre[][LONGITUD],int recursos[],int tiempo[][3]){
     printf("---------------------------------------------\n");
                printf("Producto: \n");
                printf("Nombre: %s\n", nombre[i]);
                printf("Recursos: %d\n", recursos[i]);
                printf("%s%10s%10s\n","Horas","Minutos","segundos");
                printf("%3d%10d%10d\n",tiempo[i][0],tiempo[i][1],tiempo[i][2]);
                printf("---------------------------------------------\n");
}