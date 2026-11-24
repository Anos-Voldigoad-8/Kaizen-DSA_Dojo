# Rolling Hash (Polynomial, Fixed-Length Windows)

A standalone C implementation of a **polynomial rolling hash** that slides a fixed-size window across an array of ASCII codes and computes each window's hash in O(1) per step. This is the core idea behind Rabin-Karp string matching.

## How it works

Each character's ASCII code is treated as a digit in a polynomial:

```
Hash(s) = Σ code(s[i]) × base^(m−1−i)  (mod modulus)
```

where `m` is the window length. Instead of rehashing every window from scratch, the hash is updated when the window slides by one position:

1. **Subtract** the outgoing character's weighted digit: `code(out) × base^(m−1)`
2. **Multiply** the remaining hash by the base
3. **Add** the incoming character's code

All arithmetic is done modulo `modulus`. Adding `modulus` before subtracting keeps the intermediate value non-negative.

> **Note:** Equal hashes only mean two windows are *candidates* for equality. Collisions are possible, so a real matcher must compare the actual strings.

## Complexity

| Resource | Cost |
|----------|------|
| Time     | O(n) |
| Space    | O(1) rolling state, plus O(n) for the stored hash history |

## Configuration

All parameters are globals at the top of `main.c`. Edit them to experiment:

| Variable      | Default                  | Meaning                                       |
|---------------|--------------------------|-----------------------------------------------|
| `values`      | `{66,65,78,65,78,65}`    | Input as ASCII codes (`"BANANA"`)             |
| `length`      | `6`                      | Number of input values                        |
| `window`      | `3`                      | Window size `m`                               |
| `radix`       | `31`                     | Polynomial base                               |
| `modulus`     | `101`                    | Modulus for all arithmetic                    |
| `windowCount` | `4`                      | Number of windows = `length - window + 1`     |

When changing the input, keep `length`, `windowCount`, and the `hashes[]` array size consistent with each other. `windowCount` must equal `length - window + 1`, and `hashes[]` must hold at least `windowCount` entries.

## Build & run

```bash
gcc -o rolling_hash main.c
./rolling_hash
```

On Windows (MinGW):

```bash
gcc -o rolling_hash.exe main.c
rolling_hash.exe
```

## Example

Input `"BANANA"`, window = 3, base = 31, modulus = 101:

| Window index | Substring | Hash |
|:-----------:|:---------:|:----:|
| 0 | `BAN` | 71 |
| 1 | `ANA` | 5  |
| 2 | `NAN` | 89 |
| 3 | `ANA` | 5  |

Output:

```
71 5 89 5
```

Windows 1 and 3 are both `ANA`, so they produce the same hash, which is exactly what a rolling hash is for when finding repeated substrings or pattern matches.

## Code structure

- `run()` does all the work:
  1. Computes `power = radix^(window-1) mod modulus`, the weight of the outgoing digit.
  2. Hashes the first window directly.
  3. Slides the window, applying the subtract, multiply, add update, and records each hash in `hashes[]`.
  4. Copies the hashes into `output[]`.
- `main()` calls `run()` and prints the flat output sequence.

Output is a flat sequence of integers. In the wider visualization format this was designed for, boolean results use `1` (true) and `0` (false).

## Limitations

- Fixed-size static arrays (`output[512]`, `hashes[4]`) with no bounds checking.
- Small modulus (101) is chosen for readability and **collides easily**. Use a large prime (e.g. 1,000,000,007) for real workloads.
- Input is hard-coded. There is no CLI or file input.
- Output has a trailing space and no final newline.

## Possible extensions

- Rabin-Karp substring search with collision verification
- Double hashing (two moduli) to cut collision probability
- Reading the input string from `argv` or stdin
- Detecting duplicate windows with a hash table

## License

MIT (or whichever license you choose)
