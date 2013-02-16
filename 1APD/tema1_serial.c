/*
 * Tema 1 - APD
 * Colonistii - varianta seriala neoptimizata
 * Necula Roxana - Valentina 332CA
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>

 FILE *fr, *fw;
 int n, pmin, pmax, i, j, t, k, l, min1, min2, ti, max, ra = 0, rb = 0, pma = -32000, pmb = -32000;
 char spatiu[2], fisin[50], fisout[50];

 int main(int argc,char *argv[])
 {
 	if (argc != 4)
 	{
        printf("Usage: %s T fisin fisout\n", argv[0]);
        return 1;
    }

 	strcpy(fisin, argv[2]);
 	strcpy(fisout, argv[3]);

 	fr = fopen(fisin, "r");
 	if (fr == NULL)
 	{
 		puts("cannot open file");
 		exit(0);
 	}

 	fw = fopen(fisout, "w");
 	if (fw == NULL)
 	{
 		puts("cannot open target file");
 		fclose(fr);
 		exit(0);
 	}

	fscanf(fr, "%d %d %d", &pmin, &pmax, &n);

	/*
	 * r[i][j] = matricea de resurse
	 * p[i][j] = matricea de preturi
	 * b[i][j] = matricea de buget
	 * cost[i][j] = matricea de costuri
	 * costRes[i][j] = matricea de costuri vazuta din perspectiva colonistului i j
	 * rn[i][j] (r next) = matricea de resurse pentru anul viitor
	 * pn[i][j] (p next) = matricea de preturi pentru anul viitor
	 * bn[i][j] (b next) = matricea de buget pentru anul viitor
	 */
 	int r[n][n], p[n][n], b[n][n], cost[n][n], costRes[n][n], rn[n][n], pn[n][n], bn[n][n];

 	//citire din fisier
 	fgets(spatiu, 1, fr);
 	for (i = 0; i < n; i++)
 		for (j = 0; j < n; j++)
 			fscanf(fr, "%d", &r[i][j]);
 	fgets(spatiu, 1, fr);
 	for (i = 0; i < n; i++)
 		for (j = 0; j < n; j++)
 			fscanf(fr, "%d", &p[i][j]);
 	fgets(spatiu, 1, fr);
 	for (i = 0; i < n; i++)
 		for (j = 0; j < n; j++)
 			fscanf(fr, "%d", &b[i][j]);
 	fgets(spatiu, 1, fr);

 	t = atoi(argv[1]);

 	//calculul matricelor cost[i][j] si costRes[i][j]
 	for (i = 0; i < n; i++)
 		for (j = 0; j < n; j++)
 		{
 			min1 = 32000; min2 = 32000;
 			for (k = 0; k < n; k++)
 				for (l = 0; l < n; l++)
 				{
 					if (r[k][l] == 1 - r[i][j])
 					{
 						if ((p[k][l] + abs(i - k) + abs(j - l) < min1) && (abs(i - k) > 0 || abs(j - l) > 0))
 						{
 							min1 = p[k][l] + abs(i - k) + abs(j - l);
 						}
 					} else {
						if (r[k][l] == r[i][j])
						{
 							if (p[k][l] + abs(i - k) + abs(j - l) < min2)
 							{
 								min2 = p[k][l] + abs(i - k) + abs(j - l);
 							}
 						}
 					}
 				}
 			cost[i][j] = min1;
 			costRes[i][j] = min2;
 		}

 	//calcul final
 	for (ti = 0; ti < t; ti++)
 	{
 		/*
 		 * ra = nr de colonisti ce produc resursa A
 		 * rb = nr de colonisti ce produc resursa B
 		 * pma = pretul maxim al resursei A
 		 * pmb = pretul maxim al resursei B
 		 */
 		ra = 0;
 		rb = 0;
 		pma = -32000;
 		pmb = -32000;
 		for (i = 0; i < n; i++)
 		{
 			for (j = 0; j < n; j++)
 			{
 				// pct 2
 				if (cost[i][j] > b[i][j])
 				{
 					rn[i][j] = r[i][j];
 					bn[i][j] = cost[i][j];
 					pn[i][j] = p[i][j] + cost[i][j] - b[i][j];
 				} else {
 					//pct 3
 					if (cost[i][j] < b[i][j])
 					{
 						rn[i][j] = r[i][j];
 						bn[i][j] = cost[i][j];
 						pn[i][j] = p[i][j] + (cost[i][j] - b[i][j]) / 2;
 					} else {
 						//pct 4
 						if (cost[i][j] == b[i][j])
 						{
 							rn[i][j] = r[i][j];
 							bn[i][j] = cost[i][j];
 							pn[i][j] = costRes[i][j] + 1;
 						}
 					}
 				}

 				//pct 5
 				if (pn[i][j] < pmin)
 				{
 					pn[i][j] = pmin;
 				}

 				//pct 6
 				if (pn[i][j] > pmax)
 				{
 					rn[i][j] = 1 - r[i][j];
 					bn[i][j] = pmax;
 					pn[i][j] = (pmin + pmax) / 2;
 				}

 				if (rn[i][j] == 0)
 				{
 					ra++;
 					if (pma <= pn[i][j])
 					{
 						pma = pn[i][j];
 					}
 				} else {
 					rb++;
 					if (pmb <= pn[i][j])
 						pmb = pn[i][j];
 				}
 			}
 		}

 		fprintf(fw, "%d %d %d %d\n", ra, pma, rb, pmb);

 		for (i = 0; i < n; i++)
 			for (j = 0; j < n; j++)
 			{
 				r[i][j] = rn[i][j];
 				p[i][j] = pn[i][j];
 				b[i][j] = bn[i][j];
 			}

 		// recalcularea matricelor cost si costRes
 		for (i = 0; i < n; i++)
 			for (j = 0; j < n; j++)
 			{
 				min1 = 32000; min2 = 32000;
 				for (k = 0; k < n; k++)
 					for (l = 0; l < n; l++)
 					{
 						if (r[k][l] == 1 - r[i][j])
 						{
 							if ((p[k][l] + abs(i - k) + abs(j - l) < min1) && (abs(i - k) > 0 || abs(j - l) > 0))
 							{
 								min1 = p[k][l] + abs(i - k) + abs(j - l);
 							}
 						} else {
							if (r[k][l] == r[i][j])
							{
 								if (p[k][l] + abs(i - k) + abs(j - l) < min2)
 								{
 									min2 = p[k][l] + abs(i - k) + abs(j - l);
 								}
 							}
 						}
 					}
 				cost[i][j] = min1;
 				costRes[i][j] = min2;
 			}

 	}

 	for (i = 0; i < n; i++)
 	{
 		for (j = 0; j < n; j++)
 			fprintf(fw, "(%d,%d,%d) ", r[i][j], p[i][j], b[i][j]);
 		fprintf(fw, "\n");
 	}


 	fclose(fr);
 	fclose(fw);
 }