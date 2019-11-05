while true; do
    python3 data.py
    g++ my.cpp 
    ./a.out < input.txt > my.txt
    g++ std.cpp 
    ./a.out < input.txt > std.txt
    if diff my.txt std.txt; then #比较两个输出文件
        printf "AC\n"  #结果相同显示AC

    else
        printf "WA\n" 
        exit 0
    fi
done
