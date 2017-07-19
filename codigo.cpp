#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>

#define bool int
#define true 1
#define false 0

#define ANCHO 100
#define LARGO 30

FILE *fichero;

struct puntajes
{
  
	char nombreT[10];
	int turnosT;
	
} top10[11], ganador, aux;

char tablero1[7][9];
char tablero2[7][9];
char golpes1[7][9];
char golpes2[7][9];
char nomJugador[2][10];
int jugador, i, j, k, l, ti, tj, vidas[2], turnos[2];
int cooY, cooX;

char nombreR[10];
int turnosR;

void dibujarTablero(int gtx, int reng = 0);
void info();
void iniciar();
void barco();
int convertir(char y);
void acomodar(int pl);
void secuencia();
void clear();
void jugar();
void gotoxy(int x, int y);
void victoria();
void mibeep(int tipo);
int agregar_record();
int consultar_record();
void vaciar_record();

int main()
{
	
	char opc;
	
	system("mode con cols=100");
	system("mode con lines=30");
	
	do
	{
		
		system("cls");
		system("color 19");
		barco();
		
		gotoxy(34,13); printf("BIENVENID@S A BATALLA NAVAL!!!");
		gotoxy(39,16); printf("J...\tJugar");
		gotoxy(39,17); printf("I...\tInformacion");
		gotoxy(39,18); printf("R...\tRecords");
		gotoxy(39,19); printf("S...\tSalir");
		
		gotoxy(47,23); printf("( )");
		gotoxy(48,23); fflush(stdin);
		opc = getche();
		
		switch(tolower(opc))
		{
			
			case 'i':
				info();
				break;
				
			case 'j':
				secuencia();
				break;
				
			case 'r':
				consultar_record();
				break;
				
			case 's':
				system("cls");
				gotoxy(39,14); printf("GRACIAS POR JUGAR!!!");
				gotoxy(0,27);
				getch();
				return 0;
				break;
				
			default:
				printf("\n\nLo siento, no existe esa opcion...\n\n");
				getch();
			
		}
		
	} while ( tolower(opc) != 's' );
	
}

void dibujarTablero(int gtx, int reng)
{
	
	gotoxy(gtx,reng); printf("     A   B   C   D   E   F   G   H   I\n");
	reng += 1;
	gotoxy(gtx,reng); printf("   \xDA\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xBF\n");
	for ( ti = 0 ; ti < 7 ; ti++ )
	{
		
		reng += 1;
		gotoxy(gtx,reng); printf(" %d ", ti+1);
		for ( tj = 0 ; tj < 9 ; tj++ )
		{
			if ( jugador == 0 )

			{
				
				printf("\xB3 %c ", tablero1[ti][tj]);
				
			}
			else if ( jugador == 1 )
			{
				
				printf("\xB3 %c ", tablero2[ti][tj]);
				
			}
			else if ( jugador == 2 )
			{
				
				printf("\xB3 %c ", golpes1[ti][tj]);
				
			}
			else
			{
				
				printf("\xB3 %c ", golpes2[ti][tj]);
				
			}
			
		}
		printf("\xB3\n");
		
		if ( ti < 6 )
		{
		
			reng += 1;
			gotoxy(gtx,reng); printf("   \xC3\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xB4\n");
			
		}
		
	}
	reng += 1;
	gotoxy(gtx,reng);
	printf("   \xC0\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xD9\n");
	
}

void info()
{

	system("cls");
	barco();
	gotoxy(37,12); printf("Hecho por Fernando Wong.");
	gotoxy(14,13); printf("Desarrollado en el cuatrimestre 17 - 2 para el profesor Miguel Galindo");
	gotoxy(13,14); printf("para que cubra el proyecto final de Elementos de Programacion Estructurada");
	gotoxy(20,15); printf("asi como el proyecto de Algoritmos y Estructuras de Datos.");
	gotoxy(39,18); printf("Temas cubiertos:");
	gotoxy(39,20); printf("Estructuras de datos.");
	gotoxy(39,21); printf("Funciones.");
	gotoxy(39,22); printf("Uso de archivos.");
	gotoxy(39,23); printf("Funcion gotoxy.");
	gotoxy(39,24); printf("Ordenacion burbuja.");
	gotoxy(39,25); printf("Etc.  ");
	getch();
	
}

