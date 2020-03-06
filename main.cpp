#include "directorylist.h"

int main(){
    std::string dir_path = "testdata/";
    std::vector<std::string> matchDir = {"TESTS"};
    std::vector<std::string> excludeDir = {"SRC", "DATA"};
    std::vector<std::string> matchExt = {"XYZ"};

    Query query;
    query.search(dir_path, matchDir, excludeDir, matchExt);
    query.parse();
    return 0;
}
