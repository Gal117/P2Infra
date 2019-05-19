// ISIS-1304 - FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - PROYECTO 2 - 201910
// EL PROYECTO DEBE SER DESARROLLADO EN GRUPOS DE A 3 PERSONAS MAXIMO
//
// DESARROLLADO POR:
// Daniel Galindo - 201813517
// Santiago Estupiñán - 201813414
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


// Función que carga el bmp en la estructura Imagen
void cargarBMP24(Imagen * imagen, char * nomArchivoEntrada);

// Función que guarda el contenido de la estructura imagen en un archivo binario
void guardarBMP24(Imagen * imagen, char * nomArchivoSalida);

//Función que inserta un mensaje en la imagen usando n bits por Byte
void insertarMensaje(Imagen * img, unsigned char mensaje[], int n);

//Función que lee un mensaje de una imagen dando la longitud del mensaje y el numero de bits por byte usados
void leerMensaje(Imagen * img, unsigned char msg[], int l, int n);

//Función que saca n bits de una secuencia de caracteres a partir de una posición dada
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
	op = argv[2][0]; //Se extrae la opción a realizar
	sscanf(argv[3], "%d", &num); //Se formatea el número de bits por Byte para leer o insertar

	if (op == 'w') {
		strcat(msg, argv[4]); //Se concatena la cadena a escribir en su variable, si se insertará un mensaje
	}
	else if (op == 'r') {
		sscanf(argv[4], "%d", &l); //Se formatea en l la longitud a leer de caracteres, si se leerá un mensaje
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
* parámetro img: Apuntador a una imagen en cuyos pixeles se almacenará el mensaje.
* parámetro mensaje: Apuntador a una cadena de caracteres con el mensaje.
* parámetro n: Cantidad de bits del mensaje que se almacenarán en cada componente de color de cada pixel. 0 < n <= 8.
*/
// DESARROLLAR EN ENSAMBLADOR, *NO* SE PUEDEN USAR NOMBRES SIMBOLICOS

void insertarMensaje(Imagen * img, unsigned char mensaje[], int n) {

	//int ancho = img->ancho; //Ancho en pixeles de la imagen
	//int alto = img->alto; //Alto en pixeles de la imagen
	//int numBytesAncho = ancho * 3; //Ancho en bytes de la imagen(pixel = RGB)
	//int numBytesAlto = alto * 3; //Ancho en bytes de la imagen(pixel = RGB)
	//int k = 7; //Posicion del bit en cada byte del mensaje (Es 7 porque se usara modulo para determinar tal posición)
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
			cmp ecx, [ebp-4]; comparo i con el tamanio de la imagen

			jge finForExterno

			mov ecx, [ebp - 16]; ecx apunta a count
			cmp ecx, [ebp-20]; compara count con length, si es mayor o igual, termina el ciclo
			jge finForExterno

			mov eax, 0; limpia eax
			mov edx, [ebx + 8]; guarda en edx el apuntador a informacion de la imagen que llega por parametro
			mov esi, [ebp - 24]; esi apunta a i
			mov al, [edx + esi]; guarda el char que esta en la posicion i del vector informacion de la imagen img->informacion[i]
			mov cl, [ebp + 16]; cl guarda n para hacer desplazamiento
			shr al, cl; corrimiento a char img->informacion[i]
			shl al, cl; corrimiento para dejar en cero los bits a cambiar
			mov [edx+esi], al; guarda img->informacion[i] de vuelta en la imagen, pero con el corrimiento aplicado
			mov [ebp - 32], al; guarda el apuntador a img->informacion[i] modificado en variable temporal ebp-32
			mov eax, 0; asigna 0 a eax
			mov [ebp -28],eax; j = 0 para empezar for interno
			
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
			jge finIf1
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
			cmp cl, 0; compara el resultado del and con 0
			jz finForInterno

			mov cl, [ebp + 16]; ecx apunta a n
			mov al, [ebp - 28]; al apunta a j
			sub cl, al; n - j
			sub cl, 1; n - j - 1
			mov ah, 1; ah contiene a 1
			shl ah, cl; desplazo los bits de 1 a la izquierda, lo que indique cl, que es n-j-1
			or [ebp - 32], ah; or entre img->informacion[i] y 1 << (n - j - 1)
			mov eax, 0; limpia eax
			mov ah,[ebp-32]; ah apunta a la variable local destinada a guardar img->informacion[i]
			mov ecx, [ebp-24]; ecx apunta a i
			mov edx, 0; limpia edx
			mov edx, [ebx + 8]; edx apunta a img->informacion
			mov [edx+ecx],ah; img->informacion[i] queda modificado después de haber sido aplicado el or
			mov eax, [edx+ecx]
			jmp finForInterno

			finForInterno:
			add[ebp - 28], 1; j++ como avanze de forInterno 
			sub[ebp - 12], 1; k-- como avanze de forInterno
			jmp forInterno
	
		finForExterno:
		add esp,32
		
	}
}

