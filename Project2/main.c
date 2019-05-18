// ISIS-1304 - FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - PROYECTO 2 - 201910
// EL PROYECTO DEBE SER DESARROLLADO EN GRUPOS DE A 3 PERSONAS MAXIMO
//
// DESARROLLADO POR:
// Daniel Galindo - 201813517
// Santiago Estupi��n - 201813414
// Jaime Torres - 201815481

#define _CRT_SECURE_NO_DEPRECATE 
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

// La representacion de la imagen
typedef struct img
{
	int ancho;
	int alto;
	unsigned char *informacion;
} Imagen;


// Funci�n que carga el bmp en la estructura Imagen
void cargarBMP24(Imagen * imagen, char * nomArchivoEntrada);

// Funci�n que guarda el contenido de la estructura imagen en un archivo binario
void guardarBMP24(Imagen * imagen, char * nomArchivoSalida);

//Funci�n que inserta un mensaje en la imagen usando n bits por Byte
void insertarMensaje(Imagen * img, unsigned char mensaje[], int n);

//Funci�n que lee un mensaje de una imagen dando la longitud del mensaje y el numero de bits por byte usados
void leerMensaje(Imagen * img, unsigned char msg[], int l, int n);

//Funci�n que saca n bits de una secuencia de caracteres a partir de una posici�n dada
unsigned char sacarNbits(unsigned char secuencia[], int bitpos, int n);

// Programa principal
// NO MODIFICAR
int main(int argc, char* argv[]) {

	Imagen *img = (Imagen *)malloc(sizeof(Imagen));
	char msg[10000] = "";
	char op, temp;
	int num, l, n;
	char nomArch[256] = "";

	printf("\nISIS-1304 - FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - PROYECTO 2\n");

	if (argc != 5)
	{
		printf("Se ingreso un numero incorrecto de argumentos (%d) o se ingresaron de forma erronea... :(\n", argc);
		system("pause");
		return -1;
	}

	strcat(nomArch, argv[1]); //Se concatena el nombre del archivo en su variable respectiva
	op = argv[2][0]; //Se extrae la opci�n a realizar
	sscanf(argv[3], "%d", &num); //Se formatea el n�mero de bits por Byte para leer o insertar

	if (op == 'w') {
		strcat(msg, argv[4]); //Se concatena la cadena a escribir en su variable, si se insertar� un mensaje
	}
	else if (op == 'r') {
		sscanf(argv[4], "%d", &l); //Se formatea en l la longitud a leer de caracteres, si se leer� un mensaje
	}
	else {
		printf("Se ingreso una opcion invalida para el programa... :(\n");
		system("pause");
		return -1;
	}

	printf("Se ingresaron los %d argumentos correctamente!\n", argc);

	// Cargar los datos
	cargarBMP24(img, nomArch);

	if (op == 'w') {
		printf("\nMODO INSERTAR MENSAJE\n\n");
		printf(" - Longitud mensaje: %d bytes\n", strlen(msg));
		//msg[strlen(msg)] = '\0';

		printf(" - Insertando mensaje . . .\n");
		insertarMensaje(img, msg, num);
		printf(" - Insertado correctamente!\n");

		strcat(nomArch, "generado.bmp");
		guardarBMP24(img, nomArch);

		printf(" - Mensaje insertado y guardado exitosamente en el archivo/ruta '%s'! :D\n\n", nomArch);
	}
	else if (op == 'r') {
		printf("\nMODO LEER MENSAJE\n\n");

		for (int i = 0; i < l; i++) {
			msg[i] = 0;
		}
		msg[l] = 0;

		leerMensaje(img, msg, l, num);

		printf(" - Mensaje obtenido exitosamente! El mensaje es:\n\n\t%s\n\n", msg);
	}

	system("pause");
	return 0;
}