void clear()
{
	
	for ( k = 0 ; k < 9 ; k++ )
	{
		
		for ( l = 0 ; l < 7 ; l++ )
		{
			
			if ( tablero1[l][k] != NULL )
			{
				
				tablero1[l][k] = NULL;
				
			}
			
			if ( tablero2[l][k] != NULL )
			{
				
				tablero1[l][k] = NULL;
				
			}
			
		}
		
	}
	
}

void iniciar()
{
	
	system("cls");
	fflush(stdin); gotoxy(30,13);
	printf("Nombre de jugador 1: "); gets(nomJugador[0]);
	fflush(stdin); gotoxy(30,15);
	printf("Nombre de jugador 2: "); gets(nomJugador[1]);
	
}

void barco()
{
	
	gotoxy(29,0); printf("              |    |    |");
	gotoxy(29,1); printf("             )_)  )_)  )_)");
	gotoxy(29,2); printf("            )___))___))___)\\");
	gotoxy(29,3); printf("           )____)____)_____)\\\\");
	gotoxy(29,4); printf("         _____|____|____|____\\\\\\\__");
	gotoxy(29,5); printf("---------\\                   /---------");
	gotoxy(29,6); printf("  ^^^^^ ^^^^^^^^^^^^^^^^^^^^^^^^^");
	gotoxy(29,7); printf("    ^^^^      ^^^^     ^^^    ^^");
	gotoxy(29,8); printf("         ^^^^      ^^^");
	gotoxy(17,9); printf("*************************BATALLA NAVAL!*************************\n\n");
	
}

int convertir(char y)
{
	
	int coor;
	
	switch(tolower(y))
	{
		
		case 'a':
			coor = 0;
			break;
			
		case 'b':
			coor = 1;
			break;
			
		case 'c':
			coor = 2;
			break;
				
		case 'd':
			coor = 3;
			break;
		
		case 'e':
			coor = 4;
			break;
			
		case 'f':
			coor = 5;
			break;
		
		case 'g':
			coor = 6;
			break;
		
		case 'h':
			coor = 7;
			break;
		
		case 'i':
			coor = 8;
			break;
		
	}
	
	return coor;
	
}

