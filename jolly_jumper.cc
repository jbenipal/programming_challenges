#include <iostream>
#include <vector>
#include <cstdlib>

bool is_jolly(std::vector<int> const &vec)
{
    int n = vec.size();
    long required_sum  = ((n)*(n-1))/2;

    long sum = 0;
    for (std::size_t i=1; i<n; ++i) {
        sum += std::abs(vec[i]-vec[i-1]);
    }
    if (sum == required_sum) return true;
    return false;
}

int main()
{
    std::size_t N;
    int a;
    while (std::cin>>N)
    {
        std::size_t count = 0;
        std::vector<int> vec(N);
        while(count < N)
        {
            std::cin >> vec[count++];
        }
        if (is_jolly(vec)) {
            std::cout << "Jolly" << std::endl;
        } else {
            std::cout << "Not jolly" << std::endl;
        }
    }
    return 0;
}
