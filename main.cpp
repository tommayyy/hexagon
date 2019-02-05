#include <iostream>
#include <vector>
#include <set>
#include <map>

using std::cout;
using std::endl;

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

std::vector<std::vector<int> > filter(std::vector<std::vector<int> > vect, std::map<int, int> mat)
{

    std::vector<std::vector<int> > a;

    for (auto v : vect) {
        bool found = true;
        for(auto m : mat) {
            if (v[m.first] != m.second) found = false;
        }
        if (found) a.push_back(v);

    }

    return a;

    //  foreach (auto v : vect) {
    //    $found = true;
    //    foreach ($mat as $sk => $sv) {
    //      if ($v[$sk] !== $sv) $found = false;
    //    }
    //    if ($found) $result[] = $v;
    //  }

    //  return $result;
}

std::vector<std::vector<int> > v3;
std::vector<std::vector<int> > v4;
std::vector<std::vector<int> > v5;

bool search(std::vector<std::vector<int> > result, int step)
{
    if (step == 0)
    {
        for (auto v : v5)
        {
            o(&v);
            result.push_back(v);
            if (search(result, 1))
            {
                return true;
            }
        }
        return false;
    }
    else if (step == 1)
    {
        std::vector<std::vector<int> > filtered_5 = v5;
        std::map<int, int> f;
        f[2] = result[0][2];
        for (auto v : filter(filtered_5, f))
        {
            o(&v);
            result.push_back(v);
            if (search(result, 2)) {
                return true;
            }
        }
        return false;
    } else if (step == 2)
    {
        std::vector<std::vector<int> > filtered_5 = v5;
        std::map<int, int> f;
        f[2] = result[0][2];
        for (auto v : filter(filtered_5, f))
        {
            o(&v);
            result.push_back(v);
            if (search(result, 2)) {
                return true;
            }
        }
        return false;
    }

    return false;
}

int main()
{
    std::vector<int> v;
    v.push_back(0);
    v.push_back(0);
    v.push_back(0);

    cout << "computing vectors... ";
    while (v.size() < 6)
    {
        int sum_of_elems = 0;
        incc(&v);
        if (v.size() == 3)
        {
            for (auto &n : v)
                sum_of_elems += n;
            if (sum_of_elems == 35)
                v3.push_back(v);
        }
        if (v.size() == 4)
        {
            for (auto &n : v)
                sum_of_elems += n;
            if (sum_of_elems == 34)
                v4.push_back(v);
        }
        if (v.size() == 5)
        {
            for (auto &n : v)
                sum_of_elems += n;
            if (sum_of_elems == 33)
                v5.push_back(v);
        }
    }
    cout << "done" << endl;

    cout << "Size: " << v3.size() << endl;
    o(&v3.back());
    cout << "Size: " << v4.size() << endl;
    o(&v4.back());
    cout << "Size: " << v5.size() << endl;
    o(&v5.back());

    std::vector<std::vector<int>> result;
    if (search(result, 0))
    {
        cout << "found vector" << endl;
    }
    else
    {
        cout << "no match" << endl;
    }

    return 0;
}