void acomodar()
{
	
	char coor, pos, barL;
	
	for ( j = 4 ; j >= 2 ; j-- )
	{
		
		switch(j)
		{
			
			case 4:
				barL = 'A';
				break;
				
			case 3:
				barL = 'B';
				break;
				
			case 2:
				barL = 'C';
				break;
			
		}
		
		system("cls");
		dibujarTablero(28);
		
		gotoxy(35,19); printf("El barco %c ocupa %d espacios.",barL, j);
		
		do
		{
			
			fflush(stdin);
			gotoxy(34,21); printf("Vertical u horizontal? (v/h): ");
			pos = getche();
			
			if ( tolower(pos) == 'v' )
			{
				
				gotoxy(26,26); printf("-> Se colocara automaticamente hacia abajo. <-");
				
			}
			else if ( tolower(pos) == 'h' )
			{
				
				gotoxy(24,26); printf("-> Se colocara automaticamente hacia la derecha <-");
				
			}
			
		} while ( tolower(pos) != 'v' && tolower(pos) != 'h' );
		
		again:
		
		fflush(stdin);
		gotoxy(34,22); printf("Elige las coordenadas del frente");
		gotoxy(42,23); printf("(A-I> ( , ) <1-7)");
		gotoxy(28,25); printf("(Presiona Enter luego de la coordenada.)");
		gotoxy(49,23); coor = getche();
		gotoxy(51,23); scanf("%d", &cooY);
		cooY -= 1;
		cooX = convertir(coor);
		
		if ( tolower(pos) == 'v' )
		{
			
			if ( 7 - cooY >= j )
			{
				
				for ( i = 0 ; i < j ; i++ )
				{
					
					if ( jugador == 0 )
					{
						
						if ( tablero1[cooY+i][cooX] == NULL )
						{
						
							tablero1[cooY+i][cooX] = barL;
						
						}
						else
						{
							
							for ( k = 0 ; k < 9 ; k++ )
							{
								
								for ( l = 0 ; l < 7 ; l++ )
								{
									
									if ( tablero1[l][k] == barL )
									{
										
										tablero1[l][k] = NULL;
										
									}
									
								}
								
							}
							
							
							gotoxy(26,26);
							printf("                                              ");
							gotoxy(38,26);
							printf("El barco no cabe aqui.");
							goto again;
							
						}
						
					}
					else
					{
						
						if ( tablero2[cooY+i][cooX] == NULL )
						{
						
							tablero2[cooY+i][cooX] = barL;
						
						}
						else
						{
							
							for ( k = 0 ; k < 9 ; k++ )
							{
								
								for ( l = 0 ; l < 7 ; l++ )
								{
									
									if ( tablero2[l][k] == barL )
									{
										
										tablero2[l][k] = NULL;
										
									}
									
								}
								
							}
							
							gotoxy(26,26);
							printf("                                              ");
							gotoxy(38,26);
							printf("El barco no cabe aqui.");
							goto again;
							
						}
						
					}
					
				}
				
			}
			else
			{
				
				gotoxy(26,26);
				printf("                                              ");
				gotoxy(38,26);
				printf("El barco no cabe aqui.");
				goto again;
				
			}
			
		}
		else
		{
			
			if ( 9 - cooX >= j )
			{
				
				for ( i = 0 ; i < j ; i++ )
				{
					
					if ( jugador == 0)
					{
						
						if ( tablero1[cooY][cooX+i] == NULL )
						{
						
							tablero1[cooY][cooX+i] = barL;
						
						}
						else
						{
							
							for ( k = 0 ; k < 9 ; k++ )
							{
								
								for ( l = 0 ; l < 7 ; l++ )
								{
									
									if ( tablero1[l][k] == barL )
									{
										
										tablero1[l][k] = NULL;
										
									}
									
								}
								
							}
							
							gotoxy(26,26);
							printf("                                              ");
							gotoxy(38,26);
							printf("El barco no cabe aqui.");
							goto again;
							
						}
						
					}
					else
					{
						
						if ( tablero2[cooY][cooX+i] == NULL )
						{
						
							tablero2[cooY][cooX+i] = barL;
						
						}
						else
						{
							
							for ( k = 0 ; k < 9 ; k++ )
							{
								
								for ( l = 0 ; l < 7 ; l++ )
								{
									
									if ( tablero2[l][k] == barL )
									{
										
										tablero2[l][k] = NULL;
										
									}
									
								}
								
							}
							
							gotoxy(26,26);
							printf("                                              ");
							gotoxy(38,26);
							printf("El barco no cabe aqui.");
							goto again;
							
						}
						
					}
					
				}
				
			}
			else
			{
				
				gotoxy(26,26);
				printf("                                              ");
				gotoxy(38,26);
				printf("El barco no cabe aqui.");
				goto again;
				
			}
			
		}
		
	}
	
	system("cls");
	gotoxy(40,3);
	printf("Este es tu tablero");
	
	dibujarTablero(28,6);
	
	vidas[jugador] = 9;
	
	fflush(stdin);
	getchar();
	
}

void secuencia()
{
		
	int ai, ancho;
	
	iniciar();
	
	for ( ai = 0 ; ai < 2 ; ai++ )
	{
		
		jugador = ai;
		if ( jugador == 0 ) system("color 20");
		else system("color 4f");
		system("cls");
		ancho = floor( ( ANCHO - strlen(nomJugador[jugador]) - 20 ) / 2 ) - 1;
		gotoxy(ancho,14); printf("Almirante %s esta list@?", nomJugador[jugador]);
		getchar();
		acomodar();
		
	}
	
	turnos[0] = 0;
	turnos[1] = 0;
	jugador = 0;
	
	do
	{
	
		system("cls");
		if ( jugador == 0 ) system("color 20");
		else system("color 4f");
		ancho = floor( ( ANCHO - strlen(nomJugador[jugador]) - 20 ) / 2 ) - 1;
		gotoxy(ancho,14); printf("Almirante %s esta list@?", nomJugador[jugador]);
		turnos[jugador]++;
		getchar();
		jugar();
		
		if ( jugador == 0 )
		{
			
			jugador = 1;
			
		}
		else
		{
			
			jugador = 0;
			
		}
		
	} while( vidas[0] != 0 && vidas[1] != 0 );
	
	victoria();
	
}

