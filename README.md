# Yet another n-puzzle solver

## Description
A solver for the classic sliding tile game by Sam Loyd.
This solver finds the optimal solution to a puzzle (least moves required to solve). As a result the solver may not find the solution in the quickest amount of time, but will guarantee optimality.

## Requirements
gcc (need GNU extensions for heap)

Heap is not required for IDA\* solver, so you can remove heap.c/h and A\* solver, in which case no dependencies are necessary.

## Installation
Run `make`

Board size is specified at compile time (may change this).

The macro **DIM** in board.h defines the size of aboard.

## Use
Run `./n-puzzle` to use a random board

### Specify a board as follows:
`./n-puzzle` 5 6 3 4 8 1 2 15 10 7 0 11 12 9 14 13
for the board

|||||
|-|-|-|-|
| 5 	| 6 	| 3 	| 4 	|
| 8 	| 1 	| 2 	| 15 	|
| 10 	| 7 	| 0 	| 11 	|
| 12 	| 9 	| 14 	| 13 	|

otherwise a random board will be used

_If the size of your board does not match **DIM^2** then a predetermined board will be used_

## Solver
- Currently using Manhattan distance heuristic
- Two solvers, A\* and IDA\* search

## Notes
- A\* uses a lot of memory which isn't managed that well at the moment
- A\*, by nature, uses a lot of memory anyways, so is unsuitable for many boards of size 4x4 and above
- IDA\* is much more reliable, albeit slower

## To be done
- Coding style consistency
- Implementing an improved heuristic
- Method documentation
- Make a non-optimal solver
- Command-line options
