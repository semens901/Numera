#include "BasicStatsTests.h"

void basic_stats_tests()
{
    {
        std::vector<double> v{1.0, 2.0, 3.0};
        std::vector<double> w{1.0, 1.0, 1.0};

        double result = nr::weighted_mean(v, w);
        assert(std::abs(result - 2.0) < 1e-9);
    }

    {
        std::vector<double> v{42.0};
        std::vector<double> w{10.0};

        double result = nr::weighted_mean(v, w);
        assert(result == 42.0);
    }

    {
        std::vector<double> v{15, 10, 5, 90};
        std::vector <double> w{0.25, 0.20, 0.05, 0.50};

        double result = nr::weighted_mean(v, w);
        assert(result == 51.0);
    }
    {
        std::vector<double> population{
            54, 63, 48, 29, 27, 32, 41
        };

        double result = nr::geometric_mean(population);
        const double expected = 40.135109214786738;
        const double eps = 1e-6;

        assert(std::abs(result - expected) < eps);
    }
    
    {
        std::vector<double> population{54, 63, 48, 29, 27, 32, 41};

        double expected = 38.380368771744429; // рассчитанное гармоническое среднее вручную или в калькуляторе
        double result = nr::harmonic_mean(population);
        std::cout << result << std::endl;
        // Используем assert с допуском для вещественных чисел
        double eps = 1e-4; 
        assert(std::abs(result - expected) < eps);
    }

    {
        std::vector<int> data{54, 63, 48, 29, 27, 32, 41};

        auto q1 = nr::lower_quartile(data);

        assert(q1 == 29.0);
    }

    {
        std::vector<int> data{54, 63, 48, 29, 27, 32, 41};

        auto q3 = nr::upper_quartile(data);

        assert(q3 == 54.0);
    }

    {
        std::vector<int> data{5, 3, 8, 1, 4};

        int result = nr::min(data.begin(), data.end());

        assert(result == 1);
    }

    {
        std::vector<int> data{5, 3, 8, 1, 4};

        int result = nr::max(data.begin(), data.end());

        assert(result == 8);
    }
}