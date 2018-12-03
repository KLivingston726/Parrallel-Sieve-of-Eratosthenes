/* Keith Livingston
 * Leomar Olivares
 * Dr. Lu
 * 11/26/18
 * Seive of Eratosthenes
 * 
 * This Program demonstrates how Eratosthenes Seive that he created around 250 B.C.E. works with todays modern technology.
 * We are using his same Seive to find all the prime numbers in a set of data. 
 * For this example we use parallel programing to enhance the time complexity of this algorithm. 
 * We use multiple threads and processors all running at the same time to make this code more efficient.
 * The user has to set up the number of threads they would like to use by setting it in their terminal window. 
 * To do this type in the command: export OMP_NUM_THREADS=1. This command will set the
 * total amount of threads being used to 1. Change the number at the end  to add more threads. 
 */

# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <omp.h>

using namespace std;

int Multipier(int n);
void primeRun(int num1, int num2, int multi);

int main(int argc, char *argv[])
{
    
    int num1;
    int num2;
    int multi;
    
    cout << endl << "Processors Used = " << omp_get_num_procs() << endl;
    cout << "Threads Used = " << omp_get_max_threads() << endl;

    num1 = 5;
    num2 = 327680;
    multi = 2;

    primeRun(num1, num2, multi);

    return 0;
}

//This function is what keeps track of the time complexity of the run and prints it to the screen.
//This part of the program deals with a lot of the interface on the terminal. 
//This function is also when the Miltiplier function is called to get the total number of primes. 
void primeRun(int num1, int num2, int multi)
{
  
    int primes;
    double wtime;

    cout << endl << "         N    Primes            Time" << endl << endl;

    int n = num1;

    while (n <= num2)
    {
        wtime = omp_get_wtime();
        primes = Multipier(n);
        wtime = omp_get_wtime() - wtime;

        cout << "  " << setw(8) << n << "  " << setw(8) << primes << "  " << setw(14) << wtime << endl;

        n = n * multi;
    }
 
    cout << endl;
    return;
}

//This function checks to see if the number is prime. This is where the parrallel computing happens.
//Each thread is able to take a number and run it through the Multiplier function at the same time with different data. 
//This way the program will be able to check multiple numbers to see if they are primes at the same time.
//This function returns the total number of primes in each set of numbers given.
int Multipier(int n) 
{
    int prime;
    int total = 0;
    int i;
    int j;
    
# pragma omp parallel \
    shared (n) \
    private(i,j,prime)
    
# pragma omp for reduction(+total)
    for (i = 2; i <= n; i++)
    {
        prime = 1;

        for (j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                prime = 0;
                break;
            }
        }
        
    total = total + prime;
    }

  return total;
}
