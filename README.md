# System Call Anomaly Detection using Markov Chains

System-call anomaly detection using Markov chains, with the math engine written from scratch in C++, born out of my intense liking for Markov chains.

The idea: learn what *normal* program behaviour looks like as a Markov chain over Linux system calls, then flag traces that look unlikely under that model as possible attacks.

> **Status:** work in progress. See [Progress](#progress) for what is done.

## Dataset

This project uses the **ADFA-LD** host-based intrusion detection dataset (Creech & Hu, UNSW Canberra). Each file is one trace: a single line of space-separated integers, where each integer is a Linux system call ID.

I use the labelled repackaging from [verazuo/a-labelled-version-of-the-ADFA-LD-dataset](https://github.com/verazuo/a-labelled-version-of-the-ADFA-LD-dataset), which keeps the traces as plain space-separated numbers.

The dataset is **not included** in this repository. To reproduce:

1. Download `ADFA-LD.zip` from the repository above.
2. Unzip it into `data/` so the layout looks like this:

```
data/ADFA-LD/
├── Attack_Data_Master/        (attack traces, one subfolder per attack run)
├── Training_Data_Master/      (normal traces, used to train the model)
├── Validation_Data_Master/    (normal traces, used to choose the threshold)
└── ADFA-LD+Syscall+List.txt   (syscall ID -> name lookup)
```

Quick facts from the data: system call IDs range from 0 to 340, and no trace is empty.

## Build and run

Requires a C++17 compiler (for `std::filesystem`). From the project root:

```
g++ -std=c++17 -g -fsanitize=address src/*.cpp -o a.out
./a.out
```

Run from the project root, because the data paths in `main.cpp` are relative.

## Project structure

```
src/
├── main.cpp     runs the steps in order
├── loader.*     reads trace files and loads whole folders
└── model.*      counts transitions and builds the probability matrix
data/            dataset (not tracked by git)
```

## How it works (so far)

1. **Load** every trace file in a folder, including subfolders. Each trace keeps the name of its folder, which doubles as its label (e.g. `Adduser_1` is an attack).
2. **Count transitions.** For every pair of consecutive calls `a -> b` in the training traces, add 1 to `tpm[a][b]`. Traces are never joined together.
3. **Smooth and normalise.** Add a small constant to every cell so unseen transitions are unlikely, not impossible, then divide each row by its total so it sums to 1.

The model is a first-order Markov chain: the next call depends only on the current one. The transition matrix is 341 x 341.

## Progress

- [x] Recursive dataset loader with per-folder labels
- [x] Dataset sanity summary (trace counts, largest call ID, empty traces)
- [x] First-order transition counting and smoothed probabilities
- [x] Verified: every row of the matrix sums to 1
- [ ] Trace scoring (average log-probability per transition)
- [ ] Threshold selection on validation data
- [ ] Evaluation: detection rate and false alarm rate, per attack type
- [ ] CSV output and ROC plot
- [ ] Higher-order chains (hash map storage, backoff to lower orders)

## Planned evaluation

- **Training** data trains the model and nothing else.
- **Validation** data (normal) sets the threshold, for example at a chosen false alarm rate.
- **Attack** data is used only for measuring detection, never for tuning.

## License

See [LICENSE](LICENSE).
