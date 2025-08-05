#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

string solve_treasure(int n, int k, vector<string>& grid) {
    int total_steps = 2 * n - 1;
    
    // current_states: map from encoded key to best string
    // Key encoding: ((i * 1000 + j) * 1000 + mods)
    unordered_map<long long, string> current_states;
    
    // Initialize with starting position - try all possible characters for first position
    for (int mods = 0; mods <= k; mods++) {
        for (char c = 'a'; c <= 'z'; c++) {
            int cost = (grid[0][0] == c) ? 0 : 1;
            if (cost <= mods) {
                long long key = ((long long)0 * 1000 + 0) * 1000 + mods;
                current_states[key] = string(1, c);
                break;  // Take the lexicographically smallest character we can afford
            }
        }
    }
    
    // Process each step of the path
    for (int step = 1; step < total_steps; step++) {
        unordered_map<long long, string> next_states;
        
        for (auto& [encoded_key, current_string] : current_states) {
            // Decode the key to get i, j, mods
            int mods = encoded_key % 1000;
            long long temp = encoded_key / 1000;
            int j = temp % 1000;
            int i = temp / 1000;
            
            // Try moving right
            if (j + 1 < n) {
                int ni = i, nj = j + 1;
                for (char c = 'a'; c <= 'z'; c++) {
                    int cost = (grid[ni][nj] == c) ? 0 : 1;
                    int new_mods = mods + cost;
                    if (new_mods <= k) {
                        string new_string = current_string + c;
                        long long new_key = ((long long)ni * 1000 + nj) * 1000 + new_mods;
                        
                        // Keep only the lexicographically smallest string for each state
                        if (next_states.find(new_key) == next_states.end() || 
                            new_string < next_states[new_key]) {
                            next_states[new_key] = new_string;
                        }
                        break;  // Take the first (smallest) affordable character
                    }
                }
            }
            
            // Try moving down
            if (i + 1 < n) {
                int ni = i + 1, nj = j;
                for (char c = 'a'; c <= 'z'; c++) {
                    int cost = (grid[ni][nj] == c) ? 0 : 1;
                    int new_mods = mods + cost;
                    if (new_mods <= k) {
                        string new_string = current_string + c;
                        long long new_key = ((long long)ni * 1000 + nj) * 1000 + new_mods;
                        
                        // Keep only the lexicographically smallest string for each state
                        if (next_states.find(new_key) == next_states.end() || 
                            new_string < next_states[new_key]) {
                            next_states[new_key] = new_string;
                        }
                        break;  // Take the first (smallest) affordable character
                    }
                }
            }
        }
        
        current_states = move(next_states);
    }
    
    // Find the lexicographically smallest result among all final states
    string best_result = "";
    bool found = false;
    
    for (auto& [encoded_key, result_string] : current_states) {
        // Decode to check if we're at (n-1, n-1)
        int mods = encoded_key % 1000;
        long long temp = encoded_key / 1000;
        int j = temp % 1000;
        int i = temp / 1000;
        
        if (i == n-1 && j == n-1) {
            if (!found || result_string < best_result) {
                best_result = result_string;
                found = true;
            }
        }
    }
    
    return best_result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    
    cout << solve_treasure(n, k, grid) << '\n';
    
    return 0;
}