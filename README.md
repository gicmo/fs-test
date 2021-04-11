# Check some file system access

Background is bolt test suit failure [#171](https://gitlab.freedesktop.org/bolt/bolt/-/issues/171)
on recent kernel (5.10) inside a container.

## Build and run

```sh
podman build -t fs-test .
podman run -e "DIR=/tmp" fs-test
```

Should read:

```
Temp dir at //empty-test.bplGdJ
count: 1
```

There is a bug if `count: 0` is printed.
