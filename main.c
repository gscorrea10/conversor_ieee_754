/*
https://carlosrafaelgn.com.br/Aula/Flutuante2.html
https://guiatech.net/ieee-754-conversao/
https://babbage.cs.qc.cuny.edu/ieee-754.old/decimal.html
https://imsouza.github.io/convertendo-ieee32bits-para-decimal-e-vice-versa
https://sites.google.com/a/sga.pucminas.br/puc2010-2_a417889/intro-ciencia-computacao/operacoes-ponto-flutuante-ieee754
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.c"

int main()
{
    float number1; // variável para armazenar o número digitado pelo usuário
    float number2;
    int valid;        // variável para verificar se o número digitado pelo usuário é válido
    char buffer[100]; // buffer para armazenar o número digitado pelo usuário
    do
    {
        printf("Enter the number: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (strchr(buffer, '-') != NULL) // verifica se existe o sinal '-' no número digitado pelo usuário
        {
            valid = sscanf(buffer, "%f", &number1); // verifica se o número é válido e armazena o valor na variável number
        }
        else
        {
            valid = sscanf(buffer, "%f", &number1);
        }
        if (valid != 1)
        {
            printf("Invalid input, please enter a valid floating point number\n");
        }
    } while (valid != 1);

    char exp_binary[10];      // uso um vetor de 10 bitos para armazenar o expoente, para a função reverse possa reverter a ordem dos bits corretamente
    char mantissa_binary[25]; // uso um vetor de 25 bits para armazenar a mantissa, para a função reverse possa reverter a ordem dos bits corretamente
    char ieee754_binary[32];
    int sign = get_sign(number1);
    printf("Sign: %d \n", sign);
    int exp = get_exponent(number1);
    printf("Exponent: %d \n", exp);
    int size_exp = 8;       // 8 bits para o expoente
    int size_mantissa = 23; // 23 bits para a mantissa
    int i, j;
    decimal_to_binary(exp, exp_binary);
    reverse(exp_binary);
    for (i = size_exp - 1; i >= 0; i--)
    {
        printf("%c", exp_binary[i]);
    }
    printf("\n");
    int mantissa = get_mantissa(number1);
    printf("Mantissa: %u \n", mantissa);
    decimal_to_binary(mantissa, mantissa_binary);
    for (i = 0; i < size_mantissa; i++)
    {
        if (mantissa_binary[i] != '0')
        {
            printf("Mantissa in binary: %s\n", &mantissa_binary[i]);
            break;
        }
    }
    int ieee754 = get_ieee754(sign, exp, mantissa);
    printf("IEEE754: %u \n", ieee754);
    decimal_to_binary(ieee754, ieee754_binary);
    printf("IEEE754 in binary: %s\n", ieee754_binary);

    do
    {
        printf("Enter the number: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (strchr(buffer, '-') != NULL) // verifica se existe o sinal '-' no número digitado pelo usuário
        {
            valid = sscanf(buffer, "%f", &number2); // verifica se o número é válido e armazena o valor na variável number
        }
        else
        {
            valid = sscanf(buffer, "%f", &number2);
        }
        if (valid != 1)
        {
            printf("Invalid input, please enter a valid floating point number\n");
        }
    } while (valid != 1);

    char exp_binary2[10];
    char mantissa_binary2[25];
    char ieee754_binary2[32];
    int sign2 = get_sign(number2);
    printf("Sign: %d \n", sign2);
    int exp2 = get_exponent(number2);
    printf("Exponent: %d \n", exp2);
    int size_exp2 = 8;       // 8 bits para o expoente
    int size_mantissa2 = 23; // 23 bits para a mantissa
    int i2, j2;
    decimal_to_binary(exp2, exp_binary2);
    reverse(exp_binary2);
    for (i2 = size_exp2 - 1; i2 >= 0; i2--)
    {
        printf("%c", exp_binary2[i2]);
    }
    printf("\n");
    int mantissa2 = get_mantissa(number2);
    printf("Mantissa: %u \n", mantissa2);
    decimal_to_binary(mantissa2, mantissa_binary2);
    for (i2 = 0; i2 < size_mantissa2; i2++)
    {
        if (mantissa_binary2[i2] != '0')
        {
            printf("Mantissa in binary: %s\n", &mantissa_binary2[i2]);
            break;
        }
    }
    int ieee754_2 = get_ieee754(sign2, exp2, mantissa2);
    printf("IEEE754: %u \n", ieee754_2);
    decimal_to_binary(ieee754_2, ieee754_binary2);
    printf("IEEE754 in binary: %s\n", ieee754_binary2);

    return 0;
}
