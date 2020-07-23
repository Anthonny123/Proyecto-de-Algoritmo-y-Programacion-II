#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct infraccion{
	int nroInfraccion;
	int fechaDeInfrccion;
	char tipoDeInfraccion[20];
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
	int edad;
	char direccion[40];
	struct vehiculo *misVehiculos;
	struct personas *sigPersona;
};

void aggPersona(struct personas **p, int c, char n[20], int fn, char d[40], int edad){
	struct personas *tmp = new struct personas;
	tmp->cedula = c;
	tmp->fechaDeNacimiento = fn;
	tmp->edad = edad;
	strcpy(tmp->nombre, n);
	strcpy(tmp->direccion, d);
	tmp->misVehiculos = NULL;
	tmp->sigPersona = *p;
	*p = tmp;
}

void insertarPersona(struct personas **p){
	int cedula = 0;
	char nombre[20];
	int fechaDeNacimiento = 0;
	int edad = 0;
	char direccion[40];
	fflush(stdin);
	printf("Indique el Nombre de la persona: "); gets(nombre);
	printf("\n");
	fflush(stdin);
	printf("Indique el numero de cedula de la persona: "); scanf("%i", &cedula);
	printf("\n");
	fflush(stdin);
	printf("Indique la fecha de nacimiento (dd/mm/yyyy): "); scanf("%i", &fechaDeNacimiento);
	printf("\n");
	fflush(stdin);
	printf("Indique la direccion de la persona: "); gets(direccion);
	fflush(stdin);
	printf("\n");
	printf("Indique la edad de la persona: "); scanf("%i", &edad);
	printf("\n");
	aggPersona(&(*p), cedula,nombre, fechaDeNacimiento, direccion, edad);
}

struct personas *buscarPersona(struct personas *p, int cedula){
	int encontrado = 0;
	struct personas *tmp = NULL;
	for(; p; p = p->sigPersona){
		if(cedula == p->cedula){
			printf("La persona ha sido encontrada en nuestros archivos\n");
			encontrado = 1;
			return p;
		}
	}
	if(encontrado == 0){
		printf("Esta persona no se encuentra registrada\n");
		return NULL;
	}
}

void aggVehiculo(struct vehiculo **v, int year, char placa[8], char marca[15], char modelo[15], char color[10]){
	struct vehiculo *tmp = new struct vehiculo;
	tmp->year = year;
	strcpy(tmp->placa, placa);
	strcpy(tmp->marca, marca);
	strcpy(tmp->modelo, modelo);
	strcpy(tmp->color, color);
	tmp->sigVehiculo = NULL;
	tmp->misInfracciones = NULL;
	tmp->sigVehiculo = *v;
	*v = tmp;
}

void insertarVehiculo(struct vehiculo **v, struct personas **p){
	int cedula = 0;
	char placa[8];
	char marca[15];
	char modelo[15];
	int year;
	char color[10];
	printf("Inserte el Numero de cedula a la persona que le quiere agregar un vehiculo: "); scanf("%i", &cedula);
	printf("\n");
	struct personas *tmp = buscarPersona(*p, cedula);
	fflush(stdin);
	if(tmp!=NULL){
		printf("Indique la Placa del vehiculo: "); gets(placa);
		printf("\n");
		fflush(stdin);
		printf("Indique la Marca del vehiculo: "); gets(marca);
		printf("\n");
		fflush(stdin);
		printf("Indique el modelo del vehiculo: "); gets(modelo);
		printf("\n");
		fflush(stdin);
		printf("Indique el año del vehiculo (yyyy): "); scanf("%i", &year);
		printf("\n");
		fflush(stdin);
		printf("Indique el color del vehiculo: "); gets(color);
		printf("\n");
		fflush(stdin);
		aggVehiculo(&tmp->misVehiculos, year, placa, marca, modelo, color);
	}
}

