##SHELL SORT

Shell Sort = Insertion Sort with gaps.

Shell Sort is an improved version of Insertion Sort. Instead of comparing only adjacent elements, it first compares elements that are far apart using a gap.

-gap = n/2 = 4  then   gap=4/2 so on....  till  gap =1

Original
[8,5,3,7,6,2,4,1]
       ↓
gap = 4
[6,2,3,1,8,5,4,7]
       ↓
gap = 2
[3,1,6,2,8,5,4,7]
       ↓
gap = 1
[1,2,3,4,5,6,7,8]
