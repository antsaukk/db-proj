#include "test_runner.h"
#include "database.h"

#include <sstream>
using namespace std;

void TestFind(){
	Database test_db;

	istringstream isd("2017-05-09");
	test_db.Add(ParseDate(isd), "Holiday"); 
	istringstream isd1("2017-06-10");
	test_db.Add(ParseDate(isd1), "Mary's Birthday");
	istringstream isd2("2017-07-10");
	test_db.Add(ParseDate(isd2), "Gary's Birthday");
	istringstream isd3("2017-01-01");
	test_db.Add(ParseDate(isd3), "New Year");

	//Find with not equal condition
	{
		istringstream isc(R"(event != "working day")");
		auto condition = ParseCondition(isc);
      	auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      	};
	
		auto test_res = test_db.FindIf(predicate);
		vector<string> v = {"2017-01-01 New Year", "2017-05-09 Holiday",
										"2017-06-10 Mary's Birthday", "2017-07-10 Gary's Birthday"};
		AssertEqual(test_res, v, "Find with '!=' condition");
	}
		//Find with equality condition
	{
		istringstream isc1(R"(event == "Holiday")");
		auto condition1 = ParseCondition(isc1);
      	auto predicate1 = [condition1](const Date& date, const string& event) {
        return condition1->Evaluate(date, event);
      	};

      	auto test_res1 = test_db.FindIf(predicate1);
		vector<string> v1 = {"2017-05-09 Holiday"};
		AssertEqual(test_res1, v1, "Find with '==' condition");
	}
		//Find with empty condition
	{
		istringstream isc2("");
		auto condition2 = ParseCondition(isc2);
      	auto predicate2 = [condition2](const Date& date, const string& event) {
        return condition2->Evaluate(date, event);
      	};

      	auto test_res2 = test_db.FindIf(predicate2);
		vector<string> v2 = {"2017-01-01 New Year", "2017-05-09 Holiday",
										"2017-06-10 Mary's Birthday", "2017-07-10 Gary's Birthday"};
		AssertEqual(test_res2, v2, "Find with empty condition");
	}
		//Find with OR condition
	{
		istringstream isc3(R"(event == "Holiday" OR event == "Mary's Birthday")");
		auto condition3 = ParseCondition(isc3);
      	auto predicate3 = [condition3](const Date& date, const string& event) {
        return condition3->Evaluate(date, event);
      	};

      	auto test_res3 = test_db.FindIf(predicate3);
		vector<string> v3 = {"2017-05-09 Holiday", "2017-06-10 Mary's Birthday"};
		AssertEqual(test_res3, v3, "Find with OR condition");
	}
		//Find with AND condition
	{
		istringstream isc4(R"(event == "Holiday" AND date == "2017-05-09")");
		auto condition4 = ParseCondition(isc4);
      	auto predicate4 = [condition4](const Date& date, const string& event) {
        return condition4->Evaluate(date, event);
      	};

      	auto test_res4 = test_db.FindIf(predicate4);
		vector<string> v4 = {"2017-05-09 Holiday"};
		AssertEqual(test_res4, v4, "Find with OR condition");
	}
		//Find with OR and > condition
	{
		istringstream isc5(R"(event == "Holiday" OR date > "2017-01-01")");
		auto condition5 = ParseCondition(isc5);
      	auto predicate5 = [condition5](const Date& date, const string& event) {
        return condition5->Evaluate(date, event);
      	};

      	auto test_res5 = test_db.FindIf(predicate5);
		vector<string> v5 = {"2017-05-09 Holiday",
							"2017-06-10 Mary's Birthday", "2017-07-10 Gary's Birthday"};
		AssertEqual(test_res5, v5, "Find with OR condition");
	}
}

void TestLast(){
	Database test_db;

	{
		istringstream isd("2017-05-09");
		Date D = ParseDate(isd);
		test_db.Add(D, "Holiday"); 
		test_db.Add(D, "Mary's Birthday");
		test_db.Add(D, "Gary's Birthday");
		test_db.Add(D, "New Year");
		istringstream tisd("2017-05-10");
		AssertEqual(test_db.Last(ParseDate(tisd)), "New Year", "Last 1");
	}

	{
		istringstream isd("2017-06-08");
		Date D1 = ParseDate(isd);
		test_db.Add(D1, "Football victory"); 
		test_db.Add(D1, "Harry's Birthday");
		test_db.Add(D1, "Meri's Birthday");
		test_db.Add(D1, "Christmas");
		istringstream tisd("2017-07-10");
		AssertEqual(test_db.Last(ParseDate(tisd)), "Christmas", "Last 2");
	}

	{
		istringstream isd("2017-09-10");
		Date D2 = ParseDate(isd);
		test_db.Add(D2, "Floorball victory"); 
		test_db.Add(D2, "Nancy's Birthday");
		test_db.Add(D2, "Eugen's Birthday");
		test_db.Add(D2, "Easter");
		istringstream tisd("2017-12-10");
		AssertEqual(test_db.Last(ParseDate(tisd)), "Easter", "Last 3");
	}

	{
		istringstream isd("2017-01-01");
		AssertEqual(test_db.Last(ParseDate(isd)), "No entries", "Last empty");
	}
}
