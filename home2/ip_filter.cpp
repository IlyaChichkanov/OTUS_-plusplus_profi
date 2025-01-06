#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
using StringPool = std::vector<std::string>;
using IPAdress = std::array<int, 4>;

StringPool split(const std::string &str, char d)
{
    StringPool r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start)); //std::stoi

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));
    return r;
}

IPAdress make_addess(const StringPool str)
{
    IPAdress res;
    for (int i=0; i < 4; ++i)
    {
        res[i] = std::stoi(str.at(i));
    }
    return res;
}


template<typename T>
void print(T& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << "\n";
}

std::ostream &operator<<(std::ostream &os, const IPAdress& ip) 
{ 
    for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
    {
        if (ip_part != ip.cbegin())
        {
            os << ".";
        }
        os << *ip_part;
    }
    return os;
}

class IP_filter
{
public:

    IP_filter(std::vector<IPAdress>&& ip_pool)
    {
        ip_pool_ = std::move(ip_pool);
    }

    std::vector<IPAdress> get_sorted_data()
    {
        return base_filter([](IPAdress x){return false;} );
    }

    std::vector<IPAdress> filter_by_fist_byte(int mask)
    {
        return base_filter([mask](IPAdress x){return x[0] != mask;} );
    }

    std::vector<IPAdress> filter_by_first_two_bytes(int mask1, int mask2)
    {
        return base_filter([mask1, mask2](IPAdress x){return  !((x[0] == mask1) && (x[1] == mask2));});
    }

    std::vector<IPAdress> filter_any(int mask)
    {
        return base_filter([mask](IPAdress x){return !((x[0] == mask) || (x[1] == mask) || (x[2] == mask) || (x[3] == mask));} );
    }

private:
    template<typename T>
    std::vector<IPAdress> base_filter(T sorter)
    {
        auto ip_pool_selected = ip_pool_;
        auto it = std::remove_if(ip_pool_selected.begin(), ip_pool_selected.end(), sorter );
        ip_pool_selected.erase(it, ip_pool_selected.end());
        std::sort(ip_pool_selected.begin(), ip_pool_selected.end(), my_less_);
        return ip_pool_selected;
    }

    struct
    {
        bool operator()(IPAdress a, IPAdress b) const { 
            return 
            std::make_tuple( a[0], a[1], a[2], a[3] ) > 
            std::make_tuple( b[0], b[1], b[2], b[3]);
        }
    } my_less_;
    std::vector<IPAdress> ip_pool_;
};




int main(int argc, char const *argv[])
{
    try
    {
        std::vector<IPAdress> ip_pool;
        std::string line;
        while (std::getline(std::cin, line))
        {
            auto v = split(split(line, '\t').at(0),'.');
            auto ip_adress = make_addess(v);
            ip_pool.push_back(ip_adress);
        }

        auto filter = IP_filter(std::move(ip_pool));
        // TODO reverse lexicographically sort


        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8


        {
            auto res = filter.get_sorted_data();
            print(res);
        }
        
       
        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        {
            auto res = filter.filter_by_fist_byte(1);
            print(res);
        }
        

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        {
            auto res = filter.filter_by_first_two_bytes(46, 70);
            print(res);
        }
        
        // ip_pool2 = ip_pool;
        // auto it2 = std::remove_if(ip_pool2.begin(), ip_pool2.end(), [](IPAdress x){return  !((x[0] == 46) && (x[1] == 70));} );
        // ip_pool2.erase(it2, ip_pool2.end());
        // std::sort(ip_pool2.begin(), ip_pool2.end(), my_less);
        // print(ip_pool2);




        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46

        {
            auto res = filter.filter_any(46);
            print(res);
        }
        
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}