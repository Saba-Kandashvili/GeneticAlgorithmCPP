#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include <algorithm>

struct Solution
{
	double rank; 
	double x;
	double y;
	double z;

	void fitness()
	{
		// your function here:
		double ans = (0.5 * x + -y/4.5 + std::sqrt(std::pow(z, 3))) - 9;


		rank = (ans == 0) ? 9999 : std::abs(1 / ans);
	}
};

int main ()
{
	// intitial random solutions
	std::random_device device;
	std::uniform_real_distribution<double> unif(-100, 100);
	std::vector<Solution> solutions;

	const int NUM = 1000000;
	for (int i = 0; i < NUM; i++)
		solutions.push_back(Solution{0, unif(device), unif(device), unif(device)});

	while (true)
	{



		for (auto& s : solutions)
		{
			s.fitness();
		}

		std::sort(solutions.begin(), solutions.end(), [](const auto& lhs, const auto& rhs) {return lhs.rank > rhs.rank; });

		std::for_each(solutions.begin(), solutions.begin()+1, [](const auto& s)
			{
				std::cout << std::fixed << "Rank " << static_cast<int>(s.rank) << std::endl
					<< "x:" << s.x << "y: " << s.y << "z: " << s.z << std::endl;
			});

		// take top 1000 solutions
		const int SAMPLE_SIZE = 1000;
		std::vector<Solution> sample;
		std::copy(solutions.begin(), solutions.begin() + SAMPLE_SIZE, std::back_inserter(sample));
		solutions.clear();

		// mutate top solutions %
		std::uniform_real_distribution<double> m(0.99, 1.01);
		std::for_each(sample.begin(), sample.end(), [&](auto& s) {
			s.x *= m(device);
			s.y *= m(device);
			s.z *= m(device);
			});

		// cross over
		std::uniform_int_distribution<int> cross(0, SAMPLE_SIZE - 1);
		for (int i = 0; i < NUM; i++)
		{
			solutions.push_back(Solution{
				0,
				sample[cross(device)].x,
				sample[cross(device)].y,
				sample[cross(device)].z,
				});
		}
	}
}