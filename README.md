# ACT Passes

The ACT hardware description framework permits users to define their own analysis passes and insert them into the silicon compilation flow.
This repository contains an example pass that can be loaded in dynamically into the `interact` interactive ACT system.

A number of existing core passes are written this way, including the layout generation passes.

For additional documentation, run `doxygen`.

# Running the example

To run this example, you need the ACT standard library and `interact` installed. After that,
   * Build the pass using `make`
This will install `test_pass.so` into `$ACT_HOME/lib`

To see the pass in action, run the interact script `test.ia` provided.
```
$ interact
interact> source test.ia
Hello, initialized pass!
Visiting channel type ::std::channel::bd<7>, mode 0
Visiting channel type ::std::channel::bd<4>, mode 0
Visiting process foo<>, mode 0
Visiting process test<>, mode 0
received commmand hi there
  argtest = -1
received commmand hi-again
  argtest = 42
```
