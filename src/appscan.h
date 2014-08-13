#ifndef APPSCAN_H
#define APPSCAN_H

#include "app.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace quicklaunch
{
    std::vector<App> scan_dir(const std::string& dirname);
    std::vector<App> get_all_apps();
}

#endif
