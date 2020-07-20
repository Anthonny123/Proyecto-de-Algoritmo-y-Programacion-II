#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct infraccion{
	int nroInfraccion;
	int fechaDeInfrccion;
	char tipoDeInfraccion[];
	int montoDeLaMulta;
	int pagado;
};

struct vehiculo{
	char placa[8];
	char marca[15];
	char modelo[15];
	int year;
	char color[10];
	struct infraccion *misInfracciones;
	struct vehiculo *sigVehiculo;
};

struct personas{
	int cedula;
	char nombre[20];
	int fechaDeNacimiento;
	char sexo;
	int edad;
	char direccion[40];
	struct vehiculo *misVehiculos;
};

void menu();

int comprobarSiExisteFichero(){
	FILE *t;
	if((t = fopen("Registro.txt", "r"))!= NULL){//Compruebo si el fichero esta creado
		fclose(t);//Cierro el archivo para que no se produzca algun error
		return 1;
	}
	return 0;
}


void mostrarVehiculos(struct vehiculo *v){
	vehiculo *veh = v;
	while(veh){
		printf("----------------------------------------\n");
		printf("Placa del Vehiculo: %s\n", veh->placa);
		printf("Marca del Vehiculo: %s\n", veh->marca);
		printf("Modelo del Vehiculo: %s\n", veh->modelo);
		printf("Año del Vehiculo: %i\n", veh->year);
		printf("Placa del Vehiculo: %s\n", veh->color);	
		printf("----------------------------------------");
		veh = veh->sigVehiculo;
	}
}

void mostrarInfo(struct personas p){//Mostramos la informacion del usuario
	printf("----------------------------\n");
	printf("Nombre: %s\n", p.nombre);
	printf("Cedula: %i\n", p.cedula);
	printf("Direccion: %s\n", p.direccion);
	printf("Fecha De Nacimiento: %i\n", p.fechaDeNacimiento);
	printf("Sexo: %c\n", p.sexo);
	if(p.misVehiculos == NULL){
		printf("Esta persona no posee vehiculos registrados\n");
	}else{
		mostrarVehiculos(p.misVehiculos);
	}
	printf("----------------------------\n");
}

void mostrarUsers(){//funcion para mostrar todos los usuarios que tengo almacenado en el registro
	FILE *pFile;
	personas p;
	if((pFile = fopen("Registro.txt", "r"))==NULL){//Compruebo si hay un archivo llamado registro, si no lo esta entonces muestra mensae de error
		printf("No existe ningun Fichero creado");
		system("pause");
	}else{
		fread(&p, sizeof(p), 1, pFile);//Busco la direccion de memoria de la lista que se encuentra en el registro
		while(!feof(pFile)){//mientras no sea fin de archivo no dejes de ejecutar el bucle
			mostrarInfo(p);//Llamo a la funcion, mostrar Info
			fread(&p, sizeof(p), 1, pFile);//lee lo que se encuentra en la direccion de memoria del fichero
		}
	}
	fclose(pFile);}

void aggUser(){//Funcion para agg a un usuario al registro si esta ya esta creado, si no lo esta, entonces crea el registro y agg al usuario
	FILE *pFile;
	personas p;
	if(comprobarSiExisteFichero == 0){//Si no esta creado, crea el fichero y guarda la lista
		pFile = fopen("Registro.txt", "w");//abro archivo de escritura
		fflush(stdin);//Limpio el buffer de input para que no ocurra algun error al insertar un char
		printf("Ingrese el Nombre del usuario\n");
		gets(p.nombre);fflush(stdin);//tomo lo que esta en el input y se almacena en la casilla de nombre de la lista y limpio el buffer del input nuevamente
		printf("Ingrese el numero de cedula de %s\n", p.nombre);
		scanf("%i", &p.cedula); fflush(stdin);//Tomo el integer y lo almaceno en la casilla de cedula de la lista
		printf("Ingrese la direccion donde reside %s\n", p.nombre);
		gets(p.direccion); fflush(stdin);
		printf("Ingrese la fecha de nacimiento de %s\n", p.nombre);
		scanf("%i", &p.fechaDeNacimiento); fflush(stdin);
		printf("Ingrese el sexo de %s (M/F)\n", p.nombre);
		scanf("%i", &p.sexo); fflush(stdin);
		p.misVehiculos = NULL;
		fwrite(&p,sizeof(p),1,pFile);//escribe en la direccion de la lista los datos insertados y lo guarda en el registro
		fclose(pFile);//cierro el registro para no ocasionar errores
	}else{
		pFile = fopen("Registro.txt","a");//Si esta creado entonces colocate al final del archivo y agg al nuevo usuario
		fflush(stdin);
		printf("Ingrese el Nombre del usuario\n");
		gets(p.nombre);fflush(stdin);
		printf("Ingrese el numero de cedula de %s\n", p.nombre);
		scanf("%i", &p.cedula); fflush(stdin);
		printf("Ingrese la direccion donde reside %s\n", p.nombre);
		gets(p.direccion); fflush(stdin);
		printf("Ingrese la fecha de nacimiento de %s\n", p.nombre);
		scanf("%i", &p.fechaDeNacimiento); fflush(stdin);
		printf("Ingrese el sexo de %s (M/F)\n", p.nombre);
		scanf("%c", &p.sexo); fflush(stdin);
		p.misVehiculos = NULL;
		fwrite(&p,sizeof(p),1,pFile);//escribe en la direccion de la lista los datos insertados y lo guarda en el registro
		fclose(pFile);//cierro el registro para no ocasionar errores
	}
}

