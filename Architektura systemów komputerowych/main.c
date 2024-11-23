#include <math.h>
#include <stdio.h>

void exercise1();
void exercise2();
void exercise3();
void exercise4();
void exercise5();

void printByteDataHex(const char* message, void* data, int bytes);
void printByteDataBin(const char* message, void* data, int bytes);

void printBinaryInt(int x);
void printBinaryFloat(float x);

void u2Substraction(int a, int b);

void decToFloat(float x);
void floatToDec(const char* x);

int binToDec(const char* x, int start, int size);

int main()
{
	char input = 0;

	while (input != '6')
	{
		printf("1. Wydrukowanie postaci bajtowej danych INT, FLOAT, DOUBLE\n");
		printf("2. Wydrukowanie postaci binarnej danych INT, FLOAT, DOUBLE\n");
		printf("3. Zaprezentowanie wykonywania odejmowania w U2\n");
		printf("4. Zaprezentowanie konwersji FLOAT -> DEC\n");
		printf("5. Zaprezentowanie konwersji DEC -> FLOAT\n");
		printf("6. Wyjscie\n");

		input = getch();
		system("cls");
		switch (input)
		{
			case '1': exercise1(); break;
			case '2': exercise2(); break;
			case '3': exercise3(); break;
			case '4': exercise4(); break;
			case '5': exercise5(); break;
			default: break;
		}
		system("pause");
		system("cls");
	}

	return 0;
}

void exercise1()
{
	int i = 23;
	float f = 3.14f;
	double d = 6.28318530718;

	printf("Postac bajtowa (heksadecymalnie) roznych typow danych\n");
	printf("-----------------------------------------------------\n");
	printByteDataHex("int 23 == ", &i, sizeof(int));
	printByteDataHex("float 3.14 == ", &f, sizeof(float));
	printByteDataHex("double 6.28318530718 == ", &d, sizeof(double));
}

void exercise2()
{
	int i = 23;
	float f = 3.14f;
	double d = 6.28318530718;

	printf("Postac bajtowa (binarnie) roznych typow danych\n");
	printf("----------------------------------------------\n");
	printByteDataBin("int 23 == ", &i, sizeof(int));
	printByteDataBin("float 3.14 == ", &f, sizeof(float));
	printByteDataBin("double 6.28318530718 == ", &d, sizeof(double));
}

void exercise3()
{
	int a, b;

	printf("Prezentacja odejmowania dwoch liczb w systemie U2\n");
	printf("-------------------------------------------------\n");
	printf("Podaj a: ");
	scanf("%d", &a);
	printf("Podaj b: ");
	scanf("%d", &b);
	u2Substraction(a, b);
}

void exercise4()
{
	printf("Prezentacja konwersji DEC -> FLOAT\n");
	printf("----------------------------------\n");
	decToFloat(0.3f);
}

void exercise5()
{
	printf("Prezentacja konwersji FLOAT -> DEC\n");
	printf("----------------------------------\n");
	floatToDec("11000000110110011001100110011010");
}

void printByteDataHex(const char* message, void* data, int bytes)
{
	printf("%-24s", message);
	const unsigned char* it = (const unsigned char*)data;
	for (int i = 0; i < bytes; i++)
		printf("0x%02x ", it[i]);

	printf("\n\n");
}

void printByteDataBin(const char* message, void* data, int bytes)
{
	printf("%-24s", message);
	const unsigned char* it = (const unsigned char*)data;
	for (int i = 0; i < bytes; i++)
	{
		for (int j = 7; j >= 0; j--)
			printf("%u", (it[i] >> j) & 1);

		printf(" ");
	}

	printf("\n\n");
}

void printBinaryInt(int x)
{
	for (int i = (sizeof(int) * 8) - 1; i >= 0; i--)
	{
		printf("%u", (x >> i) & 1);
		if (i != 0 && i % 8 == 0)
			printf(" ");
	}
}

void printBinaryFloat(float x)
{
	unsigned int it = *(unsigned int*)&x;
	for (int i = (sizeof(float) * 8) - 1; i >= 0; i--)
	{
		printf("%u", (it >> i) & 1);
		if (i != 0 && i % 8 == 0)
			printf(" ");
	}
}