void aggInfraccion(struct infraccion **i, int nInfraccion, int fInfraccion, char tInfraccion[20], int mInfraccion, int pagado){
	struct infraccion *tmp = new struct infraccion;
	tmp->nroInfraccion = nInfraccion;
	tmp->fechaDeInfrccion = fInfraccion;
	tmp->montoDeLaMulta = mInfraccion;
	tmp->pagado = pagado;
	strcpy(tmp->tipoDeInfraccion, tInfraccion);
}

int contarPersonas(struct personas *p){
	int cont = 0;
	while(p){
		p = p->sigPersona;
		cont ++;
	}
	return cont;
}

int contarVehiculo(struct vehiculo *v){
	int cont = 0;
	while(v){
		v = v->sigVehiculo;
		cont ++;
	}
	return cont;
}

void guardarDatos(struct personas *p){
	if(p){
		int i = 0;
		int j = 0;
		FILE *pFile;
		pFile = fopen("Registro.txt", "wt");
		if(!pFile){
			printf("Ha ocurrido un error al crear el archivo");
			return;
		}
		fprintf(pFile,"%i\n", contarPersonas(p));
		while(i<contarPersonas(p)){
			fprintf(pFile, "%i\n%s\n%i\n%s\n%i\n", p->cedula, p->nombre, p->fechaDeNacimiento, p->direccion, p->edad);//Guardo cedula, nombre, fecha de nacimiento, direccion, edad y sexo en ese orden
			fprintf(pFile, "%i\n", contarVehiculo(p->misVehiculos));
			while(j<contarVehiculo(p->misVehiculos)){
				fprintf(pFile, "%s\n%s\n%s\n%s\n%i\n", p->misVehiculos->placa, p->misVehiculos->marca, p->misVehiculos->modelo, p->misVehiculos->color, p->misVehiculos->year);//Guardo placa, marca, modelo, color y a;o en ese orden
				p->misVehiculos= p->misVehiculos->sigVehiculo;
			}
			j = 0;
			p = p->sigPersona;
		}
		fclose(pFile);
		printf("Guardado exitosamente\n");
	}else{
		return;
	}
}

void cargarDatos(struct personas **p){
	int personasRegistradas = 0;
	int vehiculosRegistrados = 0;
	char string[40];
	int cedula = 0;
	int edad = 0;
	int year = 0;
	int fechaDeNacimiento = 0;
	char nombre[20];
	char direccion[40];
	char placa[8];
	char modelo[15];
	char marca[15];
	char color[10];
	FILE *pFile;
	pFile = fopen("Registro.txt", "rt");
	if(!pFile){
		printf("Ha ocurrido un error al abrir el archivo");
		system("pause");
		return;
	}
	fgets(string, 100, pFile); sscanf(string, "%i", &personasRegistradas);//Obtengo el nro de personas que se encuentran en mis registros
	for(int i = 0; i<personasRegistradas; i++){
		fgets(string, 100, pFile); 
		sscanf(string, "%i", &cedula);//obtengo la cedula
		fgets(nombre, 100, pFile); //obtengo el nombre
		nombre[strlen(nombre)-1] = '\0';
		fgets(string, 100, pFile);
		sscanf(string, "%i", &fechaDeNacimiento);//obtengo la decha de nacimiento
		fgets(direccion, 100, pFile);//obtengo la direccion
		direccion[strlen(direccion)-1] = '\0';
		fgets(string, 100, pFile);
		sscanf(string, "%i", &edad);//Obtengo la edad
		aggPersona(p, cedula, nombre, fechaDeNacimiento,direccion, edad); //Inserto las listas con los datos de los usuarios
		fgets(string, 100, pFile); sscanf(string, "%i", &vehiculosRegistrados);//Obtengo el nro de vehiculos que tiene la persona
		for(int j = 0; j<vehiculosRegistrados; j++){
			fgets(placa, 100, pFile);
			placa[strlen(placa)-1] = '\0';
			fgets(marca, 100, pFile);
			marca[strlen(marca)-1] = '\0';
			fgets(modelo, 100, pFile);
			modelo[strlen(modelo)-1] = '\0';
			fgets(color, 100, pFile);
			color[strlen(color)-1] = '\0';
			fgets(string, 100, pFile);
			sscanf(string, "%i", &year);
			aggVehiculo(&(*p)->misVehiculos, year, placa, marca, modelo, color);
		}
	}
	fclose(pFile);
	printf("Se han encontrado unos datos y han sido cargados");
	system("pause");
}

