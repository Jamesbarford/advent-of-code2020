import re


def split_line(line):
    return re.split(" bags contain | bags, | bag, | bags.\n| bag.\n", re.sub("\d+\s", "", line))

class Solver:
    def __init__(self):
        self.SHINY_GOLD = "shiny gold"
        self.dictionary = {}
        self.valid_bags = set()

    def count_valid_bags(self):
        file = open("./input.txt", "r")

        for line in file.readlines():
            str_arr = split_line(line)
            self.create_dictionary(str_arr)

        for key in self.dictionary.keys():
            self.seek(key, key, self.dictionary[key])

        return len(self.valid_bags)

    def seek(self, seeker, key, bags):
        if not seeker in self.dictionary:
            return

        if bags.__contains__(self.SHINY_GOLD):
            self.valid_bags.add(seeker)
        else:
            for bag in bags:
                if self.valid_bags.__contains__(bag) or self.valid_bags.__contains__(key):
                    self.valid_bags.add(seeker)
                elif bag != seeker and bag in self.dictionary:
                    self.seek(seeker, bag, self.dictionary[bag])

    def create_dictionary(self, str_arr):
        key = str_arr[0]
        self.dictionary[key] = []

        for str in str_arr[1:]:
            if str == self.SHINY_GOLD:
                self.valid_bags.add(key)
            if str != "":
                self.dictionary[key].append(str)


print(Solver().count_valid_bags())

if __name__ == "__main__":
    pass
