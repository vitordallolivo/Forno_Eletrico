/*
 * ErrorHandler.h
 *
 * Created: 16-Aug-25 21:23:49
 *  Author: vitor
 */ 


#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_


/* 
	A ideia � que uma biblioteca � que ao inv�s de uma fun��o ela retornar um void ela
	pode retornar um erro, por exemplo se um vetor tem um tamanho j� pr�-definido
	o ideial � que n�o dar um overflow nele
*/


// TODO :  Implementar um handler para fun��es, como forma de avisar o usu�rio

typedef enum{ 
	ERROR_NONE = 0x00,  // Sem erros
	ERROR_REGISTER_OVERFLOW, // Passou do tamanho m�ximo permitido do registrador
	ERROR_MEMORY_OVERFLOW, // Alocar memoria al�m do permitido do vetor
}Error_t;

typedef enum{
	  SEVERITY_INFO,      // Apenas informativo
	  SEVERITY_WARNING,   // Problema recuper�vel
	  SEVERITY_ERROR,     // Funcionalidade afetada
	  SEVERITY_CRITICAL   // Pode gerar um erro cr�tico
}ErrorSeverity_t;


typedef struct{
	Error_t type;

}ERROR_HANDLER_TYPE;

#endif /* ERRORHANDLER_H_ */