void mostrarPersonas(struct personas *p){
	personas *tmp = p;
	vehiculo *tmpV = NULL;
	if(tmp){
		while(tmp){
			printf("Nombre: %s\n", tmp->nombre);
			printf("Cedula: %i\n", tmp->cedula);
			printf("Direccion: %s\n", tmp->direccion);
			tmpV = tmp->misVehiculos;
			if(tmpV!=NULL){
				while(tmpV){
					printf("Vehiculo: \n");
					printf("Placa: %s\n", tmpV->placa);
					printf("Marca: %s\n", tmpV->marca);
					printf("Modelo: %s\n", tmpV->modelo);
					printf("Color: %s\n", tmpV->color);
					tmpV = tmpV->sigVehiculo;
				}
			}
			tmp = tmp->sigPersona;
			system("pause");
		}
	}else{
		printf("No hay ningun registro");
		system("pause");
	}
}


void mostrarPersonasEncontradas(struct personas *p){
	vehiculo *tmpV = NULL;
	printf("Nombre: %s\n", p->nombre);
	printf("Cedula: %i\n", p->cedula);
	printf("Direccion: %s\n", p->direccion);
	tmpV = p->misVehiculos;
	if(tmpV!=NULL){
		while(tmpV){
			printf("Vehiculo: \n");
			printf("Placa: %s\n", tmpV->placa);
			printf("Marca: %s\n", tmpV->marca);
			printf("Modelo: %s\n", tmpV->modelo);
			printf("Color: %s\n", tmpV->color);
			tmpV = tmpV->sigVehiculo;
		}
	}
}

