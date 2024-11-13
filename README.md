# inet

An implementation of [interaction nets](https://en.wikipedia.org/wiki/Interaction_nets).

- Untyped.
- ASCII art inspired syntax.
- Pure postfix expression.
- Using a stack-based low-layer language to build nets.

## Usage

On Linux:

```
git clone https://github.com/cicada-lang/inet
cd inet
make
make test
```

The compiled `bin/ient` is the command-line program.

```sh
inet repl        # start the read-eval-print-loop
inet run         # run a script
inet version     # print version
inet help        # print help
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

. two two add two two add
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

= six-soles
  null sole cons sole cons sole cons
  null sole cons sole cons sole cons
  append

. six-soles
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
