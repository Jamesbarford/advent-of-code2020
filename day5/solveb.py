class Solver:
    def __init__(self):
        self.LOWER = 0
        self.HIGHER = 1
        self.COLUMN_COUNT = 8

    def find_seat_id(self):
        seat_dictionary = self.create_dictionary()
        missing_seats = self.validate_seats(seat_dictionary)
        return self.get_seat_id(missing_seats)

    def create_dictionary(self):
        seat_dictionary = {}
        for line in self.get_lines():
            row = line[0:7]
            column = line[7:10]

            if row in seat_dictionary:
                seat_dictionary[row]["count"] += 1
                seat_dictionary[row]["columns"].append(column)

            else:
                seat_dictionary[row] = {
                    "count": 1,
                    "columns": [column]
                }

        return filter(lambda entry: entry[1]["count"] < self.COLUMN_COUNT, seat_dictionary.items())

    def validate_seats(self, seat_dictionary):
        seat_validator = SeatValidator()
        row_letters = None
        column_letters = None

        for entry in seat_dictionary:
            missing_seats = seat_validator.validate_seats(entry[1]["columns"])
            if len(missing_seats) == 1:
                row_letters = entry[0]
                column_letters = missing_seats[0]
                break
        
        return row_letters + column_letters

    def get_seat_id(self, missing_seats):
        str_arr = missing_seats

        rows = self.convert_to_higher_and_lower(str_arr[0:7])
        row_number = self.loop(rows, 0, 127, 7)

        columns = self.convert_to_higher_and_lower(str_arr[7:10])
        column_number = self.loop(columns, 0, 7, 3)

        return (row_number * 8) + column_number

    def convert_to_higher_and_lower(self, arr):
        return list(map(lambda char: self.LOWER if char == "F" or char == "L" else self.HIGHER, arr))

    def loop(self, arr, MIN, MAX, count):
        new_mid = (MAX-MIN) / 2
        new_upper = int(MIN + new_mid)
        new_lower = int(MAX - new_mid)
        current = arr[-count]
        count -= 1

        if count == 0:
            if current == self.LOWER:
                return MIN
            else:
                return MAX

        if current == self.LOWER:
            return self.loop(arr, MIN, new_upper, count)
        else:
            return self.loop(arr, new_lower, MAX, count)

    def get_lines(self):
        input_file = open("input.txt", "r") 
        return input_file.readlines()

class SeatValidator:
    def __init__(self):
        self.COMPLETE_SEATS = ["LLL", "LLR", "LRL", "LRR", "RLL", "RLR", "RRL", "RRR"]

    def validate_seats(self, seats):
        diff = []
        if len(seats) == 1:
            return diff

        seat_length = len(self.COMPLETE_SEATS) - 1
        for i in range(seat_length):
            seat = self.COMPLETE_SEATS[i]
            next_seat = self.COMPLETE_SEATS[i + 1 % seat_length]
            if seat in seats:
                continue
            elif next_seat in seats:
                diff.append(seat)
        return diff

print(Solver().find_seat_id())
if __name__ == "__main__":
    pass
