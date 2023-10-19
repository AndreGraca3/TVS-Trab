### Exercise 1

**b) Subsections 1.1.3 and 5.3.1 specify a canonical address form for virtual addresses. With 4-level mapping, canonical addresses go from 0x0000000000000000 to 0x________________ and then from 0x________________ to 0xFFFFFFFFFFFFFFFF. Complete the missing values and write the canonical ranges for 5-level mapping.**

----

**4-level mapping**

<!-- short comment justifying the answer below -->

0x0000000000000000 to 0x00007FFFFFFFFFFF
and
0xFFFF800000000000 to 0xFFFFFFFFFFFFFFFF

In 4-level mapping there are 16 sign-extended bits meaning the 47th (starting from 0) bit controls the range of virtual addresses.
Alternating the 47th bit and the sign extended bits we obtain these 2 ranges.


**5-level mapping**

<!-- short comment justifying the answer below -->

0x0000000000000000 to 0x00FFFFFFFFFFFFFF
and
0xFF00000000000000 to 0xFFFFFFFFFFFFFFFF

In 5-level mapping there are 7 sign-extended bits meaning the 56th (starting from 0) bit controls the range of virtual addresses.
Alternating the 56th bit and the sign extended bits we obtain these 2 ranges.
