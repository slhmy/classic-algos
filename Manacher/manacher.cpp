//
// Created by slhmy on 2022/8/22.
//

#include <iostream>
#include <string>
#include <utility>

using namespace std;

string expand(string raw) {
    unsigned int len = raw.length();
    string res;
    res.push_back('@');
    for (unsigned int i = 0; i < len; i++) {
        res.push_back('#');
        res.push_back(raw[i]);
    }
    res.push_back('#');
    return res;
}

int manacherMaxLength(string raw) {
    // get the expanded string
    string s = expand(std::move(raw));

    // give an array to store the max radius you can get in pos `i`
    int radius[s.length()];
    int refCenter = 0;
    int maxRadius = 0;

    for (int i = 0; i < s.length(); i++) {
        // if `i` is in the reference palindrome
        if (i < refCenter + radius[refCenter])
            // if true, some pair check can be ignored by referencing the image palindrome on the other side
            radius[i] = min(radius[2*refCenter - i], refCenter + radius[refCenter] - i);
        else radius[i] = 1;
        // do the common pair check
        while (s[i + radius[i]] == s[i - radius[i]]) radius[i]++;
        // update the refCenter
        if (i + radius[i] > refCenter + radius[refCenter]) {
            refCenter = i;
            maxRadius = max(radius[i], maxRadius);
        }
    }

    // maxRadius is for the expanded string, so we have to recalculate the length of the palindrome
    return maxRadius % 2 == 0 ? maxRadius - 1 : int(maxRadius / 2) * 2;
}

int main() {
    cout << manacherMaxLength("aaaaa") << endl;
}