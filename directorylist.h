#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <vector>
#include <string>

using Multimap = std::multimap<int, std::string, std::greater<int>> ;

class Query{
    public:
    void search(const std::string& dir,
                     const std::vector<std::string>&,
                     const std::vector<std::string>&,
                     const std::vector<std::string>& );
    void parse();

    private:
    Multimap m_results;
};