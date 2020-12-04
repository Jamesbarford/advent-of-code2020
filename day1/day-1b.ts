import { day1array } from "./day1-array";

class FindThree {
	private ANSWER: number = 2020;
	private sortedData: number[] = [];

	public constructor(data: number[]) {
		this.sortedData = data.sort((a, b) => a - b);
	}

	public solve(): number {
		const threeNumbers = this.getThreeNumbers();
		if (!threeNumbers) return 0;

		return threeNumbers.reduce((a, b) => a * b)
	}

	private getThreeNumbers(): number[] {
		let next;
		let remaining;
		const sorted = this.sortedData.sort((a, b) => a - b);

		for (let i = 0; i < sorted.length - 2; ++i) {
			next = i + 1;
			remaining = sorted.length - 1;
	
			while (next < remaining) {
				const total = sorted[i] + sorted[next] + sorted[remaining];
				if (total === this.ANSWER) return [sorted[i], sorted[next], sorted[remaining]];
				else if (total < this.ANSWER) next++;
				else remaining--;
			}
		}
		return [];
	}
}

const findThree = new FindThree(day1array);

console.log(findThree.solve());