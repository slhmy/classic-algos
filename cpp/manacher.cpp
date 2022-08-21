#include <iostream>
#include <string>
#include <vector>

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
    // Get the expanded string
    string s = expand(raw);

    // Give an array to store the max radius you can get in pos `i`
    vector<int> radius(s.length(), 0);
    int refCenter = 0;
    int maxRadius = 0;

    for (int i = 1; i < s.length(); i++) {
        // If `i` is in the reference palindrome
        if (i < refCenter + radius[refCenter]) {
            // If true, some pair check can be ignored by referencing the image
            // palindrome on the other side
            radius[i] = min(radius[2 * refCenter - i],
                            refCenter + radius[refCenter] - i);
        } else {
            radius[i] = 1;
        }
        // Do the common pair check
        while (s[i + radius[i]] == s[i - radius[i]]) {
            radius[i]++;
        }
        // Update the refCenter
        if (i + radius[i] > refCenter + radius[refCenter]) {
            refCenter = i;
            maxRadius = max(radius[i], maxRadius);
        }
    }

    // MaxRadius is for the expanded string, so we have to recalculate the
    // length of the palindrome
    return maxRadius % 2 == 0 ? maxRadius - 1 : int(maxRadius / 2) * 2;
}

int main() { cout << manacherMaxLength("abaaa") << endl; }