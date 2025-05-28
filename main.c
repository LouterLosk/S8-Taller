#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"
/*Una fábrica de componentes electrónicos necesita optimizar su producción para cumplir con la demanda de cinco productos distintos.
Cada producto tiene un tiempo de fabricación específico y requiere una cantidad fija de recursos. 
El equipo de ingeniería ha identificado que la línea de producción tiene limitaciones de tiempo y recursos que deben ser tomadas en cuenta.
Tiempo de fabricaccion 
cantidad de recursos

Miembros Ethan Flores Isaac Vasquez Miguel Ruales
*/

int main(){
    char productos[MAXPRODUCTS][LONGITUD] = {0};
    int recursos[MAXPRODUCTS][MAXRECURSOS] = {0};
    int variedadRecursos[MAXPRODUCTS] = {0};
    char nombreRecursos[MAXPRODUCTS][MAXRECURSOS][LONGITUD] = {0};
    float tiempo[MAXPRODUCTS] = {0};
    int cantidad[MAXPRODUCTS] = {0};
    Menu(productos, recursos, variedadRecursos, nombreRecursos, tiempo, cantidad);
    return 0;
}
