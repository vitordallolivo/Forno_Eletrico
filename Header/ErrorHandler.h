/*
 * ErrorHandler.h
 *
 * Created: 16-Aug-25 21:23:49
 *  Author: vitor
 */ 


#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_


/* 
	A ideia é que uma biblioteca é que ao invés de uma função ela retornar um void ela
	pode retornar um erro, por exemplo se um vetor tem um tamanho já pré-definido
	o ideial é que não dar um overflow nele
*/


// TODO :  Implementar um handler para funções, como forma de avisar o usuário

typedef enum{ 
	ERROR_NONE = 0x00,  // Sem erros
	ERROR_REGISTER_OVERFLOW, // Passou do tamanho máximo permitido do registrador
	ERROR_MEMORY_OVERFLOW, // Alocar memoria além do permitido do vetor
}Error_t;

typedef enum{
	  SEVERITY_INFO,      // Apenas informativo
	  SEVERITY_WARNING,   // Problema recuperável
	  SEVERITY_ERROR,     // Funcionalidade afetada
	  SEVERITY_CRITICAL   // Pode gerar um erro crítico
}ErrorSeverity_t;


typedef struct{
	Error_t type;

}ERROR_HANDLER_TYPE;

#endif /* ERRORHANDLER_H_ */