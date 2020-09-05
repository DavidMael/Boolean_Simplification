README:

simplify.exe; the executable compiled from simplify.cpp, input.cpp, Kmap.cpp, Kmap_helpers.cpp and output.cpp; attemps to maximally simplify sum-of-product 
boolean expressions of up to four variables using a Karnaugh map.

The program takes with CIN an SOP expression, using the convention each English letter is a variable and that lowercase letters are the inversion of the same 
variable in uppercase. It will then COUT the simplified expression.

Example: AbC+ABC means ( A AND (NOT B) AND C ) OR (A AND B AND C) and simplifies to A AND C, which the program writes as AC.

https://math.stackexchange.com/questions/1797119/how-to-deal-with-an-8-variable-karnaugh-map

Some expressions simplify with duplicate or redundant minterms, though this has been mitigated to some extent.
