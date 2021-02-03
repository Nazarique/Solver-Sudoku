#include "sudoku.h"

uint8_t grid[N][N] = {
   {3, 0, 6, 5, 0, 8, 4, 0, 0},
   {5, 2, 0, 0, 0, 0, 0, 0, 0},
   {0, 8, 7, 0, 0, 0, 0, 3, 1},
   {0, 0, 3, 0, 1, 0, 0, 8, 0},
   {9, 0, 0, 8, 6, 3, 0, 0, 5},
   {0, 5, 0, 0, 9, 0, 6, 0, 0},
   {1, 3, 0, 0, 0, 0, 2, 5, 0},
   {0, 0, 0, 0, 0, 0, 0, 7, 4},
   {0, 0, 5, 2, 0, 6, 3, 0, 0}
};
marcador_t anotacoes[N][N];

void runMatriz(tipoFuncao_p PonteiroDeFuncao)
{
   for (uint8_t row = 0; row < N; row++)
      for (uint8_t col = 0; col < N; col++)
         PonteiroDeFuncao(row, col);
}
void prAnotacoes(uint8_t row, uint8_t col)
{
   printf("\nLinha: %i\tColuna: %i\n", row, col);
   prMark(&anotacoes[row][col]);
}
void prMark(marcador_t const *grid)
{
   printf("V| 0 1 2 3 4 5 6 7 8 9\n");
   printf("%i| ", grid->num.vazio);

   printf("%i ", grid->num.zero);
   printf("%i ", grid->num.um);
   printf("%i ", grid->num.dois);
   printf("%i ", grid->num.tres);
   printf("%i ", grid->num.quatro);
   printf("%i ", grid->num.cinco);
   printf("%i ", grid->num.seis);
   printf("%i ", grid->num.sete);
   printf("%i ", grid->num.oito);
   printf("%i\n", grid->num.nove);
}
void prSudoku(uint8_t row, uint8_t col)
{
   
   if(col == 3 || col == 6)
      printf(" | ");

   printf("%i ",grid[row][col]);
   if(col==8)
   {
      if(row == 2 || row == 5)
      {
         printf("\n");
         for(uint8_t i = 0; i<N; i++)
            printf( "---");
      }
      printf("\n");
   }
}
uint8_t existeNaColuna(uint8_t col, uint8_t num)
{
   for (uint8_t row = 0; row < N; row++)
      if (grid[row][col] == num)
         return true;
   return false;
}
uint8_t existeNaLinha(uint8_t row, uint8_t num)
{
   for (uint8_t col = 0; col < N; col++)
      if (grid[row][col] == num)
         return true;
   return false;
}
uint8_t existeNoQuadrado(uint8_t boxStartRow, uint8_t boxStartCol, uint8_t num)
{
   for (uint8_t row = 0; row < 3; row++)
      for (uint8_t col = 0; col < 3; col++)
         if (grid[row+boxStartRow][col+boxStartCol] == num)
            return true;
   return false;
}
uint8_t lugaresVazios(uint8_t *row, uint8_t *col)
{
   for (*row=0; *row < N; (*row)++)
      for (*col=0; *col < N; (*col)++)
         if (grid[*row][*col]==0 && !anotacoes[*row][*col].num.vazio)// vazio e não foi anotado?
         {
            anotacoes[*row][*col].num.vazio = FLAG_VAZIO;
            return true;
         }
   return false;
}
uint8_t lugarValido(uint8_t row, uint8_t col, uint8_t num)
{
   return !existeNaLinha(row, num)&&
          !existeNaColuna(col, num)&&
          !existeNoQuadrado(INDICE_INICIAL(row), INDICE_INICIAL(col), num);
}
void anotando(uint8_t *row, uint8_t *col, uint8_t anotar)
{
   if(anotacoes[*row][*col].num.vazio==true)
   {
      switch(anotar)
      {
         case 0:
            anotacoes[*row][*col].mark |= MASK_0;
            break;
         case 1:
            anotacoes[*row][*col].mark |= MASK_1;
            break;
         case 2:
            anotacoes[*row][*col].mark |= MASK_2;
            break;
         case 3:
            anotacoes[*row][*col].mark |= MASK_3;
            break;
         case 4:
            anotacoes[*row][*col].mark |= MASK_4;
            break;
         case 5:
            anotacoes[*row][*col].mark |= MASK_5;
            break;
         case 6:
            anotacoes[*row][*col].mark |= MASK_6;
            break;
         case 7:
            anotacoes[*row][*col].mark |= MASK_7;
            break;
         case 8:
            anotacoes[*row][*col].mark |= MASK_8;
            break;
         case 9:
            anotacoes[*row][*col].mark |= MASK_9;
            break;
         default:
            printf("Erro\n");
            break;
      }
   }
}
uint8_t sudoku(void)
{
   static uint8_t row=0, col=0;

   if(lugaresVazios(&row, &col))
   {      
      for (uint8_t num = 1; num <= N; num++)
         if (lugarValido(row, col, num))
            anotando(&row, &col, num);
         if(!sudoku())
            return false;
   }
   return false;
}

int main(int argc, char const *argv[])
{
   memset(&anotacoes, 0, (N*N)*sizeof(marcador_t));
   sudoku();
   runMatriz(prAnotacoes);
  	return 0;
}