#include <iostream>
#include <string>

using namespace std;

void getNext(string s, int *next) {
    int cur = 0, past = -1;
    next[0] = -1;
    while (cur < s.length()) {
        // |abbaaba|    |abbaaba|
        //   ^ past           ^ cur     -- >    next[cur+1] = past+1
        if (past == -1 || s[cur] == s[past]) {
            next[++cur] = ++past;
        } else {
            past = next[past];
        }
    }
}

int KMP(const string &m_str, const string &t_str) {
    // you may need to check if m/t_str are valid here

    // build `next` array
    int next[t_str.length()];
    getNext(t_str, next);

    // matching
    int mPtr = 0, tPtr = 0;
    while (mPtr < m_str.length() && tPtr < m_str.length()) {
        if (tPtr == -1 || m_str[mPtr] == t_str[tPtr]) {
            mPtr++, tPtr++;
        }
        // when mismatch occurs, you try another match possibility
        // by right move the target_str, aligning m_str[mPtr-1] to a previous
        // matched t_str character Ex. |abbaabbaaba| |abbaabbaaba|
        //        ^                                ^
        // |abbaaba    |           -->      |    abbaaba|
        //        ^ mismatch here                  ^ reset to here
        //
        // the `next` array helps you quickly get in this position
        else {
            tPtr = next[tPtr];
        }
    }

    // answer result
    if (tPtr == t_str.length()) {
        return mPtr - t_str.length();
    } else {
        return -1;
    }
}

int main() { cout << KMP("abbaabbaaba", "abbaaba") << endl; }
