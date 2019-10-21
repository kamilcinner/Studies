#include <iostream>
#include <vector>

void findValue(tree * T, int whereAmI, vector<int> &_min, vector<int> &_max)
{
    //cout << whereAmI << ", ";
    if (T->l != NULL)
    {
        if (T->l->x > _max[whereAmI]) _max[whereAmI] = T->l->x;
        if (T->l->x < _min[whereAmI]) _min[whereAmI] = T->l->x;
        findValue(T->l, whereAmI, _min, _max);
    }
    if (T->r != NULL)
    {
        whereAmI++;
        if (T->r->x > _max[whereAmI]) _max[whereAmI] = T->r->x;
        if (T->r->x < _min[whereAmI]) _min[whereAmI] = T->r->x;
        findValue(T->r, whereAmI, _min, _max);
        //cout << whereAmI << ", ";
    }
}

int solution(tree * T)
{
    if (T == NULL || (T->l == NULL && T->r == NULL))
        return 0;
    int amp = 0, i = 0;
    
    vector<int> _min, _max;
    _min.resize(500);
    _max.resize(500);
    
    for (unsigned int i = 0;i < 500;i++)
    {
        _max[i] = _min[i] = T->x;
    }
    
    findValue(T, i, _min, _max);
    
    for (unsigned int i = 0;i < _min.size();i++)
    {
        if (_max[i] - _min[i] > amp)
            amp = _max[i] - _min[i];
    }

    return amp;
}