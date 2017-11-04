# rshell-stoics
cs100 F17
Jihwan Kim & Nikhil Gowda


## Synopsis

This project allows users to run common shell commands through a C++ environment rather than a terminal. 

## Code Example

You may use a single to multiple commands connected by connectors (e.g. ';' , '||' , or '&&')
This Code can be in the format: 

ls; mkdir John_Smith || mkdir Sally_Smith && git status

This program will be able to run the above code with the specific connector behaviour
semi-colons: commands after semi-colons always run regardless if the former argument fails
OR connector (||): a command after the OR connector runs only if the command before the OR connector fail. 
AND connector (&&): a command after the AND connector runs only if the command before the AND connector succeeds. 
## Motivation

This project was created and inspired by Bash (GNU Project's shell). We hoped to mimic a Bash environment in a C++ 
environment by combining unique system calls with a composite structure that can handle a large amount of differentiating
but related objects. 

## Tests and Bugs

We have run this program through rigorous tests of : single command, multiple commands, and comment parsing.

BUT, we have come across a few bug worth of consideration. 
This program is capable of successfully doing most commands but a few specific commands must be considered:
Using pipe '|' will give the same behavior as an OR connector "||". This feature is being developed and will be fixed in the next iteration of our program. 
This applies to the "&&" connector as well. This behavior is synonymous with '&'. Again, this feature is being developed and will be fixed in the
next release. 

## Contributors

Ji Hwan Kim
and
Nikhil Gowda

## License

This program is classified under a GNU Affero General Public License v3.0


