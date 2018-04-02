reset
set ylabel 'time(sec)'
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'pref_time.png'
set format x "%0.6f"
set xtic 1000
set xtics rotate by 45 right

plot [:][:0.001]'pref_cpy.txt' using 1:2 with points title 'cpy',\
'pref_ref.txt' using 1:2 with points title 'ref',\