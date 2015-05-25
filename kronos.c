/*

5) Explicación de alternativas y estrategias consideradas:

Alternativas: 
  Manejar fecha como la ingresa el usuario - char*- y separar los campos,
o convertir esa cadena a un número -unsigned long int- y operar 
matemáticamente usando las funciones módulo y división.
  Se resolvió utilizar la segunda opción ya que las funciones aritméticas son 
más rápidas y livianas que las de manejo de cadenas de caracteres o de memoria.


asdasdasdasdasdasd
asdasd


*/


typedef unsigned long ulong;

status_t validate_arguments(int argc,char* argv[],char*date1_fmt,ulong*p_date1,char*date2_fmt,ulong*p_date2,char*p_output_unit,size_t*p_precision)
{
  size_t i,  args_to_parse;
  char * temp;

  if(argc!=CMD_ARG_ARGC)
    return ERROR_QUANTITY_ARGS;
  if(*argv==NULL||p_date1_fmt==NULL||p_date1==NULL||p_date2_fmt==NULL||p_date2==NULL||p_)
    return ERROR_NULL_POINTER;

  for(i=1,args_to_parse=argc-1;i<argc-1;i+=2)
  {
    if(!strcmp(argv[i],CMD_ARG_CANT_TOKEN))
    {
      *cant=strtod(argv[i+1],&temp);
      if(*temp){
        return ERROR_PROGRAM_INVOCATION;
      }
      args_to_parse-=2;
    }
    if(!strcmp(argv[i],CMD_ARG_LIM_INF_TOKEN))
    {
      *lim_inf=strtod(argv[i+1],&temp);
      if(*temp){
        return ERROR_PROGRAM_INVOCATION;
      }
      args_to_parse-=2;
    }
    if(!strcmp(argv[i],CMD_ARG_LIM_SUP_TOKEN))
    {
      *lim_sup=strtod(argv[i+1],&temp);
      if(*temp){
        return ERROR_PROGRAM_INVOCATION;
      }
      args_to_parse-=2;
    }
  }
  if(args_to_parse)
    return ERROR_PARSING;
  if(*cant<=0)
    return ERROR_INVALID_QUANTITY;
  if(*lim_sup<*lim_inf)
    return ERROR_INVALID_LIMITS;
  return OK;
}
/*****************************************************************/
/* SE PROPONE QUE LOS FORMATOS DE FECHA ESTEN CARGADOS EN UN ARR */
/* ESTATICO DEFINIDO COMO DICCIONARIO. DE ESTA MANERA SE COMPARA */
/* LA BANDERA QUE INGRESE EL USUARIO CON ALGUNO DE LAS PALABRAS  */
/* DEL DICCIONARIO Y EN BASE A ELLO, SE EJECUTA ---------------- */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATE_FORMAT_WITH_HOUR "DDMMAAAAhhmmss"
#define DATE_FORMAT_WITH_HOUR_LEN 14
#define DATE_FORMAT_DATE "DDMMAAAA"
#define DATE_FORMAT_DATE_LEN 8
#define DATE_FORMAT_JULIAN "DDDAAAA"
#define DATE_FORMAT_JULIAN_LEN 7
#define QTY_FORMATS 3

#define CMD_ARG_QTY_PROGRAM_ARGS 13
#define CMD_ARG_POSITION_FIRST_FLAG 1
#define FLAG_TO_FLAG_STEP 2
#define CMD_ARG_FLAG_FORMAT_1 "-fmt1"
#define CMD_ARG_FLAG_FORMAT_2 "-fmt2"
#define CMD_ARG_FLAG_DATE_1 "-f1"
#define CMD_ARG_FLAG_DATE_2 "-f2"
#define CMD_ARG_FLAG_OUT_UNIT "-u"
#define CMD_ARG_FLAG_PRECISION "-p"
#define CMD_ARG_ARGC 13

#define TIME_UNIT_FLAG_SECONDS 's'
#define TIME_UNIT_FLAG_MINUTES 'm'
#define TIME_UNIT_FLAG_HOURS 'h'
#define TIME_UNIT_FLAG_DAYS 'd'

