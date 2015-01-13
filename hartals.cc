/*
Programming Challenge: 110203
*/

#include <iostream>
#include <set>
#include <vector>

// Fri/Sat if Days start with Sun.
bool is_no_hartal_day(unsigned int n)
{
    return n%7==0 || (n+1)%7 == 0;
}

int calculate_non_working_days(std::vector<unsigned> const &hartal_params, unsigned no_of_days)
{
    std::size_t no_parties = hartal_params.size();
    std::set<unsigned> non_working_days;
    for(int i=0; i<no_parties; ++i)
    {
        int days = hartal_params[i];
        while (days<=no_of_days) {
            if (!is_no_hartal_day(days)) {
                if (!non_working_days.count(days)) {
                    non_working_days.insert(days);
                }
            }
            days += hartal_params[i];
        }
    }
    return non_working_days.size();
}

int main()
{
    unsigned tests, no_parties, no_days;;
    std::cin >> tests;
    while(tests>0)
    {
        std::cin >> no_days;
        std::cin >> no_parties;
        std::vector<unsigned> vec(no_parties);
        for(int i =0;i<no_parties;++i) {
            std::cin >> vec[i];
        }
        std::cout << calculate_non_working_days(vec, no_days) <<std::endl;
        --tests;
    }
    return 0;
}
