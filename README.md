# inet

An implementation of [interaction nets](https://en.wikipedia.org/wiki/Interaction_nets).

- Untyped.
- ASCII art inspired syntax.
- Using a concatenative stack-based low-layer language to build nets.

## Syntax

```xml
( comment )
* (<name>) <inputs> -- <outputs>  ( define node )
! (<name>)-(<name>) <program>     ( define rule )
= <name> <program>                ( define program )
. <program>                       ( run program )

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

For more examples, please see the [examples/](examples/) directory.

### Natural Number

```
* (zero) -- value!
* (add1) prev -- value!
* (add) target! addend -- result

! (zero)-(add)
  (add)-addend result-(add)

! (add1)-(add)
  (add)-addend (add1)-prev add
  add1 result-(add)

( test )

= one zero add1
= two one one add
= three two one add
= four two two add

. two two add
  two two add
  add
  @wire/print-net
  @worker/interact
  @wire/print-net
```

<details>
<summary>output</summary>

```xml
<net>
<root>
(add₂₃)-result-<>-
</root>
<body>
(add₁₁)-result-<>-addend-(add₂₃)
(add₂₂)-result-<>-!target-(add₂₃)
(add₁₆)-result-<>-addend-(add₂₂)
(add₂₁)-result-<>-!target-(add₂₂)
(add1₁₈)-value!-<>-addend-(add₂₁)
(add1₂₀)-value!-<>-!target-(add₂₁)
(zero₁₉)-value!-<>-prev-(add1₂₀)
(zero₁₇)-value!-<>-prev-(add1₁₈)
(add1₁₃)-value!-<>-addend-(add₁₆)
(add1₁₅)-value!-<>-!target-(add₁₆)
(zero₁₄)-value!-<>-prev-(add1₁₅)
(zero₁₂)-value!-<>-prev-(add1₁₃)
(add₅)-result-<>-addend-(add₁₁)
(add₁₀)-result-<>-!target-(add₁₁)
(add1₇)-value!-<>-addend-(add₁₀)
(add1₉)-value!-<>-!target-(add₁₀)
(zero₈)-value!-<>-prev-(add1₉)
(zero₆)-value!-<>-prev-(add1₇)
(add1₂)-value!-<>-addend-(add₅)
(add1₄)-value!-<>-!target-(add₅)
(zero₃)-value!-<>-prev-(add1₄)
(zero₁)-value!-<>-prev-(add1₂)
</body>
</net>

<net>
<root>
(add1₂₉)-value!-<>-
</root>
<body>
(add1₃₃)-value!-<>-prev-(add1₂₉)
(add1₃₇)-value!-<>-prev-(add1₃₃)
(add1₃₉)-value!-<>-prev-(add1₃₇)
(add1₄₃)-value!-<>-prev-(add1₃₉)
(add1₄₅)-value!-<>-prev-(add1₄₃)
(add1₄₇)-value!-<>-prev-(add1₄₅)
(add1₂)-value!-<>-prev-(add1₄₇)
(zero₁)-value!-<>-prev-(add1₂)
</body>
</net>
```

</details>

### List

```
* (null) -- value!
* (cons) head tail -- value!
* (append) target! rest -- result

! (null)-(append)
  (append)-rest result-(append)

! (cons)-(append)
  (append)-rest (cons)-tail append
  (cons)-head cons result-(append)

( test )

* sole -- value!

. null sole cons sole cons sole cons
  null sole cons sole cons sole cons
  append
  @wire/print-net
  @worker/interact
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
(cons₇)-value!-<>-rest-(append₁₅)
(cons₁₄)-value!-<>-!target-(append₁₅)
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
(sole₁₃)-value!-<>-head-(cons₁₇)
(cons₂₁)-value!-<>-tail-(cons₁₉)
(sole₁₁)-value!-<>-head-(cons₁₉)
(cons₇)-value!-<>-tail-(cons₂₁)
(sole₉)-value!-<>-head-(cons₂₁)
(cons₅)-value!-<>-tail-(cons₇)
(sole₆)-value!-<>-head-(cons₇)
(cons₃)-value!-<>-tail-(cons₅)
(sole₄)-value!-<>-head-(cons₅)
(null₁)-value!-<>-tail-(cons₃)
(sole₂)-value!-<>-head-(cons₃)
</body>
</net>
```

</details>

## Install

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

## Community

- [Discord / concatenative #inet](https://discord.gg/EcUfwRkbdx)

## Development

```shell
make all      # compile src/ files to lib/ and bin/
make run      # compile and run the command-line program
make test     # compile and run test
make clean    # clean up compiled files
```

## References

**Inspirations**:

- [uxn](https://100r.co/site/uxn.html)
- [modal](https://git.sr.ht/~rabbits/modal)
- [fractran](https://git.sr.ht/~rabbits/fractran)

**Books**:

- [Scalable C](https://github.com/booksbyus/scalable-c)

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
