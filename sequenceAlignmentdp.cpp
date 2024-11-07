#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int sequenceAlign(const string &s1, const string &s2, int gap, int mismatch) {
    int m = s1.size();
    int n = s2.size();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));  // DP table to store the alignment costs
    // Base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i * gap;  // filling the first row
    for (int j = 0; j <= n; j++) dp[0][j] = j * gap;  //  column with gap penalties
    // Filling the rest of the table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];  // No cost for matching 
            } else {
                dp[i][j] = min({mismatch + dp[i - 1][j - 1], gap + dp[i - 1][j], gap + dp[i][j - 1]});} // Mismatch ,Gap in s1 ,Gap in s2   
        }
    }
    return dp[m][n];  // return cost
}

int main() {
    string s1 = "name";
    string s2 = "naem";
    int gapP = 2;
    int mismatchP = 3;
    int cost = sequenceAlign(s1, s2, gapP, mismatchP);
    cout << "The alignment cost is: " << cost << endl;
    return 0;
}