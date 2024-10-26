## Design Questions

1. For starters, one could try all permutations of case alternation for all characters (password, Password, PAssword, ..., pASsword, ..., pAsSword, ...). It is also common for people to swap letters for numbers that look similar (3 and E), so it might be worth trying that as well.

2. Not much. Since our current approach is a brute-force attack, the bottleneck is in our CPU's computational power, and not so much in our memory availability.