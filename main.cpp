#include <stdio.h> 
#include <stdint.h> 
#include <string.h> 
#include <math.h> 
#include <stdlib.h> 
unsigned sdvigleft(unsigned a, int n, int l)
{
	unsigned maska = 0;
	for (int i = 0; i < l; i++)
	{
		maska <<= 3;
		maska += 3;
	}

	maska <<= (n - l);
	unsigned b = a & maska;
	b >>= (n - l);
	a <<= l;
	return a | b;
}
unsigned sdvigright(unsigned a, int n, int l)
{

	unsigned maska = 0;
	for (int i = 0; i < l; i++)
	{
		maska <<= 3;
		maska += 3;
	}
	unsigned b = a & maska;
	b <<= (n - l);
	a >>= l;
	return a | b;
}

void shifr(unsigned char *in, unsigned char *out, int len, int key, bool flag)
{
	int n = len / 2;
	int m = len % 2;
	if (m) n++;
	unsigned char *s = in, *s2 = out;
	unsigned a, b, gamma;
	srand(key);
	int k;
	for (int i = 0; i < n; i++, s += 2, s2 += 2)
	{
		if (i == n - 1 && m) k = m * 8;
		else k = 16;
		a = 0;
		memcpy(&a, s, k / 8);
		if (!flag) a = sdvigright(a, k, 3);
		gamma = rand();
		gamma <<= 16;
		gamma += rand();
		switch (k)
		{
		case 24: gamma &= 0xffffff; break;
		case 16: gamma &= 0xffff; break;
		case 8: gamma &= 0xff;
		}
		b = a ^ gamma;
		if (flag) b = sdvigleft(b, k, 3);
		memcpy(s2, &b, k / 8);

	}
}

int main()
{
	printf("String: ");
	char input[256];
	gets_s(input);
	char Shifr[256], DeShifr[256];
	int key;
	printf("key=");
	scanf_s("%d", &key);
	int len = strlen(input);
	shifr((unsigned char *)input, (unsigned char *)Shifr, len, key, true);
	for (int i = 0; i < len; i++)
		printf("%c Code=%d\n", Shifr[i], Shifr[i]);
	printf("DeShifr key=");
	scanf_s("%d", &key);
	shifr((unsigned char *)Shifr, (unsigned char *)DeShifr, len, key, false);
	DeShifr[len] = 0;
	printf("%s", DeShifr);
	printf("\n");
	system("pause");
	return 0;
}
