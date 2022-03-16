# Add a Custom Section to a WASM binary.

## Dependencies

[binaryen](https://github.com/WebAssembly/binaryen)

```bash
apt install build-essential binaryen
```

## Building

```bash
make
```

## Usage

```
Usage: add_custom_section <infile> <outfile> \"ic:public myname\" (\"data\" | -f <file>)\n"
Add a custom section section to the input_wasm_file with name \"ic:public myname\n"
containing either \"data\" or the contents of <file>\n.");
```

## Testing

```bash
make test
```