void jugar()
{
	int cent;
	char coor;
	
	system("cls");
	dibujarTablero(7);
	jugador += 2;
	dibujarTablero(53);
	jugador -= 2;
	cent = floor((ANCHO-(38+strlen(nomJugador[jugador])))/2);
	gotoxy(cent,19);
	printf("Almirante %s, su siguiente movimiento:", nomJugador[jugador]);
	tirar:
	gotoxy(42,21); printf("(A-I> ( , ) <1-7)");
	gotoxy(28,23); printf("(Presiona Enter luego de la coordenada.)");
	gotoxy(49,21); coor = getche();
	gotoxy(51,21); scanf("%d", &cooY);
	cooY -= 1;
	cooX = convertir(coor);
	getchar();
	
	if ( jugador == 0 )
	{
		
		if( tablero2[cooY][cooX] == 'A' || tablero2[cooY][cooX] == 'B' || tablero2[cooY][cooX] == 'C' )
		{
			
			tablero2[cooY][cooX] = 'O';
			golpes1[cooY][cooX] = 'O';
			vidas[1] -= 1;
			jugador += 2;
			dibujarTablero(53);
			jugador -= 2;
			gotoxy(43,25); printf("Le has dado!");
			
		}
		else if ( tablero2[cooY][cooX] == 'X' || tablero2[cooY][cooX] == 'O' )
		{
			
			gotoxy(41,25); printf("Ya atacaste ahi!"); getch();
			gotoxy(41,25); printf("                ");
			goto tirar;
			
		}
		else
		{
			
			tablero2[cooY][cooX] = 'X';
			golpes1[cooY][cooX] = 'X';
			jugador += 2;
			dibujarTablero(53);
			jugador -= 2;
			gotoxy(43,25); printf("Has fallado!");
			
		}
		
		fflush(stdin);
		getch();
		
	}
	else
	{
		
		if( tablero1[cooY][cooX] == 'A' || tablero1[cooY][cooX] == 'B' || tablero1[cooY][cooX] == 'C' )
		{
			
			tablero1[cooY][cooX] = 'O';
			golpes2[cooY][cooX] = 'O';
			vidas[0] -= 1;
			jugador += 2;
			dibujarTablero(53);
			jugador -= 2;
			gotoxy(43,25); printf("Le has dado!");
			
		}
		else if ( tablero1[cooY][cooX] == 'X' || tablero1[cooY][cooX] == 'O' )
		{
			
			gotoxy(41,25); printf("Ya atacaste ahi!"); getch();
			gotoxy(41,25); printf("                ");
			goto tirar;
			
		}
		else
		{
			
			tablero1[cooY][cooX] = 'X';
			golpes2[cooY][cooX] = 'X';
			jugador += 2;
			dibujarTablero(53);
			jugador -= 2;
			gotoxy(43,25); printf("Has fallado!");
			
		}
		
		fflush(stdin);
		getch();
		
	}
	
}

void victoria()
{
	
	int ancho;
	agregar_record();
	
	system("color 19");
	system("cls");
	
	if ( vidas[0] > 0 )
	{
		
		ancho = floor( ( ANCHO - strlen(nomJugador[0]) - 20 ) / 2 ) - 1;
		gotoxy(ancho, 14); printf("LA VICTORIA ES DE ");
		for ( i = 0 ; i < strlen(nomJugador[0]) ; i++ ) putchar(toupper(nomJugador[0][i]));
		printf("!!");
		
	}
	else
	{
		
		
		ancho = floor( ( ANCHO - strlen(nomJugador[1]) - 20 ) / 2 ) - 1;
		gotoxy(ancho,14); printf("LA VICTORIA ES DE ");
		for ( i = 0 ; i < strlen(nomJugador[1]) ; i++ ) putchar(toupper(nomJugador[1][i]));
		printf("!!");
		
	}
	
	system("color 27");
	Sleep(1000);
	system("color 47");
	Sleep(1000);
	system("color 57");
	Sleep(1000);
	system("color 60");
	Sleep(1000);
	system("color e0");
	Sleep(1000);
}

void mibeep(int tipo)
{

	switch (tipo)
	{
		
	    case 1:
	    	Beep(1000,50);
	    	Beep(3000,50);
	    	Beep(2000,50);
		    break;
	    case 2:
	    	Beep(100,1000);
		    break;
	    case 3:
	    	Beep(3000,50);
		    Sleep(50);
		    Beep(3000,50);
		    break;
		case 4:
			Beep(440,1000);
		    
	}
 
  }

void gotoxy(int x, int y)
{
	
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon,dwPos);
	
}

