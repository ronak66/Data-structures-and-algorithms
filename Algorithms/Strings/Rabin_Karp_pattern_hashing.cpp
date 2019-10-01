#include <bits/stdc++.h>
using namespace std;

// d is the number of characters in the input alphabet

/* pat -> pattern 
    txt -> text 
    q -> A prime number 
*/
//average case: O(m+n), worst case: O(mn);
//so use Aho-Corasick algorithm for O(m+n) worst case;
int q;
long recalculateHash(string str, int old_index, int new_index, long old_hash, int m)
{
    long new_hash = old_hash - str[old_index];
    new_hash = new_hash / q;
    new_hash += str[new_index] * pow(q, m - 1);

    return new_hash;
}
bool search(string pat, string text)
{
    int m = pat.length();
    int n = text.length();
    long patternHash = 0;
    long textHash = 0;

    //create hash for patter and first window text
    for (int i = 0; i < m; i++)
    {
        patternHash += pat[i] * pow(q, i);

        textHash += text[i] * pow(q, i);
    }

    for (int i = 0; i <= n - m; i++)
    {
        if (patternHash == textHash)
        {
            for (int j = 0; j < m; j++)
            {
                if (pat[j] != text[i + j])
                    return 0;
            }
        }
        if (i < n - m)
        {
            textHash = recalculateHash(text, i, i + m, textHash, m);
        }
    }

    return 1;
}

int main()
{
    string text, pat;
    cin >> text >> pat;

    q = 101; // A prime number
    search(pat, text) ? cout << "found" : cout << "nah";
    return 0;
}
