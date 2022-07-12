read.dat <- function(f, matrix=grepl("dist", f)){
  data.vec <- scan(f, quiet=TRUE)
  if(isTRUE(matrix)){
    N <- sqrt(length(data.vec))
    matrix(data.vec, N, N)
  }else{
    data.vec
  }
}

read.dat.dir <- function(d){
  dat.vec <- Sys.glob(file.path(d, "*"))
  dat.list <- lapply(dat.vec, read.dat)
  names(dat.list) <- gsub(".*/|[.]dat$", "", dat.vec)
  dat.list
}
