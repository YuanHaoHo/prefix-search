reset
set ylabel 'cycle'
set xlabel 'time(sec)'
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'searchtime_bench.png'
set format x "%0.9f"
set xtic 0.00001
set xtics rotate by 45 right

plot [:][:80]'calculate_pref.txt' using 1:2 with points title 'ref',\
'calculate_pref.txt' using 1:3 with points title 'cpy',\