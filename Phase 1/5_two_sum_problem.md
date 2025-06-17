# Two Sum Problem: Solution Evolution and Analysis

## Problem Statement

Given an array of integers `nums` and an integer `target`, return the indices of the two numbers that add up to the target.

**Constraints:**
- Each input has exactly one solution
- You may not use the same element twice
- You can return the answer in any order

## Solution Evolution

### 1. Brute Force Approach (Naive)

The most straightforward approach: check every possible pair of numbers.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int y = 0; y < nums.size(); y++) {
                if (i == y) continue;  // Skip same element
                if (nums[i] + nums[y] == target) {
                    return vector<int> {i, y};
                }
            }
        }
        return vector<int> {};
    }
};
```

**Complexity Analysis:**
- **Time Complexity:** O(n²)
- **Space Complexity:** O(1)
- **Total Operations:** ~n² - n (accounting for the continue statement)

**Characteristics:**
- ✅ Simple to understand and implement
- ✅ No extra space required
- ❌ Very inefficient for large datasets
- ❌ Checks pairs redundantly (both i,j and j,i)

### 2. Optimized Brute Force

Eliminate redundant pair checking by starting the inner loop from `i+1`.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int y = i + 1; y < nums.size(); y++) {
                if (nums[i] + nums[y] == target) {
                    return vector<int> {i, y};
                }
            }
        }
        return vector<int> {};
    }
};
```

**Complexity Analysis:**
- **Time Complexity:** O(n²)
- **Space Complexity:** O(1)
- **Total Operations:** (n-1) + (n-2) + ... + 1 = n(n-1)/2

**Improvements:**
- ✅ ~50% fewer operations than naive approach
- ✅ Eliminates redundant pair checking
- ✅ Removes unnecessary conditional check
- ❌ Still O(n²) algorithmic complexity

### 3. Hash Map with Ordered Map

Trade space for time using a data structure to store previously seen values.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> seen;
        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums[i];
            if (seen.contains(diff)) {
                return vector<int> {i, seen[diff]};
            } else {
                seen[nums[i]] = i;
            }
        }
        return vector<int> {};
    }
};
```

**Complexity Analysis:**
- **Time Complexity:** O(n log n)
- **Space Complexity:** O(n)

**Key Improvements:**
- ✅ Single pass through the array
- ✅ Significantly better time complexity
- ✅ Logarithmic rather than quadratic scaling
- ❌ Requires additional space
- ❌ Still not optimal due to tree-based map operations

### 4. Hash Map with Unordered Map (Optimal)

Achieve average linear time using hash table with constant-time operations.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums[i];
            if (seen.contains(diff)) {
                return vector<int> {i, seen[diff]};
            } else {
                seen[nums[i]] = i;
            }
        }
        return vector<int> {};
    }
};
```

**Complexity Analysis:**
- **Time Complexity:** 
  - Average: O(n)
  - Worst: O(n²) (due to hash collisions)
- **Space Complexity:** O(n)

**Algorithm Strategy:**
1. Iterate through array once
2. For each element, calculate its complement (target - current)
3. Check if complement exists in hash table
4. If found, return indices; otherwise, store current element

## Comprehensive Comparison

| Solution                | Time (Avg) | Time (Worst) | Space    | Iterations | Best Use Case                                     |
| ----------------------- | ---------- | ------------ | -------- | ---------- | ------------------------------------------------- |
| Brute Force (Naive)     | O(n²)      | O(n²)        | O(1)     | ~n²        | Very small arrays, memory-constrained             |
| Brute Force (Optimized) | O(n²)      | O(n²)        | O(1)     | ~n²/2      | Small arrays, memory-constrained                  |
| Ordered Map             | O(n log n) | O(n log n)   | O(n)     | n          | Medium arrays, when hash collisions are a concern |
| **Unordered Map**       | **O(n)**   | **O(n²)**    | **O(n)** | **n**      | **Most cases - industry standard**                |

## Performance Analysis

### Scalability Comparison

For an array of size n:

| n      | Brute Force     | Optimized Brute | Ordered Map | Unordered Map |
| ------ | --------------- | --------------- | ----------- | ------------- |
| 10     | 100 ops         | 45 ops          | 33 ops      | 10 ops        |
| 100    | 10,000 ops      | 4,950 ops       | 664 ops     | 100 ops       |
| 1,000  | 1,000,000 ops   | 499,500 ops     | 9,966 ops   | 1,000 ops     |
| 10,000 | 100,000,000 ops | 49,995,000 ops  | 132,877 ops | 10,000 ops    |

### Memory Usage

| Solution           | Memory Pattern | Growth Rate |
| ------------------ | -------------- | ----------- |
| Brute Force        | Constant       | O(1)        |
| Hash Map Solutions | Linear growth  | O(n)        |

## When to Use Each Solution

### Brute Force (Optimized)
- **Use when:** Arrays are very small (n < 20)
- **Use when:** Memory is extremely constrained
- **Use when:** Implementation simplicity is paramount

### Ordered Map (std::map)
- **Use when:** Hash collisions are a serious concern
- **Use when:** You need guaranteed O(n log n) performance
- **Use when:** Working with a custom data type without good hash function

### Unordered Map (std::unordered_map) ⭐ **Recommended**
- **Use when:** Working with typical integer arrays
- **Use when:** Performance is important
- **Use when:** Average O(n) time is acceptable with rare O(n²) worst case
- **Industry standard** for this problem

## Key Insights

### Algorithm Evolution Principles
1. **Identify bottlenecks:** Nested loops were the primary performance issue
2. **Trade space for time:** Using extra memory to eliminate redundant work
3. **Choose appropriate data structures:** Hash tables provide faster lookups than arrays
4. **Optimize data structure choice:** Unordered containers often outperform ordered ones

### The Hash Map Insight
The key algorithmic insight is recognizing that instead of searching for a pair (a, b) where a + b = target, we can:
1. Fix 'a' (current element)
2. Calculate 'b' (target - a)
3. Check if 'b' exists in our seen elements

This transforms a quadratic search problem into a linear lookup problem.

## Conclusion

The evolution from O(n²) brute force to O(n) hash map solution demonstrates fundamental algorithmic optimization principles. The unordered map approach represents the optimal balance of time complexity, practical performance, and code clarity, making it the industry-standard solution for the Two Sum problem.

---

Links:
- [Leetcode Solution](https://leetcode.com/problems/two-sum/submissions/1667142156)