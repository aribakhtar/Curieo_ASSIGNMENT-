#include <bits/stdc++.h>
using namespace std;
struct LogEntry
{
    int64_t timestamp;
    string log_type;
    float severity;
};

class LogMonitor
{
public:
    void op1(const LogEntry &entry)
    {
        logs.push_back(entry);
        log_type_map[entry.log_type].push_back(entry);
    }

    void op2(const string &log_type) const
    {
        if (log_type_map.find(log_type) == log_type_map.end())
        {
            printing(0.0, 0.0, 0.0);
            return;
        }

        comp(log_type_map.at(log_type));
    }

    void op3_before(int64_t timestamp) const
    {
        vector<LogEntry> filtered_logs;
        for (const auto &log : logs)
        {
            if (log.timestamp < timestamp)
            {
                filtered_logs.push_back(log);
            }
        }

        comp(filtered_logs);
    }

    void op3_after(int64_t timestamp) const
    {
        vector<LogEntry> filtered_logs;
        for (const auto &log : logs)
        {
            if (log.timestamp > timestamp)
            {
                filtered_logs.push_back(log);
            }
        }

        comp(filtered_logs);
    }

    void op4_before(const string &log_type, int64_t timestamp) const
    {
        if (log_type_map.find(log_type) == log_type_map.end())
        {
            printing(0.0, 0.0, 0.0);
            return;
        }

        vector<LogEntry> filtered_logs;
        for (const auto &log : log_type_map.at(log_type))
        {
            if (log.timestamp < timestamp)
            {
                filtered_logs.push_back(log);
            }
        }

        comp(filtered_logs);
    }

    void op4_after(const string &log_type, int64_t timestamp) const
    {
        if (log_type_map.find(log_type) == log_type_map.end())
        {
            printing(0.0, 0.0, 0.0);
            return;
        }

        vector<LogEntry> filtered_logs;
        for (const auto &log : log_type_map.at(log_type))
        {
            if (log.timestamp > timestamp)
            {
                filtered_logs.push_back(log);
            }
        }

        comp(filtered_logs);
    }

private:
    vector<LogEntry> logs;
    unordered_map<string, vector<LogEntry>> log_type_map;

    void comp(const vector<LogEntry> &log_entries) const
    {
        if (log_entries.empty())
        {
            printing(0.0, 0.0, 0.0);
            return;
        }

        float min_severity = numeric_limits<float>::max();
        float max_severity = numeric_limits<float>::lowest();
        float sum_severity = 0.0;

        for (const auto &entry : log_entries)
        {
            min_severity = min(min_severity, entry.severity);
            max_severity = max(max_severity, entry.severity);
            sum_severity += entry.severity;
        }

        float mean_severity = sum_severity / log_entries.size();
        printing(min_severity, max_severity, mean_severity);
    }

    void printing(float min_severity, float max_severity, float mean_severity) const
    {
        cout << fixed << setprecision(6);
        cout << "Min: " << min_severity << ", Max: " << max_severity << ", Mean: " << mean_severity << '\n';
    }
};

LogEntry parseLogEntry(string &log)
{
    istringstream ss(log);
    string timestamp_str, log_type, severity_str;

    getline(ss, timestamp_str, ';');
    getline(ss, log_type, ';');
    getline(ss, severity_str, ';');

    int64_t timestamp = stoll(timestamp_str);
    float severity = stof(severity_str);

    return {timestamp, log_type, severity};
}

int main()
{
    LogMonitor monitor;
    string input;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    while (getline(cin, input))
    {
        istringstream ss(input);
        int command;
        ss >> command;
        ss.ignore();

        if (command == 1)
        {
            string log_entry;
            getline(ss, log_entry);
            monitor.op1(parseLogEntry(log_entry));
            cout << "No output" << "\n";
        }
        else if (command == 2)
        {
            string log_type;
            getline(ss, log_type);
            monitor.op2(log_type);
        }
        else if (command == 3)
        {
            string direction;
            int64_t timestamp;
            ss >> direction >> timestamp;
            if (direction == "BEFORE")
            {
                monitor.op3_before(timestamp);
            }
            else if (direction == "AFTER")
            {
                monitor.op3_after(timestamp);
            }
        }
        else if (command == 4)
        {
            string direction, log_type;
            int64_t timestamp;
            ss >> direction >> log_type >> timestamp;
            if (direction == "BEFORE")
            {
                monitor.op4_before(log_type, timestamp);
            }
            else if (direction == "AFTER")
            {
                monitor.op4_after(log_type, timestamp);
            }
        }
    }

    return 0;
}