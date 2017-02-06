#!/usr/bin/env Rscript

## lines of data files must be  "#threads time"


args = commandArgs(trailingOnly=TRUE)


nbFichiers = length(args) - 1

if (nbFichiers < 1) {
  stop("At least two argument must be supplied filename [list of filenames] reference-time", call.=FALSE)
}


refTime = as.numeric(args[nbFichiers+1])

tables <- vector(mode = "list", length = nbFichiers)

xmax = 0
ymax = 0


for(i in 1:nbFichiers)
    {
        tmp = read.table(args[i])
        tmp[,2] = refTime / tmp[,2]  # compute speed up 
        tables[[i]] = aggregate(tmp[,2], tmp[1], mean)
        xmax = max(max(tables[[i]][,1]),xmax)
        ymax = max(max(tables[[i]][,2]),ymax)
    }

pdf("speedup.pdf")

plot(1,type='n',xlim=c(0,xmax),ylim=c(0,ymax),xlab='#threads', ylab='speedup')

for (i in 1:nbFichiers){
      lines(tables[[i]][,1],tables[[i]][,2], type='o', col=i, lwd=2)
}

legend("topleft", legend = args[1:nbFichiers], col=1:nbFichiers, pch=1)

title(main=paste("Speedup (reference time = " ,  args[nbFichiers+1],")"))
 dev.off()
