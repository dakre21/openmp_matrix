/* Author: David Akre
 * Date: 9/17/17
 * Description: Part 1 of hw4
 * - Apply a simple matrix multiplication and test the two 
 *   matrices by running it serially first followed by
 *   parallelized mechanism. Compare the total execution
 *   times for the processors scaling by 2 from 4 to 64.
 *   Additionally, profile the code to show the computing
 *   to communication ratios. 
 *
 * Description: Part 2 of h4
 * - Apply a filter on an image using the window size 3x3
 *   for a matrix size 256x256.
 *
 * Usage:
 * - Run ./matrix with the following argument options
 *   - arg: 1 run part 1 in parallel
 *   - arg: 2 run part 2 in parallel
 *
 * NOTE: This code heavily uses openmp for parallelization
 */

#include <matrix_ops.h>

int main (int argc, char* argv[])
{
    // NOTE: Sequential execution can be observed in hw2's mpi program
    int row_one = 512;
    int col_one = 512;
    int row_two = 256;
    int col_two = 256;
    int lower_bounds = 0;
    int upper_bounds = 512;
    double start_time = 0;
    double stop_time = 0;
    double total_time = 0;
    unsigned int** matrix_one; 
    unsigned int** matrix_two;
    unsigned int** matrix_product;

    // Create matrices for program
    create_matrix(&matrix_one, row_one, col_one, false);
    create_matrix(&matrix_two, row_two, col_two, false);
    create_matrix(&matrix_product, row_one, col_one, true);

    if (argv[1] == NULL) 
    {
        printf("ERROR: No input argument provided\n");
        exit(-1);
    }

    start_time = omp_get_wtime();

    if (strcmp(argv[1], "1")  == 0) 
    {
        multiply_matrix(&matrix_one, &matrix_one, &matrix_product,
                lower_bounds, upper_bounds, row_one, col_one);
    }
    else if (strcmp(argv[1], "2") == 0)
    {
        calc_matrix_filter(&matrix_two, 0, row_two, row_two, col_two); 
    }
    else
    {
        printf("ERROR: Input is invalid\n");
        exit(-1);
    }

    stop_time = omp_get_wtime();
    total_time = stop_time - start_time;

    printf("INFO: Total execution time %.6f\n", total_time);


    exit(0);
}

