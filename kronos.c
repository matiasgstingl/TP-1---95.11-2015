/*

5) Explicación de alternativas y estrategias consideradas:

Alternativas: 
  Manejar fecha como la ingresa el usuario - char*- y separar los campos,
o convertir esa cadena a un número -unsigned long int- y operar 
matemáticamente usando las funciones módulo y división.
  Se resolvió utilizar la segunda opción ya que las funciones aritméticas son 
más rápidas y livianas que las de manejo de cadenas de caracteres o de memoria.






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
