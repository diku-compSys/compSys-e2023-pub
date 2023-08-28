set title 'Memory mountain'
set terminal png size 1000,1000 enhanced
set output 'mountain.png'
set logscale y
set pm3d
set yrange [268435456:32768]
set zlabel 'throughput (MiB/s)' rotate
set xlabel 'stride (x4 bytes)'
set ylabel 'size (bytes)'
splot 'locality.data' with lines
exit
