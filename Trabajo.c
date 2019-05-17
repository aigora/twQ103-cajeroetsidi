/*
Título: Cajero de la ETSIDI
Autores:
Rocio Berzal Cabetas 53674
Manuel Degano Fernández-Mayo 53222
Marcos Calderon Jimeno 53855
*/
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#define N 100
#define S 10
#define L 20

//funcion para contar el numero de cifras de un numero que utilizaremos al introducir un numero y poner un limite de cifras.
//funcion para saber si un número es decimal o no.

int cuenta_cifras(int x);
int num_decimal(float num);

//etructuras para almacenar cada usuario introducido por el ordenador y otra para guardar cada
//oferta que proporciona el banco.

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
	int pinus,dnius,compra,cifras=0,decimal=0;
	int longitud_max_oferta = 11,longitud_max_nombre = 4;
	char nombreus[15],caracter;
	struct persona usuarios[N];
	FILE *registro;
	FILE *ofertas;
	float dinero,compradec;
	int seleccion;
	char persona[N];
	
	//creamos una estructura para las ofertas del banco para guardarlas en un fichero llamado ofertas
	struct oferta tickets[S] = {{1,"Viaje_a_Londres",120},
							    {2,"Cine",3.90},
							    {3,"Concierto", 42.8},
							    {4,"Puenting", 100},
								{5,"Zoo",35.25},
								{6,"Atracciones", 28.75},
								{7,"McDonalds", 6.9},
								{8,"Paseo_en_helicoptero", 80.0},
								{9,"Salto_base", 5.0},
								{10,"Visita_Museo",10.0}};
	
	/*abrimos el fichero que contiene los registros y contamos el numero de personas registradas para guardar si se introduce un nuevo
	usuario en la siguiente posicion del fichero en vez de en la posición 0 del vector.*/							
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
	
	/*Abrimos el fichero de ofertas y escribimos todas las ofertas guardadas en una estructura previamente.*/
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
		
		/*Empezamos a escribir cosas por pantalla primero asignamos un color distinto al de partida y dejamos al usuario escoger entre 
		2 opciones y estas se repetiran cada vez que se introduzca una distinta*/
		do
		{
			system("cls");
			system("Color B");
			printf("---------------------------------------\n");
			printf("---BIENVENIDO AL BANCO DE LA ETSIDI--- \n");
			printf("---------------------------------------\n\n");
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
				/*En el case 1 crearemos el usuario con dni pin y nombre y el programa repetira si se introduce un dni mayor a 8 cifras,
				un pin mayor a 4 cifras y si introduces un nombre de usuario que ya este en uso. Esta ultima parte se realizara abriendo
				el fichero en modo lectura y haciendo que el programa lea el fichero de usuarios para comprobar si el nombre ya es existente.
				Solo leerá en el fichero la columna de los nombres.*/
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
						
						cifras=0;					
						printf("\nIntroduzca su DNI (sin letra y que no empiece por 0):\n");//Modificar luego poner limite de numeros
						scanf("%i",&usuarios[cont1].DNI);
						cifras = cuenta_cifras(usuarios[cont1].DNI);
						if(cifras>=9)
						{
							printf("Su DNI sobrepasa el numero de cifras admitido. Pruebe con otro\n");
						}
					
					}while(cifras>=9);
					
					cifras=0;
					do
					{
			
						cifras=0;
						printf("\nIntroduzca su PIN (solo numeros, 4 digitos y que no empiece por 0):\n");//Modificar luego poner limite de numeros 4
						scanf("%i",&usuarios[cont1].pin);
						cifras = cuenta_cifras(usuarios[cont1].pin);
						if(cifras>=5)
						{
							printf("Su codigo PIN sobrepasa el numero de cifras admitido. Pruebe con otro mas corto\n");
						}
						
					}while(cifras>=5);
							
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
				
				/*En el case 2 se iniciará sesión y para ello se abrirá el fichero en modo lectura y esta vez si que se leerá todo el fichero.
				Primero se introducirá el numbre de usuario y una vez que sea correcto el nombre el programa guardara esa posición para que el
				dni t el pin introducidos posteriormente solo sean validos si son el de la posicion del nombre. Es decir a cada usuario le corresponde
				un único pin y un dni. El programa se repitirá cuando el pin o el dni sean incorrectos.*/
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
	
	/*Este es el segundo menu del programa el cual te dejará elegir entre muchas opciones y te repetirá el 
	menu si introduces una opcion distinta a la de salida. O distinta a las proporcionadas en el menu.*/	
	do
	{
		system ("cls");
		printf("\n");
		printf("----------------\n");
		printf("----- MENU -----\n");
		printf("----------------\n");
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
			/*En este case se modificará en la posición del usuario que ha iniciado sesión la parte de la estructura
			que pertenece al dinero. Esta opción al ser de retirar disminuirá su cuenta en la cantidad que corresponda 
			al número introducido.*/
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
			/*Este case es igual que el anterior pero en vez de retirar añades dinero a la cuenta.*/
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
			/*Este case simulará una trasferencia en la cual primero leemos el fichero del regstro y imprimimos todos
			los nombres por la pantalla. Luego se le pedirá al usuario que teclee el número con el que se desee interactuar.
			Se guardara la posición introducida y se modifica la estructura en la parte de dinero según el número introducido por teclado
			en el del usuario se retirará el dinero y en el seleccionado se le añadirá.*/
			case 3:
			{
				printf("Ahora debera elegir al usuario que desee hacer la transferencia.\n");
				printf("A continuacion se presentara una lista de todos los usuarios que dispone el cajero:\n\n");
				for(i=0;i<cont1;i++)
				{
					printf("%-*i%s\n",longitud_max_nombre,i+1,usuarios[i].nombre);
				}
				printf("\nTeclee el numero del usuario al que desee realizar una transferencia:\n");
				scanf("%i",&seleccion);
				seleccion=seleccion-1;
				printf("Teclee el dinero que desee transferir a la cuenta:\n");
				scanf("%f",&dinero);
				
				usuarios[nombrepos].dinero = usuarios[nombrepos].dinero - dinero;
				usuarios[seleccion].dinero = usuarios[seleccion].dinero + dinero;
				
				printf("\nEspere unos segundos estamos actualizando su cuenta.\n");
				Sleep(2500);
				printf("Su cuenta se ha actualizado correctamente. Gracias por realizar su tranferencia\n");
				printf("Presione cualquier tecla para continuar. ");
				getch();
				
				break;	
			}
			/*Este case simplemente le mostrará por pantalla el estado de su cuenta. Imprimirá de la estructura la parte del dinero.
			Si su cuenta esta en números negativos se le mostrará una aviso.*/
			case 4:
			{
				printf("Su saldo a dia de hoy es:\n");
				printf("%.3f $\n",usuarios[nombrepos].dinero);
				
				if(usuarios[nombrepos].dinero<0)
				{
					printf("\nLe informamos que su cuenta esta en numeros negativos.\nDebera realizar un ingreso para no cerrar su cuenta.\n\n");
				}
				
				printf("Presione cualquier tecla para continuar. ");
				getch();
				break;
			}
			/*En este case se leera el fichero de las ofertas y se imprimirán todas por pantalla. Después, se pedira al usuario que introduzca el 
			numero de la oferta que desee comprar. Una vez introducido se modificará la estructura de ese usuario en la posición del dinero restandole
			el dinero correspondiente a esa oferta.(Resta de estructuras).*/
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
					printf("Numero  /Oferta	        /Precio($)\n\n");
					for(i=0;i<S;i++)
					{
						fscanf(ofertas,"%i  %s\t%f\t",&tickets[i].codigo,tickets[i].nombre,&tickets[i].precio);
						printf("%-*i  %-*s%.2f\n",3,tickets[i].codigo,longitud_max_oferta+10,tickets[i].nombre,tickets[i].precio);	
					}
				do
				{
					fflush(stdin);
					printf("\nSeleccione la oferta que desee comprar\n");
					scanf("%i",&compra);
					
					if(compra<1 || compra >10)
					{
						printf("El numero de compra introducido no es ninguno de los proporcionados.\nPor favor pruebe otra vez.\n\n");
					}
					else 
					{
						printf("El numero introducido es correcto.\n");
					}
					
				}while(compra<1 || compra >10);
				
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
			/*En este último case se abrirá el fichero del registro en modo de escritura y se reescribira el vector de estructuras que se 
			ha modificado a lo largo del programa. No solo se introducirán en el fichero los nuevos usuarios sino que se reescribirán todos
			desde la posición 0 hast la que hayamos llegado.*/
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
				printf("Opcion incorrecta. Pruebe con otra opcion.\n");
				getch();
		}
	}while(opcion!=6);
}

int cuenta_cifras(int num)
{
	int cifras=1;
	while(num/10>0)
	{
		num=num/10;
		cifras++;
	}
	return cifras;
}

int num_decimal(float num)
{
	int num_entero = (int) num;
	int x;
	
	if(num != num_entero)
	{
		printf("Numero decimal.\n");
		return x=1;
	}
	else
	{
		printf("No es decimal.\n");
		return x=0;
	}
}
