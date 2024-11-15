# inet

An implementation of [interaction nets](https://en.wikipedia.org/wiki/Interaction_nets).

- Untyped.
- ASCII art inspired syntax.
- Using a stack-based low-layer language to build nets.

## Syntax

```inet
* (<node>) <inputs> -- <outputs>  ; define node
! (<node>)-(<node>) <program>     ; define rule
= <name> <program>                ; define program
. <program>                       ; run program
```

## Examples

For more examples, please see the [examples/](examples/) directory.

### Natural Number

```inet
* (zero) -- value!
* (add1) prev -- value!
* (add) target! addend -- result

! (zero)-(add)
  (add)-addend result-(add)

! (add1)-(add)
  (add)-addend (add1)-prev add
  add1 result-(add)

; TEST

= one zero add1
= two one one add
= three two one add
= four two two add

. two two add
  two two add
  add
```

### List

```inet
* (null) -- value!
* (cons) head tail -- value!
* (append) target! rest -- result

! (null)-(append)
  (append)-rest result-(append)

! (cons)-(append)
  (append)-rest (cons)-tail append
  (cons)-head cons result-(append)

; TEST

* sole -- value!

. null sole cons sole cons sole cons
  null sole cons sole cons sole cons
  append
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
