#define MAXPRODUCTS 2
#define LONGITUD 100



int Menu(char productos[][LONGITUD],int recursos[],int tiempo[][3],int *maxRecursos,int *maxTiempo);
void guardarPalabra(char *mensaje, char destino[], int longitud); 
int leerNumeroEnteroEntre(char *mensaje,int max,int min);
void IngresoProducto(int valor,int Maxproducts,char producto[][LONGITUD],int recursos[MAXPRODUCTS],int tiempo[][3]);
int findProducto(char destino[],char nombreBuscado[]);
int BuscarProdutcoEncontrado(char nombre[][LONGITUD],int recursos[],int tiempo[][3]);
void mostrarProducto(int i,char nombre[][LONGITUD],int recursos[],int tiempo[][3]);
void eliminarProducto(int NrProducto, char nombre[][LONGITUD], int recursos[], int tiempo[][3]);
int buscarEspacioLibre(char producto[][LONGITUD]);
void crearProducto(int Cantidad,char nombre[],int recursos,int tiempo[3],int *maxRecursos,int *maxTiempo);