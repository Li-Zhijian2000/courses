from cyaron import *

while True:
    input_io = IO(file_prefix="test", data_id=3) # test3.in, test3.out
    # t, n, m, bound = 100, randint(0, 1000), randint(0, 1000), int(1e10)
    t = 1
    ran = 3
    r2 = 10
    for _ in range(t):
        n, m = randint(1, ran), randint(1, ran)
        input_io.input_writeln(n, m)
        for _ in range(n):
            t1, t2 = randint(1, r2), randint(1, r2)
            input_io.input_writeln(t1, t2)
        for _ in range(m):
            t1, t2 = randint(1, r2), randint(1, r2)
            input_io.input_writeln(t1, t2)
    Compare.program("./a.out", input=input_io, std_program="./std") 

