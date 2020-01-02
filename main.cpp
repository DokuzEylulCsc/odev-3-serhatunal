#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <bits/stdc++.h>

using namespace std;

void readFile(const string &, int &, vector<char> &, vector <string> &);

int checkAnswer(const vector<char> &, const vector <string> &, const int &);

string getString(char);

void editVectorToMap(const vector <string> &, map <string, vector<string>> &, const int &);

void calculateStatistic(vector<int> &, int &, int &, float &, float &, int &);

void swap(int &, int &);

void bubbleSort(vector<int> &);

template<typename K, typename V>
multimap <V, K> editMapToMap(map < K, V >const &tempMap) {
    multimap <V, K> multimap;
    for (auto const &pair : tempMap) {
        multimap.insert(make_pair(pair.second, pair.first));
    }

    return multimap;
}

void writeFile(const string &, const multimap<int, string> &, const int &, const int &, const float &,
               const float &, const int &);

int main() {
    int numQuestion = 0;
    vector<char> key;
    vector <string> studentsVector;
    map <string, vector<string>> studentsMap;
    string fileName = "input.txt";

    readFile(fileName, numQuestion, key, studentsVector);
    editVectorToMap(studentsVector, studentsMap, numQuestion);

    vector<int> points;
    for (auto x : studentsMap) {
        points.push_back(checkAnswer(key, x.second, numQuestion));
        cout << endl;
    }

    map<string, int> temp;
    int i = 0;
    for (const auto &f : studentsMap) {
        for (const auto &s : f.second) {
        }

        temp[f.first] = points[i];
        i++;
    }

    multimap<int, string> newStudent = editMapToMap(temp);

    int lowest = points[0];
    int highest = points[0];
    int range = 0;
    float median = 0;
    float average = 0;

    calculateStatistic(points, lowest, highest, average, median, range);
    writeFile("output.txt", newStudent, lowest, highest, average, median, range);

    return 0;
}

void writeFile(const string &fileName, const multimap<int, string> &students, const int &low, const int &high,
               const float &average, const float &median, const int &range) {
    ofstream output(fileName);
    for (auto it = students.rbegin(); it != students.rend(); it++) {
        output << it->second << ", " << it->first << endl;
    }
    output << high << ", " << low << ", " << average << ", " << median << ", " << range;

    output.close();
}

void calculateStatistic(vector<int> &grades, int &lowestGrade, int &highestGrade, float &average, float &median,
                        int &range) {
    int sum = 0;
    int count = 0;
    for (auto grade : grades) {
        if (lowestGrade > grade) {
            lowestGrade = grade;
        }

        if (highestGrade < grade) {
            highestGrade = grade;
        }

        count++;
        sum += grade;
    }

    average = sum / count;
    bubbleSort(grades);

    if (count % 2 == 0) {
        median = (grades[count / 2 - 1] + grades[count / 2]) / 2;
    } else {
        median = grades[count / 2];
    }

    range = highestGrade - lowestGrade;
}

void swap(int &xp, int &yp) {
    int temp = xp;
    xp = yp;
    yp = temp;
}

void bubbleSort(vector<int> &nums) {
    for (int i = 0; i < nums.size() - 1; i++) {
        for (int j = 0; j < nums.size() - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
            }
        }
    }
}

void editVectorToMap(const vector <string> &source, map <string, vector<string>> &target, const int &num) {
    for (int i = 0; i < source.size(); i += num + 1) {
        if (source[i].size() > 1) {
            for (int j = i + 1; j != i + 11; j++) {
                target[source[i]].push_back(source[j]);
            }
        }
    }
}

string getString(char x) {
    string s(1, x);

    return s;
}

int checkAnswer(const vector<char> &answerKey, const vector <string> &studentAnswer, const int &numberOfQuestion) {
    int point = 0;
    for (int i = 0; i < numberOfQuestion; i++) {
        if (getString(answerKey[i]) == studentAnswer[i]) {
            point += 4;
        } else if (studentAnswer[i].empty()) {
            point += 0;
        } else {
            point -= 1;
        }
    }

    if (point < 0) return 0;
    int result = (100 * point) / (numberOfQuestion * 4);

    return result;
}

void readFile(const string &fileName, int &numberOfQuestion, vector<char> &answerKey, vector <string> &students) {
    ifstream file(fileName);
    string line;
    if (file.is_open()) {
        int i = 1;
        while (getline(file, line)) {
            if (i == 1) {
                numberOfQuestion = stoi(line);
            } else if (i == 2) {
                line.erase(remove(line.begin(), line.end(), ','), line.end());
                for (int j = 0; j < numberOfQuestion; j++) {
                    char tempAnswer = line[j];
                    answerKey.push_back(tempAnswer);
                }
            } else {
                vector <string> temp;
                vector<char> answer;
                stringstream s_stream(line);
                int j = 0;
                while (s_stream.good()) {
                    string subs;
                    getline(s_stream, subs, ',');
                    students.push_back(subs);
                    j = 0;
                }
            }

            i++;
        }
    }
}
