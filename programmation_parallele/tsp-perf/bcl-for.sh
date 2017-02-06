export OMP_NUM_THREADS

for OMP_NUM_THREADS in $(seq 2 2 24); do  echo -n $OMP_NUM_THREADS " " >> TASK-3 ; ./task 15 1234 3 2>> TASK-3; done

for OMP_NUM_THREADS in $(seq 2 2 24); do  echo -n $OMP_NUM_THREADS " " >> TASK-4 ; ./task 15 1234 4 2>> TASK-4; done

for OMP_NUM_THREADS in $(seq 2 2 24); do  echo -n $OMP_NUM_THREADS " " >> COLLAPSE ; ./collapse 15 1234 3 2>> COLLAPSE; done
