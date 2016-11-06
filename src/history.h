#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <map>
#include <vector>

namespace liftoff
{
    struct App;
    
    typedef std::map<std::string, int> frequency_map;

    const int FILE_OPEN_FAILURE = 1;
    int record_selection(const App& app, const std::string& history_file);
    int read_history(const std::string& history_file, frequency_map& read_in);
    std::vector<App>& sort_by_frequency(std::vector<App>& app_list, const frequency_map& history);
    int trim_history(const std::string& history_file);
}

#endif
