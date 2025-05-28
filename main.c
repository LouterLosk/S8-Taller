#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*Una fábrica de componentes electrónicos necesita optimizar su producción para cumplir con la demanda de cinco productos distintos.
Cada producto tiene un tiempo de fabricación específico y requiere una cantidad fija de recursos. 
El equipo de ingeniería ha identificado que la línea de producción tiene limitaciones de tiempo y recursos que deben ser tomadas en cuenta.
Tiempo de fabricaccion 
cantidad de recursos

Miembros Ethan Flores Isaac Vasquez Miguel Ruales
*/
#define MAXPRODUCTS 5
#define LONGITUD 100

int Menu(char productos[][LONGITUD], int recursos[], float tiempo[], int cantidad[]);
void guardarPalabra(char *mensaje, char destino[], int longitud); 
int leerNumeroEnteroEntre(char *mensaje,int max,int min);
void IngresoProducto(char producto[][LONGITUD], int recursos[], float tiempo[], int cantidad[], int desde, int hasta) ;
int findProducto(char destino[],char nombreBuscado[]);
int BuscarProdutcoEncontrado(char nombre[][LONGITUD]);
void mostrarProducto(int i, char nombre[][LONGITUD], int recursos[], float tiempo[], int cantidad[]);
void eliminarProducto(int NrProducto, char nombre[][LONGITUD], int recursos[], float tiempo[],int cantidad[]);
int buscarEspacioLibre(char producto[][LONGITUD]);
void calcularYVerificar(char productos[][LONGITUD], int recursos[], float tiempo[], int cantidad[], int total_productos);
float leerNumeroFlotanteEntre(char *mensaje,int max,int min);

int main(){
    char productos[MAXPRODUCTS][LONGITUD] = {0};
    int recursos[1000];
    float tiempo[MAXPRODUCTS];
    int cantidad[MAXPRODUCTS] = {0};
    Menu(productos, recursos, tiempo, cantidad);
    return 0;
}

void IngresoProducto(char producto[][LONGITUD], int recursos[], float tiempo[], int cantidad[], int desde, int hasta) {
    for (int i = desde; i < hasta && i < MAXPRODUCTS; i++) {
        printf("---------------------------------------------\n");
        printf("Producto %d\n", i + 1);
        guardarPalabra("Ingrese el nombre: ", producto[i], LONGITUD);
        recursos[i] = leerNumeroEnteroEntre("Ingrese la cantidad necesaria de recursos: ", 1000, 1);
        cantidad[i] = leerNumeroEnteroEntre("Ingrese la demanda de este producto: ", 1000, 1);
        printf("Tiempo de fabricacion\n");
        tiempo[i] = leerNumeroFlotanteEntre("Ingrese la cantidad necesaria de tiempo(minutos): ", 10000, 1);
        if (tiempo[i] == 0) {
            printf("Debe ingresar un valor\n");
        }
        printf("---------------------------------------------\n");
    }
}

int Menu(char productos[][LONGITUD], int recursos[], float tiempo[], int cantidad[]){
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
                IngresoProducto(productos, recursos, tiempo, cantidad, valor, hasta);
            } else {
                printf("No se puede agregar mas productos\n");
            }
        break;
        case 2: 
            valor = BuscarProdutcoEncontrado(productos);
            if (valor != -1) {
                mostrarProducto(valor, productos, recursos, tiempo,cantidad);
                printf("Editar el producto:\n");
                IngresoProducto(productos, recursos, tiempo,cantidad, valor, valor + 1);
            }
        break;
        case 3 : eliminarProducto(valor,productos,recursos,tiempo,cantidad);
            break;
        case 4 : calcularYVerificar(productos, recursos, tiempo, cantidad, MAXPRODUCTS);
            break;
        case 5 :
            for (int i = 0; i < MAXPRODUCTS; i++)
            {
                mostrarProducto(i,productos,recursos,tiempo,cantidad);
            }
            break;
        case 6 :
            continuar = 1;
            printf("Saliendo.....");
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
    }
}

int findProducto(char destino[],char nombreBuscado[]){
        if (strcmp(destino, nombreBuscado) == 0) {
            return 0;
        }else{
            return 1;
        }
    }

void eliminarProducto(int NrProducto, char nombre[][LONGITUD], int recursos[], float tiempo[],int cantidad[]) {
    printf("Eliminar el producto:\n");
    int valor;
        valor = BuscarProdutcoEncontrado(nombre);
        mostrarProducto(valor,nombre,recursos,tiempo,cantidad);

    if (NrProducto < 0 || NrProducto >= MAXPRODUCTS) {
        printf("Índice de producto inválido.\n");
        return;
    }
    // Mover los productos siguientes una posición hacia arriba
    for (int i = valor; i < MAXPRODUCTS - 1; i++) {
        strcpy(nombre[i], nombre[i + 1]);
        recursos[i] = recursos[i + 1];
        tiempo[i] = tiempo[i + 1];
    }
    // Limpiar el último producto
    nombre[MAXPRODUCTS - 1][0] = '\0';
    recursos[MAXPRODUCTS - 1] = 0;
    tiempo[MAXPRODUCTS - 1] = 0;
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

void calcularYVerificar(char productos[][LONGITUD], int recursos[], float tiempo[], int cantidad[], int total_productos) {
    int cantidadFabricar, idx;
    int maxRecursos, maxTiempo;
    char nombreBuscado[LONGITUD];

    // Pedir recursos y tiempo disponibles
    maxRecursos = leerNumeroEnteroEntre("Ingrese la cantidad de recursos disponibles: ", 10000, 1);
    maxTiempo = leerNumeroEnteroEntre("Ingrese el tiempo disponible (en minutos): ", 10000, 1);

    // Pedir el nombre del producto
    guardarPalabra("Ingrese el nombre del producto: ", nombreBuscado, LONGITUD);

    // Buscar el producto
    idx = -1;
    for (int i = 0; i < total_productos; i++) {
        if (strcmp(productos[i], nombreBuscado) == 0) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    // Mostrar el producto y su cantidad actual
    mostrarProducto(idx, productos, recursos, tiempo, cantidad);

    // Calcular requerimientos
    int recursosNecesarios = cantidad[idx] * recursos[idx];
    float tiempoNecesario = cantidad[idx] * tiempo[idx];

    printf("\n>> Tiempo requerido: %.2f minutos\n", tiempoNecesario);
    printf(">> Recursos requeridos: %d unidades\n", recursosNecesarios);

    if (tiempoNecesario <= maxTiempo && recursosNecesarios <= maxRecursos)
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

void mostrarProducto(int i, char nombre[][LONGITUD],int recursos[], float tiempo[],int cantidad[]) {
    printf("---------------------------------------------\n");
    printf("Producto: %d\n", i + 1);
    printf("Nombre: %s\n", nombre[i]);
    printf("Recursos: %d\n", recursos[i]);
    printf("Cantidad: %d\n", cantidad[i]);
    printf("Tiempo: %.2f\n", tiempo[i]);
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