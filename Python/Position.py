class Position:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def get_surrounding_positions(self):
        return [Position(self.x + 0, self.y - 1), # North
                Position(self.x + 1, self.y + 0), # East
                Position(self.x + 0, self.y + 1), # South
                Position(self.x - 1, self.y + 0)] # West

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __ne__(self, other):
        return not self.__eq__(other)

    def __lt__(self, other):
        return self.__hash__() < other.__hash__()

    def __repr__(self):
        return "{}({}, {})".format(self.__class__.__name__,
                                   self.x,
                                   self.y)

    def __hash__(self):
        #return ((self.x+self.y) * (self.x+self.y+1) >> 1) + self.y # cantors pairing
        return self.x * self.x + self.x + self.y if self.x >= self.y else self.x + self.y * self.y # szudziks function