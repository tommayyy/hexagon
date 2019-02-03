#include <iostream>
#include <vector>
#include <set>

bool is_unique(std::vector<int> *X)
{
    std::set<int> Y(X->begin(), X->end());
    return X->size() == Y.size();
}

void inc(std::vector<int> *vec, int nn = 0, int b = 19)
{
    if (vec->size() == nn)
    {
        vec->push_back(1);
        return;
    }
    (*vec)[nn]++;
    if ((*vec)[nn] == b)
    {
        (*vec)[nn] = 0;
        inc(vec, nn + 1, b);
    }
}

void incc(std::vector<int> *vec, int nn = 0, int b = 19)
{
    do
    {
        inc(vec, nn, b);
    } while (!is_unique(vec));
}

void o(std::vector<int> *vec)
{
    for (std::vector<int>::iterator it = vec->begin(); it != vec->end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> *v = new std::vector<int>();
    v->push_back(0);
    v->push_back(0);
    v->push_back(0);
    
    incc(v);

    o(v);
    return 0;
}
