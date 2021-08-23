// uncomment later
//#include "database.h" 
//#include "date.h"
//#include "condition_parser.h"
//#include "node.h"

//remove later
#include "date.cpp"
#include "database.cpp"
#include "node.cpp"
#include "condition_parser.cpp"
#include "token.cpp"
#include "condition_parser_test.cpp"
#include "database_test.cpp"

#include "test_runner.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <deque>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

string ParseEvent(istream& is) {
  string s;
  getline(is, s);

  deque<char> e;
  string ss;
  for (size_t i = 0; i < s.length(); i++) { e.push_back(s[i]); } 
  while(e.front() == ' ') { e.pop_front(); }
  while(!e.empty()) { ss += e.front(); e.pop_front(); }

  return ss;
}


void TestAll();

int main() {
  TestAll();

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } /*else if (command == "Del") {
      auto condition = ParseCondition(is); //condition is of shared_ptr type
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    }*/ else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
  tr.RunTest(TestFind, "TestFind");
  tr.RunTest(TestFind, "TestLast");
}
