def solve_treasure_optimal(n, k, grid):
    """
    Find the lexicographically smallest string from top-left to bottom-right
    with at most k character modifications.
    
    Uses dynamic programming where state is (position, modifications_used).
    For each state, we track the lexicographically smallest string achievable.
    """
    total_steps = 2 * n - 1
    
    # current_states: (i, j, mods) -> best_string_so_far
    current_states = {}
    
    # Initialize with starting position - try all possible characters for first position
    for mods in range(k + 1):
        for c in 'abcdefghijklmnopqrstuvwxyz':
            cost = 0 if grid[0][0] == c else 1
            if cost <= mods:
                current_states[(0, 0, mods)] = c
                break  # Take the lexicographically smallest character we can afford
    
    # Process each step of the path
    for step in range(1, total_steps):
        next_states = {}
        
        for (i, j, mods), current_string in current_states.items():
            # Try moving right
            if j + 1 < n:
                ni, nj = i, j + 1
                for c in 'abcdefghijklmnopqrstuvwxyz':
                    cost = 0 if grid[ni][nj] == c else 1
                    new_mods = mods + cost
                    if new_mods <= k:
                        new_string = current_string + c
                        key = (ni, nj, new_mods)
                        # Keep only the lexicographically smallest string for each state
                        if key not in next_states or new_string < next_states[key]:
                            next_states[key] = new_string
                        break  # Take the first (smallest) affordable character
            
            # Try moving down
            if i + 1 < n:
                ni, nj = i + 1, j
                for c in 'abcdefghijklmnopqrstuvwxyz':
                    cost = 0 if grid[ni][nj] == c else 1
                    new_mods = mods + cost
                    if new_mods <= k:
                        new_string = current_string + c
                        key = (ni, nj, new_mods)
                        # Keep only the lexicographically smallest string for each state
                        if key not in next_states or new_string < next_states[key]:
                            next_states[key] = new_string
                        break  # Take the first (smallest) affordable character
        
        current_states = next_states
    
    # Find the lexicographically smallest result among all final states
    best_result = None
    for (i, j, mods), result_string in current_states.items():
        if i == n-1 and j == n-1:
            if best_result is None or result_string < best_result:
                best_result = result_string
    
    return best_result

# Read input
n, k = map(int, input().split())
grid = []
for _ in range(n):
    grid.append(input().strip())

# Solve and output the result
result = solve_treasure_optimal(n, k, grid)
print(result)