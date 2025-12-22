#include "VectorDataTests.h"

bool almostEqual(double a, double b, double eps = 1e-9)
{
    return std::abs(a - b) < eps;
}

void vector_data_tests()
{
    {
        std::cout << "[TEST] VectorData basic functionality\n";

        nr::VectorData<double> vd;
        assert(vd.size() == 0);
        assert(vd.empty());

        vd.add(3.14);
        vd.add(2.71);
        vd.add(1.41);

        assert(vd.size() == 3);
        assert(!vd.empty());
        assert(almostEqual(vd[0], 3.14));
        assert(almostEqual(vd[1], 2.71));
        assert(almostEqual(vd[2], 1.41));

        vd.clear();
        assert(vd.size() == 0);
        assert(vd.empty());

        nr::VectorData<double> vd1;
        nr::VectorData<double> vd2 = vd1;
        nr::VectorData<double> vd4 = std::move(vd2);
        assert(vd2.size() == 0);

        nr::VectorData<double> vd5({1,2,3});
        vd5.remove_at(1);

        std::cout << "Test passed: basic functionality works correctly.\n";\
    }

    {
        std::cout << "[TEST] Adding elements\n";
        nr::VectorData<double> vd;
        vd.add({1.0, 2.0, 3.0, 4.0, 5.0});
        assert(vd.size() == 5);
        std::cout << "Test passed: size is " << vd.size() << "\n";
        
        std::cout << "[TEST] Copy and move semantics\n";
        nr::VectorData<double> vd2 = vd; // copy constructor
        assert(vd2.size() == 5);    
        std::cout << "Test passed: size is " << vd2.size() << "\n";
        
        std::cout << "[TEST] Copy and move semantics\n";
        nr::VectorData<double> vd3;
        vd3 = vd; // copy assignment
        assert(vd3.size() == 5);    
        std::cout << "Test passed: size is " << vd3.size() << "\n";

        std::cout << "[TEST] Move semantics\n";
        nr::VectorData<double> vd4 = std::move(vd); // move constructor
        assert(vd4.size() == 5);
        assert(vd.size() == 0); // vd should be empty after move
        std::cout << "Test passed: size is " << vd4.size() << "\n";    
        
        std::cout << "[TEST] Move semantics\n";
        nr::VectorData<double> vd5;
        vd5 = std::move(vd2); // move assignment
        assert(vd5.size() == 5);
        assert(vd2.size() == 0); // vd2 should be empty after move
        std::cout << "Test passed: size is " << vd5.size() << "\n";

        std::cout << "[TEST] Removing elements\n";
        nr::VectorData<double> vd6({1,2,3});
        vd6.remove_at(1); // remove element at index 1
        assert(vd6.size() == 2);
        assert(vd6[0] == 1);
        assert(vd6[1] == 3);
        std::cout << "Test passed: size is " << vd6.size() << "\n";
    }

    {
        
        std::cout << "[TEST] VectorData stats funcs\n";
        nr::VectorData<double> vc({1, 2, 3, 4});
        assert(vc.min() == 1);
        assert(vc.max() == 4);

        std::cout << "Test passed: min is " << vc.min() << ", max is " << vc.max() << "\n";
        
        assert(almostEqual(vc.mean(), 2.5));
        std::cout << "Test passed: mean is " << vc.mean() << "\n";
        /*
            assert(almostEqual(vc.median(), 2.5));
        */
        
        
    }
}