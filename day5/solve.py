class Solver:
    def __init__(self):
        self.LOWER = 0
        self.HIGHER = 1

    def find_max_seat_id(self):
        seat_ids = self.get_seat_ids()
        return max(seat_ids)

    def get_seat_ids(self):
        lines = self.get_lines()
        seat_ids = []

        for line in lines:
            str_arr = list(line)

            rows = self.convert_to_higher_and_lower(str_arr[0:7])
            row_number = self.loop(rows, 0, 127, 7)

            columns = self.convert_to_higher_and_lower(str_arr[7:10])
            column_number = self.loop(columns, 0, 7, 3)

            seat_ids.append((row_number * 8) + column_number)

        return seat_ids

    def convert_to_higher_and_lower(self, arr):
        new_arr = []
        for char in arr:
            if char == "F" or char == "L":
                new_arr.append(self.LOWER)
            else:
                new_arr.append(self.HIGHER)

        return new_arr

    def loop(self, arr, MIN, MAX, count):
        new_mid = (MAX-MIN) / 2
        new_upper = int(MIN + new_mid)
        new_lower = int(MAX - new_mid)
        current = arr[-count]
        count -= 1

        if count == 0:
            if current == self.LOWER:
                return MIN
            elif current == self.HIGHER:
                return MAX

        if current == self.LOWER:
            return self.loop(arr, MIN, new_upper, count)
        elif current == self.HIGHER:
            return self.loop(arr, new_lower, MAX, count)

    def get_lines(self):
        input_file = open('input.txt', 'r') 
        return input_file.readlines()

if __name__ == "__main__":
    pass
