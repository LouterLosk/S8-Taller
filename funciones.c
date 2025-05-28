#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"


void IngresoProducto(char producto[][LONGITUD], int recursos[][MAXRECURSOS], int variedadRecursos[], char nombreRecursos[][MAXRECURSOS][LONGITUD], float tiempo[], int cantidad[], int desde, int hasta) {
    for (int i = desde; i < hasta && i < MAXPRODUCTS; i++) {
        printf("---------------------------------------------\n");
        printf("Producto %d\n", i + 1);
        guardarPalabra("Ingrese el nombre: ", producto[i], LONGITUD);

        // Preguntar variedad de recursos
        variedadRecursos[i] = leerNumeroEnteroEntre("Cuantos tipos de recursos necesita este producto? (max 5): ", MAXRECURSOS, 1);

        // Por cada recurso, pedir nombre y cantidad
        for (int j = 0; j < variedadRecursos[i]; j++) {
            char mensaje[LONGITUD + 50];
            sprintf(mensaje, "Ingrese el nombre del recurso #%d: ", j + 1);
            guardarPalabra(mensaje, nombreRecursos[i][j], LONGITUD);

            sprintf(mensaje, "Cuantas unidades de %s necesita por producto?: ", nombreRecursos[i][j]);
            recursos[i][j] = leerNumeroEnteroEntre(mensaje, 1000, 1);
        }

        cantidad[i] = leerNumeroEnteroEntre("Cuantos productos de este tipo se necesitan?: ", 1000, 1);
        printf("Tiempo de fabricacion\n");
        tiempo[i] = leerNumeroFlotanteEntre("Ingrese la cantidad necesaria de tiempo (minutos): ", 10000, 1);
        if (tiempo[i] == 0) {
            printf("Debe ingresar un valor\n");
        }
        printf("---------------------------------------------\n");
    }
}

int Menu(char productos[][LONGITUD], int recursos[][MAXRECURSOS], int variedadRecursos[], char nombreRecursos[][MAXRECURSOS][LONGITUD], float tiempo[], int cantidad[]){
    int continuar = 0;
    int eleccion = 0;
    int valor = 0;
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
        printf("\n-----------------\n");
        eleccion = leerNumeroEnteroEntre("Seleccione una opcion: ",6,1);
        printf("\n");
        switch (eleccion){
        case 1:
            valor = buscarEspacioLibre(productos);
            if (valor != -1) {
                int maximo = leerNumeroEnteroEntre("Cuantos productos quiere ingresar (Max 5): ", MAXPRODUCTS, 1);
                int hasta = valor + maximo;
                if (hasta > MAXPRODUCTS) {
                    hasta = MAXPRODUCTS;
                }
                IngresoProducto(productos, recursos, variedadRecursos, nombreRecursos, tiempo, cantidad, valor, hasta);
            } else {
                printf("No se puede agregar mas productos\n");
            }
        break;
        case 2: 
            valor = BuscarProdutcoEncontrado(productos);
            if (valor != -1) {
                mostrarProducto(valor, productos, recursos, variedadRecursos, nombreRecursos, tiempo, cantidad);
                printf("Editar el producto:\n");
                IngresoProducto(productos, recursos, variedadRecursos, nombreRecursos, tiempo, cantidad, valor, valor + 1);
            }
break;
        case 3:
            valor = BuscarProdutcoEncontrado(productos);
            if (valor != -1) {
                eliminarProducto(valor, productos, recursos, variedadRecursos, nombreRecursos, tiempo, cantidad);
            }
            break;
        case 4:
            calcularYVerificar(productos, recursos, variedadRecursos, nombreRecursos, tiempo, cantidad, MAXPRODUCTS);
            break;
        case 5:
            for (int i = 0; i < MAXPRODUCTS; i++) {
                if (productos[i][0] != '\0')
                    mostrarProducto(i, productos, recursos, variedadRecursos, nombreRecursos, tiempo, cantidad);
            }
            break;
        case 6:
            continuar = 1;
            printf("Saliendo.....\n");
            break;
        default:
            break;
        }
    } while (continuar == 0); 
    return 1;
}

int BuscarProdutcoEncontrado(char nombre[][LONGITUD]){
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
        repetir = leerNumeroEnteroEntre("Desea volver a intentar 1.si 2.No\n",2,0);
    }
    return -1;
}

int findProducto(char destino[],char nombreBuscado[]){
    if (strcmp(destino, nombreBuscado) == 0) {
        return 0;
    }else{
        return 1;
    }
}

