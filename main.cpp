#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Convert value from any base to base 10
long long baseToDecimal(string value, int base) {
    long long result = 0;
    for (char ch : value) {
        int digit;
        if (isdigit(ch))
            digit = ch - '0';
        else if (isalpha(ch))
            digit = tolower(ch) - 'a' + 10;
        else
            digit = 0;
        result = result * base + digit;
    }
    return result;
}

// Lagrange interpolation to compute f(0)
long long lagrangeInterpolation(vector<pair<int, long long>> points, int k) {
    long long result = 0;
    for (int i = 0; i < k; ++i) {
        long long xi = points[i].first;
        long long yi = points[i].second;

        long long term = yi;

        for (int j = 0; j < k; ++j) {
            if (i != j) {
                long long xj = points[j].first;
                term *= -xj;
                term /= (xi - xj); // Integer division works if data is valid
            }
        }
        result += term;
    }
    return result;
}

void processTestCase(map<string, map<string, string>> input) {
    int n = stoi(input["keys"]["n"]);
    int k = stoi(input["keys"]["k"]);

    vector<pair<int, long long>> points;

    for (auto &entry : input) {
        if (entry.first == "keys") continue;
        int x = stoi(entry.first);
        int base = stoi(entry.second.at("base"));
        string val = entry.second.at("value");
        long long y = baseToDecimal(val, base);
        points.push_back({x, y});
    }

    // Sort and pick first k points
    sort(points.begin(), points.end());
    vector<pair<int, long long>> usedPoints(points.begin(), points.begin() + k);

    long long secret = lagrangeInterpolation(usedPoints, k);
    cout << secret << endl;
}

int main() {
    // === Test Case 1 ===
    map<string, map<string, string>> test1 = {
        {"keys", {{"n", "4"}, {"k", "3"}}},
        {"1", {{"base", "10"}, {"value", "4"}}},
        {"2", {{"base", "2"}, {"value", "111"}}},
        {"3", {{"base", "10"}, {"value", "12"}}},
        {"6", {{"base", "4"}, {"value", "213"}}}
    };

    // === Test Case 2 ===
    map<string, map<string, string>> test2 = {
        {"keys", {{"n", "10"}, {"k", "7"}}},
        {"1", {{"base", "6"}, {"value", "13444211440455345511"}}},
        {"2", {{"base", "15"}, {"value", "aed7015a346d63"}}},
        {"3", {{"base", "15"}, {"value", "6aeeb69631c227c"}}},
        {"4", {{"base", "16"}, {"value", "e1b5e05623d881f"}}},
        {"5", {{"base", "8"}, {"value", "316034514573652620673"}}},
        {"6", {{"base", "3"}, {"value", "2122212201122002221120200210011020220200"}}},
        {"7", {{"base", "3"}, {"value", "20120221122211000100210021102001201112121"}}},
        {"8", {{"base", "6"}, {"value", "20220554335330240002224253"}}},
        {"9", {{"base", "12"}, {"value", "45153788322a1255483"}}},
        {"10", {{"base", "7"}, {"value", "1101613130313526312514143"}}}
    };

    // Output both
    processTestCase(test1);
    processTestCase(test2);

    return 0;
}
