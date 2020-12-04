import { day1array } from "./day1-array";

type Tuple<K, V> = [K, V];

class SolveDayOne {
	private readonly ANSWER: number = 2020;
	private solution: Tuple<number, number> | null = null;
	private dataSize: number;

	public constructor(private readonly arr: number[]) {
		this.dataSize = arr.length;
	}

	public solve(idx = 0): number {
		const current: number = this.arr[idx];
		for (let j = 0; j < this.dataSize; ++j) {
			if (j === idx) continue;
			if ((current + this.arr[j]) === this.ANSWER) {
				this.solution = [current, this.arr[j]];
			}
		}
		if (this.solution === null) {
			this.solve(++idx);
		}
		return this.solution === null ? 0 : this.solution[0] * this.solution[1];
	}
}

const solver = new SolveDayOne(day1array);
console.log(solver.solve());