void eliminarProducto(int NrProducto, char nombre[][LONGITUD], int recursos[][MAXRECURSOS], int variedadRecursos[], char nombreRecursos[][MAXRECURSOS][LONGITUD], float tiempo[], int cantidad[]) {
    if (NrProducto < 0 || NrProducto >= MAXPRODUCTS) {
        printf("Índice de producto inválido.\n");
        return;
    }
    // Mover los productos siguientes una posición hacia arriba
    for (int i = NrProducto; i < MAXPRODUCTS - 1; i++) {
        strcpy(nombre[i], nombre[i + 1]);
        cantidad[i] = cantidad[i + 1];
        tiempo[i] = tiempo[i + 1];
        variedadRecursos[i] = variedadRecursos[i + 1];
        for (int j = 0; j < MAXRECURSOS; j++) {
            recursos[i][j] = recursos[i + 1][j];
            strcpy(nombreRecursos[i][j], nombreRecursos[i + 1][j]);
        }
    }
    // Limpiar el último producto
    nombre[MAXPRODUCTS - 1][0] = '\0';
    cantidad[MAXPRODUCTS - 1] = 0;
    tiempo[MAXPRODUCTS - 1] = 0;
    variedadRecursos[MAXPRODUCTS - 1] = 0;
    for (int j = 0; j < MAXRECURSOS; j++) {
        recursos[MAXPRODUCTS - 1][j] = 0;
        nombreRecursos[MAXPRODUCTS - 1][j][0] = '\0';
    }
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

void calcularYVerificar(char productos[][LONGITUD], int recursos[][MAXRECURSOS], int variedadRecursos[], char nombreRecursos[][MAXRECURSOS][LONGITUD], float tiempo[], int cantidad[], int total_productos) {
    int cantidadFabricar, id;
    int maxRecursos[MAXRECURSOS];
    int maxTiempo;
    char nombreBuscado[LONGITUD];

    // Pedir el nombre del producto
    guardarPalabra("Ingrese el nombre del producto: ", nombreBuscado, LONGITUD);

    // Buscar el producto
    id = -1;
    for (int i = 0; i < total_productos; i++) {
        if (strcmp(productos[i], nombreBuscado) == 0) {
            id = i;
            break;
        }
    }
    if (id == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    // Mostrar el producto y su cantidad actual
    mostrarProducto(id, productos, recursos, variedadRecursos, nombreRecursos, tiempo, cantidad);

    // Pedir recursos disponibles para cada tipo de recurso
    for (int j = 0; j < variedadRecursos[id]; j++) {
        char mensaje[LONGITUD + 50];
        sprintf(mensaje, "Ingrese la cantidad disponible de %s: ", nombreRecursos[id][j]);
        maxRecursos[j] = leerNumeroEnteroEntre(mensaje, 10000, 1);
    }
    maxTiempo = leerNumeroEnteroEntre("Ingrese el tiempo disponible (en minutos): ", 10000, 1);

    // Calcular requerimientos
    int recursosNecesarios[MAXRECURSOS];
    int puede = 1;
    for (int j = 0; j < variedadRecursos[id]; j++) {
        recursosNecesarios[j] = cantidad[id] * recursos[id][j];
        printf(">> %s requerido: %d unidades\n", nombreRecursos[id][j], recursosNecesarios[j]);
        if (recursosNecesarios[j] > maxRecursos[j]) {
            puede = 0;
        }
    }
    float tiempoNecesario = cantidad[id] * tiempo[id];
    printf(">> Tiempo requerido: %.2f minutos\n", tiempoNecesario);

    if (tiempoNecesario <= maxTiempo && puede)
        printf("La fabrica puede cumplir con la demanda.\n");
    else
        printf("No es posible cumplir con la demanda.\n");
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
            esValido = 1;
            for (size_t i = 0; i < strlen(destino); i++) {
                if (isdigit(destino[i])) { // Si hay un número
                    printf("Error: No se permiten numeros. Intente de nuevo.\n");
                    esValido = 0;
                    break;
                }
            }
        }else {
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

void mostrarProducto(int i, char nombre[][LONGITUD], int recursos[][MAXRECURSOS], int variedadRecursos[], char nombreRecursos[][MAXRECURSOS][LONGITUD], float tiempo[], int cantidad[]) {
    printf("---------------------------------------------\n");
    printf("Producto: %d\n", i + 1);
    printf("Nombre: %s\n", nombre[i]);
    printf("Cantidad a fabricar: %d\n", cantidad[i]);
    printf("Recursos necesarios:\n");
    for (int j = 0; j < variedadRecursos[i]; j++) {
        printf("  - %s: %d unidades por producto\n", nombreRecursos[i][j], recursos[i][j]);
    }
    printf("Tiempo: %.2f minutos\n", tiempo[i]);
    printf("---------------------------------------------\n");
}

float leerNumeroFlotanteEntre(char *mensaje,int max,int min){
    float valor = 0;
    printf("%s",mensaje);
    while(scanf("%f",&valor) != 1 || valor > max ||valor < min)
    {
        printf("Dato mal ingresado\n");
        printf("%s",mensaje);
        while ((getchar()) != '\n'); 
    }
    while ((getchar()) != '\n');
    return valor;
}