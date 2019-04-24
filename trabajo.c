#include <stdio.h>
#define N 100
#include <string.h>
#include <conio.h>

struct persona
{
	int DNI;
	char nombre[N];
	int pin;
};
void main()
{
	int opcion,elige,cont1=0,i,nombrepos,cmp;
	int pinus,dnius;
	char nombreus[15];
	struct persona usuarios[N];
	FILE *registro;
	float dinero[N];
	char persona[N];
	
	registro = fopen("registro.txt","r");
	if(registro==NULL)
	{
		printf("No se puedo abrir correctamente el fichero\n");
		return -1;
	}
	else
	{
		while(fscanf(registro,"%i  %s\t%i\t%i\t",&cont1,usuarios[cont1].nombre,&usuarios[cont1].DNI,&usuarios[cont1].pin)!=EOF)
		{
			cont1++;
			if(cont1!=0)
			{
				cont1=cont1-1;
			}
		}
	}
	fclose(registro);
	
	system("Color 3");
	printf("Bienvenido al banco de la etsidi \n\n");
	printf("	MENU\n");
	do
	{
		printf("\n");
		printf("Elige lo que desee hacer:\n\n");
		printf("1 Crear nueva cuenta:\n");
		printf("2 Iniciar sesion:\n\n");
		scanf("%i",&elige);	
		printf("\n");
		
		switch(elige)
		{
			case 1:
			{
				registro=fopen("registro.txt","w");
				if(registro==NULL)
				{
					printf("El fichero no se pudo abrir\n");
					return -1;
				}
				else
				{
					printf("Introduzca su nombre:\n");
					scanf("%s",usuarios[cont1].nombre);
					
					printf("Introduzca su DNI (sin letra):\n");//Modificar luego poner limite de numeros
					scanf("%i",&usuarios[cont1].DNI);
					
					printf("Introduzca su PIN (solo numeros):\n");//Modificar luego poner limite de numeros 4
					scanf("%i",&usuarios[cont1].pin);
						
					
						
					cont1++;	
				}
			break;
			fclose(registro);
			}
			case 2:
			{
				registro=fopen("registro.txt","r");
				if(registro==NULL)
				{
					printf("El fichero no se pudo abrir\n");
					return -1;
				}
				else
				{
					i=0;
					do
					{
						do
						{
							printf("Introduzca su usuario:\n\n");
							scanf("%s",nombreus);
							printf("\n");
							for(i=0;i<cont1;i++)
							{
								cmp=strcmp(nombreus,usuarios[i].nombre);
								
								if(cmp==0)
								{
									printf("El nombre es correcto. Puede continuar\n\n");
									nombrepos=i;
									break;
								}
								else if(i==cont1-1)
								{
									printf("Su nombre no esta registrado o es incorrecto.\nPruebe otra vez\n\n");
								}
							}
							
							
						}while(cmp==1||cmp==-1);
						
						do
						{
							
							printf("Introduzca su pin:\n");
							scanf("%i",&pinus);
							printf("Introduzca su DNI:\n");
							scanf("%i",&dnius);
							
							if(pinus == usuarios[nombrepos].pin && dnius == usuarios[nombrepos].DNI)
							{						
								printf("Ha introducido correctamente el pin y el DNI. Bienvenido\n");	
							}
							else
							{
							printf("\nEl pin o el dni estan mal introducidos.\nPruebe otra vez\n\n");
							}
							
						}while (pinus!=usuarios[nombrepos].pin || dnius!=usuarios[nombrepos].DNI);
						
						fclose(registro);
					
					}while(fscanf(registro,"%i  %s\t%i\t%i\t",&cont1,usuarios[cont1].nombre,&usuarios[cont1].DNI,&usuarios[cont1].pin)!=EOF);
				}
			break;
			}
		}
	}while(elige!=1 && elige!=2);
	printf("\n");
		
	do
	{
		printf("\n");
		printf("Elige su opcion:\n\n");
		printf("1 Retirar dinero:\n");
		printf("2 Ingresar dinero:\n");
		printf("3 Ver movimientos:\n");
		printf("4 Salir:\n\n");
		scanf("%i",&opcion);
		printf("\n");
		switch(opcion)
		{
			case 1:
			{
				printf("Indique la cantidad de dinero que desee retirar de su cuenta:\n");
				scanf("%f",&dinero[cont1]);
				break;
			}
			case 2:
			{
			
				break;
			}
			case 3:
			{
				
				break;	
			}
			case 4:
			{
				registro = fopen("registro.txt","w");
				if(registro==NULL)
				{
					printf("Error al abrir el fichero\n");
					return -1;
				}
				else
				{
					i=0;
					while(i<cont1)
					{
						fprintf(registro,"%i  %s\t%i\t%i\n",i+1,usuarios[i].nombre,usuarios[i].DNI,usuarios[i].pin);
						i++;
					}
					fclose(registro);
					printf("Gracias por todo hasta la proxima\n");	
				}
			break;
			}
			default:
				printf("Opcion incorrecta\n");
		}
	}while(opcion!=4);
}
