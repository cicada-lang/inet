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
