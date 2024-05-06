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
