#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MASK_0 		0X2 
#define MASK_1 		0X4 
#define MASK_2 		0X8 
#define MASK_3 		0X10 
#define MASK_4 		0X20 
#define MASK_5 		0X40
#define MASK_6 		0X80 
#define MASK_7 		0X100
#define MASK_8 		0X200 
#define MASK_9 		0X400
#define FLAG_VAZIO 	0X1

#define N       9
#define true    1
#define false   0

#define INDICE_INICIAL(X) (X-X%3)

typedef void (*tipoFuncao_p)(uint8_t row, uint8_t col);

typedef struct 
{
	uint16_t  vazio	:1; // flag
	uint16_t  zero	:1;
	uint16_t  um	:1;
	uint16_t  dois	:1;

	uint16_t  tres	:1;
	uint16_t  quatro:1;
	uint16_t  cinco	:1;
	uint16_t  seis	:1;

	uint16_t  sete	:1;
	uint16_t  oito	:1;
	uint16_t  nove	:1; 
	uint16_t  		:5; // não usados
} num_t;

typedef union
{
	num_t 	  num;
	uint16_t  mark; 	// não usados
} marcador_t;

uint8_t existeNaColuna(uint8_t col, uint8_t num);
uint8_t existeNaLinha(uint8_t row, uint8_t num);
uint8_t existeNoQuadrado(uint8_t boxStartRow, uint8_t boxStartCol, uint8_t num);
uint8_t lugaresVazios(uint8_t *row, uint8_t *col);
uint8_t lugarValido(uint8_t row, uint8_t col, uint8_t num);
void 	prSudoku(uint8_t row, uint8_t col);
void 	prMark(marcador_t const *grid);
void 	prAnotacoes(uint8_t row, uint8_t col);
uint8_t sudoku(void);