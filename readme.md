# Språk
This is a simple language written in a sort of norwegian bokmål although it is also backwards compatible with norwegian nynorsk. Each line contains a 'single' instruction. The possible instructions are as follows: \*subject to change and may include plannned feature
| COMMAND | EXPLANATION |
| - | - |
|VAR er NUMBER | sets VAR equal to NUMBER |
|VAR er VAR2 | sets VAR equal to VAR2 |
|VAR pluss VAR2 | increments VAR by VAR2 // will probably be renamed in the future |
|skriv ut VAR | outputs variable in format [VAR: VALUE] INCLUDING THE BRACKETS, may be subject to change. |

originally i was thinking of using og between lines and use it to tell what lines were at the same indentation, but i now see no point or how it would be usefull so now to show "indentation" in a loop you have to write - like a list (see example below)
The plan is that all numbers have to be spelled out in norwegian, so for 0 you write null and for 3 you write tre, but im not quite sure yet.

# questions
- use . or \n?

# TODO
- make a simple code editor in SFML and make numbers wavy :)
- make an actual compiler that doesnt go through another language like c or python and isnt interpreted

\* this is a readme as much as a note for me to remember what im doing

this is what a future script may look like
```
be om navnet
skriv ut navnet
a er ti
b er tjue
c er a
c plus b
skriv ut c som tall
når c er mer enn tjuefem så
- skriv ut c
- mink c med en
spørr om vi er ferdige nå
hvis vi er ferdige nå så
- slutt
ellers så
- gå til første linje
- gå til linje nummer en
```