int agregar_record()
{
	
	system("cls");
	system("color 19");
		
	if ( (fichero = fopen("Records.txt","r")) == NULL )
	{
		
		fflush(stdin);
		gotoxy(25,12); printf("ATENCION!! El archivo no existe o esta corrupto.");
		gotoxy(32,13); printf("Presione una tecla para crearlo..."); getche();
		fichero = fopen("Records.txt", "w");
		gotoxy(47,14); printf("...."); Sleep(2000);
		gotoxy(47,15); printf("...."); Sleep(2000);
		gotoxy(47,16); printf("...."); Sleep(2000);
		gotoxy(35,17); printf("Archivo creado con exito!!!!");
		getchar();
		return 0;
		
	}
	else
	{
		
		bool top;
		int g = 0, lugares = 1;
		
		if ( vidas[0] > 0 ) 
		{
			
			ganador.turnosT = turnos[0];
			strcpy(ganador.nombreT,nomJugador[0]);
			
		}
		else
		{
			
			ganador.turnosT = turnos[1];
			strcpy(ganador.nombreT,nomJugador[1]);
			
		}
		
		while ( !feof(fichero) )
		{
			
			fscanf(fichero, "%s %d\n", &nombreR, &turnosR);
			if ( ganador.turnosT < turnosR || lugares <= 10 )
			{
				
				top = true;
				break;
				
			}
			lugares++;
			
		}
		
		fclose(fichero);
		
		if (top)
		{
			
			fichero = fopen("Records.txt", "r");
			
			while( !feof(fichero) )
			{
				
				fscanf(fichero, "%s %d\n", &top10[g].nombreT, &top10[g].turnosT);
				g++;
				
			}
			
			if ( g < 9 )
			{
				
				fprintf(fichero, "%s %d\n", ganador.nombreT, ganador.turnosT);
				fclose(fichero);
				return 0;
				
			}
			else
			{
				
				top10[10] = ganador;
				
				for ( i = 0 ; i <= 10 ; i++ )
				{
					
					for ( j = 0 ; j <= 9 ; j++ )
					{
						
						if ( top10[j].turnosT > top10[j+1].turnosT )
						{
							
							aux = top10[j];
							top10[j] = top10[j+1];
							top10[j+1] = aux;
							
						}
						
					}
					
				}
				
				fclose(fichero);
				
				fichero = fopen("Records.txt", "w");
				
				for ( i = 0 ; i < 10 ; i++ )
				{
					
					fprintf(fichero, "%s %d\n", top10[i].nombreT, top10[i].turnosT);
					
				}
				
				fclose(fichero);
				return 0;
				
			}
			
		}
		
	}
	
	return 0;
	
}

int consultar_record()
{
	
	system("cls");
	
	if ( (fichero = fopen("Records.txt","r")) == NULL )
	{
		
		fflush(stdin);
		gotoxy(25,12); printf("ATENCION!! El archivo no existe o esta corrupto.");
		gotoxy(32,13); printf("Presione una tecla para crearlo..."); getche();
		fichero = fopen("Records.txt", "w");
		gotoxy(47,14); printf("...."); Sleep(2000);
		gotoxy(47,15); printf("...."); Sleep(2000);
		gotoxy(47,16); printf("...."); Sleep(2000);
		gotoxy(35,17); printf("Archivo creado con exito!!!!");
		getchar();
		return 0;
		
	}
	else
	{
		
		int lugarR = 1, pX = 10;
		char opcR, borR;
		
		gotoxy(36,8); printf("#L  Nombre         Turnos");
		
		while( !feof(fichero) )
		{
			
			fscanf(fichero,"%s %d", nombreR, turnosR);
			gotoxy(36,pX); printf("%d.- %-15s\t%d", lugarR, nombreR, turnosR);
			pX++; lugarR++;
			
		}
		
		fclose(fichero);
		
		final:
		fflush(stdin);
		gotoxy(33,21); printf("S... Salir     ||     L... Limpiar");
		gotoxy(47,22); printf("( )");
		gotoxy(48,22); opcR = getche(); opcR = tolower(opcR);
		
		if ( opcR == 's' ) return 0;
		else
		{
			
			gotoxy(22,23); printf("Desea limpiar permanentemente los registros? (s/n): ");
			borR = getche();
			
			if ( tolower(borR) == 's' ) vaciar_record();
			else
			{
				
				gotoxy(22,23); printf("                                                     ");
				goto final;
				
			}
			
		}
		
	}
	
	return 0;
	
}

void vaciar_record()
{
	
	system("cls");
	fichero = fopen("Records.txt", "w");
	fclose(fichero);
	gotoxy(29,29); printf("Los records han sido borrados con exito.");
	getch();
	
}
