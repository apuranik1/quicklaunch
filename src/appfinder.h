#ifndef APPFINDER_H
#define APPFINDER_H

#include "app.h"
#include "appscan.h"

#include <vector>
#include <iterator>

namespace quicklaunch
{
    std::vector<App> get_matching_apps(std::vector<App>::const_iterator start, std::vector<App>::const_iterator end, const std::string& query);

    std::vector<App>& trim_by_query(std::vector<App>& app_vector, const std::string& query);

    bool matches(const App& app, const std::string& query);
}

#endif
