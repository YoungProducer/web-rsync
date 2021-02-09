# Web-rsync

A simple rsync-ish implementation to sync files between node applications

---

## Requirements

Currently works only on Linux and Mac. The required libraries for linus are listed in `postinstall.sh` in scripts

## Installation

- #### Linux and Mac

  You can install nodejs and npm easily with apt install, just run the following commands.

      yarn add web-rsync

- #### Windows

  Unfortunately, currentlty there is no suppotrt for windows, **contributors are wecome**.

## Usage

To scan the contents of directory use `scanDir`.

```javascript
const { scanDir } = require("web-rsync");
const scan = scanDir("./node_modules");
console.log(scan);
```

And for finding actual difference you can use `getFoldersDiff`. It can make diff from a path and a scan made by `scanDir`. That is usually the way you use it:

```javascript
getFoldersDiff("./prev", nextScan);
```

From two paths:

```javascript
getFoldersDiff("./prev", "./next");
```

And from two scans:

```javascript
getFoldersDiff(prevScan, nextScan);
```

## Example

An example usage with express over http is in `test-files/server` and `test-files/client`

## Contribution

Contributors are welcome.
