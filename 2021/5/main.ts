// Copyright (c) 2021 Samplasion <samplasion@gmail.com>
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

import * as fs from 'fs';
import * as path from 'path';

type Point = [x: number, y: number];
type Vector = [start: Point, end: Point];

class Grid {
    data: number[];
    width: number;

    constructor(width: number, height: number) {
        this.width = width;
        this.data = Array(width * height).fill(0);
    }

    get(x: number, y: number): number {
        return this.data[y * this.width + x];
    }

    set(x: number, y: number, value: number): void {
        this.data[y * this.width + x] = value;
    }

    getRow(y: number): number[] {
        return this.data.slice(y * this.width, (y + 1) * this.width);
    }

    toString(vals = 10): string {
        let res = '[\n\t';
        for (let y = 0; y < Math.min(this.width, vals); y++) {
            res += this.getRow(y).slice(0, vals).join(', ');
            if (y < this.width - 1) {
                res += ',\n\t';
            }
        }
        res += '\n]';
        return res;
    }
}

const straight: Vector[] = [];
const diag: Vector[] = [];

const file = process.argv.includes("--test") ? "test.txt" : "input.txt";
const input = fs.readFileSync(path.resolve(__dirname, file), 'utf8');
for (const line of input.trim().split('\n')) {
    const [, x1, y1, x2, y2] = line.match(/(\d+),(\d+) -> (\d+),(\d+)/)!.map(Number);

    if (x1 !== x2 && y1 !== y2) {
        // Don't mess with diagonals
        diag.push([[x1, y1], [x2, y2]]);
    } else {
        // Normalize the vector
        const startX = Math.min(x1, x2);
        const startY = Math.min(y1, y2);
        const endX = Math.max(x1, x2);
        const endY = Math.max(y1, y2);

        straight.push([[startX, startY], [endX, endY]]);
    }
}

const size = [...straight, ...diag].reduce((max, [, [x2, y2]]) => Math.max(max, x2, y2), 0) + 1;
const grid = new Grid(size, size);

for (const [start, end] of straight.reverse()) {
    if (start[0] === end[0]) {
        // Vertical
        for (let y = start[1]; y <= end[1]; y++) {
            grid.set(start[0], y, grid.get(start[0], y) + 1);
        }
    } else if (start[1] === end[1]) {
        // Horizontal
        for (let x = start[0]; x <= end[0]; x++) {
            grid.set(x, start[1], grid.get(x, start[1]) + 1);
        }
    }
}

console.log("[Part 1] The number of points where two or more lines intersect, excluding diagonals, is:", grid.data.filter(x => x >= 2).length);

for (const [start, end] of diag) {
    // Diagonal (45 degrees)
    const dx = end[0] - start[0];
    const dy = end[1] - start[1];
    const length = Math.max(Math.abs(dx), Math.abs(dy));
    const xInc = dx / length;
    const yInc = dy / length;
    for (let i = 0; i <= length; i++) {
        const pointX = start[0] + i * xInc;
        const pointY = start[1] + i * yInc;
        grid.set(pointX, pointY, grid.get(pointX, pointY) + 1);
    }
}

console.log("[Part 2] The number of points where two or more lines intersect, including diagonals, is:", grid.data.filter(x => x >= 2).length);