/**
* Inserta un mensaje, de a n bits por componente de color, en la imagen apuntada por img
* par�metro img: Apuntador a una imagen en cuyos pixeles se almacenar� el mensaje.
* par�metro mensaje: Apuntador a una cadena de caracteres con el mensaje.
* par�metro n: Cantidad de bits del mensaje que se almacenar�n en cada componente de color de cada pixel. 0 < n <= 8.
*/
// DESARROLLAR EN ENSAMBLADOR, *NO* SE PUEDEN USAR NOMBRES SIMBOLICOS
void insertarMensaje(Imagen * img, unsigned char mensaje[], int n) {
	//int ancho = img->ancho; //Ancho en pixeles de la imagen
	//int alto = img->alto; //Alto en pixeles de la imagen
	//int numBytesAncho = ancho * 3; //Ancho en bytes de la imagen(pixel = RGB)
	//int numBytesAlto = alto * 3; //Ancho en bytes de la imagen(pixel = RGB)
	//int k = 7; //Posicion del bit en cada byte del mensaje (Es 7 porque se usara modulo para determinar tal posici�n)
	//int count = 0; //Byte actual del mensaje 
	//int length = 0; //Longitud del mensaje


	//while (mensaje[length] != '\0') //Se recorre el mensaje hasta que se acabe para determinar su longitud.
	//{
	//	length++;
	//}

	//for (int i = 0; i < numBytesAlto*numBytesAncho; i++) //Byte actual de la imagen.
	//{
	//	if (count >= length) //Si el byte actual del mensaje supera o es igual a su longitud, se acaba el ciclo, para evitar excepciones.
	//	{
	//		break;
	//	}
	//	img->informacion[i] = (img->informacion[i] >> n) << n; //Se eliminan los bits menos significativos mediante corrimientos.
	//	for (int j = 0; j < n; j++, k--) //Aqui se controla de a cuanto se agrupan los bits del mensaje dependiendo de n.
	//	{
	//		if (k < 0) //Si la posicion del bit en el byte del mensaje es menor a 0, k vuelve a 7 y se cambia de byte en el mensaje, porque ya se inserto todo el byte.
	//		{
	//			k = 7;
	//			count++;
	//		}
	//		if ((mensaje[count] & (1 << (k % 8))) != 0) //Se determina si el bit actual del mensaje es un 1 con AND. Si lo es, inserta el 1 en el byte de la imagen con un OR. Si no lo es, cambia de bit.
	//		{
	//			img->informacion[i] = (img->informacion[i] | 1 << (n - j - 1)); //n-j-1 determina que tanto se debe correr el 1 para ser insertado en el byte de la imagen, pues j me dice en que bit del grupo de tamanio n voy.
	//		}
	//	}
	//}
	
	__asm {

		sub esp, 32
		mov ebx, [ebp + 8]; ebx apunta a la imagen
		mov ecx, [ebx]; ecx apunta al ancho de la imagen
		mov edx, [ebx + 4]; edx apunta al alto de la imagen
		imul ecx, 3; multiplicar ancho por 3
		imul edx, 3; multiplicar alto por 3
		mov[ebp - 4], ecx; ancho * 3 queda en ebp - 4
		mov[ebp - 8], edx; alto * 3 queda en ebp - 8
		imul ecx, edx; multiplica ancho por alto
		mov[ebp - 4], ecx; guarda ancho*alto en ebp - 4
		mov eax, 0
		mov[ebp - 16], eax; asigna 0 a una variable llamada count
		mov[ebp - 20], eax; inicializa length en 0
		mov[ebp - 24], eax; inicializa i en 0
		mov[ebp - 28], eax; inicializa j en 0
		mov[ebp - 32], eax; inicializa ebp - 32 en 0
		mov eax, 7
		mov[ebp - 12], eax; asigna 7 a una variable llamada k
		mov edi, [ebp + 12]; edi apunta al inicio del mensaje
		mov eax, 0; limpia eax
		mov ecx, 0; limpia ecx, que antes tenis numBytesAlto*numBytesAncho

		while:	

			mov esi, [ebp - 20]; esi apunta a length, que esta inicializado en 0
			mov eax, 0
			mov al, [edi+esi]; recupera el char actual del parametro mensaje[]
			cmp al, 0; comparo char actual con caracter vacio, si es igual, termina while
			je finWhile; etiqueta para saltar a fin de while
			add [ebp - 20],1; incrementa length
			jmp while 
			
		finWhile:
		
		
		forExterno:

			mov ecx, [ebp - 24]; ecx apunta a i
			cmp ecx, [ebp - 4]; comparo i con bytesAlto*bytesAncho
			jge finForExterno

			mov ecx, [ebp - 16]; ecx apunta a count
			cmp ecx, [ebp-20]; compara count con length, si es mayor o igual, termina el ciclo
			jge finForExterno

			mov eax, 0; limpia eax
			mov edx, [ebx + 8]; guarda en edx el apuntador a informacion de la imagen que llega por parametro
			mov esi, [ebp - 24]; esi apunta a i
			mov al, [edx + esi]; guarda el char que esta en la posicion i del vector informacion de la imagen
			mov cl, [ebp + 16]; cl guarda n para hacer desplazamiento
			shr al, cl; corrimiento a char actual
			shl al, cl; corrimiento para dejar en cero los bits a cambiar
			mov [ebp - 32], al; guarda el apuntador a img->informacion[i] modificado en variable temporal ebp-32

			forInterno:

			mov esi, 0; limpiar esi por prevencion
			mov esi, [ebp - 28]; esi apunta a j
			cmp esi, [ebp + 16]; compara j con n
			jge sumarI
			jmp if1

			sumarI:
			add[ebp - 24], 1
			jmp forExterno

			if1:

			cmp[ebp - 12], 0; compara k con 0
			jg finIf1
			mov esi, 7; esi apunta a 7, para asignar k a 7 nuevamente
			mov[ebp - 12], esi; Si k es menor, k = 7
			add[ebp - 16], 1; Suma 1 a count
			mov esi, 0; limpia esi
		
			finIf1:


			mov esi, [ebp - 16]; esi apunta a count
			mov ax, [ebp - 12]; ax apunta a k
			push ebx; salvaguarda ebx, que apunta originalmente a la imagen parametro
			mov bh, 0x8; divisor es 8
			idiv bh; divido k entre 8 para sacar modulo que esta guardado en ah, en al esta el cociente que puede ser sobreescrito
			pop ebx; recupero ebx, que apuntaba a la imagen
			mov ecx, 0; limpia ecx por prevencion
			mov cl, ah; muevo el residuo de la division a cl
			mov al, 1; muevo 1 a al
			shl al, cl; muevo a la izquierda a lo que apunta al, el residuo de la division
			mov cl, [edi + esi]; cl apunta al char mensaje[count]
			and cl, al; hace and entre el char[mensaje] y el 1 << k % 8
			jz finForInterno

			mov cl, [ebp + 16]; ecx apunta a n
			mov al, [ebp - 28]; ax apunta a j
			sub cl, al; n - j
			sub cl, 1; n - j - 1
			mov ah, 1; ah contiene a 1
			shl ah, cl; desplazo los bits de 1 a la izquierda, lo que indique cl, que es n-j-1
			or [ebp - 32], ah; or entre img->informacion[i]
			jmp finForInterno

			finForInterno:
			; add[ebp - 24], 1; i++ como avanze de forExterno
			add[ebp - 28], 1; j++ como avanze de forInterno 
			sub[ebp - 12], 1; k-- como avanze de forInterno
			jmp forInterno
	
		finForExterno:
		add esp,32
		
	}
}

