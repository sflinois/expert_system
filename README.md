# expert_system

The goal of this project is to make an expert system for propositional calculus.

The program accept one parameter, which is the input file. It will contain a listof rules, then a list of initial facts, then a list of queries. For each of these queries, the program, given the facts and rules, tell if the query is true, false, or undetermined. By default, all facts are false, and can only be made true by the initial facts statement, or by application of a rule. If there is an error in the input, for example a contradiction in the facts, or a syntaxerror, the program must inform the user of the problem.

[ + ] : "AND" conditions. For example,"If A and B and [...]  then X"

[ | ] : "OR" conditions. For example,"If C or D then Z"

[ ^ ] : "XOR" conditions.  For example,"If A xor E then V".  Remember that thismeans "exclusive OR". It is only true if one and only one of the operands is true.

[ ! ] : Negation. For example,"If A and not B then Y"

[ (, ) ] : Parentheses in expressions. Interpreted in much the same way as an arithmetic expression


You can find input file examples in the tests folder