/**
* Extrae un mensaje de tamanio l, guardado de a n bits por componente de color, de la imagen apuntada por img
* parámetro img: Apuntador a una imagen que tiene almacenado el mensaje en sus pixeles.
* parámetro msg: Apuntador a una cadena de caracteres donde se depositará el mensaje.
* parámetro l: Tamanio en bytes del mensaje almacenado en la imagen.
* parámetro n: Cantidad de bits del mensaje que se almacenan en cada componente de color de cada pixel. 0 < n <= 8.
*/
// DESARROLLAR EN ENSAMBLADOR, SE PUEDEN USAR NOMBRES SIMBOLICOS
void leerMensaje(Imagen * img, unsigned char msg[], int l, int n) {
	
	int pos_arr = 0;
	int anchoAlto = img->alto * img->ancho;
	int posMensaje = 0;
	int k = 0;
	int o = 8; 
	int pos = 0;
	unsigned char *apuntador = img->informacion;
	unsigned char *mensaje = msg;
	int comp = l * 8;
	__asm {

		forExterno:

		mov eax, pos_arr; eax apuna a pos_arr
		cmp eax, anchoAlto; compara pos_arr con anchoAlto
		jge finForExterno

		mov eax, pos; eax apunta a pos
		cmp eax, comp; compara eax con comp
		jge finForExterno

		mov eax, n; eax apunta a n
		sub eax, 1; hago n - 1
		mov k, eax; k es igual a n - 1

		
			forInterno:

			mov eax, k; eax apunta a k
			cmp eax, 0; compara a k con 0
			jl sumarForExterno

			mov eax, pos; eax apunta a pos
			cmp eax, comp; compara pos con comp
			jge sumarForExterno
			jmp proceso

			sumarForExterno:
				add pos_arr,1
				jmp forExterno

			proceso:

			mov eax, k; eax apunta a k
			mov[ebp - 4], eax; asigna k en ebp - 4
			mov eax, 0; limpia eax
			mov ebx, pos_arr; ebx apunta a pos_arr
			mov ecx, [apuntador + ebx]; guarda en ecx la direccion del char en img->informacion[pos_arr]
			mov al, [ecx];  guarda en al el char img->informacion[pos_arr]
			
			mov cl, [ebp - 4]; cl guarda k, ue es para desplazar el char en al k veces
			shr al, cl; desplaza char al, cl veces`(img->informacion[pos_arr] >> k)
			and al, 1; ((img->informacion[pos_arr] >> k) & 1)

			push al; guarda eax
			mov eax, pos; eax apunta a pos
			mov ebx, o; ebx apunta a o
			cdq; permite division
			idiv ebx; eax / ebx es decir pos / 8 eax guarda cociente y edx guarda residuo
			mov[ebp - 16], eax; en ebp - 16 queda pos / 8
			mov ecx, 7; esi guarda 7
			sub ecx, edx; 7 - pos % 8
			mov[ebp - 8], ecx; en ebp - 8 queda(7 - pos % 8)
			mov cl, [ebp - 8]; cl guarda  7 - pos % 8
			pop al; recupera al

			shl al, cl; (((img->informacion[pos_arr] >> k) & 1) << (7 - (pos % 8)))
			mov[ebp - 12], al; en ebp - 12 queda(((img->informacion[pos_arr] >> k) & 1) << (7 - (pos % 8)))
			mov eax, [ebp - 16]; eax apunta a pos / 8
			mov ecx, [mensaje + eax]; ecx guarda direccion de char en msg[pos / 8]
			mov edx, 0
			mov dl, [ecx]; dl guarda el char msg[pos / 8]
			or dl, [ebp - 12]; dl guarda msg[pos / 8] | (((img->informacion[pos_arr] >> k) & 1) << (7 - (pos % 8)))
			mov [ecx], dl; en msg[pos/8] queda el char modificado
			jmp finForInterno

			finForInterno:

				sub k, 1
				add pos, 1
				jmp forInterno

		finForExterno:
	}

	/*for (int pos = 0, pos_arr = 0; pos_arr < img->alto*img->ancho && pos < l * 8; pos_arr++)
		for (int k = n - 1; k >= 0 && pos < l * 8; k--, pos++)
			msg[pos / 8] = msg[pos / 8] | (((img->informacion[pos_arr] >> k) & 1) << (7 - (pos % 8)));
*/
}

/**
* Extrae n bits a partir del bit que se encuentra en la posición bitpos en la secuencia de bytes que
* se pasan como parámetro
* parámetro secuencia: Apuntador a una secuencia de bytes.
* parámetro n: Cantidad de bits que se desea extraer. 0 < n <= 8.
* parámetro bitpos: Posición del bit desde donde se extraerán los bits. 0 <= n < 8*longitud de la secuencia
* retorno: Los n bits solicitados almacenados en los bits menos significativos de un unsigned char
*/
// DESARROLLAR EN ENSAMBLADOR, SE PUEDEN USAR NOMBRES SIMBOLICOS
unsigned char sacarNbits(unsigned char secuencia[], int bitpos, int n) {
	// DESARROLLO OPCIONAL: Puede ser útil para el desarrollo de los procedimientos obligatorios.
	__asm {

	}
}

// Lee un archivo en formato BMP y lo almacena en la estructura img
// NO MODIFICAR
void cargarBMP24(Imagen * imagen, char * nomArchivoEntrada) {
	// bmpDataOffset almacena la posición inicial de los datos de la imagen. Las otras almacenan el alto y el ancho
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

	fseek(bitmapFile, 10, SEEK_SET); // 10 es la posición del campo "Bitmap Data Offset" del bmp	
	fread(&bmpDataOffset, sizeof(int), 1, bitmapFile);

	fseek(bitmapFile, 18, SEEK_SET); // 18 es la posición del campo "height" del bmp
	fread(&bmpWidth, sizeof(int), 1, bitmapFile);
	bmpWidth = bmpWidth * 3;

	fseek(bitmapFile, 22, SEEK_SET); // 22 es la posición del campo "width" del bmp
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

// Esta función se encarga de guardar una estructura de Imagen con formato de 24 bits (formato destino) en un archivo binario
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