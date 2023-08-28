set terminal pngcairo size 800,400 enhanced font 'Verdana,10'
set output 'plot.png'
set logscale y
set ylabel "Runtime (ms)
set xlabel "n"
set key outside
set grid

plot 'ijk.runtimes' title 'ijk' with lines, \
     'kij.runtimes' title 'kij' with lines, \
     'jki.runtimes' title 'jki' with lines
exit
