#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

/*
* The file with the data will be a CSV file with 3 columns: turnover(int), characteristics(string), and success(boolean).
*/
class Company {
public:
    Company(int turnover, string characteristics, bool success) :
        turnover(turnover), success(success), distance(-1)
    {
        this->characteristics = transformCharacteristics(characteristics);
    }
    double distance;
    int turnover;
    int characteristics;
    bool success;

private:
    int transformCharacteristics(string& c) {
        unsigned sum = 0;
        for (size_t i = 0; i < c.size(); ++i) {
            if (c[i] != ' ') {
                sum += (int)c[i];
            }
        }
        return sum;
    }
};

class CSVReader {
public:
    CSVReader(const string& fileName, const string& delimiter = ",") :
        fileName(fileName),
        delimiter(delimiter)
    {}

    vector<vector<string>> getData() {
        ifstream file(this->fileName);
        vector<vector<string>> data;
        string line = "";

        while (getline(file, line)) {
            vector<string> tmp;
            tmp = this->split(line, ",");
            data.push_back(tmp);
        }
        file.close();
        return data;
    }

private:
    string fileName;
    string delimiter;
    vector<string> split(string target, string delim) {
        vector<string> v;
        if (!target.empty()) {
            size_t start = 0;
            do {
                size_t x = target.find(delim, start);
                if (x == -1) {
                    break;
                }
                string tmp = target.substr(start, x - start);
                v.push_back(tmp);
                start += delim.size() + tmp.size();
            } while (true);

            v.push_back(target.substr(start));
        }
        return v;
    }
};

bool comparison(Company& lhs, Company& rhs) {
    return lhs.distance < rhs.distance;
}

double euclideanDistance(Company& lhs, Company& test) {
    return sqrt(pow((lhs.turnover - test.turnover), 2) + pow((lhs.characteristics - test.characteristics), 2));
}

double manhattanDistance(Company& lhs, Company& test) {
    return (abs(lhs.turnover - test.turnover) + abs(lhs.characteristics - test.characteristics));
}

void fillDistances(vector<Company>& data, Company& test, double(*distanceFunction)(Company&, Company&)) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i].distance = distanceFunction(data[i], test);
    }
}

bool KNN(vector<Company>& data, Company& test, int k, double(*distanceFunction)(Company&, Company&)) {
    fillDistances(data, test, distanceFunction);

    sort(data.begin(), data.end(), comparison);

    int countSuccessful = 0;
    int countUnsuccessful = 0;
    for (int i = 0; i < k; ++i) {
        if (data[i].success) {
            ++countSuccessful;
        }
        else {
            ++countUnsuccessful;
        }
    }
    if (countSuccessful == countUnsuccessful) {
        test.success = data[0].success;
    }
    else {
        test.success = countSuccessful > countUnsuccessful ? true : false;
    }
    return test.success;
}

int main() {
    const string path = "DATA.csv";
    CSVReader reader(path);
    vector<vector<string>> rawData = reader.getData();
    vector<Company> data;
    for (vector<string> line : rawData) {
        Company comp(stoi(line[0]), line[1], line[2] == "1" ? true : false);
        data.push_back(comp);
    }

    // Test examples
    vector<Company> testPoints = {
        {1256, "Weak", true},       // Actual label: Successful
        {725, "Weak", false},       // Actual label: Unsuccessful
        {1471, "Average", true},    // Actual label: Successful
        {703, "Very Strong", false},// Actual label: Unsuccessful
        {1301, "Strong", true}      // Actual label: Successful
    };

    int k = 3;
    for (auto& testPoint : testPoints) {
        bool predictedSuccess = KNN(data, testPoint, k, euclideanDistance);
        string predictedLabel = predictedSuccess ? "Successful" : "Unsuccessful";
        string actualLabel = testPoint.success ? "Successful" : "Unsuccessful";
        cout << "Test Point: {" << testPoint.turnover << ", " << testPoint.characteristics << "} Predicted label: " << predictedLabel << " Actual label: " << actualLabel << endl;
    }

    return 0;
}