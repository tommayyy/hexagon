#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <thread>

using std::cout;
using std::endl;

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

bool is_unique(std::vector<int> *X)
{
    std::set<int> Y(X->begin(), X->end());
    return X->size() == Y.size();
}

void incc(std::vector<int> *vec, int nn = 0, int b = 19)
{
    do
    {
        inc(vec, nn, b);
    } while (!is_unique(vec));
}

bool in_list(std::vector<int> search, std::vector<std::vector<int>> list)
{
    return false;
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

std::vector<std::vector<int>> filter(std::vector<std::vector<int>> *unfiltered_list, std::vector<std::vector<int>> b, std::map<int, int> search_map)
{

    // calculate set with already used numbers (exclude search_map)
    std::set<int> ignore_set;
    for (auto _b : b)
    {
        for (auto i : _b)
        {
            bool ignore = false;
            for (auto it = search_map.begin(); it != search_map.end(); ++it)
            {
                if (it->second == i)
                {
                    ignore = true;
                    break;
                }
            }
            if (!ignore && (ignore_set.find(i) == ignore_set.end()))
                ignore_set.insert(i);
        }
    }

    std::vector<std::vector<int>> result;

    // filter by ignore_set
    for (auto it = unfiltered_list->begin(); it != unfiltered_list->end(); ++it)
    {
        bool found = false;
        for (auto i : (*it))
        {
            if (ignore_set.find(i) != ignore_set.end())
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            continue;
        }

        found = true;
        for (auto m : search_map)
        {
            if ((*it)[m.first] != m.second)
            {
                found = false;
                break;
            }
        }
        if (!found)
        {
            continue;
        }

        for (auto v : b)
        {
            found = false;
            if (v.size() != (*it).size())
            {
                continue;
            }
            found = true;
            for (int i = 0; i < v.size(); i++)
            {
                if (v[i] != (*it)[i])
                {
                    found = false;
                    break;
                }
            }
            if (found)
                break;
        }
        if (found)
        {
            continue;
        }

        result.push_back(*it);
    }
    return result;
}

bool check(std::vector<std::vector<int>> result)
{
    if (result[5][1] + result[7][1] + result[8][1] + result[6][0] != 34)
    {
        return false;
    }
    if (result[5][0] + result[7][2] + result[8][2] + result[6][1] + result[2][0] != 33)
    {
        return false;
    }
    if (result[7][3] + result[8][3] + result[6][2] + result[2][1] != 34)
    {
        return false;
    }

    if (result[0][1] + result[8][1] + result[6][1] + result[2][1] != 34)
    {
        return false;
    }
    if (result[0][0] + result[7][1] + result[8][2] + result[6][2] + result[2][2] != 33)
    {
        return false;
    }
    if (result[5][1] + result[7][2] + result[8][3] + result[6][3] != 34)
    {
        return false;
    }

    return true;
}

void print_result(std::vector<std::vector<int>> result)
{
    printf("    %2d  %2d  %2d\n", result[0][0] + 1, result[0][1] + 1, result[0][2] + 1);
    printf("  %2d  %2d  %2d  %2d\n", result[5][1] + 1, result[7][1] + 1, result[8][1] + 1, result[6][0] + 1);
    printf("%2d  %2d  %2d  %2d  %2d\n", result[5][0] + 1, result[7][2] + 1, result[8][2] + 1, result[6][1] + 1, result[1][2] + 1);
    printf("  %2d  %2d  %2d  %2d\n", result[4][1] + 1, result[8][3] + 1, result[6][2] + 1, result[2][1] + 1);
    printf("    %2d  %2d  %2d\n\n", result[3][2] + 1, result[3][1] + 1, result[3][0] + 1);
    fflush(stdout);
}

bool search(std::vector<std::vector<int>> result, int step, std::vector<std::vector<int>> *search_space)
{
    if (step == 0)
    {
        for (auto v : (*search_space))
        {
            result.push_back(v);
            if (search(result, 1, search_space))
            {
                return true;
            }
            result.pop_back();
        }
        return false;
    }
    else if (step <= 5)
    {
        std::map<int, int> f;
        f[0] = result[step - 1][2];
        if (step == 5)
        {
            f[2] = result[0][0];
        }
        for (auto v : filter(&v3, result, f))
        {
            if (in_list(v, result))
                continue;
            result.push_back(v);
            if (search(result, step + 1, search_space))
            {
                return true;
            }
            result.pop_back();
        }
        return false;
    }
    else if (step == 6)
    {
        std::map<int, int> f;
        f[0] = result[1][1];
        f[3] = result[3][1];

        for (auto v : filter(&v4, result, f))
        {
            if (in_list(v, result))
                continue;
            result.push_back(v);
            if (search(result, 7, search_space))
            {
                return true;
            }
            result.pop_back();
        }
        return false;
    }
    else if (step == 7)
    {
        std::map<int, int> f;
        f[0] = result[0][1];
        f[3] = result[4][1];
        for (auto v : filter(&v4, result, f))
        {
            if (in_list(v, result))
            {
                continue;
            }

            result.push_back(v);
            if (search(result, 8, search_space))
            {
                return true;
            }
            result.pop_back();
        }
        return false;
    }
    else if (step == 8)
    {
        std::map<int, int> f;
        f[0] = result[0][2];
        f[4] = result[3][2];
        for (auto v : filter(&v5, result, f))
        {
            if (in_list(v, result))
            {
                continue;
            }

            result.push_back(v);
            if (check(result))
            {
                print_result(result);
            }
            result.pop_back();
        }
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
    std::map<int, std::vector<std::vector<int>>> v3_map;

    while (v.size() < 6)
    {
        incc(&v);

        if (v.size() == 3 && sum(&v) == 35)
        {
            v3.push_back(v);

            auto key = v[0];
            std::vector<std::vector<int>> *v_3;
            if (v3_map.find(key) == v3_map.end())
            {
                // insert new
                v_3 = new std::vector<std::vector<int>>;
            }
            else
            {
                v_3 = &(v3_map[key]);
                // found
            }
            v_3->push_back(v);
            auto set =
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
    std::thread t1(search, result, 0, &v3);
    t1.join();
    return 0;
}
