#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

string solution(int A, int B, int C, int D)
{
    vector<int> values;
    for (int i : {A, B, C, D})
    {
        values.push_back(i);
    }
    sort(values.begin(), values.end());
    /*for (unsigned int i = 0;i < values.size();i++)
    {
        cout << values[i];
    }*/
    /*if (values[0] > 2)
        return "NOT POSSIBLE";*/
    vector<int> maxTime;
    // searching for the first time digit
    for (int i = values.size() - 1;i >= 0;i--)
    {
        if (values[i] <= 2)
        {
            maxTime.push_back(values[i]);
            values[i] = -1;
            break;
        }
    }
    // second
    if (maxTime[0] == 2)
    {
        for (int i = values.size() - 1;i >= 0;i--)
        {
            if (values[i] == -1)
                continue;
            if (values[i] <= 3)
            {
                maxTime.push_back(values[i]);
                values[i] = -1;
                break;
            }
        }
    }
    else
    {
        for (int i = values.size() - 1;i >= 0;i--)
        {
            if (values[i] == -1)
                continue;
            maxTime.push_back(values[i]);
            values[i] = -1;
            break;
        }
    }
    // third
    for (int i = values.size() - 1;i >= 0;i--)
    {
        if (values[i] == -1)
            continue;
        if (values[i] <= 5)
        {
            maxTime.push_back(values[i]);
            values[i] = -1;
            break;
        }
    }
    // fourth
    for (int i = values.size() - 1;i >= 0;i--)
    {
        if (values[i] == -1)
            continue;
        maxTime.push_back(values[i]);
        values[i] = -1;
        break;
    }
    
    if (maxTime.size() < 4)
        return "NOT POSSIBLE";
        
    stringstream ss;
    ss << maxTime[0] << maxTime[1] << ":" << maxTime[2] << maxTime[3];
    return ss.str();
}
