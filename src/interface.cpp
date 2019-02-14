#include "knn.h"
#include <R.h>
#include <R_ext/Rdynload.h>
void knn_interface(
                     const double *train_inputs_ptr,//n_train_observations, n_features
                     const double *train_label_ptr, //n_train_observations
                     const double *test_input_ptr, //n_train_observations, n_features
                     const int *n_test_observations_ptr, 
                     const int *n_train_observations_ptr, 
                     const int *n_features_ptr, 
                     const int *max_neighbours_ptr,
                     double **test_predictions_ptr //n_test_observations, max_neighbors 
){
  int status = knn(train_inputs_ptr, train_label_ptr, test_input_ptr,
                   *n_test_observations_ptr, *n_train_observations_ptr, *n_features_ptr, *max_neighbours_ptr,
                  test_predictions_ptr);
  
  if(status == -1 )
  {
    error("Input is not valid, Problem dimension or Max neighbors is less than 0!!");
  }
  else if(status != 0){
    error("non-zero exit status from knn");
  }
}

R_CMethodDef cMethods[] = {
  {"knn_interface" , (DL_FUNC) &knn_interface, 8},
  {NULL,NULL,0}
};

extern "C" {
  void R_init_nearestNeighborsDemo(DllInfo *info){
    R_registerRoutines(info, cMethods, NULL, NULL, NULL);
    R_useDynamicSymbols(info, FALSE);
  }
}
