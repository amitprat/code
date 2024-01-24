## Given the array of digits (0 is also allowed), what is the minimal sum of two integers that are made of the digits contained in the array. For example, array: 1 2 7 8 9. The min sum (129 + 78) should be 207

```
Sort the array. The largest numbers should be in the least significant positions, so build up your two integers by alternating from the two arrays. 
E.g. 1 3 5 7 8 9  => 1 and 3, then 15 and 37, then 158 and 379. 0 is a special case, if not allowed to use that as a leading digit then have to use it as the second digit.
```

