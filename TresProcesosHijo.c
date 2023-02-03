#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<wait.h>

int existenciaArchivo();
void escribirEnArchivo(char const *PID);
void leerArchivo();
void reescribirArchivo();

int main()
{
	int proc, proc1, i=0,n=0;
	char PID[10];
	int resultadoArchivo;
	int arregloPID[3];//El arreglo se crea el numero de veces del for, porque se crea una copia de antes del fork
	for(i=0; i<3; i++)
	{
	proc = fork();
	if(proc<0)
	printf("Ocurrio un error \n");
		if(proc == 0)//Hijo
		{	
			printf("Proceso hijo numero %i: %i, mi padre es: %i\n",i+1,getpid(),getppid());
			arregloPID[i] = getpid();//La siguiente vez qe se ejecute esta linea, 
			break;
		}
			else//Papa (Se cambio la estructura para hacer que un proceso no muera)
			{
			//wait(&proc);	
			}	
	}	
	while(1)
	{
	sleep(1);
	if(i==0) //Hijo
	{
		sprintf(PID,"%d",getpid());//Se convierte el entero a cadena de caracteres
		resultadoArchivo = existenciaArchivo();
		if(resultadoArchivo == -1)//NO EXISTE EL ARCHIVO, OSEA ES NULL
			{
				printf("\tEL HIJO 1 ESTÁ ESCRIBIENDO POR PRIMERA VEZ\n");
				escribirEnArchivo(PID);
			}
			else//YA EXISTE EL ARCHIVO
			{
				FILE *Archivo;
				Archivo = fopen("ArchivoPractica1.txt","r");
				fseek(Archivo, 0L, SEEK_END);
				if(ftell(Archivo)==0) //NO HAY NADA ESCRITO
				{
					printf("\tEL HIJO 1 REVISÓ EL ARCHIVO Y NO HAY NADA ESCRITO\n");
					printf("\tEL HIJO 1 VA A ESCRIBIR SU PID\n");
					escribirEnArchivo(PID);	
				}
				else
				{
					printf("\tEL HIJO 1 REVISÓ EL ARCHIVO Y ESTÁ EL PID DE OTRO PROCESO\n");
					leerArchivo();
					printf("\tEL HIJO 1 VA A BORRAR EL CONTENIDO\n");
					reescribirArchivo();	
				}	
			}
	}
		if(i==1)
		{
		//printf("Soy el Proceso hijo numero 2. Mi PID es: %i \n",getpid());
		sprintf(PID,"%d",getpid());//Se convierte el entero a cadena de caracteres
		resultadoArchivo = existenciaArchivo();
		if(resultadoArchivo == -1)//NO EXISTE EL ARCHIVO, OSEA ES NULL
			{
				printf("\t\tEL HIJO 2 ESTÁ ESCRIBIENDO POR PRIMERA VEZ\n");
				escribirEnArchivo(PID);
			}
			else//YA EXISTE EL ARCHIVO
			{
				FILE *Archivo;
				Archivo = fopen("ArchivoPractica1.txt","r");
				fseek(Archivo, 0L, SEEK_END);
				if(ftell(Archivo)==0) //NO HAY NADA ESCRITO
				{
					printf("\t\tEL HIJO 2 REVISÓ EL ARCHIVO Y NO HAY NADA ESCRITO\n");
					printf("\t\tEL HIJO 2 VA A ESCRIBIR SU PID\n");
					escribirEnArchivo(PID);	
				}
				else
				{
					printf("\t\tEL HIJO 2 REVISÓ EL ARCHIVO Y ESTÁ EL PID DE OTRO PROCESO\n");
					leerArchivo();
					printf("\t\tEL HIJO 2 VA A BORRAR EL CONTENIDO\n");
					reescribirArchivo();	
				}	
			}	
			
		}
			if(i==2)
			{
			//printf("Soy el Proceso hijo numero 3. Mi PID es: %i \n",getpid());
			sprintf(PID,"%d",getpid());//Se convierte el entero a cadena de caracteres
			resultadoArchivo = existenciaArchivo();
			if(resultadoArchivo == -1)//NO EXISTE EL ARCHIVO, OSEA ES NULL
			{
				printf("\t\t\tEL HIJO 3 ESTÁ ESCRIBIENDO POR PRIMERA VEZ");
				escribirEnArchivo(PID);
			}
			else//YA EXISTE EL ARCHIVO
			{
				FILE *Archivo;
				Archivo = fopen("ArchivoPractica1.txt","r");
				fseek(Archivo, 0L, SEEK_END);
				if(ftell(Archivo)==0) //NO HAY NADA ESCRITO
				{
					printf("\t\t\tEL HIJO 3 REVISÓ EL ARCHIVO Y NO HAY NADA ESCRITO\n");
					printf("\t\t\tEL HIJO 3 VA A ESCRIBIR SU PID\n");
					escribirEnArchivo(PID);	
				}
				else
				{
					printf("\t\t\tEL HIJO 3 REVISÓ EL ARCHIVO Y ESTÁ EL PID DE OTRO PROCESO\n");
					leerArchivo();
					printf("\t\t\tEL HIJO 3 VA A BORRAR EL CONTENIDO\n");
					reescribirArchivo();	
				}	
			}
			}
		n++;
	}
	wait(&proc);
	exit(0);
}

int existenciaArchivo()
{
	if(access("ArchivoPractica1.txt",F_OK) != -1)
	{
		//printf("El archivo existe\n");
		return 1;
	}
	else
	{
		//printf("EL archivo no existe\n");
		return -1;
	}
}

void escribirEnArchivo(char const *PID)//Se escribe en el archivo el PID DE CADA ARCHIVO
{
	FILE *Archivo = NULL;
	//char cadena[15];
	Archivo = fopen("ArchivoPractica1.txt","w");
	if(Archivo == NULL)
	{
		printf("Error al abrir el archivo\n");
	}
	else
	{
		fprintf(Archivo,"%s\n",PID);
	}
	fclose(Archivo);
	printf("\n");
}

void leerArchivo()
{
	FILE *Archivo;
	char cadena;
	Archivo = fopen("ArchivoPractica1.txt","r");
	if(Archivo == NULL)
	{
		printf("Error al abrir el archivo\n");
	}
	else
	{
		printf("El PID del archivo es:");
		while(!feof(Archivo))
		{
		fscanf(Archivo,"%c",&cadena);
		printf("%c",cadena);
		}
	}
	fclose(Archivo);
	printf("\n");
}

void reescribirArchivo()
{
	FILE *Archivo = NULL;
	Archivo = fopen("ArchivoPractica1.txt","w");
	if(Archivo == NULL)
	{
		printf("Error al abrir el archivo\n");
	}
	else
	{
		//se vacia el documento nuevamente
	}
	fclose(Archivo);
}

