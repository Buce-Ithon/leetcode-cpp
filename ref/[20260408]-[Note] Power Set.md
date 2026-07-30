## Date: 2026.04.08

### Note: Power Set

### Abstract

Power Set $P(S)$ of a set $S$ is the set of all subsets of $S$. For example $S = {a, b, c}$ then $P(s) = {{}, {a}, {b}, {c}, {a,b}, {a, c}, {b, c}, {a, b, c}}$. If $S$ has n elements in it then $P(s)$ will have $2^n$ elements.

### Approach 1: By Using Binary Representation of Numbers from 0 to $2^n - 1$

### Code

```cpp
vector<string> allPossibleStrings(string &s) {
    int n = s.size();
    vector<string> res;
    
    // Iterate through all subsets (by 0 to 2^n - 1)
    for (int i = 0; i < (1 << n); i++) {
        string sub = "";
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                sub += s[j];
            }
        }
        res.push_back(sub);
    }
    
    return res;
}
```

### Analysis

Time complexity: $O(2^n\cdot n)$

Auxiliary space: $O(1)$

### References

https://www.geeksforgeeks.org/dsa/power-set/

https://www.geeksforgeeks.org/dsa/lexicographically-previous-permutation-in-c/

https://www.geeksforgeeks.org/dsa/recursive-program-to-generate-power-set/
