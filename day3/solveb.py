class Solver:
    def __init__(self):
        self.tree = "#"
        self.output = []
        self.trees_hit = 0
        self.current_position = 0
        self.lines_traversed = 0
        self.inputs = [
            [1, 1],
            [3, 1],
            [5, 1],
            [7, 1],
            [1, 2]
        ]

    def reset(self):
        self.trees_hit = 0
        self.current_position = 0
        self.lines_traversed = 0
        return

    def get_total_tree_hits(self):
        for i in self.inputs:
            tree_hits = self.get_tree_hits(i[0], i[1])
            self.output.append(tree_hits)
            self.reset()
        return self.calculate_total_tree_hits()

    def calculate_total_tree_hits(self):
        accumulator = 1
        for tree_hit in self.output:
            accumulator *= tree_hit
        return accumulator

    def get_tree_hits(self, across, down):
        lines = self.get_lines()
        total_lines = len(lines)
        line_length = len(lines[0].rstrip("\n")) - 1
        current_line_counter = 0

        for line in lines:
            if current_line_counter % down == 0:
                self.lines_traversed += down
                if total_lines <= self.lines_traversed:
                    break

                self.current_position += across

                if line_length < self.current_position:
                    self.current_position -= (line_length + 1)

                next_line = lines[self.lines_traversed].rstrip("\n")
                next_line_char = next_line[self.current_position]

                if next_line_char == self.tree:
                    self.trees_hit += 1

            current_line_counter += 1

        return self.trees_hit

    def get_lines(self):
        input_file = open('input.txt', 'r') 
        return input_file.readlines()

print(Solver().get_total_tree_hits())

if __name__ == "__main__":
    pass
