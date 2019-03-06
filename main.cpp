#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <thread>
#include <algorithm>

using std::cout;
using std::endl;

class vb19
{
  public:
    vb19() : val(3, 0) {}
    vb19(std::vector<int> v) : val(v) {}
    std::vector<int> val;
    int base = 19;

    void inc(unsigned int nn = 0)
    {
        if (this->val.size() == nn)
        {
            this->val.push_back(1);
            return;
        }
        this->val[nn]++;
        if (this->val[nn] == this->base)
        {
            this->val[nn] = 0;
            inc(nn + 1);
        }
    }

    bool is_unique()
    {
        std::vector<int> *X = &this->val;
        std::set<int> Y(X->begin(), X->end());
        return X->size() == Y.size();
    }

    void incc(unsigned int nn = 0)
    {
        do
        {
            this->inc(nn);
        } while (!this->is_unique());
    }

    int sum()
    {
        int result = 0;
        for (auto it = this->val.begin(); it != this->val.end(); ++it)
        {
            result += *it;
        }
        return result;
    }

    int size()
    {
        return this->val.size();
    }

    int get_digit(int index)
    {
        return this->val[index] + 1;
    }
};

std::vector<vb19> v3;
std::vector<vb19> v4;
std::vector<vb19> v5;

class hexagon
{
  public:
    std::map<int, vb19 *> rows;

    void set_row(int index, vb19 *value)
    {
        std::map<int, vb19 *>::iterator it = this->rows.find(index);

        if (it != this->rows.end())
        {
            it->second = value;
        }
        else
        {
            this->rows.insert(std::make_pair(index, value));
        }
    }

    vb19 *get_row(int index)
    {
        std::map<int, vb19 *>::iterator it = this->rows.find(index);
        if (it != this->rows.end())
        {
            return it->second;
        }
        return nullptr;
    }

    void erase_row(int index)
    {
        std::map<int, vb19 *>::iterator it = this->rows.find(index);
        if (it != this->rows.end())
        {
            this->rows.erase(it);
        }
    }

    void print()
    {
        printf("    %2d  %2d  %2d\n", this->get_row(0)->get_digit(0), this->get_row(0)->get_digit(1), this->get_row(0)->get_digit(2));
        printf("  %2d  %2d  %2d  %2d\n", this->get_row(5)->get_digit(1), this->get_row(7)->get_digit(1), this->get_row(8)->get_digit(1), this->get_row(6)->get_digit(0));
        printf("%2d  %2d  %2d  %2d  %2d\n", this->get_row(5)->get_digit(0), this->get_row(7)->get_digit(2), this->get_row(8)->get_digit(2), this->get_row(6)->get_digit(1), this->get_row(1)->get_digit(2));
        printf("  %2d  %2d  %2d  %2d\n", this->get_row(4)->get_digit(1), this->get_row(8)->get_digit(3), this->get_row(6)->get_digit(2), this->get_row(2)->get_digit(1));
        printf("    %2d  %2d  %2d\n\n", this->get_row(3)->get_digit(2), this->get_row(3)->get_digit(1), this->get_row(3)->get_digit(0));
        fflush(stdout);
    }

    bool check()
    {
        if (this->get_row(5)->get_digit(1) + this->get_row(7)->get_digit(1) + this->get_row(8)->get_digit(1) + this->get_row(6)->get_digit(0) != 38)
        {
            return false;
        }
        if (this->get_row(5)->get_digit(0) + this->get_row(7)->get_digit(2) + this->get_row(8)->get_digit(2) + this->get_row(6)->get_digit(1) + this->get_row(2)->get_digit(0) != 38)
        {
            return false;
        }
        if (this->get_row(7)->get_digit(3) + this->get_row(8)->get_digit(3) + this->get_row(6)->get_digit(2) + this->get_row(2)->get_digit(1) != 38)
        {
            return false;
        }

        if (this->get_row(0)->get_digit(1) + this->get_row(8)->get_digit(1) + this->get_row(6)->get_digit(1) + this->get_row(2)->get_digit(1) != 38)
        {
            return false;
        }
        if (this->get_row(0)->get_digit(0) + this->get_row(7)->get_digit(1) + this->get_row(8)->get_digit(2) + this->get_row(6)->get_digit(2) + this->get_row(2)->get_digit(2) != 38)
        {
            return false;
        }
        if (this->get_row(5)->get_digit(1) + this->get_row(7)->get_digit(2) + this->get_row(8)->get_digit(3) + this->get_row(6)->get_digit(3) != 38)
        {
            return false;
        }

        return true;
    }

    std::vector<vb19 *> get_filtered_list(int step)
    {
        if (step == 0)
        {
            // to do exception
        }
        if (step <= 5)
        {
            std::map<int, int> f;
            f[0] = this->get_row(step - 1)->get_digit(2) - 1;
            if (step == 5)
            {
                f[2] = this->get_row(0)->get_digit(0) - 1;
            }
            return filter(&v3, f);
        }
        if (step == 6)
        {
            std::map<int, int> f;
            f[0] = this->get_row(1)->get_digit(1) - 1;
            f[3] = this->get_row(3)->get_digit(1) - 1;
            return filter(&v4, f);
        }
        if (step == 7)
        {
            std::map<int, int> f;
            f[0] = this->get_row(0)->get_digit(1) - 1;
            f[3] = this->get_row(4)->get_digit(1) - 1;
            return filter(&v4, f);
        }
        if (step == 8)
        {
            std::map<int, int> f;
            f[0] = this->get_row(0)->get_digit(2) - 1;
            f[4] = this->get_row(3)->get_digit(2) - 1;
            return filter(&v5, f);
        }
    }

