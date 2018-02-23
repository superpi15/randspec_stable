Generate an incomplete spec. in which each don’t-care entry has the same bit pattern on input and output sides.
1) Generate 2n sized spec S. It has ordered input patterns ranged from [0,2n-1]. These patterns are directly assigned to output entries on the truth table.
2) Generate a 2n-bit boolean array. In this array, -bit of 1s are used to denote cared entries on the spec S. The positions of these -bit are decided by random shuffle.
3) Perform random shuffle on output side of cared entries.


