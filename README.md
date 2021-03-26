# ELECTRONIC PLUG GAME

The goal is to plug inputs in the right ouputs, by pairs.

There are nb_pairs to plug.

<u>Code</u>:

For each input of the electrical panel :

- Send a signal into the input (LOW because pullup for noise)
- scan all elec panel outputs until found the one plug (= LOW) OR scan all of them.

   - Return the number of the output plug or -1 if no plug.
   - check if it is the good one.

Then turn on a lamp if all pairs are well plugged.