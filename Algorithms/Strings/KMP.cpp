
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * get prefix list
 */
//O(m+n)

vector<int> computePrefix(string str)
{

    int m = str.length();

    vector<int> prefix(m);

    for (int i = 1, j = 0; i < m;)
    {
        if (str[j] == str[i])
            prefix[i++] = ++j;
        else
        {
            if (j > 0)
            {
                j = prefix[j - 1];
            }
            else
                prefix[i++] = 0;
        }
    }

    return prefix;
}

void KMP(string &str, string pat)
{
    int m = str.length();
    int n = pat.length();
    vector<int> longestPrefix = computePrefix(pat);

    for (int i = 0, k = 0; i < m; i++)
    {
        if (k > 0 && pat[k] != str[i])
            k = longestPrefix[k - 1];
        if (str[i] == pat[k])
            k++;
        if (k == n)
        {
            cout << i - n + 1 << '\n';
            k = longestPrefix[k - 1];
        }
    }
}

int main()
{
    string s, p;
    cin >> s >> p;
}