int main(){
	personas *p = NULL;
	cargarDatos(&p);
	int x = -1;
	while(x!=0){
		int n;
		system("cls");
		printf("\n\t1. Mantenimiento");
		printf("\n\t2. Operaciones y Consultas");
		printf("\n\t0. Salir\n");
		printf("\n\t Ingrese una opcion (0..2):");
		scanf("%i", &x);
		if ((x >= 0) && (x <= 2)) {
			switch(x){
				case 1: {
					system("cls");
					int y = -1;
					while(y!=0){
						printf("\n\t1. Personas");
						printf("\n\t2. Vehiculos");
						printf("\n\t0. Volver al menu anterior\n");
						scanf("%i", &y);
						if(y>=0 && y<=2){
							switch(y){
								case 1:{
									system("cls");
									int z = -1;
									while(z!=0){
										printf("\n\t1. Agregar a una persona al sistema");
										printf("\n\t2. Modificar a una persona en el sistema");
										printf("\n\t3. Consultar informacion de una persona en el sistema");
										printf("\n\t4. Eliminar a una persona del sistema");
										printf("\n\t0. Volver al menu anterior\n");
										scanf("%i", &z);
										if(z>=0&&z<=4){
											switch(z){
												case 1: insertarPersona(&p);
												break;
												case 2: //Falta hacer la funcion de modificar a una persona
												break;
												case 3:{
													system("cls");
													int cedula = 0;
													printf("Introduce el Numero de cedula de la personas que deseas buscar: "); scanf("%i", &cedula);
													mostrarPersonasEncontradas(buscarPersona(p, cedula));
													break;
													//Falta agregar la funcion de buscar a una persona por su nombre
												}
												case 4: break;//Falta hacer la funcion de eliminar a una persona
											}
										}
									}
									break;
								}
								case 2:{
									system("cls");
									int z = -1;
									while(z!=0){
										printf("\n\t1. Agregar un vehiculo al sistema");
										printf("\n\t2. Modificar los datos de un vehiculo");
										printf("\n\t3. Consultar los datos de un vehiculo en el sistema");
										printf("\n\t4. Eliminar a un vehiculo del sistema");
										printf("\n\t0. Volver al menu anterior\n");
										scanf("%i", &z);	
										if(z>=0&&z<=4){
											switch(z){
												case 1: insertarVehiculo(&p->misVehiculos, &p);
												break;
												case 2: //Falta hacer la funcion de modificar a un vehiculo
												break;
												case 3:{
													system("cls");
													//Falta hacer la funcion de buscar un vehiculo
													break;
												}
												case 4: break;//Falta hacer la funcion de eliminar a un vehiculo
											}
										}
									}
									break;
								}
							}
						}
					}	
				break;
				}
				case 2:{
					system("cls");
					int y = -1;
					while(y!=0){
						printf("\n\t1. Operaciones con Multas");
						printf("\n\t2. Consultas");
						printf("\n\t0. Volver al menu anterior\n");
						scanf("%i", &y);
						if(y>=0 && y<=2){
							switch(y){
								case 1:{
									system("cls");
									int z = -1;
									while(z!=0){
										printf("\n\t1. Agregar una multa al sistema");
										printf("\n\t2. Pagar una Multa asociada a un Vehiculo");
										printf("\n\t3. Consultar informacion de las multas asociada a un vehiculo");
										printf("\n\t4. Eliminar a una multa del sistema");
										printf("\n\t0. Volver al menu anterior\n");
										scanf("%i", &z);
										if(z>=0&&z<=4){
											switch(z){
												case 1: break;//Falta la funcion de agregar multa
												case 2: break;//Falta la funcion de Pagar una multa
												case 3: break;//Falta la funcion de Consultar la informacion de multas asociada a un vehiculo
												case 4: break;//Falta hacer la funcion de eliminar una multa del sistema
											}
										}
									}
									break;
								}
								case 2:{
									system("cls");
									int z = -1;
									while(z!=0){
										printf("\n\t1. Ingresar nombre o sinonimos de un nombre para buscar su informacion en el sistema");
										printf("\n\t2. Busqueda completa de los datos del titular asociados a su cedula");
										printf("\n\t3. Busqueda de multas asociada a una placa en el sistema");
										printf("\n\t4. Eliminar a un vehiculo del sistema");
										printf("\n\t0. Busqueda de multas por tipo de infraccion y año de infraccion\n");
										scanf("%i", &z);	
										if(z>=0&&z<=4){
											switch(z){
												case 1:break;//Falta hacer la funcion
												case 2:{
													system("cls");
													int w = -1;
													while(w!=0){
														printf("\n\t1. Mostrar datos completos del titular(Informacion personal, datos de sus vehiculos y total de multas asociada a la persona)");
														printf("\n\t2. Mostrar datos del titular y la informacion de cada uno de sus vehiculos con sus respectivas multas");
														printf("\n\t3. Mostrar las multas no pagadas de todos sus vehiculos de manera ordenada por placa, y el monto total a pagar");//Ordenada por numero de placa de manera ascendente
														printf("\n\t4. Mostrar todas las multas asociadas a una placa");//Ordenar de manera ascendente las no paagdas primero y luego las pagadas
														printf("\n\t5. Mostrar todas las multas que posee el titular, asociadas a un tipo de infraccion");
														scanf("%i", &w);
														if(w>=0&&w<=5){
															switch(w){
																case 1: break;
																case 2: break;
																case 3: break;
																case 4: break;
																case 5: break;
															}
														}
													}
													break;
												}
												case 3:break;//Falta hacer la funcion
												case 4:break;//Falta hacer la funcion
											}
										}
									}
									break;
								}
							}
						}
					}	
					break;
				}
			}
		}
	}
	guardarDatos(p);
	return 0;
}

