#include <vector>
#include <iostream>

template<typename T>
void print_vector(std::vector<T> vec){
    for (auto i = vec.begin(); i != vec.end(); ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;
}

void tamper(std::vector<int> &vec){
    vec.emplace_back(6);
}

int main(int argc, char const *argv[])
{
    std::vector<int> v{1,2,3};
    tamper(v);
    print_vector(v);
    return 0;
}
