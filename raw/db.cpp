//====================================================================================================
// database.h
//====================================================================================================
#pragma once
 
#include "date.h"
#include "node.h"
 
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <set>
 
using namespace std;
 
class Database {
public:
    void Add(const Date& date, const string& event);
    ostream& Print(ostream& os) const;
 
    template<typename lambda>
    int RemoveIf(lambda predicate){
        int count = 0;
 
        vector<Date> dates_to_del;
        for (auto& [date, events] : data) {
            vector<string> events_to_del;
            for (const string& event : events.second) {
                if (predicate(date, event)) {
                    events_to_del.push_back(event);
                    ++count;
                }
            }
 
            for (const string& event : events_to_del) {
                events.second.erase(event);
            }
 
            if (events.second.empty()){
                dates_to_del.push_back(date);
            }
        }
 
        for (const Date& date : dates_to_del) {
            data.erase(date);
        }
        return count;
    }
 
    template<typename lambda>
    vector<string> FindIf(lambda predicate) const{
        ostringstream os;
        vector<string> result;
        for (auto& [date, events] : data) {
            for (const string& event : events.second) {
                if (events.second.count(event) && predicate(date, event)) {
                    os << date << " " << event;
                    result.push_back(os.str());
                    os.str("");
                    os.clear();
                }
            }
        }
        return result;
    }
    string Last(const Date& date) const;
 
    map<Date, pair<vector<string>, set<string>>> GetData();
 
private:
    map<Date, pair<vector<string>, set<string>>> data;
};
 
 
//====================================================================================================
// database.cpp
//====================================================================================================
 
#include "database.h"
 
using namespace std;
 
void Database::Add(const Date& date, const string &event) {
    if (!data.count(date) || !data[date].second.count(event)) {
        data[date].first.push_back(event);
        data[date].second.insert(event);
    }
}
 
ostream& Database::Print(ostream &os) const {
    for (const auto& [date, events] : data) {
        for (const auto& event : events.first) {
            if (events.second.count(event)) {
                os << date << " " << event << endl;
            }
        }
    }
    return os;
}
 
string Database::Last(const Date& date) const {
    ostringstream os;
    auto it = data.upper_bound(date);
    if (it == data.begin()) {
        os << "No entries";
    } else {
        --it;
        for (auto it_i = rbegin(data.at(it->first).first); it_i != rend(data.at(it->first).first); ++it_i) {
            if (data.at(it->first).second.count(*it_i)) {
                os << it->first << " " << *it_i;
                break;
            }
        }
    }
    return os.str();
}
 
map<Date, pair<vector<string>, set<string>>> Database::GetData() {
    return data;
}