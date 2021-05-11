# Output Settings
set terminal png size 800,300
set output 'out.png'
# Labels, Title and Data
set key inside bottom right
set xlabel 'Number of Threads'
set ylabel 'Time(s)'
set title 'Sequential 2D,3D and Parallel 2D,3D Comparison'
plot "data.txt" using 1:2 title 'Sequential 2D Array' with linespoints,\
"data.txt" using 1:3 title "Sequential 3D Array" with linespoints,\
"data.txt" using 1:4 title "Parallel 2D Array" with linespoints,\
"data.txt" using 1:5 title "Parallel 3D Array" with linespoints
