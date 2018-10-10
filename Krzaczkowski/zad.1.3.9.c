#include <stdio.h>
int main()
{
	double liczba1=0; 
	double liczba2=0;
        char znak = ' ';	
	scanf("%lf %c %lf", &liczba1, &znak, &liczba2);
	printf("%lf %c %lf \n", liczba1, znak, liczba2);

	double wynik = 0;

	switch(znak)
	{
		case '+':
			wynik = liczba1 + liczba2;
			break;
		case '-':
			wynik = liczba1 - liczba2;
			break;
		case '*':
			wynik = liczba1 * liczba2;
			break;
		case '/':
			wynik = liczba1 / liczba2;
			break;
		default:
			printf("Nieobslugiwane dzialanie");
			return -1;
	}

	printf("Wynik %lf \n", wynik);

	return 0;
}

