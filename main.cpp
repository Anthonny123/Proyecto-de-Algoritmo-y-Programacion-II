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
	if((t = fopen("Registro.txt", "r"))!= NULL){
		fclose(t);
		return 1;
	}
	return 0;
}


void aggUser(){
	FILE *pFile;
	personas p;
	if(comprobarSiExisteFichero == 0){
		pFile = fopen("Registro.txt", "w");
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
		scanf("%i", &p.sexo); fflush(stdin);
		fwrite(&p,sizeof(p),1,pFile);
		fclose(pFile);
	}else{
		pFile = fopen("Registro.txt","a");
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
		fwrite(&p,sizeof(p),1,pFile);
		fclose(pFile);
	}
}

void mostrarUsers(){
	FILE *pFile;
	personas p;
	if((pFile = fopen("Registro.txt", "r"))==NULL){
		printf("No existe ningun Fichero creado");
		system("pause");
	}else{
		fread(&p, sizeof(p), 1, pFile);
		while(!feof(pFile)){
			printf("----------------------------\n");
			printf("Nombre: %s\n", p.nombre);
			printf("Cedula: %i\n", p.cedula);
			printf("Direccion: %s\n", p.direccion);
			printf("Fecha De Nacimiento: %i\n", p.fechaDeNacimiento);
			printf("Sexo: %c\n", p.sexo);
			printf("----------------------------\n");
			fread(&p, sizeof(p), 1, pFile);
		}
	}
	fclose(pFile);
}


/*menu prototipo para el proyecto*/
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
	case 1:
		break;
    
	case 2:
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
