# inet

An implementation of [interaction nets](https://en.wikipedia.org/wiki/Interaction_nets)
as a [forth-like](https://en.wikipedia.org/wiki/Forth_(programming_language))
[concatenative programming language](https://en.wikipedia.org/wiki/Concatenative_programming_language).

- Untyped, i.e. no static type checking.
- Using a concatenative stack-based low-layer language to build nets.
- Programming with interaction nets directly (no compilation via combinators).

## Syntax

```xml
define-node <name> <inputs> -> <outputs> end
define-rule <name> <name> ... end
define <name> ... end
```

## Examples

### Natural Number

```
define-node nzero -> value! end
define-node nadd1 prev -> value! end
define-node nadd target! addend -> result end
```

The rule between `(nadd1)` and `(nadd)` as ASCII art:

```
     value             value            value
       |                 |                |
    (nadd)     =>                =>    (nadd1)
     /   \                 \              |
(nadd1)   addend           addend       (nadd)
   |                 |                  /   \
 prev              prev              prev   addend
```

Define the rule between `(nadd1)` and `(nadd)`:

```
define-rule nadd1 nadd
  ( addend result ) ( prev )
  prev addend nadd
  nadd1 result connect
end
```

To apply this rule is to disconnect and delete `(nadd1)` and `(nadd)` and reconnect newly exposed wires:

- `( addend result )` save the wires that were connected to `(nadd)` to local variable `addend` and `result`.
- `( prev )` save the wire that was connected to `(nadd1)` to local variable `prev`.
- `prev` push local variables to the stack.
- `addend` push local variables to the stack.
- `nadd` take two arguments from the stack and create a new `(nadd)` node.
- `nadd1` take one argument from the stack and create a new `(nadd1)` node.
- `result` push local variable to the stack.
- `connect` take two wires from the stack and connect them.

The rule between `(nzero)` and `(nadd)` as ASCII art:

```
     value          value         value
       |              |             |
     (nadd)     =>             =>   |
     /   \              \            \
(nzero)   addend        addend       addend
```

Define the rule between `(nzero)` and `(nadd)`:

```
define-rule nzero nadd
  ( addend result )
  addend result connect
end
```

To apply this rule is to disconnect and delete `(nzero)` and `(nadd)` and reconnect newly exposed wires:

- `( addend result )` save the wires that were connected to `(nadd)` to local variable `addend` and `result`.
- `addend` push local variables to the stack.
- `result` push local variables to the stack.
- `connect` take two wires from the stack and connect them.

Example interaction:

```
       |                   |                   |              |
    (nadd)              (nadd1)             (nadd1)        (nadd1)
     /   \                 |                   |              |
(nadd1)  (nadd1)        (nadd)              (nadd1)        (nadd1)
   |        |    =>      /   \       =>        |        =>    |
(nadd1)  (nadd1)    (nadd1)  (nadd1)         (nadd)        (nadd1)
   |        |          |        |            /   \            |
(nzero)  (nzero)    (nzero)  (nadd1)    (nzero) (nadd1)    (nadd1)
                                |                  |          |
                             (nzero)            (nadd1)    (nzero)
                                                   |
                                                (nzero)
```

The whole program with test:

```
define-node nzero -> value! end
define-node nadd1 prev -> value! end
define-node nadd target! addend -> result end

define-rule nzero nadd
  ( addend result )
  addend result connect
end

define-rule nadd1 nadd
  ( addend result ) ( prev )
  prev addend nadd
  nadd1 result connect
end

define two
  nzero nadd1 nadd1
end

wire-print-net
run
wire-print-net
```

<details>
<summary>output</summary>

```xml
<net>
<root>
(nadd₇)-result-<>-
</root>
<body>
(nadd1₃)-value!-<>-!target-(nadd₇)
(nadd1₆)-value!-<>-addend-(nadd₇)
(nadd1₅)-value!-<>-prev-(nadd1₆)
(nzero₄)-value!-<>-prev-(nadd1₅)
(nadd1₂)-value!-<>-prev-(nadd1₃)
(nzero₁)-value!-<>-prev-(nadd1₂)
</body>
</net>

<net>
<root>
(nadd1₉)-value!-<>-
</root>
<body>
(nadd1₁₁)-value!-<>-prev-(nadd1₉)
(nadd1₆)-value!-<>-prev-(nadd1₁₁)
(nadd1₅)-value!-<>-prev-(nadd1₆)
(nzero₄)-value!-<>-prev-(nadd1₅)
</body>
</net>
```

</details>

### List

```
define-node nil -> value! end
define-node cons tail head -> value! end
define-node append target! rest -> result end

define-rule nil append
  ( rest result )
  rest result connect
end

define-rule cons append
  ( rest result ) ( tail head )
  tail rest append
  head cons result connect
end

define-node sole -> value! end

nil sole cons sole cons sole cons
nil sole cons sole cons sole cons
append

wire-print-net
run
wire-print-net
```

<details>
<summary>output</summary>

```xml
<net>
<root>
(append₁₅)-result-<>-
</root>
<body>
(cons₇)-value!-<>-!target-(append₁₅)
(cons₁₄)-value!-<>-rest-(append₁₅)
(cons₁₂)-value!-<>-tail-(cons₁₄)
(sole₁₃)-value!-<>-head-(cons₁₄)
(cons₁₀)-value!-<>-tail-(cons₁₂)
(sole₁₁)-value!-<>-head-(cons₁₂)
(nil₈)-value!-<>-tail-(cons₁₀)
(sole₉)-value!-<>-head-(cons₁₀)
(cons₅)-value!-<>-tail-(cons₇)
(sole₆)-value!-<>-head-(cons₇)
(cons₃)-value!-<>-tail-(cons₅)
(sole₄)-value!-<>-head-(cons₅)
(nil₁)-value!-<>-tail-(cons₃)
(sole₂)-value!-<>-head-(cons₃)
</body>
</net>

<net>
<root>
(cons₁₇)-value!-<>-
</root>
<body>
(cons₁₉)-value!-<>-tail-(cons₁₇)
(sole₆)-value!-<>-head-(cons₁₇)
(cons₂₁)-value!-<>-tail-(cons₁₉)
(sole₄)-value!-<>-head-(cons₁₉)
(cons₁₄)-value!-<>-tail-(cons₂₁)
(sole₂)-value!-<>-head-(cons₂₁)
(cons₁₂)-value!-<>-tail-(cons₁₄)
(sole₁₃)-value!-<>-head-(cons₁₄)
(cons₁₀)-value!-<>-tail-(cons₁₂)
(sole₁₁)-value!-<>-head-(cons₁₂)
(nil₈)-value!-<>-tail-(cons₁₀)
(sole₉)-value!-<>-head-(cons₁₀)
</body>
</net>
```

</details>

### More

For more examples, please see the [examples/](examples/) directory.

## Docs

- [Programming with Interaction Nets](docs/articles/programming-with-interaction-nets.md)
- [反应网编程](docs/articles/反应网编程.md)

## Community

- [Discord / concatenative #inet](https://discord.gg/EcUfwRkbdx)

## Install

Dependencies:

- `libx11`:
  - debian: `sudo apt install libx11-dev`
  - ubuntu: `sudo apt install libx11-dev`

Compile:

```
git clone https://github.com/cicada-lang/inet-forth
cd inet-forth
make -j
make test
```

The compiled binary `./bin/inet-forth` is the command-line program.

```sh
$ ./bin/inet-forth
inet-forth 0.1.0

commands:
  run -- run files
  self-test -- run self test
  version -- print version
  help -- print help message
```

For examples:

```sh
./bin/inet-forth run examples/nat.fth
```

## Development

```shell
make all      # compile src/ files to lib/ and bin/
make run      # compile and run the command-line program
make test     # compile and run test
make clean    # clean up compiled files
```

## Other Implementations

- [inet-cute](https://github.com/cicada-lang/inet-cute)
- [inet-js](https://github.com/cicada-lang/inet-js)

## References

**Papers**:

- [1990-interaction-nets](./docs/references/1990-interaction-nets.pdf)
- [1997-interaction-combinators](./docs/references/1997-interaction-combinators.pdf)

**Inspirations**:

- [forth](https://en.wikipedia.org/wiki/Forth_(programming_language))

**Books**:

- [scalable c](https://github.com/booksbyus/scalable-c)

## Contributions

To make a contribution, fork this project and create a pull request.

Please read the [STYLE-GUIDE.md](STYLE-GUIDE.md) before you change the code.

Remember to add yourself to [AUTHORS](AUTHORS).
Your line belongs to you, you can write a little
introduction to yourself but not too long.

## License

[GPLv3](LICENSE)
