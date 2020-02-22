# Plurality

## Specification

Complete the implementation of plurality.c in such a way that the program simulates a plurality vote election.

- Complete the vote function.
vote takes a single argument, a string called name, representing the name of the candidate who was voted for.
- If name matches one of the names of the candidates in the election, then update that candidate’s vote total to account for the new vote. The vote function in this case should return true to indicate a successful ballot.
- If name does not match the name of any of the candidates in the election, no vote totals should change, and the vote function should return false to indicate an invalid ballot.
- You may assume that no two candidates will have the same name.
- Complete the print_winner function.
- The function should print out the name of the candidate who received the most votes in the election, and then print a newline.
- It is possible that the election could end in a tie if multiple candidates each have the maximum number of votes. In that case, you should output the names of each of the winning candidates, each on a separate line.
- You should not modify anything else in plurality.c other than the implementations of the vote and print_winner functions (and the inclusion of additional header files, if you’d like).

# Runoff

## Specification

Complete the implementation of runoff.c in such a way that it simulates a runoff election. You should complete the implementations of the vote, tabulate, print_winner, find_min, is_tie, and eliminate functions, and you should not modify anything else in runoff.c (except you may include additional header files, if you’d like).

## `vote`

Complete the vote function.

- The function takes arguments voter, rank, and name. If name is a match for the name of a valid candidate, then you should update the global preferences array to indicate that the voter voter has that candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.).
- If the preference is successfully recorded, the function should return true; the function should return false otherwise (if, for instance, name is not the name of one of the candidates).
- You may assume that no two candidates will have the same name.
