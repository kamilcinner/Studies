#include <stdlib.h> // atoi, itoa, strtoul
#include <bits/stdc++.h> // strcpy

void p3(const vector<string>& binarne)
{
    char* bin;
    unsigned long int max_dziesietnie=0,dziesietnie;
    for(unsigned int i=0; i<500; i++)
    {
        if(binarne[i].size()>16)
            continue;

        bin=new char[binarne[i].size()+1];
        strcpy(bin,binarne[i].c_str());
        dziesietnie=strtoul(bin,NULL,2);

        if(dziesietnie>max_dziesietnie)
            max_dziesietnie=dziesietnie;
    }
    delete bin;

    char max_binarnie[16];
    itoa(max_dziesietnie,max_binarnie,2);

    cout<<"3:\nmax dziesietnie: "<<max_dziesietnie<<endl;
    cout<<"max binarnie: "<<max_binarnie<<endl;
}