
export OMP_NUM_THREADS

ITE=$(seq 10) # nombre de mesures
  
THREADS=$(seq 2 2 24) # nombre de threads

PARAM="-n -s 512 -i 100" # parametres commun à toutes les executions 

execute (){
EXE=" ./prog $* $PARAM"
OUTPUT="$(echo $EXE | tr -d ' ')"
for nb in $ITE; do for OMP_NUM_THREADS in $THREADS; do  echo -n "$OMP_NUM_THREADS " >> $OUTPUT ; $EXE 2>> $OUTPUT; done; done
}

execute1 (){
EXE=" ./prog $* $PARAM"
OUTPUT="$(echo $EXE | tr -d ' ')"
for nb in $ITE; do for OMP_NUM_THREADS in $THREADS; do  echo -n "$OMP_NUM_THREADS " >> $OUTPUT ;KERNEL=version_naive $EXE 2>> $OUTPUT; done; done
}


execute1 -v 8 

