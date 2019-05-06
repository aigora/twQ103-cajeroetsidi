#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define N 100
#define S 7

struct oferta
{
	int codigo;
	char nombre[N];
	float precio;
};
struct persona
{
	int DNI;
	char nombre[N];
	int pin;
	float dinero;
};
void main()
{
	int opcion,elige,cont1=0,i,nombrepos,cmp,errornombre=0,cmp1,x,volver=0;
	int pinus,dnius,compra;
	char nombreus[15];
	struct persona usuarios[N];
	FILE *registro;
	FILE *ofertas;
	float dinero;
	int seleccion;
	char persona[N];
	
	struct oferta tickets[S] = {{01,"Viaje",120},
							    {02,"Cine",3.90},
							    {03,"Concierto", 42.80},
							    {04,"Puenting", 100},
								{05,"Zoo",35.25},
								{06,"Atracciones", 28.75},
								{07,"Teleferico", 5}};
								
	registro = fopen("registro.txt","r");
	if(registro==NULL)
	{
		printf("No se puedo abrir correctamente el fichero\n");
		return -1;
	}
	else
	{
		while(fscanf(registro,"%i  %s\t%i\t%i\t%f\t",&cont1,usuarios[cont1].nombre,&usuarios[cont1].DNI,&usuarios[cont1].pin,&usuarios[cont1].dinero)!=EOF)
		{
			cont1++;
			if(cont1!=0)
			{
				cont1=cont1-1;
			}
		}
	}
	fclose(registro);
	
	ofertas = fopen("ofertas.txt","w");
	if(ofertas==NULL)
	{
		printf("No se ha podido abrir correctamente el fichero \n");
	}
	else
	{
		for(i=0;i<S;i++)
		{
			fprintf(ofertas,"%i  %s\t%.2f\n",tickets[i].codigo,tickets[i].nombre,tickets[i].precio);
		}
		fclose(ofertas);
	}
	
	do
	{
		do
		{
			system("cls");
			system("Color 3");
			printf("Bienvenido al banco de la etsidi \n\n");
			printf("	MENU\n");
		
			printf("\n");
			printf("Elige lo que desee hacer:\n\n");
			printf("1 Crear nueva cuenta:\n");
			printf("2 Iniciar sesion:\n\n");
			fflush(stdin);
			scanf("%i",&elige);	
			printf("\n");
			volver=0;
			
			switch(elige)
			{
				case 1:
				{
					do
					{		
						printf("Introduzca su nombre:\n\n");
						scanf("%s",usuarios[cont1].nombre);
						printf("\n");
						x=cont1;
						
						registro = fopen("registro.txt","r");
						if(registro == NULL)
						{
							printf("EL fichero no se ha podido abrir correctamente.\n");
							return -1;
						}
						else
						{
							i=0;
							while(fscanf(registro,"%i  %s\t%i\t%i\t%f\t",&i+1,usuarios[i].nombre,&usuarios[i].DNI,&usuarios[i].pin,&usuarios[i].dinero)!=EOF)
							{
									cmp1=strcmp(usuarios[i].nombre,usuarios[x].nombre);
									if(cmp1==0)
									{
										printf("El nombre de usuario introducido ya existe. Pruebe con otro nombre.\n\n");
										break;
									}
									else if(i==x-1 || cont1==0)
									{
										printf("El nombre de usuario ha sido introducido correctamente.\n");
										break;	
									}
									i++;
							}
						}
					}while(cmp1==0 && x!=0);
					
					do
					{
					printf("\nIntroduzca su DNI (8 cifras sin 0 inicial y sin letra):\n");//Modificar luego poner limite de numeros
					scanf("%i",&usuarios[cont1].DNI);
					}			
					while(usuarios[cont1].DNI>=99999999);
					do	
					{					
					printf("\nIntroduzca su PIN (solo numeros):\n");//Modificar luego poner limite de numeros 4
					scanf("%i",&usuarios[cont1].pin);
					}
					while(usuarios[cont1].pin>=9999);		
					cont1++;
						
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
							fprintf(registro,"%i  %s\t%i\t%i\t%.3f\n",i+1,usuarios[i].nombre,usuarios[i].DNI,usuarios[i].pin,usuarios[i].dinero);
							i++;
						}
						printf("\nSu cuenta se esta creando. Espere unos segundos\n");
						Sleep(2500);
						printf("Ya se ha creado su usuario correctamente. Ahora debera iniciar sesion\n");
						printf("Presione cualquier tecla para continuar. ");
						getch();	
						
					}	
				fclose(registro);
				volver=1;
				break;
				}
				case 2:
				{
					if(cont1==0)
					{
						printf("Todavia no hay ningun usuario registrado en el cajero. Cree un usuario antes.");
						break;
					}
					else
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
									
									printf("Introduzca su DNI:\n");
									scanf("%i",&dnius);
									printf("Introduzca su codigo PIN:\n");
									scanf("%i",&pinus);
									
									if(pinus == usuarios[nombrepos].pin && dnius == usuarios[nombrepos].DNI)
									{						
										printf("\nHa introducido correctamente el pin y el DNI. Bienvenido al banco de la ETSIDI\n");	
									}
									else
									{
									printf("\nEl pin o el dni estan mal introducidos.\nPruebe otra vez\n\n");
									}
									
								}while (pinus!=usuarios[nombrepos].pin || dnius!=usuarios[nombrepos].DNI);
								
								fclose(registro);
							
							}while(fscanf(registro,"%i  %s\t%i\t%i\t%f\t",&cont1,usuarios[cont1].nombre,&usuarios[cont1].DNI,&usuarios[cont1].pin,&usuarios[cont1].dinero)!=EOF);
						}
				
					printf("Presione cualquier tecla para continuar: ");
					getch();
					break;
					
					}	
				}
			}
		}while(elige!=1 && elige!=2);
		printf("\n");
	}while(volver==1);
		
	do
	{
		system ("cls");
		printf("\n");
		printf("Elige su opcion:\n\n");
		printf("1 Retirar dinero:\n");
		printf("2 Ingresar dinero:\n");
		printf("3 Realizar una transferencia:\n");
		printf("4 Ver estado de cuenta:\n");
		printf("5 Acceder a las ofertas del banco:\n");
		printf("6 Salir:\n\n");
		scanf("%i",&opcion);
		printf("\n");
		switch(opcion)
		{
			case 1:
			{
				printf("Indique la cantidad de dinero que desee retirar de su cuenta:\n");
				scanf("%f",&dinero);
				usuarios[nombrepos].dinero = usuarios[nombrepos].dinero-dinero;
				printf("\nEspere unos segundos estamos actualizando su cuenta.\n");
				Sleep(2500);
				printf("Su cuenta se ha actualizado correctamente\n");
				printf("Presione cualquier tecla para continuar. ");
				getch();
				break;
			}
			case 2:
			{
				printf("Indique la cantidad de dinero que desee ingresar de su cuenta:\n");
				scanf("%f",&dinero);
				usuarios[nombrepos].dinero = usuarios[nombrepos].dinero+dinero;
				printf("\nEspere unos segundos estamos actualizando su cuenta.\n");
				Sleep(2500);
				printf("Su cuenta se ha actualizado correctamente\n");
				printf("Presione cualquier tecla para continuar. ");
				getch();
				break;
			}
			case 3:
			{
				printf("Ahora debera elegir al usuarios que desee hacer la transferencia.\n");
				printf("A continuacion se presentara una lista de todos los usuarios que dispone el cajero:\n\n");
				for(i=0;i<cont1;i++)
				{
					printf("%i:  %s\n",i+1,usuarios[i].nombre);
				}
				printf("\nTeclee el numero del usuario al que desee realizar una transferencia:");
				scanf("%i",&seleccion);
				seleccion=seleccion-1;
				printf("Teclee el dinero que desee transferir a la cuenta:\n");
				scanf("%f",&dinero);
				usuarios[nombrepos].dinero = usuarios[nombrepos].dinero - dinero;
				usuarios[seleccion].dinero = usuarios[seleccion].dinero + dinero;
				printf("\n\nEspere unos segundos estamos actualizando su cuenta.\n");
				Sleep(2500);
				printf("Su cuenta se ha actualizado correctamente. Gracias por realizar su tranferencia\n");
				printf("Presione cualquier tecla para continuar. ");
				getch();
				
				break;	
			}
			case 4:
			{
				printf("Su saldo a dia de hoy es:\n");
				printf("%.3f\n",usuarios[nombrepos].dinero);
				printf("Presione cualquier tecla para continuar. ");
				getch();
				break;
			}
			case 5:
			{
				printf("A continuacion le mostraremos todas las ofertas que dispone nuestro banco:\n\n");
				i=0;
				ofertas = fopen("ofertas.txt","r");
				if(ofertas == NULL)
				{
					printf("El fichero no se ha podido abrir\n");
				}
				else
				{
					i=0;
					printf("Numero  /Oferta	/Precio\n\n");
					for(i=0;i<S;i++)
					{
						fscanf(ofertas,"%i  %s\t%f\t",&tickets[i].codigo,tickets[i].nombre,&tickets[i].precio);
						printf("%i  %s\t%f\n",tickets[i].codigo,tickets[i].nombre,tickets[i].precio);	
					}
				
				printf("\nSeleccione la oferta que desee comprar\n");
				scanf("%i",&compra);
				compra = compra - 1;	
				usuarios[nombrepos].dinero = usuarios[nombrepos].dinero - tickets[compra].precio;
				printf("Actualizando cuenta\n");
				Sleep(2500);
				printf("Cuenta actualizada\n");
							
				fclose(ofertas);
				printf("Presione cualquier tecla para continuar. ");
				getch();
				}
				break;		
			}
			case 6:
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
						fprintf(registro,"%i  %s\t%i\t%i\t%.3f\n",i+1,usuarios[i].nombre,usuarios[i].DNI,usuarios[i].pin,usuarios[i].dinero);
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
	}while(opcion!=6);
}