void buscarUser(){
	FILE *pFile;
	personas p;
	fflush(stdin);
	int x;
	printf("Coloca el nro de Cedula de la persona que deseas buscar\n");
	scanf("%i",&x);
	if((pFile = fopen("Registro.txt", "r"))==NULL){//Si no se encuentra el archivo entonces muestra mensaje de error
		printf("No puede hacer la busqueda si no existe un archivo creado anteriormente");
		system("pause");
	}else{
		fread(&p,sizeof(p),1,pFile);//lee lo que se encuentra en la direccion de memoria del fichero
		while(!feof(pFile)){//Mientras no llegue al final del archivo no dejes de ejecutar el bucle
			if(p.cedula == x){//Comparamos si la cedula insertada coincide con alguna de las cedulas de las personas ingresadas en el registro
				mostrarInfo(p);//Muestro la informacion del usaurio
			}
			fread(&p,sizeof(p),1,pFile);//Lee cada uno de los usuarios registrados a medida que se ejecuta el bucle
		}
	}
	fclose(pFile);//cierro el programa para no ocasionar problemas
	system("pause");
}

struct vehiculo *agregarUnVehiculo(struct personas *p){
	struct vehiculo *v = NULL;
	printf("Marca\n");
	gets(v->marca); fflush(stdin);
	printf("Modelo\n");
	gets(v->modelo); fflush(stdin);
	printf("Placa\n");
	gets(v->placa); fflush(stdin);
	v->sigVehiculo = NULL;
	p->misVehiculos = v;
}

void registrarVehiculo(){
	FILE *pFile;
	FILE *pFileCopy;
	personas p;
	int encontrado = 0;
	int x;
	printf("Coloca el nro de Cedula de la persona que deseas buscar\n");
	scanf("%i",&x);
	pFile = fopen("Registro.txt", "r");
	pFileCopy = fopen("Temp.txt", "w");
	if(pFile==NULL){
		printf("Error");
		system("pause");
		return;
	}else{
		fread(&p,sizeof(p),1,pFile);
		while(!feof(pFile)){
			if(p.cedula == x){
				encontrado = 1;
				vehiculo *v = new vehiculo;
				fflush(stdin);
				printf("Ingrese la placa del vehiculo (Maximo 8 caracteres)\n");
				gets(v->placa);fflush(stdin);
				printf("Ingrese la marca del vehiculo\n");
				gets(v->marca);fflush(stdin);
				printf("Ingrese el modelo del vehiculo\n");
				gets(v->modelo);fflush(stdin);
				printf("Ingrese el año del vehiculo\n");
				scanf("%i", &v->year); fflush(stdin);
				printf("Ingrese el Color del vehiculo\n");
				gets(v->color);fflush(stdin);
				v->sigVehiculo = NULL;
				if(p.misVehiculos == NULL){
					p.misVehiculos = v;
				}else{
					p.misVehiculos->sigVehiculo = p.misVehiculos;
					p.misVehiculos = v;
				}
				fflush(stdin);
				fwrite(&p, sizeof(p), 1, pFileCopy);
			}else{
				fwrite(&p,sizeof(p),1,pFileCopy);
			}
			fread(&p,sizeof(p),1,pFile);
		}
	}
	fclose(pFile);
	fclose(pFileCopy);
	remove("Registro.txt");
	rename("Temp.txt", "Registro.txt");
	system("pause");
}


