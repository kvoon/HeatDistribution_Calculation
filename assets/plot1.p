# Output Settings
set terminal png size 800,300
set output 'out.png'
# Labels, Title and Data
set key inside bottom right
set xlabel 'Chunksize'
set ylabel 'Time(s)'
set title '3D Parallel Version Scheduling Comparison'
plot "data3D.txt" using 1:2 title 'Default' with linespoints,\
"data3D.txt" using 1:3 title "Static" with linespoints,\
"data3D.txt" using 1:4 title "Dynamic" with linespoints

