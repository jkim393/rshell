# rshell-stoics
cs100 F17
Jihwan Kim & Nikhil Gowda


## Synopsis

This project allows users to run common shell commands through a C++ environment rather than a terminal. 

## Code Example

You may use a single to multiple commands connected by connectors (e.g. ';' , '||' , or '&&')
UPDATE: We are now able to take in precedence commands and successfully use the TEST function with brackets
This Code can be in the format: 

ls; mkdir John_Smith || mkdir Sally_Smith && git status
((echo A && ls) || (echo B && mkdir Coder) && ls)

This program will be able to run the above code with the specific connector behaviour
semi-colons: commands after semi-colons always run regardless if the former argument fails
OR connector (||): a command after the OR connector runs only if the command before the OR connector fail. 
AND connector (&&): a command after the AND connector runs only if the command before the AND connector succeeds. 
Precedence '(' or ')'  will operate very similarly to mathematics or any other logic-based system

## Motivation

This project was created and inspired by Bash (GNU Project's shell). We hoped to mimic a Bash environment in a C++ 
environment by combining unique system calls with a composite structure that can handle a large amount of differentiating
but related objects. 

## Tests and Bugs (Part 1 of program before update)

We have run this program through rigorous tests of : single command, multiple commands, and comment parsing.

BUT, we have come across a few bug worth of consideration. 
This program is capable of successfully doing most commands but a few specific commands must be considered:
Using pipe '|' will give the same behavior as an OR connector "||". This feature is being developed and will be fixed in the next iteration of our program. 
This applies to the "&&" connector as well. This behavior is synonymous with 'running a progra&'. Again, this feature is being developed and will be fixed in the
next release. 
Another error is connector arguments existent in strings with parenthesis may have undefined behavior such as : echo "cat; dog || mouse"
Also, multiple newlines without input will create a seg fault. We are going to release a fix next development. 

## Tests and Bugs (Current Version)

We have run this program through further tests and implementations of recommended tests:

test_test.sh			#tests for the test command
precedence_test.sh		#tests for precedence operators
commented_command.sh		#tests commands with comments
exit.sh				#tests exit and commands with exit

We have achieved the ability to handle tests, precedence, commented, as well as exit commands. We have increased the functionality of our shell dramatically by having the ability to use test commands and precedence. You are able to use nested precedence without any issue. 

A few issues do maintain:

Using pipe '|' will give the same behavior as an OR connector "||". We apologize for the lack of bugfix, our engineers are working on it as we speak. We also do pose the same issue with parenthesis. Since we have not been able to fix this big, we do want to explain. Our parsing algorithm uses a modification of strtok that checks for parenthesis. We are looking for a wise fix to where we can ignore the parsing inside of quotations without affecting the character pointers in addition to the other co-dependent parsings. Another issue is our precedence: sentences like " ( echo B && echo C ) " will have undefined behavior. We are somehow parsing in a null value. It is a very interesting error we  hope we will fix soon. 



## Contributors

Ji Hwan Kim
and
Nikhil Gowda

## License

This program is classified under a GNU Affero General Public License v3.0


