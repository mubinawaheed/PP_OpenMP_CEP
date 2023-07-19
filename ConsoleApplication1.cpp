#include <omp.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>

int main() {
	int InputImage[6][6];
	int OutputImage[6][6];
	int NoOfRows = 6;
	int NoOfColumns = 6;
	int i, j, k, m, R1;
	int Kernel[3][3];

	omp_set_nested(1);

	Kernel[0][0] = 0;
	Kernel[0][1] = -1;
	Kernel[0][2] = 0;
	Kernel[1][0] = -1;
	Kernel[1][1] = 4;
	Kernel[1][2] = -1;
	Kernel[2][0] = 0;
	Kernel[2][1] = -1;
	Kernel[2][2] = 0;

	printf("\n----------Kernel-----------\n");
	for (int i = 0; i < 3; i++) {
		std::cout << " | ";
		for (int j = 0; j < 3; j++) {
			std::cout << Kernel[i][j] << ", ";
		}
		std::cout << " | ";
		printf("\n");
	}

	//populating the image pixels
	for (i = 0; i < NoOfRows; i++) {
		for (j = 0; j < NoOfColumns; j++) {
			InputImage[i][j] = rand() % 50;
			OutputImage[i][j] = 0;
		}
	}
	printf("\n --------Input Image--------------\n");
	for (int i = 0; i < 6; i++) {
		std::cout << " | ";
		for (int j = 0; j < 6; j++) {
			std::cout << InputImage[i][j] << ", ";
		}
		std::cout << " | ";
		printf("\n");
	}
	printf("\n");

	//code for execution time
	double start_time = omp_get_wtime();
	printf("Total threads: %d\n", omp_get_max_threads());

	#pragma omp parallel for shared(InputImage, OutputImage), num_threads(NoOfRows-2)
	for (i = 1; i < NoOfRows - 1; i++) { // i and j are starting from 1 and NoOfRows & NoOfColumns

	#pragma omp parallel for num_threads(NoOfColumns-2)
		for (j = 1;j < NoOfColumns - 1; j++) // are reduced by 1 to ignore border pixels
		{
			R1 = 0;			
			for (k = -1; k < 2; k++) { 
				for (m = -1; m < 2; m++) {
					R1 += InputImage[i + k][j + m] * Kernel[k + 1][m + 1]; //values between (0-255)
				}
			}
			OutputImage[i][j] = R1;
			printf("\n Thread %d of %d: OutputImage[%d][%d] = %d\n", omp_get_thread_num(), omp_get_num_threads(),i,j, OutputImage[i][j]);
		}
	}

	double end_time = omp_get_wtime();

	printf("\n----output Image------\n");
	for (int i = 0; i < 6; i++) {
		printf("\n ");
		for (int j = 0; j < 6; j++) {
			std::cout << OutputImage[i][j] << ", ";
		}
		printf("\n");
	}

	// Calculate and print the execution time
	double execution_time = end_time - start_time;
	printf("\n Execution time for parallelized version: %.6f seconds\n", execution_time);
}