/**
* Extrae un mensaje de tamanio l, guardado de a n bits por componente de color, de la imagen apuntada por img
* par�metro img: Apuntador a una imagen que tiene almacenado el mensaje en sus pixeles.
* par�metro msg: Apuntador a una cadena de caracteres donde se depositar� el mensaje.
* par�metro l: Tamanio en bytes del mensaje almacenado en la imagen.
* par�metro n: Cantidad de bits del mensaje que se almacenan en cada componente de color de cada pixel. 0 < n <= 8.
*/
// DESARROLLAR EN ENSAMBLADOR, SE PUEDEN USAR NOMBRES SIMBOLICOS
void leerMensaje(Imagen * img, unsigned char msg[], int l, int n) {
	int primeraVez = 1;		//variable de referencia para el primer caso (es decir, cuando se empieza a sacar los primeros n bits de todo el arreglo de informaci�n
	int pos = 0;	//Contador de posiciones del arreglo informacion de img
	int totbits = 0;	//contador de cu�ntos bits se tienen de una letra
	int vtb = 0;	//Contador de cu�ntas letras se han le�do y a la par, es el �ndice donde se guardar� la letra completa en msg
	int faltan = 0;	//Contador de cu�ntos bits faltan
	unsigned char temp1;	//Variable donde se guardan los primeros n bits de la letra en las posiciones m�s significativas del char
	unsigned char tempAux;	//Variable que guardan los siguientes n bits de la letra
	unsigned char tempFalta;	//Variable que guarda los ultimos bits necesarios para completar la letra
	unsigned char tempResiduo;	//Variable que guarda los bits restantes (son menos que n) de cada unsigned char de informacion
	unsigned char letra;	//Char completo a guardar en msg

	__asm {

	}
	

	for (int pos = 0, pos_arr = 0; pos_arr < img->alto*img->ancho && pos < l * 8; pos_arr++)
		for (int k = n - 1; k >= 0 && pos < l * 8; k--, pos++)
			msg[pos / 8] = msg[pos / 8] | (((img->informacion[pos_arr] >> k) & 1) << (7 - (pos % 8)));

}

