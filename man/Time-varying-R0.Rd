\name{Time-varying R0}
\alias{Time-varying R0}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
    Time-varying R0 in SPARSEMODr models.
}
\description{
    The SPARSEMODr models allow for transmission dynamics to change over time by allowing users to specify the time-varying R0, also known as the effective reproduction number (R-eff) or the instantaneous Rt.
}

\details{
    In SPARSEMODr models, we allow the user to specify the time-varying R0 as an input (see \code{\link{time_windows}} for details). We then use these values to back-calculate the transmission rate (\emph{beta}) for the model on any given day of the simulation. In this way, we are assuming that R0 is effectively changing only due to changes in the \emph{beta} term, which encapsulates the effective contact rate among individuals and the probability of transmission given contact between a susceptible and infectious individual. We say 'effective' contact to define contacts that can actually lead to transmission. For instance, the wearing of masks or other face coverings may reduce the effective contact rate relevant to respiratory pathogens. As of now, in our models, we do not allow other parameters that define a pathogen's R0 to vary over time (e.g., recovery rates).

    For simple models, the calcuation of \emph{beta} from a time-varying R0 value is straightforward algebra. For more complex models with many state variables, this becomes more complicated. Therefore, to back-calculate the \emph{beta} parameter from the time-varying R0 value, we derive the equation for time-varying R0 for each SPARSEMODr model. Then, to calculate \emph{beta} in our C++ code, we implement a root-finding algorithm with the Brent-Dekker method, using the Gnu Scientific Library (\code{gsl_root_fsolver}). Thus, the user inputs the time-varying R0 value, and we calculate the value of \emph{beta} on the back-end.

}

\seealso{
    \code{\link{model_interface}}, \code{\link{model_parallel}}, \code{\link{time_windows}}
}
