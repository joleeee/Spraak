# Språk
This is a simple language written in a sort of norwegian bokmål although it is also backwards compatible with norwegian nynorsk. Each line contains a 'single' instruction. The possible instructions are as follows: \*subject to change and may include plannned feature
| COMMAND | EXPLANATION | CPP EQUIVALENT |
| - | - | - |
|VAR er NUMBER | sets VAR equal to NUMBER | VAR = NUMBER |
|VAX er VAY | sets VAX equal to VAY | VAX = VAY |
|VAX pluss VAY | increments VAX by VAY | VAX += VAY |
|skriv ut VAR | outputs an integer to the standard ouput | cout << VAR / printf("%d", VAR) |

The plan is that all numbers have to be spelled out in norwegian, so for 0 you write null and for 3 you write tre, but im not quite sure yet.

Im currently working on s2c.cpp, it translates språk into c(pp).
To run it you can issue the following commands ``g++ s2c.cpp -o s2c.o -O2 && ./s2c.o > code.cpp && g++ code.cpp -o compiled.o && ./compiled.o``.

# questions
- use . or \n?

# TODO
- make a simple code editor in SFML and make numbers wavy :)
- make an actual compiler that doesnt go through another language like c and isnt interpreted

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
