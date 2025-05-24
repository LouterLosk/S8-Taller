#include "funciones.h"
#include<stdio.h>
/*Una fábrica de componentes electrónicos necesita optimizar su producción para cumplir con la demanda de cinco productos distintos.
Cada producto tiene un tiempo de fabricación específico y requiere una cantidad fija de recursos. 
El equipo de ingeniería ha identificado que la línea de producción tiene limitaciones de tiempo y recursos que deben ser tomadas en cuenta.
Tiempo de fabricaccion 
cantidad de recursos
*/

int main()
{
    int maxRecursos = 0;
    int maxTiempo = 0;
    char productos[MAXPRODUCTS][LONGITUD];
    int recursos[MAXPRODUCTS];
    int tiempo[MAXPRODUCTS][3];
    maxRecursos = leerNumeroEnteroEntre("Ingrese la cantidad de recursos: ",10000,0);
    maxTiempo = leerNumeroEnteroEntre("Ingrese las horas de de produccion: ",10000,0);
    IngresoProducto(0,MAXPRODUCTS,productos,recursos,tiempo);
    Menu(productos,recursos,tiempo,&maxRecursos,&maxTiempo);
    return 0;
}