/**
* Extrae n bits a partir del bit que se encuentra en la posici�n bitpos en la secuencia de bytes que
* se pasan como par�metro
* par�metro secuencia: Apuntador a una secuencia de bytes.
* par�metro n: Cantidad de bits que se desea extraer. 0 < n <= 8.
* par�metro bitpos: Posici�n del bit desde donde se extraer�n los bits. 0 <= n < 8*longitud de la secuencia
* retorno: Los n bits solicitados almacenados en los bits menos significativos de un unsigned char
*/
// DESARROLLAR EN ENSAMBLADOR, SE PUEDEN USAR NOMBRES SIMBOLICOS
unsigned char sacarNbits(unsigned char secuencia[], int bitpos, int n) {
	// DESARROLLO OPCIONAL: Puede ser �til para el desarrollo de los procedimientos obligatorios.
	__asm {

	}
}

// Lee un archivo en formato BMP y lo almacena en la estructura img
// NO MODIFICAR
void cargarBMP24(Imagen * imagen, char * nomArchivoEntrada) {
	// bmpDataOffset almacena la posici�n inicial de los datos de la imagen. Las otras almacenan el alto y el ancho
	// en pixeles respectivamente
	int bmpDataOffset, bmpHeight, bmpWidth;
	int y;
	int x;
	int	residuo;

	FILE *bitmapFile;
	bitmapFile = fopen(nomArchivoEntrada, "rb");
	if (bitmapFile == NULL) {
		printf("No ha sido posible cargar el archivo: %s\n", nomArchivoEntrada);
		exit(-1);
	}

	fseek(bitmapFile, 10, SEEK_SET); // 10 es la posici�n del campo "Bitmap Data Offset" del bmp	
	fread(&bmpDataOffset, sizeof(int), 1, bitmapFile);

	fseek(bitmapFile, 18, SEEK_SET); // 18 es la posici�n del campo "height" del bmp
	fread(&bmpWidth, sizeof(int), 1, bitmapFile);
	bmpWidth = bmpWidth * 3;

	fseek(bitmapFile, 22, SEEK_SET); // 22 es la posici�n del campo "width" del bmp
	fread(&bmpHeight, sizeof(int), 1, bitmapFile);

	residuo = (4 - (bmpWidth) % 4) & 3; // Se debe calcular los bits residuales del bmp, que surjen al almacenar en palabras de 32 bits

	imagen->ancho = bmpWidth;
	imagen->alto = bmpHeight;
	imagen->informacion = (unsigned char *)calloc(bmpWidth * bmpHeight, sizeof(unsigned char));

	fseek(bitmapFile, bmpDataOffset, SEEK_SET); // Se ubica el puntero del archivo al comienzo de los datos

	for (y = 0; y < bmpHeight; y++) {
		for (x = 0; x < bmpWidth; x++) {
			int pos = y * bmpWidth + x;
			fread(&imagen->informacion[pos], sizeof(unsigned char), 1, bitmapFile);
		}
		fseek(bitmapFile, residuo, SEEK_CUR); // Se omite el residuo en los datos
	}
	fclose(bitmapFile);
}

