#define MAXPRODUCTS 1
#define LONGITUD 100
#define RECURSOSINI 1000


int Menu(char productos[][LONGITUD],int recursos[],int tiempo[][3],int *maxRecursos);
void convertirMinusculas(char *cadena);
void guardarPalabra(char *mensaje, char destino[], int longitud); 
int VerificarNoNumero(char destino[]);
int leerNumeroEnteroEntre(char *mensaje,int max,int min);
void Eleccion(int eleccion,int *continuar,char producto[][LONGITUD],int recursos[],int tiempo[][3],int *maxRecursos);
void IngresoProducto(int valor,char producto[][LONGITUD],int recursos[MAXPRODUCTS],int tiempo[][3]);
int findProducto(char destino[],char nombreBuscado[]);
int BuscarProdutcoEncontrado(char nombre[][LONGITUD],int recursos[],int tiempo[][3]);
void mostrarProducto(int i,char nombre[][LONGITUD],int recursos[],int tiempo[][3]);
void eliminarProducto(int NrProducto, char nombre[][LONGITUD], int recursos[], int tiempo[][3]);
int buscarEspacioLibre(char producto[][LONGITUD]);
void crearProducto(int Cantidad,char nombre[],int recursos,int tiempo[3],int *maxRecursos);