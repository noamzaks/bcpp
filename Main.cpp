#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    // 1
    vector<int> numbers = {8, 4, 1, 2, 3, 10, 4, 5, 4, 1574};

    // 2
    cout << count_if(numbers.begin(), numbers.end(), bind(equal_to<int>(), placeholders::_1, 4)) << endl;

    // 3
    cout << count_if(numbers.begin(), numbers.end(), bind(greater<int>(), placeholders::_1, 4)) << endl;

    // 4
    numbers.erase(remove_if(numbers.begin(), numbers.end(), bind(less<int>(), placeholders::_1, 8)), numbers.end());

    // 5
    copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));

    // 6
    vector<int> moreNumbers;

    // 7 - is the intention to remove the first element?
    adjacent_difference(numbers.begin(), numbers.end(), back_inserter(moreNumbers));

    // 8
    copy(moreNumbers.begin(), moreNumbers.end(), ostream_iterator<int>(cout, " "));

    // 9
    cout << accumulate(moreNumbers.begin(), moreNumbers.end(), 0, plus<int>()) << endl;
}