// Esta funci�n se encarga de guardar una estructura de Imagen con formato de 24 bits (formato destino) en un archivo binario
// con formato BMP de Windows.
// NO MODIFICAR
void guardarBMP24(Imagen * imagen, char * nomArchivoSalida) {
	unsigned char bfType[2];
	unsigned int bfSize, bfReserved, bfOffBits, biSize, biWidth, biHeight, biCompression, biSizeImage, biXPelsPerMeter, biYPelsPerMeter, biClrUsed, biClrImportant;
	unsigned short biPlanes, biBitCount;
	FILE * archivoSalida;
	int y, x;
	int relleno = 0;

	int residuo = (4 - (imagen->ancho) % 4) & 3; // Se debe calcular los bits residuales del bmp, que quedan al forzar en palabras de 32 bits


	bfType[2];       // Tipo de Bitmap
	bfType[0] = 'B';
	bfType[1] = 'M';
	bfSize = 54 + imagen->alto * ((imagen->ancho) / 3) * sizeof(unsigned char);       // Tamanio total del archivo en bytes
	bfReserved = 0;   // Reservado para uso no especificados
	bfOffBits = 54;    // Tamanio total del encabezado
	biSize = 40;      // Tamanio del encabezado de informacion del bitmap	
	biWidth = (imagen->ancho) / 3;     // Ancho en pixeles del bitmap	
	biHeight = imagen->alto;    // Alto en pixeles del bitmap	
	biPlanes = 1;    // Numero de planos	
	biBitCount = 24;  // Bits por pixel (1,4,8,16,24 or 32)	
	biCompression = 0;   // Tipo de compresion
	biSizeImage = imagen->alto * imagen->ancho;   // Tamanio de la imagen (sin ecabezado) en bits
	biXPelsPerMeter = 2835; // Resolucion del display objetivo en coordenada x
	biYPelsPerMeter = 2835; // Resolucion del display objetivo en coordenada y
	biClrUsed = 0;       // Numero de colores usados (solo para bitmaps con paleta)	
	biClrImportant = 0;  // Numero de colores importantes (solo para bitmaps con paleta)	

	archivoSalida = fopen(nomArchivoSalida, "w+b"); // Archivo donde se va a escribir el bitmap
	if (archivoSalida == 0) {
		printf("No ha sido posible crear el archivo: %s\n", nomArchivoSalida);
		exit(-1);
	}

	fwrite(bfType, sizeof(char), 2, archivoSalida); // Se debe escribir todo el encabezado en el archivo. En total 54 bytes.
	fwrite(&bfSize, sizeof(int), 1, archivoSalida);
	fwrite(&bfReserved, sizeof(int), 1, archivoSalida);
	fwrite(&bfOffBits, sizeof(int), 1, archivoSalida);
	fwrite(&biSize, sizeof(int), 1, archivoSalida);
	fwrite(&biWidth, sizeof(int), 1, archivoSalida);
	fwrite(&biHeight, sizeof(int), 1, archivoSalida);
	fwrite(&biPlanes, sizeof(short), 1, archivoSalida);
	fwrite(&biBitCount, sizeof(short), 1, archivoSalida);
	fwrite(&biCompression, sizeof(int), 1, archivoSalida);
	fwrite(&biSizeImage, sizeof(int), 1, archivoSalida);
	fwrite(&biXPelsPerMeter, sizeof(int), 1, archivoSalida);
	fwrite(&biYPelsPerMeter, sizeof(int), 1, archivoSalida);
	fwrite(&biClrUsed, sizeof(int), 1, archivoSalida);
	fwrite(&biClrImportant, sizeof(int), 1, archivoSalida);

	// Se escriben en el archivo los datos RGB de la imagen.
	for (y = 0; y < imagen->alto; y++) {
		for (x = 0; x < imagen->ancho; x++) {
			int pos = y * imagen->ancho + x;
			fwrite(&imagen->informacion[pos], sizeof(unsigned char), 1, archivoSalida);
		}
		fwrite(&relleno, sizeof(unsigned char), residuo, archivoSalida);
	}
	fclose(archivoSalida);
}