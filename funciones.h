
#define MAXPRODUCTS 5
#define MAXRECURSOS 5
#define LONGITUD 100

int Menu(char productos[][LONGITUD], int recursos[][MAXRECURSOS], int variedadRecursos[], char nombreRecursos[][MAXRECURSOS][LONGITUD], float tiempo[], int cantidad[]);
void guardarPalabra(char *mensaje, char destino[], int longitud); 
int leerNumeroEnteroEntre(char *mensaje,int max,int min);
void IngresoProducto(char producto[][LONGITUD], int recursos[][MAXRECURSOS], int variedadRecursos[], char nombreRecursos[][MAXRECURSOS][LONGITUD], float tiempo[], int cantidad[], int desde, int hasta);
int findProducto(char destino[],char nombreBuscado[]);
int BuscarProdutcoEncontrado(char nombre[][LONGITUD]);
void mostrarProducto(int i, char nombre[][LONGITUD], int recursos[][MAXRECURSOS], int variedadRecursos[], char nombreRecursos[][MAXRECURSOS][LONGITUD], float tiempo[], int cantidad[]);
void eliminarProducto(int NrProducto, char nombre[][LONGITUD], int recursos[][MAXRECURSOS], int variedadRecursos[], char nombreRecursos[][MAXRECURSOS][LONGITUD], float tiempo[], int cantidad[]);
int buscarEspacioLibre(char producto[][LONGITUD]);
void calcularYVerificar(char productos[][LONGITUD], int recursos[][MAXRECURSOS], int variedadRecursos[], char nombreRecursos[][MAXRECURSOS][LONGITUD], float tiempo[], int cantidad[], int total_productos);
float leerNumeroFlotanteEntre(char *mensaje,int max,int min);