#include <stdio.h>

int main(int argc, char const *argv[])
{
	int aux1, aux2, n, arreglo[10], pal;
	aux1 = 0;

	printf("introduce el numero: ");
	scanf("%d", &n);

	if(n == 0)
	{
		printf("el numero %d es palindromo", n);
		return 0;
	}
	else if(n < 0)
	{
		printf("el numero %d no es palindromo", n);
		return 0;
	}
	else
	{
		aux2 = n;
		while (aux2 > 0)
		{
			aux2 /= 10;
			aux1 ++;
		}

		for (int i = aux1 - 1; i >= 0; i--)
		{
			arreglo[i] = n % 10;
			n /= 10;
		}
	}

	pal = 1;

	for(int i = 0; i < aux1 / 2; i++)
	{
		if(arreglo[i] != arreglo[aux1 - 1 - i])
			pal = 0;
			break;
	}

	if(pal)
	{
		printf("es palindromo\n");
	}
	else
	{
		printf("no es palindromo\n");
	}

	return 0;
}