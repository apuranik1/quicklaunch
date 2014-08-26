#include "appfinder.h"

#include "strutils.h"

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

using std::vector;
using std::string;

using util::find_ignore_case;

namespace quicklaunch
{
    /* Functor to check whether an app fails to match a query */
    struct no_query_match
    {
        no_query_match(const string& query) : query(query) {}
        string query;
        bool operator()(const App& app)
        {
            return !app.matches(query);;
        }
    };

    vector<App> get_matching_apps(vector<App>::const_iterator start, vector<App>::const_iterator end, const string& query)
    {
        vector<App> output;
        std::remove_copy_if(start, end, back_inserter(output), 
                [&query](const App& app)
                {
                    return !app.matches(query);
                });
        return output;
    }

    vector<App>& trim_by_query(vector<App>& app_vec, const string& query)
    {
        // well that was straightforward...
        app_vec.erase(std::remove_if(app_vec.begin(), app_vec.end(), no_query_match(query)), app_vec.end());
        return app_vec;
    }

}
