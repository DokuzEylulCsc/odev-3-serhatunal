#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

void readFile(const string &, int &, vector<char>&, vector<string> &);

int main() {
    int n = 0;
    vector<char> a;
    vector<string> b;
    map<string, vector<string>> m;
    readFile("input.txt", n, a, b);
    for (int i = 0; i < b.size(); i+=n+1) {
        if (b[i].size() > 1) {
            for (int j = i+1; j != i+11; j++) {
                m[b[i]].push_back(b[j]);
            }
        }
    }

    for (const auto& f : m) {
        cout << f.first << ": ";
        for (const auto& s : f.second) {
            cout << s << " ";
        }

        cout << endl;
    }

    return 0;
}

void readFile(const string &fileName, int &numberOfQuestion, vector<char> &answerKey, vector<string> &students) {
    ifstream file(fileName);
    string line;
    if (file.is_open()) {
        int i = 1;
        while (getline(file, line)) {
            if (i == 1) {
                numberOfQuestion = stoi(line);
            } else if(i == 2) {
                line.erase(remove(line.begin(), line.end(), ','), line.end());
                for (int j = 0; j < numberOfQuestion; j++) {
                    char tempAnswer = line[j];
                    answerKey.push_back(tempAnswer);
                }
            } else {
                vector<string> temp;
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