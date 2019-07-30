# expert_system

The goal of this project is to make an expert system for propositional calculus.

The program accept one parameter, which is the input file. It will contain a listof rules, then a list of initial facts, then a list of queries. For each of these queries, the program, given the facts and rules, tell if the query is true, false, or undetermined. By default, all facts are false, and can only be made true by the initial facts statement, or by application of a rule. If there is an error in the input, for example a contradiction in the facts, or a syntaxerror, the program must inform the user of the problem.


You can find input file examples in the tests folder
