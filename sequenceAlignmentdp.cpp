#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int sequenceAlign(const string &s1, const string &s2, int gap, int vowelMismatch, int consonantMismatch, int vowelConsonantMismatch) {
    int m = s1.size();
    int n = s2.size();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));  // DP table to store the alignment costs
    
    // Base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i * gap;  // filling the first row
    for (int j = 0; j <= n; j++) dp[0][j] = j * gap;  // filling the first column
    
    // Filling the rest of the table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];  // No cost for matching characters
            } else {
                // Check if characters are vowels directly
                char c1 = tolower(s1[i - 1]);
                char c2 = tolower(s2[j - 1]);
                bool isC1Vowel = (c1 == 'a' || c1 == 'e' || c1 == 'i' || c1 == 'o' || c1 == 'u');
                bool isC2Vowel = (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
                
                int mismatchCost;
                if ((isC1Vowel && isC2Vowel) || (!isC1Vowel && !isC2Vowel)) {
                    mismatchCost = consonantMismatch;  // Both vowels or both consonants
                } else {
                    mismatchCost = vowelConsonantMismatch;  // One vowel, one consonant
                }
                
                // Fill dp[i][j] with the minimum cost
                dp[i][j] = min({mismatchCost + dp[i - 1][j - 1], gap + dp[i - 1][j],gap + dp[i][j - 1]});
            }
        }
    }
    return dp[m][n];  // return the final alignment cost
}

int main() {
    string s1, s2;
    cout << "Enter first string (s1): ";
    cin >> s1;
    cout << "Enter second string (s2): ";
    cin >> s2;
    int gapP = 2;                   // Gap penalty
    int vowelMismatch = 1;          // vowel mismatch
    int consonantMismatch = 1;      // Consonet mismatch
    int vowelConsonantMismatch = 3; // vowel consonet mismatch
    int cost = sequenceAlign(s1, s2, gapP, vowelMismatch, consonantMismatch, vowelConsonantMismatch );
    cout << "The alignment cost is: " << cost << endl;
    return 0;
}