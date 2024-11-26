# inet

An implementation of [interaction nets](https://en.wikipedia.org/wiki/Interaction_nets)
as a [forth-like](https://en.wikipedia.org/wiki/Forth_(programming_language))
[concatenative programming language](https://en.wikipedia.org/wiki/Concatenative_programming_language).

- ASCII art inspired syntax.
- Untyped, i.e. no static type checking.
- Using a concatenative stack-based low-layer language to build nets.
- Programming with interaction nets directly (no compilation via combinators).

## Syntax

```xml
-- line comment
(- inline comment -)
* (<name>) <inputs> -> <outputs>  -- define node
! (<name>)-(<name>) <program>     -- define rule
= <name> <program>                -- define program
. <program>                       -- run program
```

<details>
<summary>full grammar</summary>

```xml
<inputs> := <ports>
<outputs> := <ports>
<ports> := <port> | <port> <ports>

<port> := <auxiliary-port> | <principle-port>
  <auxiliary-port> := <name>
  <principle-port> := <name>!

<program> := <word> | <word> <program>

<word> := <call> | <use-free-port> | <reconnect-free-port>
  <call> := <name>
  <use-free-port> := (<name>)-<name>
  <reconnect-free-port> := <name>-(<name>)

<name> := <alphanumeric>
```

</details>

## Examples

### Natural Number

Define nodes:

```
* (zero) -> value!
* (add1) prev -> value!
* (add) target! addend -> result
```

The rule between `(zero)` and `(add)` as ASCII art:

```
     value          value         value
       |              |             |
     (add)     =>             =>    |
     /   \              \            \
(zero)   addend         addend       addend
```

Define the rule between `(zero)` and `(add)`:

```
! (zero)-(add)
  (add)-addend result-(add)
```

Explanation of the above rule definition:

- Disconnect and delete `(zero)-(add)`.
- Reconnect newly exposed wires:
  - `(add)-addend`
    - push the corresponding wire to the stack.
  - `result-(add)`
    - connect the corresponding wire with the wire on top of the stack.

The rule between `(add1)` and `(add)` as ASCII art:

```
     value             value            value
       |                 |                |
     (add)     =>                =>     (add1)
     /   \                 \              |
(add1)   addend            addend       (add)
   |                 |                  /   \
 prev              prev              prev   addend
```

Define the rule between `(add1)` and `(add)`:

```
! (add1)-(add)
  (add1)-prev (add)-addend add
  add1 result-(add)
```

Explanation of the above rule definition:

- Disconnect and delete `(add1)-(add)`.
- Reconnect newly exposed wires:
  - `(add1)-prev`
  - `(add)-addend`
     - push the corresponding wire to the stack.
  - `add`
  - `add1`
    - create new node by applying it like a Forth function:
      - wires from the stack and connect them to the node's input ports,
      - then return free wires connected to the node's output ports.
  - `result-(add)`
     - connect the corresponding wire with the wire on top of the stack.

Example interaction:

```
       |                  |                 |            |
     (add)              (add1)            (add1)       (add1)
     /   \                |                 |            |
(add1)   (add1)         (add)             (add1)       (add1)
  |        |    =>      /   \      =>       |       =>   |
(add1)   (add1)    (add1)   (add1)        (add)        (add1)
  |        |         |        |           /   \          |
(zero)   (zero)    (zero)   (add1)   (zero)   (add1)   (add1)
                              |                 |        |
                            (zero)            (add1)   (zero)
                                                |
                                              (zero)
```

The whole program with test:

```
* (zero) -> value!
* (add1) prev -> value!
* (add) target! addend -> result

! (zero)-(add)
  (add)-addend result-(add)

! (add1)-(add)
  (add1)-prev (add)-addend add
  add1 result-(add)

(- test -)

. zero add1 add1
  zero add1 add1
  add
```

<details>
<summary>output</summary>

```xml
<net>
<root>
(add₇)-result-<>-
</root>
<body>
(add1₃)-value!-<>-!target-(add₇)
(add1₆)-value!-<>-addend-(add₇)
(add1₅)-value!-<>-prev-(add1₆)
(zero₄)-value!-<>-prev-(add1₅)
(add1₂)-value!-<>-prev-(add1₃)
(zero₁)-value!-<>-prev-(add1₂)
</body>
</net>

<net>
<root>
(add1₉)-value!-<>-
</root>
<body>
(add1₁₁)-value!-<>-prev-(add1₉)
(add1₆)-value!-<>-prev-(add1₁₁)
(add1₅)-value!-<>-prev-(add1₆)
(zero₄)-value!-<>-prev-(add1₅)
</body>
</net>
```

</details>

### List

```
* (null) -> value!
* (cons) tail head -> value!
* (append) target! rest -> result

! (null)-(append)
  (append)-rest result-(append)

! (cons)-(append)
  (cons)-tail (append)-rest append
  (cons)-head cons result-(append)

(- test -)

* (sole) -> value!

. null sole cons sole cons sole cons
  null sole cons sole cons sole cons
  append

  @wire/print-net
  @interact
  @wire/print-net
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
(null₈)-value!-<>-tail-(cons₁₀)
(sole₉)-value!-<>-head-(cons₁₀)
(cons₅)-value!-<>-tail-(cons₇)
(sole₆)-value!-<>-head-(cons₇)
(cons₃)-value!-<>-tail-(cons₅)
(sole₄)-value!-<>-head-(cons₅)
(null₁)-value!-<>-tail-(cons₃)
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
(null₈)-value!-<>-tail-(cons₁₀)
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
git clone https://github.com/cicada-lang/inet
cd inet
make
make test
```

The compiled binary `./bin/inet` is the command-line program.

```sh
$ ./bin/inet
inet 0.1.0

commands:
  run -- run files, use --debug to see each step
  help -- print help message
  version -- print version
  self-test -- run self test
```

For examples:

```sh
./bin/inet run examples/nat.inet
./bin/inet run examples/nat.inet --debug
```

## Development

```shell
make all      # compile src/ files to lib/ and bin/
make run      # compile and run the command-line program
make test     # compile and run test
make clean    # clean up compiled files
```

## Other Implementations

- [iNet Cute](https://github.com/cicada-lang/inet-cute)
- [iNet JS](https://github.com/cicada-lang/inet-js)

## References

**Papers**:

- [1990-interaction-nets](./docs/references/1990-interaction-nets.pdf)
- [1997-interaction-combinators](./docs/references/1997-interaction-combinators.pdf)

**Inspirations**:

- [forth](https://en.wikipedia.org/wiki/Forth_(programming_language))
- [uxn](https://100r.co/site/uxn.html)
- [modal](https://git.sr.ht/~rabbits/modal)
- [fractran](https://git.sr.ht/~rabbits/fractran)

**Books**:

- [scalable c](https://github.com/booksbyus/scalable-c)

**Tools**:

- [makefile tutorial](https://makefiletutorial.com)
- [makefile manual](https://www.gnu.org/software/make/manual/make.html)

## Contributions

To make a contribution, fork this project and create a pull request.

Please read the [STYLE-GUIDE.md](STYLE-GUIDE.md) before you change the code.

Remember to add yourself to [AUTHORS](AUTHORS).
Your line belongs to you, you can write a little
introduction to yourself but not too long.

## License

[GPLv3](LICENSE)
