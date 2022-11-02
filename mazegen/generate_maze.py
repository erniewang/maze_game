from mazelib import Maze
from mazelib.generate.HuntAndKill import HuntAndKill

m = Maze()
m.generator = HuntAndKill(15, 15)

for i in range(20):
    m.generate()
    with open(f'../Resources/maze{i:02}.txt', 'w') as f:
        f.write(str(m))