    std::vector<int> get_used_digits()
    {
        std::vector<int> result;
        for (auto row : this->rows)
        {
            for (auto digit : row.second->val)
            {
                if (std::find(result.begin(), result.end(), digit) != result.end())
                    continue;
                result.push_back(digit);
            }
        }
        return result;
    }

    std::vector<vb19 *> filter(std::vector<vb19> *unfiltered_list, std::map<int, int> search_map)
    {
        // calculate set with already used numbers (exclude search_map)
        std::set<int> ignore_set;
        for (auto i : this->get_used_digits())
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
            {
                ignore_set.insert(i);
            }
        }

        std::vector<vb19 *> result;

        // filter by ignore_set
        for (auto it = unfiltered_list->begin(); it != unfiltered_list->end(); ++it)
        {
            bool found = false;
            for (auto i : (*it).val)
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
                if ((*it).val[m.first] != m.second)
                {
                    found = false;
                    break;
                }
            }
            if (!found)
            {
                continue;
            }

            for (auto itt : this->rows)
            {
                auto v = itt.second;
                found = false;
                if (v->size() != (*it).size())
                {
                    continue;
                }
                found = true;
                for (int i = 0; i < v->size(); i++)
                {
                    if (v->val[i] != (*it).val[i])
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

            result.push_back(&(*it));
        }
        return result;
    }
};

bool search(std::vector<vb19 *>, hexagon *, int, std::vector<vb19 *>);

bool inner_search(std::vector<vb19 *> result, hexagon *hex, int step, std::vector<vb19 *> search_space, std::vector<vb19 *> values, std::function<bool(std::vector<vb19 *>, hexagon *, int, std::vector<vb19 *>)> func)
{
    for (auto v : values)
    {
        result.push_back(v);
        hex->set_row(step, v);
        if (func(result, hex, step + 1, search_space))
        {
            return true;
        }
        result.pop_back();
        hex->erase_row(step);
    }
    return false;
}

bool search2(std::vector<vb19 *> result, hexagon *hex, int step, std::vector<vb19 *> search_space)
{
    if (hex->check())
    {
        hex->print();
    }
    return false;
}

bool search(std::vector<vb19 *> result, hexagon *hex, int step, std::vector<vb19 *> search_space)
{
    if (step == 0)
    {
        return inner_search(result, hex, step, search_space, search_space, search);
    }
    else if (step <= 5)
    {
        std::map<int, int> f;
        f[0] = result[step - 1]->val[2];
        if (step == 5)
        {
            f[2] = result[0]->val[0];
        }

        return inner_search(result, hex, step, search_space, hex->get_filtered_list(step), search);
    }
    else if (step == 6)
    {
        std::map<int, int> f;
        f[0] = result[1]->val[1];
        f[3] = result[3]->val[1];

        return inner_search(result, hex, step, search_space, hex->get_filtered_list(step), search);
    }
    else if (step == 7)
    {
        std::map<int, int> f;
        f[0] = result[0]->val[1];
        f[3] = result[4]->val[1];

        return inner_search(result, hex, step, search_space, hex->get_filtered_list(step), search);
    }
    else if (step == 8)
    {
        std::map<int, int> f;
        f[0] = result[0]->val[2];
        f[4] = result[3]->val[2];
        return inner_search(result, hex, step, search_space, hex->get_filtered_list(step), search2);
    }

    return false;
}

int main()
{
    vb19 v;
    while (v.size() < 6)
    {
        v.incc();

        if (v.size() == 3 && v.sum() == 35)
        {
            v3.push_back(v);
        }
        else if (v.size() == 4 && v.sum() == 34)
        {
            v4.push_back(v);
        }
        else if (v.size() == 5 && v.sum() == 33)
        {
            v5.push_back(v);
        }
    }

    std::map<int, std::vector<vb19 *> *> v3_map;
    int threads_supported = std::thread::hardware_concurrency();
    if (threads_supported == 0)
    {
        threads_supported = 4;
    }

    for (int i = 0; i < threads_supported; i++)
    {
        auto n = new std::vector<vb19 *>();
        v3_map.insert(make_pair(i, n));
    }

    for (int i = 0; i < v3.size(); i++)
    {
        auto key = i % threads_supported;
        auto v_3 = v3_map[key];
        v_3->push_back(&v3[i]);
    }

    std::vector<std::thread *> threads;
    for (int i = 0; i < v3_map.size(); i++)
    {
        std::vector<vb19 *> result;
        hexagon *hex = new hexagon();
        std::thread *t1 = new std::thread(search, result, hex, 0, *v3_map[i]);
        threads.push_back(t1);
    }

    for (int i = 0; i < v3_map.size(); i++)
    {
        threads[i]->join();
    }

    return 0;
}
