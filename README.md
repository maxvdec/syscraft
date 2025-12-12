# syscraft

`syscraft` is a set of command line tools that basically replace original tools from macOS. These tools are written in C with no standard library dependencies, making them suitable for low-level system tasks and environments where the standard library is not available.
This is basically a project for me to learn more about low-level programming in C and macOS internals.

## Tools

- `echo`
- `true` and `false`
- `cat`
- `sleep`
- `pwd`
- `yes`

These are just tools that I have implemented so far. More tools will be added in the future as I continue to learn and explore.

## Building

To build the project, simply run:

```bash
just
```

The compiled binaries will be located in the `bin` directory.