void editarUser(){
	FILE *pFile;
	FILE *pFileCopy;
	personas p;
	int x;
	int encontrado = 0;
	pFile = fopen("Registro.txt", "r");
	if(pFile == NULL){
		printf("No hay un registro creado en este momento\n");
		system("pause");
		return;
	}
	printf("Escriba el nro de cedula");
	scanf("%i",&x);
	pFileCopy = fopen("Temp.txt", "w");
	fread(&p, sizeof(p), 1, pFile);
	while(!feof(pFile)){
		if(p.cedula == x){
			fflush(stdin);
			printf("Ingrese el Nombre del usuario\n");
			gets(p.nombre);fflush(stdin);
			//p.cedula = x;
			printf("Ingrese la direccion donde reside %s\n", p.nombre);
			gets(p.direccion); fflush(stdin);
			printf("Ingrese la fecha de nacimiento de %s\n", p.nombre);
			scanf("%i", &p.fechaDeNacimiento); fflush(stdin);
			printf("Ingrese el sexo de %s (M/F)\n", p.nombre);
			scanf("%c", &p.sexo); fflush(stdin);
			encontrado = 1;
			fwrite(&p,sizeof(p),1,pFileCopy);//escribe en la direccion de la lista los datos insertados y lo guarda en el registro
		}else{
			fwrite(&p, sizeof(p),1,pFileCopy);//si no lo es, escribe los datos que se encuentran en p
		}
		fread(&p, sizeof(p),1,pFile);
	}
	fclose(pFile);
	fclose(pFileCopy);
	remove("Registro.txt");
	rename("Temp.txt", "Registro.txt");
	if(encontrado){
		printf("El usuario de cedula %i ha sido modificado\n", x);
		system("pause");
	}else{
		printf("El usuario de cedula %i no se encuentra en la base de datos\n", x);
		system("pause");
	}
}


/*menu prototipo para el proyecto*/

void vehiculos(){
	int n;
	system("cls");
	printf("\n\t1. Agregar Vehiculo");
	printf("\n\t2. Buscar Vehiculo");
	printf("\n\t3. Editar Informacion del Vehiculo");
	printf("\n\t4. Volver al menu principal");
	printf("\n\t0. Salir\n");
	printf("\n\t Ingrese una opcion (0..4):");
	scanf("%i", &n);

	if((n>=0) && (n<=4)){

	switch (n)
	{
	case 1: registrarVehiculo();
		system("cls");
		vehiculos();
		break;
    
	case 2: buscarUser();
		system("cls");
		personas();
		break;

	case 3: editarUser();
		system("cls");
		personas();
		break;

	case 4: menu();
		break;

	case 0: break;
	}
  }
	else {
		printf("\n\t opcion no valida\n");
		system("pause");
		personas();
	}
}

void personas(){
	int n;
	system("cls");
	printf("\n\t1. Agregar Persona");
	printf("\n\t2. Buscar Persona");
	printf("\n\t3. Editar Persona");
	printf("\n\t4. Volver al menu principal");
	printf("\n\t0. Salir\n");
	printf("\n\t Ingrese una opcion (0..4):");
	scanf("%i", &n);

	if((n>=0) && (n<=4)){

	switch (n)
	{
	case 1: aggUser();
		system("cls");
		personas();
		break;
    
	case 2: buscarUser();
		system("cls");
		personas();
		break;

	case 3: editarUser();
		system("cls");
		personas();
		break;

	case 4: menu();
		break;

	case 0: break;
	}
  }
	else {
		printf("\n\t opcion no valida\n");
		system("pause");
		personas();
	}
}
void mantenimiento() {
	int n;
	system("cls");
	printf("\n\t1. Personas");
	printf("\n\t2. Vehiculos");
	printf("\n\t3. Volver al menu principal");
	printf("\n\t0. Salir\n");
	printf("\n\t Ingrese una opcion (0..2):");
	scanf("%i", &n);

	if((n>=0) && (n<=3)){

	switch (n)
	{
	case 1: personas();
		break;
    
	case 2: vehiculos();
		break;

	case 3: menu();
		break;

	case 0: break;
	}
  }
	else {
		printf("\n\t opcion no valida\n");
		system("pause");
		mantenimiento();
	}
}

void operaciones_consultas() {
	int n;

	system("cls");
	printf("\n\t1. Operaciones");
	printf("\n\t2. Consultas");
	printf("\n\t3. Volver al menu principal");
	printf("\n\t0. Salir\n");
	printf("\n\t Ingrese una opcion (0..2):");
	scanf("%i", &n);

	if ((n >= 0) && (n <= 3)) {

		switch (n)
		{
		case 1: aggUser();
			system("cls");
			operaciones_consultas();
			break;

		case 2: mostrarUsers();
			system("pause");
			system("cls");
			operaciones_consultas();
			break;

		case 3: menu();
			break;

		case 0: break;
		}
	}
	else {
		printf("\n\t opcion no valida\n");
		system("pause");
		operaciones_consultas();
	}
}

void menu(){
	int n;
	system("cls");
	printf("\n\t\t Menu Principal\n");
	printf("\n\t1. Mantenimiento");
	printf("\n\t2. Operaciones y Consultas");
	printf("\n\t0. Salir");
	printf("\n Marque una opcion (0..2)");
	scanf("%i",&n);
	
	if((n>=0)&&(n<=2)){
		switch(n){
			case 1: mantenimiento();
			break;
			case 2: operaciones_consultas();
			break;
		}
	}else{
		printf("\n\t Opcion no valida\n");
		system("pause");
		menu();
	}
}

int main(){
	menu();
	return 0;
}
