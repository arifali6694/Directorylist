#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <vector>
#include <string>

class Query{
    public:
};

using Multimap = std::multimap<int, std::string, std::greater<int>> ;

Multimap search(const std::string& dir,
                     const std::vector<std::string>& matchDir,
                     const std::vector<std::string>& excludeDir,
                     const std::vector<std::string>& matchExt){

    size_t counta(0);
    Multimap sortedmap;
    // multimap will store file sizes as keys and file paths as values.
    // the map will automatically order based on the key (file size).
    // multimap can handle multiple equal keys with different values,
    // in case two files are exaclty the same size.
    // elements are descending in size by using the 'std::greater' comparison functor

    for (const auto& entry : std::filesystem::recursive_directory_iterator(dir)){
        const auto pathStr = entry.path().string();
        //check if path is a file in 'TESTS' && not in {'SRC','DATA} && file.ext == .XYZ
        if(entry.is_regular_file()
            && pathStr.find(matchDir[0]) != std::string::npos
            && pathStr.find(excludeDir[0]) == std::string::npos
            && pathStr.find(excludeDir[1]) == std::string::npos
            && pathStr.find(matchExt[0]) != std::string::npos){ // alternative: entry.path().extension() == ".EXT"
                //counta++;
                sortedmap.insert({entry.file_size(), pathStr});
                //std::cout << counta << " path: " << pathStr << " , " << entry.file_size() << '\n';
        }
    }
    for (const auto& entry : sortedmap){ //print results list by size in console.
        //std::cout << entry.first << " , " << entry.second << '\n';
    }
    return std::move(sortedmap);
}

void parse(const Multimap& sortedmap){
    size_t sumcountlines(0), sumcountblanks(0), sumcountdashed(0);
    for (const auto& entry : sortedmap){
        size_t countlines(0), countblanks(0), countdashed(0);
        std::cout << "path: " << entry.second << ", size: " << entry.first << '\n';
        std::ifstream input(entry.second); // open file
        std::string line;
        while (std::getline(input, line)){ // copy line from filestream and insert into string.
            ++countlines;
            if (line.empty() || line == "" || line.size() == 0){
                ++countblanks;
                //std::cout << line << '\n';
            }
            if (line.find("--") == 0){
                ++countdashed;
                //std::cout << line << '\n';
            }
        }
        std::cout<< "line count: "<< countlines << ", blank line count: "<< countblanks << ", lines srating with '--' : "<< countdashed <<'\n';
        sumcountlines += countlines;
        sumcountblanks += countblanks;
        sumcountdashed += countdashed;
    }
        std::cout<< "total line count: "<< sumcountlines << ", total blank line count: "<< sumcountblanks << ", total lines starting with '--' : "<< sumcountdashed <<'\n';
}

int main(){
    std::string dir_path = "testdata/";
    std::vector<std::string> matchDir = {"TESTS"};
    std::vector<std::string> excludeDir = {"SRC", "DATA"};
    std::vector<std::string> matchExt = {"XYZ"};

    Multimap results;
    results = search(dir_path, matchDir, excludeDir, matchExt);
    parse(results);
    return 0;
}