#define MSG_ERROR_FEW_ARGS "Error, pocos argumentos en su linea de orden."
#define MSG_ERROR_MANY_ARGS "Error, demasiados argumentos en su linea de orden."
#define MSG_ERROR_INVALID_ARG "Error, argumento invalido."
#define MSG_ERROR_NULL_POINTER "Error de puntero nulo."
#define MSG_ERROR_INVALID_DATE_1 "Error, La fecha 1 ingresada es invalida."
#define MSG_ERROR_INVALID_DATE_2 "Error, La fecha 2 ingresada es invalida."
#define MSG_ERROR_INVALID_OUT_UNIT "Error, La unidad especificada es invalida."
#define MSG_ERROR_INVALID_PRECISION "Error, La precision especificada es invalida."
#define MSG_ERROR_INVALID_FORMAT_1 "Error, El formato para la fecha 1 es invalido."
#define MSG_ERROR_INVALID_FORMAT_2 "Error, El formato para la fecha 2 es invalido."
#define MSG_ERROR_REPEATED_ARG "Error, Se ha repetido una bandera."


/******************************* TIPOS ENUMERATIVOS Y ESTRUCTURAS ***************/
typedef enum{ERROR = -2, OK = -1, ERROR_FEW_ARGS = 0, ERROR_MANY_ARGS = 1, ERROR_INVALID_ARG = 2, ERROR_NULL_POINTER = 3, ERROR_INVALID_DATE_1 = 4, ERROR_INVALID_DATE_2 = 5, ERROR_INVALID_OUT_UNIT = 6, ERROR_INVALID_PRECISION = 7, ERROR_INVALID_FORMAT_1 = 8, ERROR_INVALID_FORMAT_2 = 9, ERROR_REPEATED_ARG = 10}status_t;
typedef enum{TRUE, FALSE}bool_t;
typedef unsigned long ulong;
/********************************************************************************/

/************************************** DICCIONARIOS *************************/
char * date_formats[] = {DATE_FORMAT_WITH_HOUR, DATE_FORMAT_DATE, DATE_FORMAT_JULIAN};  
char * error_msgs[] = {MSG_ERROR_FEW_ARGS, MSG_ERROR_MANY_ARGS, MSG_ERROR_INVALID_ARG, MSG_ERROR_NULL_POINTER, MSG_ERROR_INVALID_DATE_1, MSG_ERROR_INVALID_DATE_2, MSG_ERROR_INVALID_OUT_UNIT, MSG_ERROR_INVALID_PRECISION, MSG_ERROR_INVALID_FORMAT_1, MSG_ERROR_INVALID_FORMAT_2, MSG_ERROR_REPEATED_ARG}; 
/*****************************************************************************/

/************* PROTOTIPOS *****************/
status_t validate_args (int argc, char * argv[], ulong * p_date_1, ulong * p_date_2, char ** p_date_1_fmt, char ** p_date_2_fmt, char * p_output_unit, int * p_precision);
status_t handle_error(status_t err);
status_t parse_date_with_hour_fmt (ulong date, struct tm * str_date);
/******************************************/

int main (int argc, char * argv[])
{
	/*** INICIALIZAMOS ***/
	ulong date_1 = 0;
	ulong date_2 = 0;
	char * date_1_fmt = NULL;
	char * date_2_fmt = NULL;
	char output_unit = 0;
	int precision = -1;
	struct tm str_date_1;
	struct tm str_date_2;
	/*********************/

	if(validate_args(argc, argv, &date_1, &date_2, &date_1_fmt, &date_2_fmt, &output_unit, &precision)!=OK)
		return EXIT_FAILURE;

	if(parse_date_with_hour_fmt(date_1, &str_date_1)!=OK)
		return EXIT_FAILURE;
	

	printf("formato 1: %s\n", date_1_fmt);
	printf("formato 2: %s\n", date_2_fmt);
	printf("fecha 1: %lu\n", date_1);
	printf("fecha 2: %lu\n", date_2);
	printf("unidad de salida: %c\n", output_unit);
	printf("precision: %i\n", precision);

	return EXIT_SUCCESS;
}

status_t parse_date_with_hour_fmt (ulong date, struct tm * p_str_date)
{
	p_str_date->tm_sec = date % 100;
	if(p_str_date->tm_sec>=60 || p_str_date->tm_sec<0)
    return error_handling(ERROR_INVALID_SEC);
    
  date /= 100;
	p_str_date->tm_min = date % 100;
	if(p_str_date->tm_min>=60 || p_str_date->tm_min<0)
    return error_handling(ERROR_INVALID_MIN);
	
  date /= 100;
	p_str_date->tm_hour = date % 100;
	if(p_str_date->tm_hour>=24 || p_str_date->tm_hour<0)
    return error_handling(ERROR_INVALID_HOUR);
	
  date /= 100;
	p_str_date->tm_year = (date % 10000) - 1900; /* guardo como especifica struct tm: dferencia con 1900 */
	if(p_str_date->tm_year>=0) /* valido para fechas a partir del año 0 */
    return error_handling(ERROR_INVALID_YEAR);
	
  date /= 10000;
	p_str_date->tm_mon = (date % 100) - 1; /* idem, guardo de 0 a 11 */
	if(p_str_date->tm_mon>=12 || p_str_date->tm_mon<0)
    return error_handling(ERROR_INVALID_MONTH);
	
  date /= 100;
	p_str_date->tm_mday = date;
  if(validate_mday!=OK)
    return error_handling(ERROR_INCOMPATIBLE_MDAY);
  
  
	return OK;
}
		

