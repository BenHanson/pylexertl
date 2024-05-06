pylexertl
=========
This is the python bindings for lexertl17

Building
========
- Make sure you have python and cmake installed
- If on Linux, make sure you have installed python3-dev
```
cd 3rd
git clone https://github.com/pybind/pybind11.git
cd ..
cd build
cmake ..
```

Example
=======
```
import pylexertl
rules = pylexertl.rules()
sm = pylexertl.state_machine()
rules.insert_macro('digit', '\\d')
rules.push('{digit}+', 1)
rules.push('[A-Za-z]+', 2)
pylexertl.build(rules, sm)

results = pylexertl.match_results('101One200Two')
# Look-ahead
pylexertl.lookup(sm, results)

while results.id:
  print("ID: {}, Token: '{}'".format(results.id, results.str()))
  pylexertl.lookup(sm, results)

print('')
pylexertl.dump(sm)
```
Output
======

```
ID: 1, Token: '101'
ID: 2, Token: 'One'
ID: 1, Token: '200'
ID: 2, Token: 'Two'

Lexer state: 0

State: 0
  [\0] -> 1

State: 1
  [\0] -> 2

State: 2
  [0-9] -> 3
  [A-Za-z] -> 4

State: 3
  END STATE, Id = 1, User Id = 65535, dfa = 0
  [\0] -> 5

State: 4
  END STATE, Id = 2, User Id = 65535, dfa = 0
  [\0] -> 6

State: 5
  [\0] -> 7

State: 6
  [\0] -> 8

State: 7
  [0-9] -> 3

State: 8
  [A-Za-z] -> 4
```
