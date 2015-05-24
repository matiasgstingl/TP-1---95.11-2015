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

#define ENGLISH_LENG



#define DATE_FORMAT_1 "DDMMAAAAhhmmss"
#define DATE_FORMAT_1_LEN 14
#define DATE_FORMAT_2 "DDMMAAAA"
#define DATE_FORMAT_2_LEN 8
#define DATE_FORMAT_3 "DDDAAAA"
#define DATE_FORMAT_3_LEN 7
#define QTY_FORMATS 3

#define CMD_ARG_QTY_PROGRAM_ARGS 12
#define CMD_ARG_POSITION_FIRST_FLAG 1
#define CMD_ARG_FLAG_TO_FLAG_STEP 2
#define CMD_ARG_FLAG_FORMAT_1 "-fmt1"
#define CMD_ARG_FLAG_FORMAT_2 "-fmt2"
#define CMD_ARG_FLAG_DATE_1 "-f1"
#define CMD_ARG_FLAG_DATE_2 "-f2"
#define CMD_ARG_FLAG_OUT_UNIT "-u"
#define CMD_ARG_FLAG_PRECISION "-p"

#define MSG_ERROR_FEW_ARGS "Error, pocos argumentos en su linea de orden."
#define MSG_ERROR_MANY_ARGS "Error, demasiados argumentos en su linea de orden."
#define MSG_ERROR_INVALID_ARG "Error, argumento invalido."
#define MSG_ERROR_NULL_POINTER "Error de puntero nulo."
#define MSG_ERROR_INVALID_DATE_1 "La fecha 1 ingresada es invalida."
#define MSG_ERROR_INVALID_DATE_2 "La fecha 2 ingresada es invalida."
#define MSG_ERROR_INVALID_OUT_UNIT "La unidad especificada es invalida."
#define MSG_ERROR_INVALID_PRECISION "La precision especificada es invalida."

/******************************* TIPOS ENUMERATIVOS Y ESTRUCTURAS ***************/
typedef enum{OK = -1, ERROR_FEW_ARGS = 0, ERROR_MANY_ARGS = 1, ERROR_INVALID_ARG = 2, ERROR_NULL_POINTER = 3, ERROR_INVALID_DATE_1 = 4, ERROR_INVALID_DATE_2 = 5, ERROR_INVALID_OUT_UNIT = 6, ERROR_INVALID_PRECISION = 7}status_t;
typedef enum{TRUE, FALSE}bool_t;
typedef unsigned long ulong;
/********************************************************************************/

/************************************** DICCIONARIOS *************************/
char * date_formats[] = {DATE_FORMAT_1, DATE_FORMAT_2, DATE_FORMAT_3};  
char * error_msgs[] = {MSG_ERROR_FEW_ARGS, MSG_ERROR_MANY_ARGS, MSG_ERROR_INVALID_AR, MSG_ERROR_NULL_POINTER, MSG_ERROR_INVALID_DATE_1, MSG_ERROR_INVALID_DATE_2, MSG_ERROR_INVALID_OUT_UNIT, MSG_ERROR_INVALID_PRECISION}; 
/*****************************************************************************/

/************* PROTOTIPOS *****************/
status_t validate_args (int argc, char * argv[]);
status_t error_handling(status_t err);
/******************************************/

int main (int argc, char * argv[])
{
	ulong date_1;
	ulong date_2;
	if(validate_args(argc, argv, &date_1, &date_2)!=OK)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

status_t error_handling(status_t err)
{
	fprintf(stderr, "%s\n", error_msgs[err]);
	return err;
}

status_t validate_args (int argc, char * argv[], ulong * p_date_1, ulong * p_date_2, char * p_date_1_fmt, char * p_date_2_fmt, char * p_output_unit, size_t * p_precision)
{
	size_t i;
	char * aux;
	bool_t correct_date;
	
	/********** VALIDAMOS PUNTEROS **********/
	if(date_1 == NULL || date_2 == NULL || p_date_1_fmt == NULL || p_date_2_fmt == NULL || p_output_unit == NULL || p_precision == NULL)
		return error_handling(ERROR_NULL_POINTER);

	/********** VALIDAMOS CANTIDAD **********/
	if(argc < QTY_PROGRAM_ARGS)
		return error_handling(ERROR_FEW_ARGS);

	if(argc > QTY_PROGRAM_ARGS)
		return error_handling(ERROR_MANY_ARGS);
	/****************************************/

	/********** VALIDAMOS FLAG A FLAG ***********/
	for(i=1, args_to_parse = 0; i < CMD_ARG_QTY_PROGRAM_ARGS; i+=FLAG_TO_FLAG_STEP)
	{
		if(strcmp(argv[i], CMD_ARG_FLAG_FORMAT_1) == 0)
		{
			p_date_1_fmt = argv[i+1];
			continue;		
		}	
		if(strcmp(arg[i], CMD_ARG_FLAG_FORMAT_2) == 0)
		{
			p_date_2_fmt = argv[i+1];
			continue;
		}
		if(strcmp(arg[i], CMD_ARG_FLAG_DATE_1) == 0)
		{
			*p_date_2 = strtol(argv[i+1], &aux, 10);
			if(*aux)
				return error_handling(ERROR_INVALID_DATE_2); 
			continue;
		}
		if(strcmp(arg[i], CMD_ARG_FLAG_DATE_2) == 0)
		{
			*p_date_2 = strtol(argv[i+1], &aux, 10);
			if(*aux)
				return error_handling(ERROR_INVALID_DATE_2);
			continue;
		}
		if(strcmp(arg[i], CMD_ARG_FLAG_OUT_UNIT) == 0)
		{
			*p_output_unity = arg[i+1][0];
			if(*p_output_unity != 's' && *p_output_unity != 'm' && *p_output_unity != 'h' && *p_output_unity != 'd')
				return error_handling(ERROR_INVALID_OUT_UNIT); 
			continue;
		}
		if(strcmp(arg[i], CMD_ARG_FLAG_PRECISION) == 0)
		{
			*p_precision = (size_t) strtol(argv[i+1], &aux, 10);
			if(*aux)
				return error_handling(ERROR_INVALID_PRECISION);
			if(*p_precision != 0 && *p_precision != 1 && *p_precision != 2 && *p_precision != 3)
				return error_handling(ERROR_INVALID_PRECISION);
			continue;
		}				
	}
			
	return OK;
}	