status_t handle_error(status_t err)
{
	fprintf(stderr, "%s\n", error_msgs[err]);
	return err;
}

status_t validate_args (int argc, char * argv[], ulong * p_date_1, ulong * p_date_2, char ** p_date_1_fmt, char ** p_date_2_fmt, char * p_output_unit, int * p_precision)
{
	size_t i, args_to_validate;
	char * aux;
	char * date_1_user;
	char * date_2_user;
	
	/********** VALIDAMOS PUNTEROS **********/
	if(argv == NULL || p_date_1 == NULL || p_date_2 == NULL || p_date_1_fmt == NULL || p_date_2_fmt == NULL || p_output_unit == NULL || p_precision == NULL)
		return handle_error(ERROR_NULL_POINTER);

	/********** VALIDAMOS CANTIDAD **********/
	if(argc < CMD_ARG_ARGC)
		return handle_error(ERROR_FEW_ARGS);

	if(argc > CMD_ARG_ARGC)
		return handle_error(ERROR_MANY_ARGS);
	/****************************************/

	/********** VALIDAMOS FLAG A FLAG ***********/
	for(i=1, args_to_validate = (CMD_ARG_ARGC-1) ; i < (CMD_ARG_ARGC-1); i+=FLAG_TO_FLAG_STEP)
	{
		if(strcmp(argv[i], CMD_ARG_FLAG_FORMAT_1) == 0)
		{
			if( (strcmp(argv[i+1], DATE_FORMAT_WITH_HOUR)) && (strcmp(argv[i+1], DATE_FORMAT_DATE)) && (strcmp(argv[i+1], DATE_FORMAT_JULIAN)) )
				return handle_error(ERROR_INVALID_FORMAT_1);
			*p_date_1_fmt = argv[i+1];
			args_to_validate-=FLAG_TO_FLAG_STEP;
			continue;		
		}	
		if(strcmp(argv[i], CMD_ARG_FLAG_FORMAT_2) == 0)
		{
			if( (strcmp(argv[i+1], DATE_FORMAT_WITH_HOUR)) && (strcmp(argv[i+1], DATE_FORMAT_DATE)) && (strcmp(argv[i+1], DATE_FORMAT_JULIAN)) )
				return handle_error(ERROR_INVALID_FORMAT_2);
			*p_date_2_fmt = argv[i+1];
			args_to_validate-=FLAG_TO_FLAG_STEP;			
			continue;
		}
		if(strcmp(argv[i], CMD_ARG_FLAG_DATE_1) == 0)
		{
			date_1_user = argv[i+1];
			*p_date_1 = (ulong) strtod(argv[i+1], &aux);
			if(*aux)
				return handle_error(ERROR_INVALID_DATE_2); 
			args_to_validate-=FLAG_TO_FLAG_STEP;
			continue;
		}
		if(strcmp(argv[i], CMD_ARG_FLAG_DATE_2) == 0)
		{
			date_2_user = argv[i+1];
			*p_date_2 = (ulong) strtod(argv[i+1], &aux);
			if(*aux)
				return handle_error(ERROR_INVALID_DATE_2);
			args_to_validate-=FLAG_TO_FLAG_STEP;
			continue;
		}
		if(strcmp(argv[i], CMD_ARG_FLAG_OUT_UNIT) == 0)
		{
			if(strlen(argv[i+1])>1)
				return handle_error(ERROR_INVALID_OUT_UNIT);
			*p_output_unit = argv[i+1][0];
			if(*p_output_unit != TIME_UNIT_FLAG_SECONDS && *p_output_unit != TIME_UNIT_FLAG_MINUTES && *p_output_unit != TIME_UNIT_FLAG_HOURS && *p_output_unit != TIME_UNIT_FLAG_DAYS)
				return handle_error(ERROR_INVALID_OUT_UNIT); 
			args_to_validate-=FLAG_TO_FLAG_STEP;
			continue;
		}
		if(strcmp(argv[i], CMD_ARG_FLAG_PRECISION) == 0)
		{
			*p_precision = (int) strtol(argv[i+1], &aux, 10);
			if(*aux)
				return handle_error(ERROR_INVALID_PRECISION);
			if(*p_precision != 0 && *p_precision != 1 && *p_precision != 2 && *p_precision != 3)
				return handle_error(ERROR_INVALID_PRECISION);
			args_to_validate-=FLAG_TO_FLAG_STEP;
			continue;
		}
		return handle_error(ERROR_INVALID_ARG);
	/********************************************/				
	}

	/************ VALIDAMOS QUE EL ANCHO DE LA FECHA IGNRESADA SEA CORRECTO **********/
	if(!strcmp(*p_date_1_fmt, DATE_FORMAT_WITH_HOUR))
		if(strlen(date_1_user)!=DATE_FORMAT_WITH_HOUR_LEN)
			return handle_error(ERROR_INVALID_DATE_1);

	if(!strcmp(*p_date_1_fmt, DATE_FORMAT_DATE))
		if(strlen(date_1_user)!=DATE_FORMAT_DATE_LEN)
			return handle_error(ERROR_INVALID_DATE_1);
	if(!strcmp(*p_date_1_fmt, DATE_FORMAT_JULIAN))
		if(strlen(date_1_user)!=DATE_FORMAT_JULIAN_LEN)
			return handle_error(ERROR_INVALID_DATE_1);

	if(!strcmp(*p_date_2_fmt, DATE_FORMAT_WITH_HOUR))
		if(strlen(date_2_user)!=DATE_FORMAT_WITH_HOUR_LEN)
			return handle_error(ERROR_INVALID_DATE_2);
	if(!strcmp(*p_date_2_fmt, DATE_FORMAT_DATE))
		if(strlen(date_2_user)!=DATE_FORMAT_DATE_LEN)
			return handle_error(ERROR_INVALID_DATE_2);
	if(!strcmp(*p_date_2_fmt, DATE_FORMAT_JULIAN))
		if(strlen(date_2_user)!=DATE_FORMAT_JULIAN_LEN)
			return handle_error(ERROR_INVALID_DATE_2);
	/**********************************************************************************/


	if(!(*p_date_1) || !(*p_date_2) || *p_date_1_fmt == NULL || *p_date_2_fmt == NULL || !(*p_output_unit) || *p_precision == -1)
		return handle_error(ERROR_REPEATED_ARG);

	if(args_to_validate)
		return ERROR;
			
	return OK;
}


