#include <bits/stdc++.h>
#include "json.hpp" // Include nlohmann/json header
using namespace std;
using json = nlohmann::json;

const long long MOD = 1000000007;

// Modular exponentiation
long long modPow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// Modular inverse using Fermat's theorem
long long modInverse(long long a, long long mod) {
    return modPow(a, mod - 2, mod);
}

// Convert string in given base to decimal (mod MOD)
long long baseToDecimal(string value, int base) {
    long long result = 0;
    for (char c : value) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else if (isalpha(c)) digit = 10 + (tolower(c) - 'a');
        result = (result * base + digit) % MOD;
    }
    return result;
}

// Lagrange interpolation to find f(0)
long long lagrangeInterpolation(vector<pair<long long,long long>> &points) {
    int k = points.size();
    long long secret = 0;
    for (int i = 0; i < k; i++) {
        long long xi = points[i].first;
        long long yi = points[i].second;
        
        long long term = yi;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                long long xj = points[j].first;
                long long numerator = (-xj + MOD) % MOD;
                long long denominator = (xi - xj + MOD) % MOD;
                term = (term * numerator) % MOD;
                term = (term * modInverse(denominator, MOD)) % MOD;
            }
        }
        secret = (secret + term) % MOD;
    }
    return (secret + MOD) % MOD;
}

void generateCombinations(vector<pair<long long,long long>> &points, int k) {
    int n = points.size();
    vector<int> mask(n);
    fill(mask.begin(), mask.begin() + k, 1);
    
    unordered_map<long long, int> secretFreq;
    vector<vector<int>> combinations;
    vector<long long> secretsForComb;
    
    do {
        vector<pair<long long,long long>> subset;
        vector<int> idx;
        for (int i = 0; i < n; i++) {
            if (mask[i]) {
                subset.push_back(points[i]);
                idx.push_back(i);
            }
        }
        long long sec = lagrangeInterpolation(subset);
        secretFreq[sec]++;
        combinations.push_back(idx);
        secretsForComb.push_back(sec);
    } while (prev_permutation(mask.begin(), mask.end()));
    
    // Find most frequent secret
    int maxFreq = 0;
    long long correctSecret = -1;
    for (auto &it : secretFreq) {
        if (it.second > maxFreq) {
            maxFreq = it.second;
            correctSecret = it.first;
        }
    }
    
    cout << "Correct Secret: " << correctSecret << "\n";
    
    // Track share usage in correct secret combinations
    vector<int> countInCorrect(n, 0);
    for (int c = 0; c < combinations.size(); c++) {
        if (secretsForComb[c] == correctSecret) {
            for (int idx : combinations[c]) countInCorrect[idx]++;
        }
    }
    
    cout << "Wrong Shares (likely corrupt): ";
    bool anyWrong = false;
    for (int i = 0; i < n; i++) {
        if (countInCorrect[i] == 0) { // never in correct combinations
            cout << "Share with x=" << points[i].first << " ";
            anyWrong = true;
        }
    }
    if (!anyWrong) cout << "None";
    cout << "\n";
}

int main() {
    ifstream inFile("testcase.json");
    json data;
    inFile >> data;
    
    int n = data["keys"]["n"];
    int k = data["keys"]["k"];
    
    vector<pair<long long,long long>> points;
    for (auto& [key, val] : data.items()) {
        if (key == "keys") continue;
        long long x = stoll(key);
        int base = stoi(val["base"].get<string>());
        string value = val["value"].get<string>();
        long long y = baseToDecimal(value, base);
        points.push_back({x, y});
    }
    
    generateCombinations(points, k);
    
    return 0;
}
