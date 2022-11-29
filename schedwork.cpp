

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "schedwork.h"

using namespace std;

bool computeSchedule(int callCount, long unsigned int rowIt, long unsigned int colIt, const AvailabilityMatrix &avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule &sched, vector<int> &dayCount, int rowSize, int colSize);

bool schedule(const AvailabilityMatrix &avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule &sched)
{
    if (avail.size() == 0U)
    {
        return false;
    }
    sched.clear();
    int colSize = avail[0].size();
    int rowSize = avail.size();
    sched = vector<vector<Worker_T>>(rowSize, vector<Worker_T>(dailyNeed, 0));
    vector<int> dayCount = vector<int>(colSize, 0);
    return computeSchedule(0, 0, 0, avail, dailyNeed, maxShifts, sched, dayCount, rowSize, colSize);
}

bool computeSchedule(int callCount, long unsigned int rowIt, long unsigned int colIt, const AvailabilityMatrix &avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule &sched, vector<int> &dayCount, int rowSize, int colSize)
{
    if (dailyNeed <= colIt)
    {
        return computeSchedule(0, rowIt + 1, 0, avail, dailyNeed, maxShifts, sched, dayCount, rowSize, colSize);
    }
    if (callCount >= rowSize)
    {
        return false;
    }
    else if (rowSize <= rowIt)
    {
        return true;
    }
    if (dayCount[callCount] < maxShifts && avail[rowIt][callCount])
    {
        sched[rowIt][colIt] = callCount;
        dayCount[callCount]++;
        bool isValid = computeSchedule(callCount + 1, rowIt, colIt + 1, avail, dailyNeed, maxShifts, sched, dayCount, rowSize, colSize);
        if (isValid)
        {
            return true;
        }
        sched[rowIt][colIt] = NULL;
        dayCount[callCount]--;
    }
    bool isValid = computeSchedule(callCount + 1, rowIt, colIt, avail, dailyNeed, maxShifts, sched, dayCount, rowSize, colSize);
    if (isValid)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}
