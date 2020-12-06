class Solver:
    def __init__(self):
        self.tree = "#"
        self.clear = "."
        self.trees_hit = 0
        self.current_position = 0
        self.line_counter = 1

    def get_tree_hits(self):
        lines =  self.get_lines()
        total_lines = len(lines)
        line_length = len(lines[0].rstrip("\n")) - 1

        for line in lines:
            if total_lines <= self.line_counter:
                break

            self.current_position += 3

            if line_length < self.current_position:
                self.current_position -= (line_length + 1)

            next_line = lines[self.line_counter].rstrip("\n")
            next_line_char = next_line[self.current_position]

            if next_line_char == self.tree:
                self.trees_hit += 1

            self.line_counter += 1

        return self.trees_hit

    def get_lines(self):
        input_file = open('input.txt', 'r') 
        return input_file.readlines()

Solver().get_tree_hits()

if __name__ == "__main__":
    pass
