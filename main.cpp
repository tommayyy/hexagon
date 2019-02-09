#include <iostream>
#include <iomanip>
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

std::vector<std::vector<int>> filter(std::vector<std::vector<int>> vect, std::map<int, int> mat)
{

    std::vector<std::vector<int>> a;

    for (auto v : vect)
    {
        bool found = true;
        for (auto m : mat)
        {
            if (v[m.first] != m.second)
                found = false;
        }
        if (found)
            a.push_back(v);
    }

    return a;
}

bool in_list(std::vector<int> search, std::vector<std::vector<int>> list)
{
    for (auto v : list)
    {
        if (v.size() != search.size())
            continue;
        bool found = true;
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i] != search[i])
            {
                found = false;
                break;
            }
        }
        if (found)
            return true;
    }
    return false;
}

std::vector<std::vector<int>> v3;
std::vector<std::vector<int>> v4;
std::vector<std::vector<int>> v5;

std::vector<std::vector<int>> filter_2(std::vector<std::vector<int>> a, std::vector<std::vector<int>> b, std::map<int, int> m)
{
    std::vector<std::vector<int>> result;
    std::set<int> s;
    for (auto _b : b)
    {
        for (auto i : _b)
        {
            bool ignore = false;
            for (auto it = m.begin(); it != m.end(); ++it)
            {
                if (it->second == i)
                    ignore = true;
            }
            if (!ignore && (s.find(i) == s.end()))
                s.insert(i);
        }
    }

    for (auto _v : a)
    {
        bool found = false;
        for (auto i : _v)
        {
            if (s.find(i) != s.end())
            {
                found = true;
                break;
            }
        }
        if (!found)
            result.push_back(_v);
    }
    return result;
}

bool check(std::vector<std::vector<int>> result)
{
    if (result[5][1] + result[7][1] + result[8][1] + result[6][0] != 34)
        return false;
    if (result[5][0] + result[7][2] + result[8][2] + result[6][1] + result[2][0] != 33)
        return false;
    if (result[7][3] + result[8][3] + result[6][2] + result[2][1] != 34)
        return false;

    if (result[0][1] + result[8][1] + result[6][1] + result[2][1] != 34)
        return false;
    if (result[0][0] + result[7][1] + result[8][2] + result[6][2] + result[2][2] != 33)
        return false;
    if (result[5][1] + result[7][2] + result[8][3] + result[6][3] != 34)
        return false;

    return true;
}

void print_result(std::vector<std::vector<int>> result)
{
    printf("    %2d  %2d  %2d\n", result[0][0] + 1, result[0][1] + 1, result[0][2] + 1);
    printf("  %2d  %2d  %2d  %2d\n", result[5][1] + 1, result[7][1] + 1, result[8][1] + 1, result[6][0] + 1);
    printf("%2d  %2d  %2d  %2d  %2d\n", result[5][0] + 1, result[7][2] + 1, result[8][2] + 1, result[6][1] + 1, result[1][2] + 1);
    printf("  %2d  %2d  %2d  %2d\n", result[4][1] + 1, result[8][3] + 1, result[6][2] + 1, result[2][1] + 1);
    printf("    %2d  %2d  %2d\n\n", result[3][2] + 1, result[3][1] + 1, result[3][0] + 1);
}

bool search(std::vector<std::vector<int>> result, int step)
{
    if (step == 0)
    {
        for (auto v : v3)
        {
            // o(&v);
            result.push_back(v);
            if (search(result, 1))
            {
                return true;
            }
            result.pop_back();
        }
        return false;
    }
    else if (step <= 5)
    {
        std::vector<std::vector<int>> filtered = v3;
        std::map<int, int> f;
        f[0] = result[step - 1][2];
        if (step == 5)
        {
            f[2] = result[0][0];
        }
        filtered = filter_2(filtered, result, f);
        for (auto v : filter(filtered, f))
        {
            if (in_list(v, result))
                continue;
            // o(&v);
            result.push_back(v);
            if (search(result, step + 1))
            {
                return true;
            }
            result.pop_back();
        }
        return false;
    }
    else if (step == 6)
    {
        std::vector<std::vector<int>> filtered = v4;
        std::map<int, int> f;
        f[0] = result[1][1];
        f[3] = result[3][1];
        filtered = filter_2(filtered, result, f);
        for (auto v : filter(filtered, f))
        {
            if (in_list(v, result))
                continue;
            // o(&v);
            result.push_back(v);
            if (search(result, 7))
            {
                return true;
            }
            result.pop_back();
        }
        return false;
    }
    else if (step == 7)
    {
        std::vector<std::vector<int>> filtered = v4;
        std::map<int, int> f;
        f[0] = result[0][1];
        f[3] = result[4][1];
        filtered = filter_2(filtered, result, f);
        for (auto v : filter(filtered, f))
        {
            if (in_list(v, result))
            {
                continue;
            }

            result.push_back(v);
            if (search(result, 8))
            {
                return true;
            }
            result.pop_back();
        }
        return false;
    }
    else if (step == 8)
    {
        std::vector<std::vector<int>> filtered = v5;
        std::map<int, int> f;
        f[0] = result[0][2];
        f[4] = result[3][2];
        filtered = filter_2(filtered, result, f);
        for (auto v : filter(filtered, f))
        {
            if (in_list(v, result))
            {
                continue;
            }
            // o(&v);
            result.push_back(v);
            if (check(result))
            {
                print_result(result);
                //return true;
            }
            result.pop_back();
        }
        return false;
    }
    else
    {
        return false;
    }

    return false;
}

int sum(std::vector<int> *v)
{
    int result = 0;
    for (auto it = v->begin(); it != v->end(); ++it)
    {
        result += *it;
    }
    return result;
}

int main()
{
    std::vector<int> v(3, 0);

    while (v.size() < 6)
    {
        incc(&v);

        if (v.size() == 3 && sum(&v) == 35)
        {
            v3.push_back(v);
        }
        else if (v.size() == 4 && sum(&v) == 34)
        {
            v4.push_back(v);
        }
        else if (v.size() == 5 && sum(&v) == 33)
        {
            v5.push_back(v);
        }
    }
    std::vector<std::vector<int>> result;
    search(result, 0);
    return 0;
}
