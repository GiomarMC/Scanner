#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAYOR	'>'
#define MENOR   '<'
#define IGUAL   '='
#define PUNTOYCOMA   ';'
#define COMA    ','
#define PARI	'('
#define PARF    ')'
#define CORI    '['
#define CORF    ']'
#define LLAVEI  '{'
#define LLAVEF  '}'
#define MAS '+'
#define MENOS   '-'
#define MULT    '*'
#define DIV '/'
#define ID 	256	
#define NUM 	257
#define MAYORIGUAL  258
#define WHILE	259
#define IF	260
#define MENORIGUAL  261
#define COMPARACION 262
#define DISTINTO    263
#define STRUCT 264
#define ELSE 265
#define INCLUDE 266

int scaner();
void mostrar(int);
int espalres();

FILE *f;
char lexema[80];


void main(int n, char *pal[])
{
	int token;
	f=stdin;	//entrada estandar del teclado
	if(n==2)         //si se especifico un archivo de lectura
	{
		f=fopen(pal[1],"rt");  //lectura modo texto
		if(f==NULL)
			f=stdin;
	}
	if(f==stdin)      //la lectura sera desde la entrada estandar
	     printf("Ingrese texto ........ termine con Ctrl z \n");

	while(1)
	{
		token=scaner();
		if(token==EOF) break;
		mostrar(token);
	}

	if(f !=stdin)   // si la entrada fue de un archivo
		fclose(f);  // entonces cerrar el archivo.
}//fin del main

int scaner()
{
	int c;
	int i;
	do
	{
		c=fgetc(f);
		//ignorar comentarios de linea y de bloque
		if(c=='/')
		{
			int next_char = fgetc(f);
			if(next_char == '/') //ignora comentario de linea
			{
				while(c != '\n' && c != EOF)
				{
					c = fgetc(f);
				}
			}
			else if(next_char == '*')
			{
				while(1) //ignorar comentario de bloque
				{
					c = fgetc(f);
					if(c == '*')
					{
						int next_char = fgetc(f);
						if(next_char == '/')
						{
							c = fgetc(f); //se lee el siguiente caracter luego de */
							break;
						}
					}
					else if(c == EOF)
					{
						return EOF; //fin del archivo sin encontrar el final del comentario
					}
				}
			}
			else
			{
				ungetc(next_char, f); //No era un comentario
			}
		}
	} while(isspace(c));  //ignora blancos

	if(c==EOF) return EOF;

	if(isalpha(c))   //regla del ID
	{
		i=0;
		do{
			lexema[i++]=c;
			c=fgetc(f);
		} while(isalnum(c)||c=='_');
		
		lexema[i]=0;
		ungetc(c,f);   //se devuelve c al flujo de entrada
		i=espalres();   // verifica si es palabra reservada 
		                        //  WHILE , IF 
		if(i>=0)
		   return i;
		return ID;    // se trata de un ID
	}

	if(isdigit(c))   //regla del NUM
	{
		i=0;
		do{
		   lexema[i++]=c;
		   c=fgetc(f);
		}while(isdigit(c));

		lexema[i]=0;
		ungetc(c,f);
		return NUM;
	}

                                          //regla de PUNTOYCOMA y PARI
	if((c==';')|| (c==',') ||(c=='(') || (c==')') || (c=='[')  || (c==']') || (c=='{') || (c=='}') || (c=='+') || (c=='-') || (c=='*') || (c=='/')) return c;      //regla del ";" y "("
	                                               
	if(c=='>')	//regla de ">" o ">="
	{
		c=fgetc(f);
		if(c=='=')   //return MAYORIGUAL
		{   lexema[0]='>';  lexema[1]='=';  lexema[2]=0;
		    return MAYORIGUAL;
		}
		ungetc(c,f);
		return MAYOR;  //return MAYOR
	}

    if(c=='<')	//regla de "<" o "<="
    {
        c=fgetc(f);
        if(c=='=')   //return MENORIGUAL
        {   lexema[0]='<';  lexema[1]='=';  lexema[2]=0;
            return MENORIGUAL;
        }
        ungetc(c,f);
        return MENOR;  //return MENOR
    }
    if(c=='=')	//regla de "=" o "=="
    {
        c=fgetc(f);
        if(c=='=')   //return COMPARACION
        {   lexema[0]='=';  lexema[1]='=';  lexema[2]=0;
            return COMPARACION;
        }
        ungetc(c,f);
        return IGUAL;  //return IGUAL
    }
    if(c=='!')	//regla de "!"
    {
        c=fgetc(f);
        if(c=='=')   //return DISTINTO
        {   lexema[0]='!';  lexema[1]='=';  lexema[2]=0;
            return DISTINTO;
        }
    }
}//fin de scaner

int espalres()
{
	if(strcmp(lexema,"while")==0) return WHILE;
	if(strcmp(lexema,"if")==0) return IF;
    if(strcmp(lexema,"else")==0) return ELSE;
    if(strcmp(lexema,"struct")==0) return STRUCT;
    if(strcmp(lexema,"include")==0) return INCLUDE;

	return -1;
}

void mostrar(int token)
{
    switch(token)
    {
        case ID: printf("token = ID [%s] \n",lexema);    break;
        case NUM: printf("token = NUM [%s] \n",lexema);    break;
        case MAYORIGUAL: printf("token = MAYORIGUAL [%s] \n",lexema); break;
        case WHILE: printf("token = WHILE [%s] \n",lexema);	break;
        case IF: printf("token = IF [%s] \n",lexema); break;	
        case PARI: printf("token = PARI [%c] \n",token);    break;
        case MAS: printf("token = MAS [%c] \n",token);    break;
        case MENOS: printf("token = MENOS [%c] \n",token);    break;
        case MULT: printf("token = MULT [%c] \n",token);    break;
        case DIV: printf("token = DIV [%c] \n",token);    break;
        case MAYOR: printf("token = MAYOR [%c] \n",token);    break;
        case PUNTOYCOMA: printf("token = PUNTOYCOMA [%c] \n",token);    break;
        case MENOR: printf("token = MENOR [%c] \n",token);    break;
        case IGUAL: printf("token = IGUAL [%c] \n",token);    break;
        case MENORIGUAL: printf("token = MENORIGUAL [%s] \n",lexema);    break;
        case COMPARACION: printf("token = COMPARACION [%s] \n",lexema);    break;
        case DISTINTO: printf("token = DISTINTO [%s] \n",lexema);    break;
        case PARF: printf("token = PARF [%c] \n",token);    break;
        case CORI: printf("token = CORI [%c] \n",token);    break;
        case CORF: printf("token = CORF [%c] \n",token);    break;
        case LLAVEI: printf("token = LLAVEI [%c] \n",token);    break;
        case LLAVEF: printf("token = LLAVEF [%c] \n",token);    break;
        case COMA: printf("token = COMA [%c] \n",token);    break;
        case ELSE: printf("token = ELSE [%s] \n",lexema);    break;
        case STRUCT: printf("token = STRUCT [%s] \n",lexema);    break;
        case INCLUDE: printf("token = INCLUDE [%s] \n",lexema);    break;
    }
}