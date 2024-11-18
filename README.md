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

( TEST )

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

( TEST )

* sole -- value!

. null sole cons sole cons sole cons
  null sole cons sole cons sole cons
  append
  @wire/print-net
  @worker/interact
  @wire/print-net
```

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
