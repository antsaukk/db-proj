# **Database project**
Simple Database project implemented in C++. This project was meant to be the final assignment for yellow belt in C++ [Coursera](https://www.coursera.org/) specialization. The description of the project can be find under the link [Project](https://www.coursera.org/learn/c-plus-plus-yellow/programming/n1Nbg/kursovoi-proiekt)
 
 ## Among others, the program is capable to do the following simple commands:
 - Add entries inside the database
 - Perform search for the entries based on boolean criteria
 - Remove entries based on boolean criteria
 - Display the content of the database

### Some basic commands
Input:
```
Add 2017-06-01 1st of June
Add 2017-07-08 8th of July
Add 2017-07-08 Someone's birthday
Del date == 2017-07-08
```
Output:
```
Removed 2 entries
```
Input:
```
Add 2017-01-01 Holiday
Add 2017-03-08 Holiday
Add 2017-1-1 New Year
Add 2017-1-1 New Year
Print
```
Output:
```
2017-01-01 Holiday
2017-01-01 New Year
2017-03-08 Holiday
```
Input:
```
Add 2017-01-01 Holiday
Add 2017-03-08 Holiday
Add 2017-01-01 New Year
Find event != "working day"
Add 2017-05-09 Holiday
```
Output:
```
2017-01-01 Holiday
2017-01-01 New Year
2017-03-08 Holiday
Found 3 entries
```
Input:
```
Add 2017-01-01 New Year
Add 2017-03-08 Holiday
Add 2017-01-01 Holiday
Last 2016-12-31
Last 2017-01-01
Last 2017-06-01
Add 2017-05-09 Holiday
```
Output:
```
No entries
2017-01-01 Holiday
2017-03-08 Holiday
```
Input:
```
Add 2017-11-21 Tuesday
Add 2017-11-20 Monday
Add 2017-11-21 Weekly meeting
Print
Find event != "Weekly meeting"
Last 2017-11-30
Del date > 2017-11-20
Last 2017-11-30
Last 2017-11-01
```
Output:
```
2017-11-20 Monday
2017-11-21 Tuesday
2017-11-21 Weekly meeting
2017-11-20 Monday
2017-11-21 Tuesday
Found 2 entries
2017-11-21 Weekly meeting
Removed 2 entries
2017-11-20 Monday
No entries
```
