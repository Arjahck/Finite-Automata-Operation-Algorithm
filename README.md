# Finite-Automata-Operation-Algorithm

alorithme to excutre operations on automata

.
+-- main.cpp
+-- src
|   +-- automate.cpp
|   +-- etat.cpp
|   +-- transition.cpp
|   +-- utilitaire.cpp
+-- include
|   +-- automate.h
|   +-- etat.h
|   +-- transition.h
|   +-- utilitaire.h


## Disclaimer

This project was done in Codeblocks (can result to missing file error when run by another application).
Most of the files names, variable names and commentary is in french.

## Working exemple

1) Reading an automaton in a file

Line 1: Initial_Status
Line 2: the state or states that are initial
Line 3: End_Status
Line 4: the state or states that are final/terminal
Line 5: Alphabet
Line 6: characters of the alphabet
Line 7: Automaton
Line 8: Transitions
…
Line 10: END
In a .txt file, we wrote the automaton as indicated in the statement.

Ex : 
![alt text](https://i.imgur.com/uFjUnMH.png)


!!! All The screenshots are based on the finite automata 6.

### 2) display automata

![alt text](https://i.imgur.com/EcWP71V.png)

### 3) Determination and Completion

#### Determination :
![alt text](https://i.imgur.com/o7TwYLQ.png)

#### Determination and Completion
![alt text](https://i.imgur.com/td0gAaG.png)

### 4) Complementary
![alt text](https://i.imgur.com/3gZJnr7.png)

### 5) Minimization

#### selected automata
![alt text](https://i.imgur.com/BAhVBdb.png)

#### minimization result
![alt text](https://i.imgur.com/sXHcNWM.png)

### 6) Standardization
![alt text](https://i.imgur.com/NwjOQFF.png)

### 7) Word recognition in the selected automata
![alt text](https://i.imgur.com/G7LBQGG.png)
