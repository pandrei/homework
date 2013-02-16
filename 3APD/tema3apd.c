/*
 * Necula Roxana - Valentina 332CA
 * Tema3 APD - Calcul paralel folosind MPI
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);

	int rank, size;
	int set;
	double x_min, x_max, y_min, y_max;
	double pas;
	int max_steps;
	double param_julia1, param_julia2;

    int i, j, k;
    int *vprel, **matrice;

    int width, height;
    double xy[4];
    double param[2];
    MPI_Status status;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        FILE *fp_in, *fp_out;
    	fp_in = fopen(argv[1], "r");
        fp_out = fopen(argv[2], "w");
    	if (fp_in == NULL)
    	{
    		printf("File in not found!");
    		return 1;
    	}
        if (fp_out == NULL)
        {
            printf("File out not found!");
            return 1;
        }

    	fscanf(fp_in, "%d %lf %lf %lf %lf", &set, &x_min, &x_max, &y_min, &y_max);
    	fscanf(fp_in, "%lf %d", &pas, &max_steps);
    	if (set == 1)
        {
    		fscanf(fp_in, "%lf %lf", &param_julia1, &param_julia2);
            param[0] = param_julia1;
            param[1] = param_julia2;
        }
        xy[0] = x_min; xy[1] = x_max; xy[2] = y_min; xy[3] = y_max;

    	width = (int) ((x_max - x_min) / pas + 0.5);
        height = (int) ((y_max - y_min) / pas + 0.5);

        matrice = (int**) malloc(height * sizeof(int*));
        for (i = 0; i < height; i++)
            matrice[i] = (int*) malloc(width * sizeof(int));
        vprel = (int *) malloc(width * (height / size) * sizeof(int));

        //TAG: 0 = calcul    1 = prelucrare date
        //trimit datele citite din fisier
        for (i = 1; i < size; i++)
        {
            MPI_Send(&height, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&width, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&set, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&xy, 4, MPI_DOUBLE, i , 0 , MPI_COMM_WORLD);
            MPI_Send(&pas, 1, MPI_DOUBLE, i, 0 , MPI_COMM_WORLD);
            MPI_Send(&max_steps, 1, MPI_INT, i , 0 , MPI_COMM_WORLD);
            if (set == 1)
                MPI_Send(&param, 2, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
        
        /*
         * Masterul (procesul cu rank 0) prelucreaza prima bucata de matrice
         * adica chunksize = nr de linii(height) / size (nr de procese).
         * Apoi fiecare worker prelucreaza partea lui de matrice
         */

        //primesc de la workeri datele calculate in vectorul vprel
        for (i = 1; i < size; i++)
        {
            MPI_Recv(vprel, width * (height / size), MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
            for (j = 0; j < (height / size); j++)
                for (k = 0; k < width; k++)
                    matrice[j + status.MPI_SOURCE * (height / size)][k] = vprel[j * width + k];
        }

        int color, step;
        double zr, zi, temp;

        //calculez primul chunksize de linii
        //multimea Mandelbrot
        if (set == 0)
        {
            for (i = 0; i < (height / size); i++)
            {
                for (j = 0; j < width; j++)
                {
                    zr = 0;
                    zi = 0;
                    step = 0;
                    while ( (sqrt(zr * zr + zi * zi) < 2) && (step < max_steps) )
                    {
                        temp = zr * zr - zi * zi + (xy[0] + pas * j);
                        zi = 2 * zr * zi + (xy[2] + pas * i);
                        zr = temp;
                        step++;
                    }
                    color = step % 256;
                    matrice[i][j] = color;
                }
            }
        } else {
            //multimea Julia
            for (i = 0; i < (height / size); i++)
            {
                for (j = 0; j < width; j++)
                {
                    step = 0;
                    zr = xy[0] + pas * j;
                    zi = xy[2] + pas * i;
                    while ( (zr * zr + zi * zi < 4) && (step < max_steps) )
                    {
                        temp = zr * zr - zi * zi + param_julia1;
                        zi = 2 * zr * zi + param_julia2;
                        zr = temp;
                        step++;
                    }
                    color = step % 256;
                    matrice[i][j] = color;
                }
            }
        }

        //calculez ultimele linii necalculate de workeri
        if (set == 0)
        {
            for (i = size * ((int) height / size); i < height; i++)
                for (j = 0; j < width; j++)
                {
                    zr = 0;
                    zi = 0;
                    step = 0;
                    while ( (sqrt(zr * zr + zi * zi) < 2) && (step < max_steps) )
                    {
                        temp = zr * zr - zi * zi + (xy[0] + pas * j);
                        zi = 2 * zr * zi + (xy[2] + pas * i);
                        zr = temp;
                        step++;
                    }
                    color = step % 256;
                    matrice[i][j] = color;
                }
        } else {
            for (i = size * ((int) height / size); i < height; i++)
                for (j = 0; j < width; j++)
                {
                    step = 0;
                    zr = xy[0] + pas * j;
                    zi = xy[2] + pas * i;
                    while ( (zr * zr + zi * zi < 4) && (step < max_steps) )
                    {
                        temp = zr * zr - zi * zi + param_julia1;
                        zi = 2 * zr * zi + param_julia2;
                        zr = temp;
                        step++;
                    }
                    color = step % 256;
                    matrice[i][j] = color;
                }
        }

        fprintf(fp_out, "P2\n");
        fprintf(fp_out, "%d %d\n", width, height);
        fprintf(fp_out, "255\n");
        for (i = height - 1; i >= 0; i--)
        {
            for (j = 0; j < width; j++)
            {
                fprintf(fp_out, "%d ", matrice[i][j]);
            }
            fprintf(fp_out, "\n");
        }
            
        fclose(fp_in);
        fclose(fp_out);

    } else {
        //workerii
        MPI_Recv(&height, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&width, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&set, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&xy, 4, MPI_DOUBLE, 0 , 0 , MPI_COMM_WORLD, &status);
        MPI_Recv(&pas, 1, MPI_DOUBLE, 0, 0 , MPI_COMM_WORLD, &status);
        MPI_Recv(&max_steps, 1, MPI_INT, 0 , 0 , MPI_COMM_WORLD, &status);
        if (set == 1)
            MPI_Recv(&param, 2, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);

        vprel = (int *) malloc(width * (height / size) * sizeof(int));

        int color, step;
        double zr, zi, temp;
        //multimea Mandelbrot
        if (set == 0)
        {  
            for (i = 0; i < (height / size); i++)
            {
                for (j = 0; j < width; j++)
                {
                    zr = 0;
                    zi = 0;
                    step = 0;
                    while ( (zr * zr + zi * zi < 4) && (step < max_steps) )
                    {
                        temp = zr * zr - zi * zi + (xy[0] + pas * j);
                        zi = 2 * zr * zi + (xy[2] + pas * (i + (rank * (height / size))));
                        zr = temp;
                        step++;
                    }
                    color = step % 256;
                    vprel[i * width + j] = color;
                }
            }
            MPI_Send(vprel, width * (height / size), MPI_INT, 0, 1, MPI_COMM_WORLD);
            
        } else {
            //multimea Julia
            int step, color;
            double zr, zi, temp;

            for (i = 0; i < (height / size); i++)
            {
                for (j = 0; j < width; j++)
                {
                    step = 0;
                    zr = xy[0] + pas * j;
                    zi = xy[2] + pas * (i + (rank * (height / size)));
                    while ( (zr * zr + zi * zi < 4) && (step < max_steps) )
                    {
                        temp = zr * zr - zi * zi + param[0];
                        zi = 2 * zr * zi + param[1];
                        zr = temp;
                        step++;
                    }
                    color = step % 256;
                    vprel[i * width + j] = color;
                }
            }
            MPI_Send(vprel, width * (height / size), MPI_INT, 0, 1, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;

}