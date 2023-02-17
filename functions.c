#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

void reverse(char str[])
/*
Essa função é responsável por inverter a ordem dos caracteres de uma string.
É usada para inverter a ordem dos bits armazenados na string (exp_binary e mantissa_binary).
*/
{
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++)
    {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void decimal_to_binary(int decimal, char *binary)
/*
Essa função é responsável por converter um número decimal para sua representação binária.
É usada para converter o expoente e a mantissa para suas representações binárias.
*/
{
    int i;
    for (i = 0; i < 32; i++)
    {
        binary[i] = (decimal & (1 << i)) ? '1' : '0';
    }
    binary[i] = '\0';
    reverse(binary);
}

int get_sign(float number)
/*
Essa função é responsável por retornar o sinal do número.
Verifica se o bit mais significativo é 1 ou 0 e retorna 1 se for 1 e 0 se for 0.
*/
{
    int *p = (int *)&number;
    int s = 0x80000000; // 10000000000000000000000000000000 em binário (bit mais significativo) para verificar o sinal do número (1 para negativo e 0 para positivo)
    if ((*p & s) != 0)
        return 1;
    else
        return 0;
}

int get_exponent(float number)
/*
Essa função é responsável por retornar o expoente de um número.
*/
{
    int exp;
    int bias = 127;
    float fraction;
    // A função frexp() retorna a fração e o expoente de um número. A fração é um número entre 0.5 e 1.0 (ou -0.5 e -1.0) e o expoente é um inteiro.
    fraction = frexp(number, &exp);
    exp = exp + bias - 1;
    return exp;
}

int get_mantissa(float number)
/*
Essa função é responsável por retornar a mantissa de um número.
Ela obtém a representação binária do número e retorna os 23 bits menos significativos.
*/
{
    int *p = (int *)&number;
    int m = (*p & 0x7fffff);
    return m;
}

int get_ieee754(int sign, int exp, int mantissa)
/*
é responsável por retornar a representação IEEE 754 de um número. Ela usa os valores obtidos pelas outras funções (sinal, expoente e mantissa)
para construir a representação IEEE 754. Deslocando o bit de sinal para a posição mais significativa,
deslocando o expoente para a segunda posição mais significativa e mantendo a mantissa na parte menos significativa.
Depois, ela usa operações bit a bit para juntar esses três valores e retornar o número IEEE 754 final.
*/
{
    int s = sign << 31;
    int e = exp << 23;
    // int ieee = (s & 0x80000000) | (e & 0x7f800000) | (mantissa & 0x7fffff); // juntar os bits de sinal, expoente e mantissa e "|" serve para juntar os 3 resultados
    int ieee = (s) | (e) | (mantissa);
    return ieee;

    /*
    (s & 0x80000000) é usada para pegar o bit mais significativo de s (que representa o sinal) e manter apenas esse bit. (bit mais a esquerda)
    (e & 0x7f800000) é usada para pegar os bits 8-31 de e (que representam o expoente) e manter apenas esses bits. (próximo ou longe de zero)
    (mantissa & 0x7fffff) é usada para pegar os bits 0-22 de mantissa (que representam a mantissa) e manter apenas esses bits. (número sem expoente)
    */
}

/*void add_ieee754(float num1, float num2, float *result)
{
    int mantissa1, mantissa2, exp1, exp2, sign1, sign2;
    int mantissaResult, expResult, signResult;
    char mantissaBinary1[32], mantissaBinary2[32];

    sign1 = get_sign(num1);
    exp1 = get_exponent(num1);
    mantissa1 = get_mantissa(num1);
    decimal_to_binary(mantissa1, mantissaBinary1);

    sign2 = get_sign(num2);
    exp2 = get_exponent(num2);
    mantissa2 = get_mantissa(num2);
    decimal_to_binary(mantissa2, mantissaBinary2);

    int shift, resultMantissa;

    if (exp1 > exp2)
    {
        shift = exp1 - exp2;
        expResult = exp1;
        mantissaResult = mantissa1 + (mantissa2 >> shift);
    }
    else
    {
        shift = exp2 - exp1;
        expResult = exp2;
        mantissaResult = mantissa2 + (mantissa1 >> shift);
    }

    if (mantissaResult >= pow(2, 23))
    {
        mantissaResult = mantissaResult >> 1;
        expResult++;
    }

    signResult = (sign1 == sign2) ? sign1 : -sign1;

    int ieee = get_ieee754(signResult, expResult, mantissaResult);
    *result = *(float *)&ieee;
}*/
void add_ieee754(int sign, int exp, int mantissa, int sign2, int exp2, int mantissa2, int *signResult, int *expResult, int *mantissaResult)
{
    int shift, resultMantissa, resultExponent, resultSign;

    if (exp > exp2)
    {
        shift = exp - exp2;
        resultExponent = exp;
        resultMantissa = mantissa + (mantissa2 >> shift);
    }
    else
    {
        shift = exp2 - exp;
        resultExponent = exp2;
        resultMantissa = mantissa2 + (mantissa >> shift);
    }

    while ((int)resultMantissa >= pow(2, 23))
    {
        resultMantissa = (int)resultMantissa >> 1;
        resultExponent++;
    }

    resultSign = (sign == sign2) ? sign : -sign;

    *signResult = resultSign;
    *expResult = resultExponent;
    *mantissaResult = resultMantissa;
}
