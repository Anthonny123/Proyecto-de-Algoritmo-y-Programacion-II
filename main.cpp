#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct infraccion{
	int nroInfraccion;
	int fechaDeInfraccion;
	char tipoDeInfraccion[50];
	int montoDeLaMulta;
	int pagado;
	infraccion *sigInfraccion;
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

/*//////////////////////////////////////////////////////////////////////////////////////////
                          FUNCIONES PARA LAS PERSONAS
//////////////////////////////////////////////////////////////////////////////////////////*/

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

void modificarPersona(struct personas *p){
	if(p){
		fflush(stdin);
		printf("Ingrese el nuevo nombre: "); gets((p)->nombre);
		printf("\n");
		fflush(stdin);
		printf("Ingrese la nueva direccion: "); gets(p->direccion);
		printf("\n");
		fflush(stdin);
		printf("Ingrese la nueva fecha de nacimiento: "); scanf("%i", &p->fechaDeNacimiento);
		printf("\n");
		fflush(stdin);
		printf("Ingrese la nueva edad de la persona: "); scanf("%i",&p->edad);
		printf("\n");
	}else{
		return;
	}
	printf("Modificacion Exitosa\n");
}

void eliminarVehiculosDelasPersonas(struct personas *p){
	vehiculo *aux = p->misVehiculos;
	if(aux){
		while(p->misVehiculos){
			aux = p->misVehiculos;
			p->misVehiculos = p->misVehiculos->sigVehiculo;
			delete(aux);
		}
	} 
}


void eliminarTodasLasMultasDeUnVehiculos(struct vehiculo *v);