void u2Substraction(int a, int b)
{
	printf("1. Zapisz liczby w postaci binarnej\n");
	printBinaryInt(a);
	printf(" (%d)\n", a);
	printBinaryInt(b);
	printf(" (%d)", b);

	printf("\n\n2. Odwroc wszystkie bity drugiej liczby\n");

	printBinaryInt(b);
	printf(" =\n");
	b = ~b;
	printBinaryInt(b);

	printf("\n\n3. Dodaj do niej 1\n");
	printBinaryInt(b);
	printf(" + 1 =\n");
	b += 1;
	printBinaryInt(b);

	printf("\n\n4. Dodaj dwie liczby do siebie (zignoruj bity przeniesienia ktore spowodowaly by przekroczenie zakresu)\n");
	printBinaryInt(a);
	printf("\n");
	printBinaryInt(b);
	printf(" +\n---------------------------\n");

	int result = a + b;
	const unsigned char* it = (const unsigned char*)&result;
	printBinaryInt(result);
	printf(" (%d)\n%d - %d = %d\n\n", result, a, ~(b - 1), result);
}

void decToFloat(float x)
{
	float xCopy = x;

	printf("1. Okreslamy znak (0 dla dodatnich, 1 dla ujemnych)\n");
	int sign = x < 0 ? 1 : 0;
	printf("%f < 0\n%s%d\n\n", x, sign ? "tak, znak = " : "nie, znak = ", sign);

	printf("2. Normalizujemy liczbe %f do zakresu [1, 2)\n", x);
	int exponent = 0;
	if (x >= 2)
	{
		while (x >= 2)
		{
			printf("%f / 2 = %f\n", x, x / 2.0f);
			x /= 2.0f;
			exponent++;
		}
	}
	else
	{
		while (x < 1)
		{
			printf("%f * 2 = %f\n", x, x / 2.0f);
			x *= 2.0f;
			exponent--;
		}

	}

	printf("Otrzymano: %f\n%f = %f * 2^(%d)\n\n", x, xCopy, x, exponent);
	printf("3. Wyznaczenie wykladnika\n(127 + cecha = wykladnik) => (127 + %d = %d)\n", exponent, 127 + exponent);
	exponent = 127 + exponent;
	printf("%d = ", exponent);
	for (int i = 7; i >= 0; i--)
		printf("%d", (exponent >> i) & 1);

	char mantissa[23];
	printf("\n\n4. Obliczanie mantysy\n");
	for (int i = 0; i < 23; i++)
	{
		if (x >= 1.0f)
		{
			float fraction = x - 1;
			printf("%f -> %f, ", x, fraction);
			x -= 1;
		}

		printf("%f * 2 = %f.2f -> ", x, x * 2.0f);
		x *= 2.0f;
		mantissa[i] = x >= 1.0f ? '1' : '0';
		printf("%c\n", mantissa[i]);
	}

	printf("\n\n5. Finalna reprezentacja IEEE 754\n");
	printf("%f\n=\n%d ", xCopy, sign);
	for (int i = 7; i >= 0; i--)
		printf("%d", (exponent >> i) & 1);

	printf(" ");
	for (int i = 0; i < 23; i++)
		printf("%c", mantissa[i]);

	printf("\n\n");
}

int binToDec(const char* x, int start, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		if (x[i + start] == '1')
			sum += pow(2, size - 1 - i);
	}

	return sum;
}

void floatToDec(const char* x)
{
	printf("1. Konwertowanie %s\n\n", x);

	printf("2. Okreslamy znak\n");
	int sign = x[0] - '0';
	printf("%c - znak (1 ujemny, 0 dodatni)\n\n", x[0]);

	printf("3. Okreslamy ceche\n");
	int exponent = binToDec(x, 1, 8);
	printf("%.8s = %d\n\n", &x[1], exponent);

	printf("4. Konwertujemy mantyse\n");
	printf("%.23s = ", &x[9]);

	float mantissa = 0.0f;
	for (int i = 0; i < 23; i++)
	{
		int bit = x[9 + i] - '0';
		mantissa += bit * (1.0f / (1 << (i + 1)));

		if (i != 22)
			printf("%d * 2^(%d) + ", bit, -(i + 1));
		else 
			printf("%d * 2^(%d) = ", bit, -(i + 1));
	}
	printf("%f\n\n", mantissa);

	printf("5. Obliczamy rezultat\n");
	float result = pow(-1, sign) * (1 + mantissa) * (1 << (exponent - 127));
	printf("(-1)^(znak) * (1 + mantysa) * 2^(cecha - 127)\n");
	printf("=> (-1)^(%d) * (1 + %f) * 2^(%d - 127)\n", sign, mantissa, exponent);
	printf("=> %f\n\n", result);
}
