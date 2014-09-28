#include "history.h"

#include "app.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::ifstream;
using std::ios_base;
using std::ofstream;
using std::string;
using std::vector;

namespace quicklaunch
{
    int record_selection(const App& app, const string& history_file)
    {
        ofstream ofile(history_file, ofstream::app);
        if (!ofile)
            return FILE_OPEN_FAILURE;

        ofile << app.app_id() << std::endl;
        ofile.close();
        trim_history(history_file);
        return 0;
    }

    int read_history(const string& history_file, frequency_map& history)
    {
        ifstream ifile(history_file);
        if (!ifile)
            return FILE_OPEN_FAILURE;

        string line;
        while (std::getline(ifile, line))
            // no, the parentheses are not needed
            // yes, they increase readability tenfold
            ++(history[line]);

        ifile.close();
        return 0;
    }

    vector<App>& sort_by_frequency(vector<App>& app_list, const frequency_map& history)
    {
        // what the hell did I do
        std::sort(app_list.begin(), app_list.end(),
                [&history](const App& a, const App& b)
                {
                    bool contains_a = history.count(a.app_id());
                    if (history.count(b.app_id()) && contains_a)
                        return history.at(b.app_id()) < history.at(a.app_id());
                    return contains_a;
                });
        return app_list;
    }

    int trim_history(const string& history_file)
    {
        ifstream infile(history_file);
        if (!infile)
            return FILE_OPEN_FAILURE;

        // read into a circular buffer
        const int BUF_SIZE = 100;
        string lines[BUF_SIZE];
        int index = 0;

        string line;
        while (getline(infile, line))
            lines[index++ % BUF_SIZE] = line;
        infile.close();

        // not worth trimming if the file won't be cut by at least half
        if (index < 2 * BUF_SIZE)
            return 0;

        ofstream ofile(history_file, ios_base::trunc);
        if (!ofile)
            return FILE_OPEN_FAILURE;

        for (int i = 0; i < BUF_SIZE; ++i)
            ofile << lines[(i + index) % BUF_SIZE] << '\n';
        ofile.close();

        return 0;
    }
}
