#include "directorylist.h"

int main(){
    const std::string dir_path = "path_to_dirs/";
    const std::vector<std::string> matchDir = {"data"};
    const std::vector<std::string> excludeDir = {"dir1", "dir2"};
    const std::vector<std::string> matchExt = {"PDF"};

    Query query;
    query.search(dir_path, matchDir, excludeDir, matchExt);
    query.parse();
    return 0;
}
