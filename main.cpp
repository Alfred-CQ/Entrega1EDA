/*
 * Distancias en N dimensiones
 * Chillitupa Quispihuanca, Alfred Addison
 * Estructuras de Datos Avanzadas
 * CCOMP6-1
 * C++
*/

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include <fstream>

#include <math.h>

using namespace std;


int main() {

    string filename("out.txt"); fstream file_out;

	const int elements{20000};
    int dimensions[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int ndimensions = sizeof(dimensions)/sizeof(dimensions[0]), 
        pivotBegin, pivotEnd, subtraction, power, pivotDistance, counter{0},
        distancesSize;

    long int sum;

	random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<> distrib(1, 100);

    int d, i, j;
    
    vector<int> distances;

    file_out.open(filename, std::ios_base::out);

    if (!file_out.is_open()) {
        cout << "failed to open " << filename << '\n';
        return -1;
    }

    for (d = 0; d < ndimensions; ++d)
    {

        vector<int> randomNumbers (elements * dimensions[d]);

	    for (i = 0; i < elements * dimensions[d]; ++i)
            randomNumbers[i] = distrib(gen);


        pivotBegin = dimensions[d]; pivotEnd = (2*dimensions[d])-1;
       
        j = 0;
        sum = 0;
        counter = 0;

        file_out << "\n------- Dimension: " << dimensions[d] << " ---------\n";
        cout << "\n------- Dimension: " << dimensions[d] << " ---------\n";

        for (i = 0; i < elements * dimensions[d]; ++i)
        {
            if ( i < pivotBegin || i > pivotEnd)
            {
                subtraction = randomNumbers[i] - randomNumbers[pivotBegin + j];
                power = subtraction * subtraction;
                
                if (dimensions[d] == 1)
                    distances.push_back(power);
                else
                {
                    sum += power;
                    j++;

                    if (j == dimensions[d])
                    {
                        distances.push_back(round(sqrt(sum)));
                        j = 0; sum = 0;
                    }
                    
                }
            }
        }

        sort(distances.begin(),distances.end());
        distancesSize = distances.size();
        pivotDistance = distances[0];

        file_out << pivotDistance << " : ( ";
	    cout << pivotDistance << " : ( ";

	    for (int i = 0; i < distancesSize; ++i)
	    {
		    if (pivotDistance == distances[i])
			    counter++;
		    else
		    {
			    pivotDistance = distances[i];

                file_out << counter << " )\n" << pivotDistance << " : ( ";

			    cout << counter << " )\n" << pivotDistance << " : ( ";

                counter = 1;
		    }   
	    }

        file_out << counter << " )\n";
        cout << counter << " )\n";

        distances.clear();
        randomNumbers.clear();
    }

    file_out.close();

	return 0;
}