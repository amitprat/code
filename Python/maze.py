import tkinter as tk
from collections import deque

# Maze definition: 0 = open, 1 = wall
maze = [
    [0, 1, 0, 0, 0, 0],
    [0, 1, 0, 1, 1, 0],
    [0, 0, 0, 1, 0, 0],
    [1, 1, 1, 1, 0, 1],
    [0, 0, 0, 0, 0, 0],
]

start = (0, 0)  # Starting cell coordinates (row, col)
end = (4, 5)    # Ending cell coordinates

def find_path_bfs(maze, start, end):
    rows, cols = len(maze), len(maze[0])
    queue = deque([start])
    visited = set()
    visited.add(start)
    parent = {start: None}

    directions = [(1,0), (-1,0), (0,1), (0,-1)]

    while queue:
        r, c = queue.popleft()
        if (r, c) == end:
            # Reconstruct path
            path = []
            while (r,c) is not None:
                path.append((r,c))
                r,c = parent[(r,c)] if (r,c) in parent else (None, None)
            path.reverse()
            return path

        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols:
                if maze[nr][nc] == 0 and (nr, nc) not in visited:
                    visited.add((nr, nc))
                    parent[(nr, nc)] = (r, c)
                    queue.append((nr, nc))
    return None  # no path found

# GUI part
CELL_SIZE = 40

def draw_maze(canvas, maze, path):
    rows, cols = len(maze), len(maze[0])
    canvas.config(width=cols * CELL_SIZE, height=rows * CELL_SIZE)
    canvas.delete("all")

    for r in range(rows):
        for c in range(cols):
            x1, y1 = c * CELL_SIZE, r * CELL_SIZE
            x2, y2 = x1 + CELL_SIZE, y1 + CELL_SIZE

            if maze[r][c] == 1:
                color = "black"  # Wall
            else:
                color = "white"  # Open path
            canvas.create_rectangle(x1, y1, x2, y2, fill=color, outline="gray")

    # Highlight the path
    if path:
        for (r, c) in path:
            x1, y1 = c * CELL_SIZE, r * CELL_SIZE
            x2, y2 = x1 + CELL_SIZE, y1 + CELL_SIZE
            canvas.create_rectangle(x1, y1, x2, y2, fill="yellow", outline="gray")

    # Mark start and end
    sr, sc = start
    er, ec = end
    canvas.create_oval(sc*CELL_SIZE+10, sr*CELL_SIZE+10, sc*CELL_SIZE+CELL_SIZE-10, sr*CELL_SIZE+CELL_SIZE-10, fill="green")
    canvas.create_oval(ec*CELL_SIZE+10, er*CELL_SIZE+10, ec*CELL_SIZE+CELL_SIZE-10, er*CELL_SIZE+CELL_SIZE-10, fill="red")

def main():
    path = find_path_bfs(maze, start, end)
    if path is None:
        print("No path found!")

    root = tk.Tk()
    root.title("Maze Solver")

    canvas = tk.Canvas(root)
    canvas.pack()

    draw_maze(canvas, maze, path)

    root.mainloop()

if __name__ == "__main__":
    main()