/* 24 de MAYO de 2015 */
gabriel@gabriel-desktop:~/Documentos/Facultad de Ingeniería/Algoritmos y Program
ación 1/TP_1/pruebas_preliminares/manejo_formato_fecha$ gcc -ansi -pedantic -Wall -o date_format.exe date_format.c
gabriel@gabriel-desktop:~/Documentos/Facultad de Ingeniería/Algoritmos y Program
ación 1/TP_1/pruebas_preliminares/manejo_formato_fecha$ ./date_format.exe -fmt1 DDMMAAAAhhmmss -f1 13121993143022 -fmt2 DDDAAAA -f2 1232003 -u m -p 2
formato 1: DDMMAAAAhhmmss
formato 2: DDDAAAA
fecha 1: 13121993143022
fecha 2: 1232003
unidad de salida: m
precision: 2
gabriel@gabriel-desktop:~/Documentos/Facultad de Ingeniería/Algoritmos y Program
ación 1/TP_1/pruebas_preliminares/manejo_formato_fecha$ ^C
gabriel@gabriel-desktop:~/Documentos/Facultad de Ingeniería/Algoritmos y Program
ación 1/TP_1/pruebas_preliminares/manejo_formato_fecha$ 

gabriel@gabriel-desktop:~/Documentos/Facultad de Ingeniería/Algoritmos y Program
ación 1/TP_1/pruebas_preliminares/manejo_formato_fecha$ gcc -ansi -pedantic -Wall -o date_format.exe date_format.c
gabriel@gabriel-desktop:~/Documentos/Facultad de Ingeniería/Algoritmos y Program
ación 1/TP_1/pruebas_preliminares/manejo_formato_fecha$ ./date_format.exe -u d -f2 13121993 -f1 3222005 -fmt2 DDDAAAA -fmt1 DDMMAAAA -p 3 
formato 1: DDMMAAAA
formato 2: DDDAAAA
fecha 1: 3222005
fecha 2: 13121993
unidad de salida: d
precision: 3
prompt
