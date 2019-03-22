#include <stdio.h>
void main()
{
	int opcion,elige;
	printf("Bienvenido al banco de la etsidi \n\n");
	printf("	MENU\n");
	do
	{
		printf("\n");
		printf("Elige lo que desee hacer:\n\n");
		printf("1 Crear nueva cuenta:\n");
		printf("2 Iniciar sesion:\n\n");
		fflush(stdin);
		scanf("%i",&elige);	
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
		fflush(stdin);
		scanf("%i",&opcion);
		printf("\n");
		switch(opcion)
		{
			case 1:
			{
					
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
				printf("Gracias por todo hasta la proxima\n");
				break;	
			}
			default:
				printf("Opcion incorrecta\n");
		}
	}while(opcion!=4);
}
