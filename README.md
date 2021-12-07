# crumb

crumb is a small C library containing common data structures and utility functions.

crumb was born out of simply wanting to write C, so you probably shouldn't actually use it.

## Dependencies

- [xxHash](https://github.com/Cyan4973/xxHash)
- [Unity](https://github.com/ThrowTheSwitch/Unity/)

## Building

There are several `make` commands that can be used for building, testing, and generating docs.

```bash
# download and build third-party dependencies
make deps
```

```bash
# build .o files and a small demo executable
make build
```

```bash
# build static library object
make dist
```

```bash
# run unit tests
make test
```

```bash
# generate Doxygen docs
make docs
```

```bash
# start an nginx Docker container for serving docs
make serve-docs
```
