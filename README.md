# README:

simplify.exe; the executable compiled from simplify.cpp, input.cpp, Kmap.cpp, Kmap_helpers.cpp and output.cpp; attemps to maximally simplify sum-of-product 
boolean expressions of up to four variables using a Karnaugh map.

The program takes an SOP expression as a command line parameter or through CIN, using the convention that each English letter is a variable and that lowercase 
letters are the inversion of the same variable in uppercase. It will then COUT the simplified expression.

Example: AbC+ABC means ( A AND (NOT B) AND C ) OR (A AND B AND C) and simplifies to A AND C, which the program writes as AC.

Fun bonus feature: a K-map will still be constructed for single variable inputs, though minterms equal to 0 cannot be represented on the map. All non-zero
minterms will therefore be printed back out as if they were products of two identically named variables.

Examples: Aa+a+AA simplifies to aa+AA, BBB simplifies to BB, and Cc will not be simplified.
