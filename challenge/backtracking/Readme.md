# Backtracking -- How to Recognize When to Use It

## Definition

Backtracking is a recursive algorithmic technique that explores all
possible solutions by:

1.  Making a choice
2.  Recursing
3.  Undoing the choice (backtracking)

Pattern:

    choose
    recurse
    undo

------------------------------------------------------------------------

## Core Idea

Backtracking is used when:

-   You must explore multiple possible configurations
-   You must generate all valid solutions
-   You must try something, and undo it if it fails

It is essentially a DFS over a decision tree.

------------------------------------------------------------------------

## How to Identify Backtracking Problems

Look for these signals in the problem statement:

### Signal 1: "Return ALL possible..."

Examples:

-   All permutations
-   All combinations
-   All subsets
-   All valid strings

Keywords:

-   "all"
-   "generate"
-   "list all"
-   "return all"

------------------------------------------------------------------------

### Signal 2: Decision tree structure

At each step, you must choose between multiple options.

Example:

    "abc"

    choose a
    choose b
    choose c

This creates a tree of possibilities.

------------------------------------------------------------------------

### Signal 3: Constraints that must be checked

Examples:

-   Valid parentheses
-   Valid Sudoku
-   Valid queen placement

Pattern:

    if valid:
        recurse

------------------------------------------------------------------------

### Signal 4: Incremental solution construction

You build solution piece-by-piece.

Example:

    current = ""
    add letter
    add number
    add substring

------------------------------------------------------------------------

### Signal 5: Exponential number of possibilities

If total possibilities are:

    2^n
    n!
    k^n

Backtracking is likely required.

------------------------------------------------------------------------

## Common Backtracking Problem Types

### Type 1: Permutations

Example:

    Permutations of "ABC"

Pattern:

    use visited array OR swap

------------------------------------------------------------------------

### Type 2: Subsets / Combinations

Example:

    Subsets of [1,2,3]

Pattern:

    include OR exclude

------------------------------------------------------------------------

### Type 3: Constraint placement

Example:

    N‑Queens
    Sudoku
    Graph coloring

Pattern:

    if safe → place → recurse → remove

------------------------------------------------------------------------

### Type 4: Grid traversal

Example:

    Word Search
    Rat in Maze

Pattern:

    mark visited
    recurse neighbors
    unmark visited

------------------------------------------------------------------------

### Type 5: Partition problems

Example:

    Palindrome Partitioning
    Restore IP addresses

Pattern:

    for end in range(start, n):
        choose substring
        recurse

------------------------------------------------------------------------

## Universal Backtracking Template

    function backtrack(state):

        if solution complete:
            save result
            return

        for choice in choices:

            if valid:

                make choice

                backtrack(new state)

                undo choice

------------------------------------------------------------------------

## Mental Model

Backtracking = DFS on a decision tree.

Example tree:

            ""
          /  |  \
         a   b   c
        / \
       d   e

Explore → undo → explore next.

------------------------------------------------------------------------

## When NOT to use backtracking

Do NOT use backtracking if:

-   Only one optimal answer needed (use greedy or DP)
-   Problem requires shortest path (use BFS)
-   Problem requires maximum/minimum value (often DP)

------------------------------------------------------------------------

## Complexity

Usually:

    O(2^n)
    O(n!)

Backtracking is exponential but pruned by constraints.

------------------------------------------------------------------------

## Summary Checklist

Use backtracking if:

-   Need all solutions
-   Need combinations/permutations
-   Problem has constraints
-   Solution built step‑by‑step
-   Problem has exponential possibilities
