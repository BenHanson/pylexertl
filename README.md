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
rules.push('\\d+', 1)
rules.push('[A-Za-z]+', 2)
pylexertl.build(rules, sm)
results = pylexertl.match_results('101Ben200Hanson')
pylexertl.lookup(sm, results)
print("ID: {}, Token: '{}'".format(results.id(), results.str()))
pylexertl.lookup(sm, results)
print("ID: {}, Token: '{}'".format(results.id(), results.str()))
pylexertl.lookup(sm, results)
print("ID: {}, Token: '{}'".format(results.id(), results.str()))
pylexertl.lookup(sm, results)
print("ID: {}, Token: '{}'".format(results.id(), results.str()))
#pylexertl.dump(sm)
```
