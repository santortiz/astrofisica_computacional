reset

set terminal png
set output "simulacion_parabolico.png"

set title "parabolico"

set xlabel "t[s]"
set ylabel "E[J]"

plot "parabolico_energia_rutina20.dat" u 1:3 w l lc 'red' title '20', "parabolico_energia_rutina100.dat" u 1:3 w l lc 'blue' title '100', "parabolico_energia_rutina1000.dat" u 1:3 w l lc 'black' title '1000', "parabolico_energia_rutina1e6.dat" u 1:3 w l lc 'green' title '1e6'

reset