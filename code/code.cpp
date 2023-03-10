#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_distribution(float distribution[]) {
	FILE *fp;
	int i;
	
	fp = fopen("frequences.txt", "r");
	if (fp == NULL) {
		printf("Failed to open file.\n");
		return;
	}

	for (i = 0; i < 26; i++) {
		if (fscanf(fp, "%f", &distribution[i]) != 1) {
			printf("Failed to read distribution for letter %c.\n", 'a' + i);
			fclose(fp);
			return;
		}
	}

	fclose(fp);
}

void encrypt(char s[], int n) {

	int i = 0;
	while (s[i] != NULL)
	{
		if (s[i] >= 'a' && 'z' >= s[i])
			if (s[i] + n < 'a' || s[i] + n>'z')
				if (n > 0)
					s[i] = (s[i] - 'a' + n) % 26 + 'a';
				else
					s[i] = (s[i] - 'a' + n + 26) % 26 + 'a';
			else
				s[i] = s[i] + n;
		else
			if (s[i] >= 'A' && 'Z' >= s[i])
				if (s[i] + n < 'A' || s[i] + n>'Z')
					if (n > 0)
						s[i] = (s[i] - 'A' + n) % 26 + 'A';
					else
						s[i] = (s[i] - 'A' + n + 26) % 26 + 'A';
				else
					s[i] = s[i] + n;;


		i++;
	}
}


int normalized_freq(char s[], float distrb[], float nrapp[])
{
	int i = 0;
	int nrwords = 0;
	for (i = 0; i < 26; i++)
		nrapp[i] = 0;
	i = 0;
	
	while (s[i] != NULL)
	{	
		if (s[i] >= 'a' && 'z' >= s[i])
		{
			nrapp[s[i] - 'a']++;
			
		}
			
		else
			if (s[i] >= 'A' && 'Z' >= s[i])
			{
				nrapp[s[i] - 'A']++;
				nrwords++;

			}
				
		i++;
	}
	for (i = 0; i < 26; i++)
	{
		nrapp[i] = nrwords * nrapp[i] / 100;
		
	}
	
		
	return nrwords;
}
float chiDist(char s[], float distrb[], float  nrapp[])
{
	int i;
	float chi = 0;
	int words=normalized_freq(s, distrb, nrapp);
	for (i = 0; i < 26; i++)
		
		chi += (nrapp[i] - words*distrb[i]/100)*(nrapp[i] - words * distrb[i] / 100) / distrb[i];

	return chi;
}
void breaks(char s[], float distrb[], float nrapp[])
{
	char s1[300], sol[300];

	strcpy(s1, s);
	encrypt(s1, 1);
	strcpy(sol, s1);
	float min = chiDist( s, distrb, nrapp);
	
	
	int i = 1;
	while (i<26)
	{
		encrypt(s1, i++);
		int chi = chiDist(s1, distrb, nrapp);
		if (chi < min)
		{
			min = chiDist( s1, distrb, nrapp);
			strcpy(sol, s1);
		}
		
		
		

	}
	strcpy(s, sol);

}

int main()
{
	
	int n;
	char s[] = "Uf ime ftq nqef ar fuyqe, uf ime ftq iadef ar fuyqe, uf ime ftq msq ar iuepay, uf ime ftq msq ar raaxuetzqee, uf ime ftq qbaot ar nqxuqr, uf ime ftq qbaot ar uzodqpgxufk, uf ime ftq eqmeaz ar xustf, uf ime ftq eqmeaz ar pmdwzqee, uf ime ftq ebduzs ar tabq, uf ime ftq iuzfqd ar pqebmud.";

	float distribution[26], nrapp[26] = { 0 };
	int i;

	read_distribution(distribution);

	printf("Distribution of letters:\n");
	
	printf("Coded text: ");

	printf("%s\n", s);
	s[strlen(s) - 1] = NULL;
	printf("Decoded text: ");
	breaks(s, distribution, nrapp);
	printf("%s\n", s);

	

	

	return 0;
}