#include <stdio.h>

void bin(int num);
void swap (int num);
void bin_with_count(int num);
void bin_otric(int num);

int main() {
   int num;
   scanf("%d", &num);
   bin_with_count(num);
   swap(num);
   printf("Введите отрицательное число\n");
   scanf("%d", &num);
   bin_otric(num);
   return 0;
}

void bin(int num) { 
   int count = 0;
   int count_for_one = 0;
   int bit;
   for (int i = num; i > 0; i = i >> 1){
      count +=1;    
   }
   for (int i = count - 1; i >= 0; --i){
      bit = (num >> i) & 1;
      printf("%d", bit);

   }
   printf("\n");
}
void swap (int num){
    unsigned int b, b1,b2,b3,b4;
    int i=0;
    for (i;i<4;i++){
        b=((num>>i*8) & 0xFF);
       switch (i)
       {
            case 0:
               printf("Первый байт - ");
                bin(b);
                b1=b;
                break;
            case 1:
               printf("Второй байт - ");
               bin(b);
                b2=b;
                break;
            case 2:
                printf("Третий байт - ");
                bin(b);
                break;
            case 3:
                printf("Четвёртый байт - ");
                bin(b);
                b4=b;
                break;
            default:
                break;
       }
    }
   printf("Введите замену третьего байта в десятичном виде\n");
   scanf("%d", &b3);
   int a1= (b4<<24) | (b3<<16) | (b2<<8) | b1;
   printf("Число с изменённым третьим байтом - %d\n",a1);
}
void bin_with_count(int num) { 
   int count = 0;
   int count_for_one = 0;
   int bit;
   for (int i = num; i > 0; i = i >> 1){
      count +=1;    
   }
   printf("Двоичное представление числа  - ");
   for (int i = count - 1; i >= 0; --i){
      bit = (num >> i) & 1;
      printf("%d", bit);
      if (bit == 1){
         count_for_one += 1;
      }
   }
   printf("\n");
   printf("Количество единиц = %d\n", count_for_one);
}
void bin_otric(int num) { 
   int count = 0;
   int count_for_one = 0;
   int bit;
   for (int i = num; i > 0; i = i >> 1){
      count +=1;    
   }
   printf("Двоичное представление отрицательного числа  - 1");
   for (int i = count - 1; i >= 0; --i){
      bit = (num >> i) & 1;
      printf("%d", bit);
   }
   printf("\n");
}