void eliminarPersonas(struct personas **p, int cedula){
	struct personas *tmp = *p;
	if(tmp){
		if(tmp->cedula == cedula){
			eliminarTodasLasMultasDeUnVehiculos((*p)->misVehiculos);
			eliminarVehiculosDelasPersonas(*p);
			*p = (*p)->sigPersona;
			delete(tmp);
		}else{
			while(tmp->sigPersona && tmp->sigPersona->cedula!= cedula){
				tmp = tmp->sigPersona;
			}
			if(tmp->sigPersona){
				struct personas *aux = tmp->sigPersona;
				eliminarVehiculosDelasPersonas(aux);
				eliminarTodasLasMultasDeUnVehiculos(aux->misVehiculos);
				tmp->sigPersona = tmp->sigPersona->sigPersona;
				delete(aux);
			}
		}
	}
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
	if(p){
		printf("Nombre: %s\n", p->nombre);
		printf("Cedula: %i\n", p->cedula);
		printf("Direccion: %s\n", p->direccion);
		printf("Fecha de Nacimiento: %i\n", p->fechaDeNacimiento);
		printf("Edad: %i\n", p->edad);
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
}

int contarPersonas(struct personas *p){
	int cont = 0;
	while(p){
		p = p->sigPersona;
		cont ++;
	}
	return cont;
}

/*//////////////////////////////////////////////////////////////////////////////////////////
                          FUNCIONES PARA LOS VEHICULOS 
//////////////////////////////////////////////////////////////////////////////////////////*/

void aggVehiculo(struct vehiculo **v, int year, char placa[8], char marca[15], char modelo[15], char color[10]){
	struct vehiculo *tmp = new struct vehiculo;
	tmp->year = year;
	strcpy(tmp->placa, placa);
	strcpy(tmp->marca, marca);
	strcpy(tmp->modelo, modelo);
	strcpy(tmp->color, color);
	//tmp->sigVehiculo = NULL;
	tmp->misInfracciones = NULL;
	tmp->sigVehiculo = *v;
	*v = tmp;
}

struct vehiculo *buscarVehiculoPlaca(struct personas *p, char placa[8]){
	struct vehiculo *v = NULL;
	int encontrado = 0;
	char placaVehiculo[8];
	for(;p; p = p->sigPersona){
		v = p->misVehiculos;
		for(;v; v = v->sigVehiculo){
			if(strcmp(v->placa, placa) == 0){
				encontrado = 1;
				printf("El vehiculo pertenece al propietario del numero de cedula %i\n", p->cedula);
				return v;
			}
		}
	}
	if(encontrado == 0){
		printf("La placa %s no se ha encontrado en nuestro sistema\n", placa);
		system("pause");
		return NULL;
	}
}

void mostrarVehiculoEncontrado(struct vehiculo *v){
	if(v){
		//printf("Vehiculo: \n");
		printf("----------------------------------");
		printf("\n\tPlaca: %s", v->placa);
		printf("\n\tMarca: %s", v->marca);
		printf("\n\tModelo: %s", v->modelo);
		printf("\n\tColor: %s\n", v->color);
		//printf("----------------------------------\n");	
	}
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

void modificarVehiculo(struct vehiculo *v){
	if(v){
		fflush(stdin);
		printf("Ingrese una nueva marca para el vehiculo: "); gets(v->marca);
		printf("\n");
		fflush(stdin);
		printf("Ingrese un nuevo modelo para el vehiculo: "); gets(v->modelo);
		printf("\n");
		fflush(stdin);
		printf("Ingrese un nuevo año para el vehiculo: "); scanf("%i", &v->year);
		printf("\n");
		fflush(stdin);
		printf("Ingrese un nuevo color para el vehiculo: "); gets(v->color);
		printf("\n");
	}
}

void eliminarTodasLasMultasDeUnVehiculos(struct vehiculo *v){
	infraccion *aux = v->misInfracciones;
	if(aux){
		while(v->misInfracciones){
			aux = v->misInfracciones;
			v->misInfracciones = v->misInfracciones->sigInfraccion;
			delete(aux);
		}
	} 
}

void eliminarVehiculosPorNroDePlaca(struct personas **p, char placa[8]){
	struct vehiculo *tmpV = NULL;
	struct personas *tmp = *p;
	if(tmp){
		for(;tmp; tmp = tmp->sigPersona){
			tmpV = tmp->misVehiculos;
			if(tmpV){
				if(strcmp(tmpV->placa, placa) == 0){
					eliminarTodasLasMultasDeUnVehiculos(tmpV);
					tmp->misVehiculos = tmp->misVehiculos->sigVehiculo;
					delete(tmpV);
				}else{
					while((tmpV->sigVehiculo!=NULL)&&(strcmp(tmpV->sigVehiculo->placa, placa) != 0)){
						tmpV = tmpV->sigVehiculo;
					}
					if(tmpV->sigVehiculo!=NULL){
						eliminarTodasLasMultasDeUnVehiculos(tmpV);
						struct vehiculo *aux = tmpV->sigVehiculo;
						tmpV->sigVehiculo = aux->sigVehiculo;
						delete(aux);	
					}
				}
			}
		}
	}
}


int contarVehiculo(struct vehiculo *v){
	int cont = 0;
	while(v){
		v = v->sigVehiculo;
		cont ++;
	}
	return cont;
}

/*//////////////////////////////////////////////////////////////////////////////////////////
                          FUNCIONES PARA LAS INFRACCIONES 
//////////////////////////////////////////////////////////////////////////////////////////*/

void aggInfraccion(struct infraccion **i, int nInfraccion, int fInfraccion, char tInfraccion[50], int mInfraccion, int pagado){
	struct infraccion *tmp = new struct infraccion;
	tmp->nroInfraccion = nInfraccion;
	tmp->fechaDeInfraccion = fInfraccion;
	tmp->montoDeLaMulta = mInfraccion;
	tmp->pagado = pagado;
	strcpy(tmp->tipoDeInfraccion, tInfraccion);
	tmp->sigInfraccion = *i;
	*i = tmp;
}

void insertarInfraccion(struct personas **p){
	char placa[8];
	int nroInfraccion = 0;
	int fechaDeInfraccion = 0;
	char tipoDeInfraccion[50];
	int montoDeLaMulta = 0;
	int pagado = 0;
	fflush(stdin);
	printf("Inserte la placa del vehiculo al cual le quiere colocar una multa: "); gets(placa);
	struct vehiculo *tmp = buscarVehiculoPlaca(*p, placa);
	fflush(stdin);
	if(tmp!=NULL){
		printf("Indique el nro de infraccion: "); scanf("%i", &nroInfraccion);
		printf("\n");
		fflush(stdin);
		printf("Indique la fecha en la que ocurrio la infraccion: "); scanf("%i", &fechaDeInfraccion);
		printf("\n");
		fflush(stdin);
		printf("Indique Cual es el tipo de infraccion: "); gets(tipoDeInfraccion);
		printf("\n");
		fflush(stdin);
		printf("Indique el Monto de la multa: "); scanf("%i", &montoDeLaMulta);
		printf("\n");
		fflush(stdin);
		aggInfraccion(&tmp->misInfracciones, nroInfraccion, fechaDeInfraccion, tipoDeInfraccion, montoDeLaMulta, pagado);
	}
}

struct infraccion *buscarMultaPorNroDeMulta(struct personas *p, int nroMulta){
	int encontrada = 0;
	struct vehiculo *tmpV = NULL;
	struct infraccion *tmpI = NULL;
	if(p){
		for(;p; p=p->sigPersona){
			tmpV = p->misVehiculos;
			for(;tmpV; tmpV = tmpV->sigVehiculo){
				tmpI = tmpV->misInfracciones;
				for(;tmpI; tmpI = tmpI->sigInfraccion){
					if(tmpI->nroInfraccion == nroMulta){
						printf("Esta multa esta asociada al vehiculo de placa: %s", tmpV->placa);
						printf("\n");
						int encontada = 1;
						return tmpI;
					}
				}
			}
		}
	}
	if(encontrada == 0){
		printf("Lo sentimos pero no se ha encontrado en nuestros registros\n");
		system("pause");
	}
}

void mostrarMultaEncontrada(struct infraccion *i){
	if(i){
		printf("\t\tInfraccion Nro %i: \n", i->nroInfraccion);
		printf("\t\tTipo de infraccion: %s\n", i->tipoDeInfraccion);
		printf("\t\tFecha en la que se ocasiono la infraccion: %i\n", i->fechaDeInfraccion);
		printf("\t\tMonto a pagar: %i\n", i->montoDeLaMulta);
		if(i->pagado == 0){
			printf("\t\tEsta multa no ha sido pagada\n");
		}else{
			printf("\t\tEsta multa ya fue pagada\n");
		}
	}
}


void eliminarMultaPorNroDeMulta(struct personas **p, int nroMulta){
	struct vehiculo *tmpV = NULL;
	struct infraccion *tmpI = NULL;
	struct personas *tmp = *p;
	if(tmp){
		for(;tmp; tmp = tmp->sigPersona){
			tmpV = tmp->misVehiculos;
			for(;tmpV; tmpV = tmpV->sigVehiculo){
				tmpI = tmpV->misInfracciones;
				if(tmpI){
					if(tmpI->nroInfraccion == nroMulta){
						tmpV->misInfracciones = tmpV->misInfracciones->sigInfraccion;
						delete(tmpI);
					}else{
						while((tmpI->sigInfraccion!=NULL)&&(tmpI->sigInfraccion->nroInfraccion!=nroMulta)){
							tmpI = tmpI->sigInfraccion;
						}
						if(tmpI->sigInfraccion != NULL){
							struct infraccion *aux = tmpI->sigInfraccion;
							tmpI->sigInfraccion = aux->sigInfraccion;
							delete(aux);	
						}
					}
				}
			}
		}
	}
}

void pagarMultas(infraccion *i){
	int opcion = -1;
	printf("\n\t El monto de la multa es: %i", i->montoDeLaMulta);
	printf("\n\t ¿Desea cancelar la multa? (1-Si/0-No)");
	scanf("%i", &opcion);
	switch(opcion){
		case 1: {
			printf("\n\t La multa nro %i, ha sido cancelada", i->nroInfraccion);
			i->pagado = 1;
			system("pause");
			system("cls");
			break;
		}
		case 2: break;
	}
}

int contarMultas(struct infraccion *i){
	int count = 0;
	while(i){
		i = i->sigInfraccion;
		count++;
	}
	return count;
}


/*//////////////////////////////////////////////////////////////////////////////////////////
                     FUNCIONES PARA LAS OPERACIONES DE CONSULTAS
//////////////////////////////////////////////////////////////////////////////////////////*/


void mostrarDatosCompletosDelTitular(struct personas *p, int cedula){
	struct personas *tmp = buscarPersona(p,cedula);
	vehiculo *tmpV = NULL;
	infraccion *tmpI = NULL;
	if(tmp){
		printf("Nombre: %s\n", tmp->nombre);
		printf("Cedula: %i\n", tmp->cedula);
		printf("Direccion: %s\n", tmp->direccion);
		printf("Fecha de Nacimiento: %i\n", tmp->fechaDeNacimiento);
		printf("Edad: %i\n", p->edad);
		tmpV = tmp->misVehiculos;
		if(tmpV!=NULL){
			while(tmpV){
				mostrarVehiculoEncontrado(tmpV);
				tmpI = tmpV->misInfracciones;
				printf("Este vehiculo posee %i multas\n", contarMultas(tmpI));
				printf("----------------------------------\n");
				printf("\n");
				tmpV = tmpV->sigVehiculo;
			}
		}	
	}
}


void mostrarDatosDelTitularMasInformacionDeVehiculosYMultas(struct personas *p, int cedula){
	struct personas *tmp = buscarPersona(p,cedula);
	vehiculo *tmpV = NULL;
	infraccion *tmpI = NULL;
	if(tmp){
		printf("Nombre: %s\n", tmp->nombre);
		printf("Cedula: %i\n", tmp->cedula);
		printf("Direccion: %s\n", tmp->direccion);
		printf("Fecha de Nacimiento: %i\n", tmp->fechaDeNacimiento);
		printf("Edad: %i\n", p->edad);
		tmpV = tmp->misVehiculos;
		if(tmpV!=NULL){
			while(tmpV){
				mostrarVehiculoEncontrado(tmpV);
				tmpI = tmpV->misInfracciones;
				if(tmpI!=NULL){
					while(tmpI){
						mostrarMultaEncontrada(tmpI);
						printf("----------------------------------\n");
						printf("\n");
						tmpI = tmpI->sigInfraccion;
					}
				}
				tmpV = tmpV->sigVehiculo;
			}
		}
	}
}

int compararPlacasOrdenAlfabetico(char placa1[8], char placa2[8]){
	int letraPlaca1 = 0;
	int letraPlaca2 = 0;
	int i = 0;
	const int maxLen = 6;
	while((letraPlaca1 == letraPlaca2)&&(i<=maxLen)){
		letraPlaca1 = placa1[i];
		letraPlaca2 = placa2[i];
		i++;
	}
	if(letraPlaca1<letraPlaca2){
		printf("%s va primero que %s\n", placa1, placa2);
		return 1;
	}else if(letraPlaca1>letraPlaca2){
		printf("%s va primero que %s\n", placa2, placa1);
		return 0;
	}else{
		printf("son iguales\n");
	}
}

void swap( vehiculo *x, vehiculo *y){ /* Intercambia los contenidos de las direcciones x , y */
	vehiculo c= *x;
	*x=*y;
	*y=c;
};

void ordenarPlacasOrdenAlfabetico(vehiculo *v){
	int menor = 0;
	vehiculo *tmp = v;
	if(tmp){
		while(tmp){
			printf("direccion de la placa %s: %i \n",tmp->placa, &tmp);
			system("pause");
			tmp = tmp->sigVehiculo;
		}
	}
}


/*//////////////////////////////////////////////////////////////////////////////////////////
                     FUNCIONES PARA LOS GUARDAR Y CARGAR DATOS 
//////////////////////////////////////////////////////////////////////////////////////////*/

void guardarDatos(struct personas *p){
	if(p){
		int i = 0;
		int j = 0;
		int k = 0;
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
				fprintf(pFile, "%i\n", contarMultas(p->misVehiculos->misInfracciones));
				while(k<contarMultas(p->misVehiculos->misInfracciones)){
					fprintf(pFile,"%i\n%i\n%s\n%i\n%i\n",p->misVehiculos->misInfracciones->nroInfraccion, p->misVehiculos->misInfracciones->fechaDeInfraccion, p->misVehiculos->misInfracciones->tipoDeInfraccion, p->misVehiculos->misInfracciones->montoDeLaMulta, p->misVehiculos->misInfracciones->pagado);
					p->misVehiculos->misInfracciones = p->misVehiculos->misInfracciones->sigInfraccion;
					//k++;
				}
				k = 0;
				p->misVehiculos= p->misVehiculos->sigVehiculo;
				//j++;
			}
			j = 0;
			p = p->sigPersona;
			//i++;
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
	int infraccionesRegistradas = 0;
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
	int nroInfraccion = 0;
	int fechaDeInfraccion = 0;
	char tipoDeInfraccion[50];
	int montoDeLaMulta = 0;
	int pagado = 0;
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
			fgets(string, 100, pFile); sscanf(string, "%i", &infraccionesRegistradas);
			for(int k = 0; k<infraccionesRegistradas; k++){
				fgets(string, 100, pFile); 
				sscanf(string, "%i", &nroInfraccion);
				fgets(string, 100, pFile); 
				sscanf(string, "%i", &fechaDeInfraccion);
				fgets(tipoDeInfraccion, 100, pFile);
				tipoDeInfraccion[strlen(tipoDeInfraccion)-1] = '\0';
				fgets(string, 100, pFile); 
				sscanf(string, "%i", &montoDeLaMulta);
				fgets(string, 100, pFile); 
				sscanf(string, "%i", &pagado);
				aggInfraccion(&(*p)->misVehiculos->misInfracciones,nroInfraccion, fechaDeInfraccion, tipoDeInfraccion, montoDeLaMulta, pagado);
			}
		}
	}
	fclose(pFile);
	printf("Se han encontrado unos datos y han sido cargados");
	system("pause");
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
						system("cls");
						printf("\n\t1. Personas");
						printf("\n\t2. Vehiculos");
						printf("\n\t0. Volver al menu anterior\n");
						scanf("%i", &y);
						if(y>=0 && y<=2){
							switch(y){
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    SECCION PERSONAS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
								case 1:{
									int z = -1;
									while(z!=0){
										system("cls");
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
												case 2:{
													int cedula = 0;
													printf("Introduce el numero de cedula de la persona a la cual le quieres hacer una modificacion de sus datos: ");
													scanf("%i", &cedula);
													modificarPersona((buscarPersona(p, cedula)));	
													system("pause");
													break;
												}
												case 3:{
													system("cls");
													int cedula = 0;
													printf("Introduce el Numero de cedula de la personas que deseas buscar: "); scanf("%i", &cedula);
													mostrarPersonasEncontradas(buscarPersona(p, cedula));
													system("pause");
													break;
													//Falta agregar la funcion de buscar a una persona por su nombre
												}
												case 4:{
													system("cls");
													int cedula = 0;
													printf("Introduce el Numero de cedula de la personas que deseas eliminar: "); scanf("%i", &cedula);
													eliminarPersonas(&p, cedula);
													system("pause");
													break;
												}
											}
										}
									}
									break;
								}
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    SECCION VEHICULOS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
								case 2:{
									int z = -1;
									while(z!=0){
										system("cls");
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
												case 2: {
													system("cls");
													char placaV[8];
													system("cls");
													printf("Introduce la placa del vehiculo que desea modificar: ");
													fflush(stdin);
													gets(placaV);
													modificarVehiculo(buscarVehiculoPlaca(p,placaV));
													system("pause");
													break;
												}
												case 3:{
													system("cls");
													char placaV[8];
													system("cls");
													printf("Introduce la placa del vehiculo que desea buscar: ");
													fflush(stdin);
													gets(placaV);
													mostrarVehiculoEncontrado(buscarVehiculoPlaca(p, placaV));
													system("pause");
													break;
												}
												case 4:{
													system("cls");
													char placaV[8];
													printf("Introduce la placa del vehiculo que desea buscar: ");
													fflush(stdin);
													gets(placaV);
													eliminarVehiculosPorNroDePlaca(&p, placaV);
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
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    SECCION MULTAS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
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
												case 1: insertarInfraccion(&p); 
												break;
												case 2:{
													int nroMulta = 0;
													printf("Inserte el Nro de infraccion que desea buscar en el sistema: ");
													scanf("%i", &nroMulta);
													system("cls");
													pagarMultas(buscarMultaPorNroDeMulta(p, nroMulta));
													break;
												}
												case 3:{
													int nroMulta = 0;
													printf("Inserte el Nro de infraccion que desea buscar en el sistema: ");
													scanf("%i", &nroMulta);
													system("cls");
													mostrarMultaEncontrada(buscarMultaPorNroDeMulta(p,nroMulta));
													system("pause");
													break;
												} //Falta la funcion de Consultar la informacion de multas asociada a un vehiculo
												case 4:{
													int nroMulta = 0;
													printf("Inserte en nro de infraccion que desee eliminar del sistema: ");
													scanf("%i", &nroMulta);
													eliminarMultaPorNroDeMulta(&p, nroMulta);
													printf("La multa de nro: %i, ha sido eliminada de nuestros registros\n", nroMulta);
													break;
												} 
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
													int w = -1;
													while(w!=0){
														system("cls");
														printf("\n\t1. Mostrar datos completos del titular(Informacion personal, datos de sus vehiculos y total de multas asociada a la persona)");
														printf("\n\t2. Mostrar datos del titular y la informacion de cada uno de sus vehiculos con sus respectivas multas");
														printf("\n\t3. Mostrar las multas no pagadas de todos sus vehiculos de manera ordenada por placa, y el monto total a pagar");//Ordenada por numero de placa de manera ascendente
														printf("\n\t4. Mostrar todas las multas asociadas a una placa");//Ordenar de manera ascendente las no paagdas primero y luego las pagadas
														printf("\n\t5. Mostrar todas las multas que posee el titular, asociadas a un tipo de infraccion\n");
														scanf("%i", &w);
														if(w>=0&&w<=5){
															switch(w){
																case 1: {
																	int cedula = 0;
																	printf("Ingrese el nro de cedula del titular que quiere buscar en el sistema: ");
																	scanf("%i", &cedula);
																	mostrarDatosCompletosDelTitular(p, cedula);
																	//fflush(stdin);
																	system("pause");
																	break;
																}
																case 2:{
																	int cedula = 0;
																	printf("Ingrese el nro de cedula del titular que quiere buscar en el sistema: ");
																	scanf("%i", &cedula);
																	mostrarDatosDelTitularMasInformacionDeVehiculosYMultas(p,cedula);
																	//fflush(stdin);
																	system("pause");
																	break;
																} 
																case 3:{
																	struct personas *tmp = NULL;
																	tmp = buscarPersona(p, 26327898); 
																	ordenarPlacasOrdenAlfabetico(tmp->misVehiculos);
																	system("pause");
																	break;
																}
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

