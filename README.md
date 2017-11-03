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
environment by combining 

## Tests and Bugs

We have run this program through 

## Contributors

Ji Hwan Kim
Nikhil Gowda

## License

A short snippet describing the license (MIT, Apache, etc.)
