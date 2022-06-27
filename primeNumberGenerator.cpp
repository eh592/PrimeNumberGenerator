// primeNumbergenerator.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <vector>

using namespace std;
// still need to optimize lower input case

// update, cutting out checks of even numbers by intializing list to only odd numbers.
// maybe cut out the checks for first couple primes?

//loop count record

//Ruben 
//20 --> 72
//26 -- > 111
//165-->1917
//1228-->34883
//500 -->9,597
//5000--> 259,247
//20000-->1,854,790
//90000--> 15,808,379

//program(initial implementation of sieve)
//500-->22,900
//5000-->256, 673
//20000 --> 2, 742, 961
//90000 -->28,844,737

//update program (cut out the check for even numbers) 
//24 -->96
//26 -->1274
//165 -->1458
//170 -->16746
//1228-->18071
//500 --> 17,902
//5000-->206,675
//20000-->2,242,963
// 90000-->23,844,739


//http://mathworld.wolfram.com/PrimeCountingFunction.html
//i used the pi(10^n) table to set upper limit for a guided lower inner loop count
// although it is quite rigid, these bounds seem to give a structure to set my upperlimit 

const unsigned int INTERVALS_PRIMES[12] = {
	0, 4, 25, 168, 1229, 9592, 78498, 664579, 5761455, 50847534, 455052511, 4118054813
}; // depending on how many primes my user wants, I will set the upper bound accordingly
// ex. if user inputs 5000 then the upper bound will be set to 10^5. So it maps the index of each array to the other
// The closer the selection is to the upper bound it performs better relative to example code
// however once prime input crosses over into the next bound slightly, its perfomance becomes dramatically worse
// due to the upper bound scaling by ten.

// --> bottomline efficency drops as wanted primes crosses predefined UPPERBOUNDS,
// BUT in between each bound efficiency progressively gets closer to example exe. (even crossing it once it approaches close enough the next bound)
// then once it crosses the process starts all over again. the graph of my inner loop count would probably exhibit jump discontinuities,
// and progressive increase inbetween each upper bound. 

const unsigned long UPPERBOUND[8] = {
	10,
	10 * 10,
	10 * 10 * 10,
	10 * 10 * 10 * 10,
	10 * 10 * 10 * 10 * 10,
	10 * 10 * 10 * 10 * 10 * 10,
	10 * 10 * 10 * 10 * 10 * 10 * 10,
	10 * 10 * 10 * 10 * 10 * 10 * 10 * 10
};

int main()
{
	vector <unsigned int> list(4);
	list[0] = 0;
	list[1] = 0;
	list[2] = 1;
	list[3] = 1;
	vector <unsigned long long> foundPrimes(1);
	foundPrimes[0] = 2;

	unsigned long long coutner = 0;
	
	unsigned int numberOfPrimes;
	cout << "How many primes do you want to see??" << endl;
	cin >> numberOfPrimes; // the number of primes I want

	int sizeUPPERBOUND = sizeof(INTERVALS_PRIMES) / sizeof(INTERVALS_PRIMES[0]);

	unsigned long chosenBound = 0;
	

	for (int i = 0; i < sizeUPPERBOUND; i++) // set the upper interval limit for which to start computing primes
	{
		if ((numberOfPrimes >= INTERVALS_PRIMES[i]) && (numberOfPrimes <= INTERVALS_PRIMES[i + 1]))
		{
			for (int j = 0; j <= i; j++)
			{
				chosenBound = UPPERBOUND[i];
			}
		}
		else if (numberOfPrimes >= INTERVALS_PRIMES[10]) //
		{
			chosenBound = INTERVALS_PRIMES[11];
		}
	}
	for (unsigned long i = 4; i < chosenBound; i++) // fills the list vector with ones(YES IT IS PRIME) in which we'd would interpret the index number that corresponds to each one
	{									// as prime
		list.push_back(1);
		if ((i % 2) == 0) // to cut out evens upon creation of list to check 
		{
			list[i] = 0;
		}
			
	} // creates list of numbers 2 through upperBound

	// now starting at 2, cross out all multiples of two. then cross out all multiples of three... and so on until I have enough primes to output to user
	// after which this search process should exit.

	for (unsigned long i = 3; i < (chosenBound); i++)
	{
		if (list[i] == 1)// take the "assumed prime" entry and use it to eliminate multiples
		{
			for (unsigned int j = 2; (i*j) < (chosenBound); j++)// sets multiples of each incremented number as false since is is guarenteed to be Not Prime
			{
				list[i*j] = 0;
				coutner++;  
			}
			foundPrimes.push_back(i);// add number to the list since we assume it to be prime to begin with
		}
		if (foundPrimes.size() == numberOfPrimes) // since chosen bound scales by ten, it should properly get me out of the loop. 
		{
			i += chosenBound;
		}
	}
	cout << endl;
	if (numberOfPrimes != 1) 
	{
		for (int i = 0; i < foundPrimes.size(); i++)// walks through the list of found primes
		{
			cout << foundPrimes[i] << " ";
		}
	}
	else
	{
		cout << foundPrimes[0] <<endl;
	}
	
	cout << endl << endl << "Number times innermost loop ran: " << coutner << endl;
	return 0;
}

