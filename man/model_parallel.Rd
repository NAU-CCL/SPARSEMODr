\name{model_parallel}
\alias{model_parallel}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{

Parallelized implementation of the SPARSE-MOD COVID-19 Model

}

\description{

    The function uses \code{R}-level parallelization to speed up the generation of stochastic realizations of the SPARSEMODr COVID-19 model and to combine output data into a read-to-use data frame. This is the preferred method to run \code{\link{model_interface}}.

}

\usage{
  model_parallel(..., input_realz_seeds = 1:2, control)
}

%- maybe also 'usage' for other objects documented here.
\arguments{
    \item{...}{
        Universal model arguments passed to \code{\link{model_interface}}.
    }
    \item{input_realz_seeds}{
        An integer vector of user-specified random seeds to generate the stochastic realizations of the model. The number of realizations will be equal to the length of this vector.
    }
    \item{control}{
        Either a \code{\link{covid19_control}} or a \code{\link{seir_control}} named list data object.
    }
}

\details{
%%  ~~ If necessary, more details than the description above ~~
    Relies on \code{\link{future_lapply}} to run stochastic realizations of the SPARSEMODr model in parallel.
}
\value{
    A data frame that combines the two named lists of \code{\link{model_interface}}.
}
\author{
    Joseph Mihaljevic, \email{joseph.mihaljevic@nau.edu}; Toby Hocking, \email{toby.hocking@r-project.org}
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\seealso{
    \code{\link{future_lapply}}, \code{\link{model_interface}}, \code{\link{time_windows}}, \code{\link{covid19_control}}, \code{\link{seir_control}}
}
\examples{
## See vignettes for more detailed work-ups.


##########################################
## Using supplied example data:

# Read in the example data:
ex_dir <- system.file(
  "extdata", "sparsemodr_example.Rdata", package="SPARSEMODr", mustWork=TRUE)
load(ex_dir)
n_pop <- length(dat_list[["pop_N"]])

# Set up realizations:
realz_seeds <- 1:2
n_realz <- length(realz_seeds)

# START FUTURE PLAN FOR PARALLELIZATION
future::plan("multisession")

# Set up time windows (see time_windows for other ways to do this)
input_R0 <-             c(   2.0,   2.0,   0.8,   0.8,   1.5)
input_dist_param <-     c(   200,   200,    20,   150,   150)
input_m <-              c( 0.002, 0.002, 0.002,  0.02,  0.02)
input_imm_frac <-       c(   0.0,   0.0,   0.0,  0.02,  0.02)
input_window_length <-  c(     0,    36,    10,    35,   169)

# User creates the time_windows object here
tw <- time_windows(r0 = input_R0,
                   dist_param = input_dist_param,
                   m = input_m,
                   imm_frac = input_imm_frac,
                   window_length = input_window_length)

# Randomly generate initial conditions for
# EXPOSED class:
E_pops <- vector("numeric", length = n_pop)
n_initial_E <- 40
# (more exposed in larger populations)
these_E <- sample.int(n_pop,
                     size = n_initial_E,
                     replace = TRUE,
                     prob = dat_list$pop_N)
for(i in 1:n_initial_E){
  E_pops[these_E[i]] <- E_pops[these_E[i]] + 1
}

# Inputs for the models
N_pops <- as.integer(dat_list[["pop_N"]])
S_pops <- N_pops - E_pops
I_pops <- vector("integer", length = n_pop)
R_pops <- vector("integer", length = n_pop)
I_asym_pops <- vector("integer", length = n_pop)
I_presym_pops <- vector("integer", length = n_pop)
I_sym_pops <- vector("integer", length = n_pop)
I_home_pops <- vector("integer", length = n_pop)
I_hosp_pops <- vector("integer", length = n_pop)
I_icu1_pops <- vector("integer", length = n_pop)
I_icu2_pops <- vector("integer", length = n_pop)
D_pops <- vector("integer", length = n_pop)

# Set up a function to use the dat_list

get_result <- function(input_realz_seeds, control = NULL){

    with(dat_list, SPARSEMODr::model_parallel(
        input_census_area = census_area,
        input_dist_mat = dist_vec,
        input_realz_seeds = input_realz_seeds,
        input_tw = tw,
        control = control)
    )
}

# User creates control list of parameters
covid19_control <- covid19_control(input_N_pops = N_pops,
                                   input_E_pops = E_pops,
                                   input_I_asym_pops=I_asym_pops,
                                   input_I_presym_pops=I_presym_pops,
                                   input_I_sym_pops=I_sym_pops,
                                   input_I_home_pops=I_home_pops,
                                   input_I_hosp_pops=I_hosp_pops,
                                   input_I_icu1_pops=I_icu1_pops,
                                   input_I_icu2_pops=I_icu2_pops,
                                   input_R_pops=R_pops,
                                   input_D_pops=D_pops)

covid_model_output <-
    get_result(
        input_realz_seeds = realz_seeds,
        control = covid19_control
    )

# Shut down parallel workers
future::plan("sequential")
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
%\keyword{ ~kwd1 }% use one of  RShowDoc("KEYWORDS")
%\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
